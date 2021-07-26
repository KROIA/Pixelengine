#include "InteractiveGameObject.h"

InteractiveGameObject::InteractiveGameObject()
{
/*    setting.chunkSize    = Vector2u(128,128); // Pixels
    setting.chunkMapSize = setting.chunkSize * 4u;
    setting.position     = -Vector2i(setting.chunkSize);
*/
    constructor(__defaultSettings);
}
InteractiveGameObject::InteractiveGameObject(const Settings &settings)
{
    constructor(settings);
}
void InteractiveGameObject::constructor(const Settings &settings)
{
    GAME_OBJECT_FUNCTION("new InteractiveGameObject()",profiler::colors::Purple50);
    m_gameObject                    = nullptr;

    //m_interactiveObjectsChunkMap    = new ChunkMap(settings.chunkMap);
    //m_gameObjectChunkMap            = new ChunkMap(settings.chunkMap);

    m_colliderObjects.objectTreePainter = new VertexPathPainter();
    m_colliderObjects.objectTreePainter->setVisibility(false);
    m_colliderObjects.objectTree        = new ObjectTree(settings.objectTree);
    m_colliderObjects.objectTree->setAsRoot(true);
    m_colliderObjects.interactsWithObjectsList.push_back(new GameObjectGroup());
    m_colliderObjects.interactorAmount              = 0;
    m_colliderObjects.drawingIsDisabled             = true;
    m_colliderObjects.interactsWithOthers           = false;

    m_detectionObjects.objectTreePainter = new VertexPathPainter();
    m_detectionObjects.objectTreePainter->setVisibility(false);
    m_detectionObjects.objectTree        = new ObjectTree(settings.objectTree);
    m_detectionObjects.objectTree->setAsRoot(true);
    m_detectionObjects.interactsWithObjectsList.push_back(new GameObjectGroup());
    m_detectionObjects.interactorAmount              = 0;
    m_detectionObjects.drawingIsDisabled             = true;
    m_detectionObjects.interactsWithOthers           = false;

    /*m_objectTreePainter             = new VertexPathPainter();
    m_objectTreePainter->setVisibility(false);
    m_objectTree                    = new ObjectTree(settings.objectTree);
    m_objectTree->setAsRoot(true);

    m_interactsWithObjectsList.push_back(new GameObjectGroup());*/
}
InteractiveGameObject::InteractiveGameObject(const InteractiveGameObject &other)
{
    this->setGameObject(other.m_gameObject);
    this->m_colliderObjects    = other.m_colliderObjects;
    this->m_detectionObjects    = other.m_detectionObjects;
   // this->m_interactiveObjectsChunkMap  = new ChunkMap(*other.m_interactiveObjectsChunkMap);
   // this->m_gameObjectChunkMap          = new ChunkMap(*other.m_gameObjectChunkMap);
   // this->m_drawingIsDisabled           = other.m_drawingIsDisabled;
    //this->m_interactsWithOthers         = other.m_interactsWithOthers;
}
InteractiveGameObject::~InteractiveGameObject()
{
    SIGNAL_UNSUBSCRIBE(GameObject,m_gameObject)

    m_gameObject->setThisInteractiveGameObject(nullptr);


    for(GameObjectGroup* &group : m_colliderObjects.interactsWithObjectsList)
        SIGNAL_UNSUBSCRIBE(GameObjectGroup,group)

    delete m_colliderObjects.interactsWithObjectsList[0];
    delete m_colliderObjects.objectTree;
    delete m_colliderObjects.objectTreePainter;

    for(GameObjectGroup* &group : m_detectionObjects.interactsWithObjectsList)
        SIGNAL_UNSUBSCRIBE(GameObjectGroup,group)

    delete m_detectionObjects.interactsWithObjectsList[0];
    delete m_detectionObjects.objectTree;
    delete m_detectionObjects.objectTreePainter;
}
const InteractiveGameObject &InteractiveGameObject::operator=(const InteractiveGameObject &other)
{
   /* setGameObject(other.m_gameObject);
    //*m_interactiveObjectsChunkMap   = *other.m_interactiveObjectsChunkMap;
    //*m_gameObjectChunkMap           = *other.m_gameObjectChunkMap;

    m_interactorAmount              = other.m_interactorAmount;
    m_drawingIsDisabled             = other.m_drawingIsDisabled;
    m_interactsWithOthers           = other.m_interactsWithOthers;
    *m_objectTree                   = *other.m_objectTree;

    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        SIGNAL_UNSUBSCRIBE(GameObjectGroup,m_interactsWithObjectsList[i])
        //m_interactsWithObjectsList[i]->unsubscribe_GroupSignal(this);
    }
    m_interactsWithObjectsList = other.m_interactsWithObjectsList;
    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        //m_interactsWithObjectsList[i]->subscribe_GroupSignal(this);
        SIGNAL_SUBSCRIBE(GameObjectGroup,m_interactsWithObjectsList[i])
    }
    return *this;*/
}
InteractiveGameObject::Settings InteractiveGameObject::getSettings() const
{
    Settings settings;
   // settings.chunkMap = m_interactiveObjectsChunkMap->getSettings();

    return settings;
}
void InteractiveGameObject::engineCalled_preTick()
{
    m_gameObject->engineCalled_preTick();
}
void InteractiveGameObject::engineCalled_postTick()
{
    m_gameObject->engineCalled_postTick();
}
void InteractiveGameObject::engineCalled_preDraw()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple50);
    m_gameObject->engineCalled_preDraw();
    if(m_colliderObjects.objectTreePainter->isVisible())
    {
        GAME_OBJECT_BLOCK("objectTree",profiler::colors::Purple50);
        vector<VertexPath*> tree;
        m_colliderObjects.objectTree->getDrawable(tree);
        m_colliderObjects.objectTreePainter->clear();
        m_colliderObjects.objectTreePainter->addPath(tree);
        GAME_OBJECT_END_BLOCK;
    }
    if(m_detectionObjects.objectTreePainter->isVisible())
    {
        GAME_OBJECT_BLOCK("objectTree",profiler::colors::Purple50);
        vector<VertexPath*> tree;
        m_detectionObjects.objectTree->getDrawable(tree);
        m_detectionObjects.objectTreePainter->clear();
        m_detectionObjects.objectTreePainter->addPath(tree);
        GAME_OBJECT_END_BLOCK;
    }
}
void InteractiveGameObject::setGameObject(GameObject *obj)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple50);
    if(obj == nullptr || obj == m_gameObject)
        return;

    if(m_gameObject != nullptr)
    {
        //m_gameObject->unsubscribe_ObjSignal(this);
        SIGNAL_UNSUBSCRIBE(GameObject,m_gameObject)
        m_gameObject->setThisInteractiveGameObject(nullptr);
        m_gameObject->removePainter(m_colliderObjects.objectTreePainter);
        m_gameObject->removePainter(m_detectionObjects.objectTreePainter);
       // m_gameObjectChunkMap->remove(m_gameObject);
    }
    m_gameObject = obj;
    //m_gameObject->subscribe(this);
    m_gameObject->setThisInteractiveGameObject(this);
    m_gameObject->addPainter(m_colliderObjects.objectTreePainter);
    m_gameObject->addPainter(m_detectionObjects.objectTreePainter);
  //  m_gameObjectChunkMap->add(m_gameObject);
    //m_interactiveObjectsChunkMap->add(m_gameObject);
}
GameObject *InteractiveGameObject::getGameObject() const
{
    return m_gameObject;
}

void InteractiveGameObject::addInteractionWith(GameObject *obj,Interaction type)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple100);
    if(obj == nullptr)
        return;
    switch(type)
    {
        case Interaction::collision:
        {
#ifdef CHECK_FOR_DOUBLE_OBJ
            for(size_t i=0; i<m_colliderObjects.interactsWithObjectsList.size(); i++)
            {
                if(m_colliderObjects.interactsWithObjectsList[i]->indexOf(obj) != -1)
                    return;
            }
#endif

            m_colliderObjects.interactsWithObjectsList[0]->add(obj);
            m_colliderObjects.objectTree->insert(obj);
            m_colliderObjects.interactsWithOthers = true;
            m_colliderObjects.interactorAmount++;
            SIGNAL_SUBSCRIBE(GameObject,obj)
            //obj->subscribe_ObjSignal(this);


            break;
        }
        case Interaction::detection:
        {
#ifdef CHECK_FOR_DOUBLE_OBJ
            for(size_t i=0; i<m_detectionObjects.interactsWithObjectsList.size(); i++)
            {
                if(m_detectionObjects.interactsWithObjectsList[i]->indexOf(obj) != -1)
                    return;
            }
#endif

            m_detectionObjects.interactsWithObjectsList[0]->add(obj);
            m_detectionObjects.objectTree->insert(obj);
            m_detectionObjects.interactsWithOthers = true;
            m_detectionObjects.interactorAmount++;
            SIGNAL_SUBSCRIBE(GameObject,obj)
            break;
        }
    }

  //  m_interactiveObjectsChunkMap->add(obj);

}
void InteractiveGameObject::addInteractionWith(GameObjectGroup *group,Interaction type)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple100);
    if(group == nullptr)
        return;

    switch(type)
    {
        case Interaction::collision:
        {
#ifdef CHECK_FOR_DOUBLE_OBJ
            for(size_t i=0; i<m_colliderObjects.interactsWithObjectsList.size(); i++)
            {
                if(m_colliderObjects.interactsWithObjectsList[i] == group)
                    return;
            }
#endif

            m_colliderObjects.interactsWithObjectsList.push_back(group);
            SIGNAL_SUBSCRIBE(GameObjectGroup,group)
            for(size_t i=0; i<group->size(); i++)
            {
                m_colliderObjects.objectTree->insert((*group)[i]);
                SIGNAL_UNSUBSCRIBE(GameObject,(*group)[i])
            }
            m_colliderObjects.interactsWithOthers = true;
            m_colliderObjects.interactorAmount+=group->size();
            break;
        }
        case Interaction::detection:
        {
#ifdef CHECK_FOR_DOUBLE_OBJ
            for(size_t i=0; i<m_detectionObjects.interactsWithObjectsList.size(); i++)
            {
                if(m_detectionObjects.interactsWithObjectsList[i] == group)
                    return;
            }
#endif

            m_detectionObjects.interactsWithObjectsList.push_back(group);
            SIGNAL_SUBSCRIBE(GameObjectGroup,group)
            for(size_t i=0; i<group->size(); i++)
            {
                m_detectionObjects.objectTree->insert((*group)[i]);
                SIGNAL_UNSUBSCRIBE(GameObject,(*group)[i])
            }
            m_detectionObjects.interactsWithOthers = true;
            m_detectionObjects.interactorAmount+=group->size();
            break;
        }
    }
}
void InteractiveGameObject::addInteractionWith(vector<GameObjectGroup*> *groupList,Interaction type)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple100);
    for(size_t i=0; i<groupList->size(); i++)
    {
        addInteractionWith((*groupList)[i],type);
    }
}

void InteractiveGameObject::removeInteractionWith(GameObject *obj,Interaction type)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple200);
    if(obj == nullptr)
        return;


    switch(type)
    {
        case Interaction::collision:
        {
            bool removed = false;
            removed |= m_colliderObjects.interactsWithObjectsList[0]->remove(obj);
            for(size_t i=1; i<m_colliderObjects.interactsWithObjectsList.size(); i++)
            {
                removed |= m_colliderObjects.interactsWithObjectsList[i]->remove(obj);
            }
            if(!removed)
                return;
            SIGNAL_UNSUBSCRIBE(GameObject,obj)
            m_colliderObjects.objectTree->removeRecursive(obj);
            if(m_colliderObjects.interactorAmount == 0)
                qDebug() << "ERROR: InteractiveGameObject: m_interactorAmount will count wrong";
            else
                m_colliderObjects.interactorAmount--;

            if(m_colliderObjects.interactsWithObjectsList.size() == 1 && m_colliderObjects.interactsWithObjectsList[0]->size() == 0)
                m_colliderObjects.interactsWithOthers = false;
            break;
        }
        case Interaction::detection:
        {
            bool removed = false;
            removed |= m_detectionObjects.interactsWithObjectsList[0]->remove(obj);
            for(size_t i=1; i<m_detectionObjects.interactsWithObjectsList.size(); i++)
            {
                removed |= m_detectionObjects.interactsWithObjectsList[i]->remove(obj);
            }
            if(!removed)
                return;
            SIGNAL_UNSUBSCRIBE(GameObject,obj)
            m_detectionObjects.objectTree->removeRecursive(obj);
            if(m_detectionObjects.interactorAmount == 0)
                qDebug() << "ERROR: InteractiveGameObject: m_interactorAmount will count wrong";
            else
                m_detectionObjects.interactorAmount--;
            if(m_detectionObjects.interactsWithObjectsList.size() == 1 && m_detectionObjects.interactsWithObjectsList[0]->size() == 0)
                m_detectionObjects.interactsWithOthers = false;
            break;
        }
    }
}
void InteractiveGameObject::removeInteractionWith(GameObjectGroup *group,Interaction type)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple200);
    switch(type)
    {
        case Interaction::collision:
        {
            for(size_t i=0; i<m_colliderObjects.interactsWithObjectsList.size(); i++)
            {
                if(m_colliderObjects.interactsWithObjectsList[i] == group)
                {
                    SIGNAL_UNSUBSCRIBE(GameObjectGroup,m_colliderObjects.interactsWithObjectsList[i])
                    m_colliderObjects.interactsWithObjectsList.erase(m_colliderObjects.interactsWithObjectsList.begin()+i);

                    for(size_t i=0; i<group->size(); i++)
                    {
                        m_colliderObjects.objectTree->removeRecursive((*group)[i]);
                        SIGNAL_UNSUBSCRIBE(GameObject,(*group)[i])
                    }
                    if(m_colliderObjects.interactorAmount < group->size())
                        qDebug() << "ERROR: InteractiveGameObject: m_interactorAmount will count wrong";
                    else
                        m_colliderObjects.interactorAmount -= group->size();
                }
            }
            if(m_colliderObjects.interactsWithObjectsList.size() == 1 && m_colliderObjects.interactsWithObjectsList[0]->size() == 0)
                m_colliderObjects.interactsWithOthers = false;
            break;
        }
        case Interaction::detection:
        {
            for(size_t i=0; i<m_detectionObjects.interactsWithObjectsList.size(); i++)
            {
                if(m_detectionObjects.interactsWithObjectsList[i] == group)
                {
                    SIGNAL_UNSUBSCRIBE(GameObjectGroup,m_detectionObjects.interactsWithObjectsList[i])
                    m_detectionObjects.interactsWithObjectsList.erase(m_detectionObjects.interactsWithObjectsList.begin()+i);

                    for(size_t i=0; i<group->size(); i++)
                    {
                        m_detectionObjects.objectTree->removeRecursive((*group)[i]);
                        SIGNAL_UNSUBSCRIBE(GameObject,(*group)[i])
                    }
                    if(m_colliderObjects.interactorAmount < group->size())
                        qDebug() << "ERROR: InteractiveGameObject: m_interactorAmount will count wrong";
                    else
                        m_colliderObjects.interactorAmount -= group->size();
                }
            }
            if(m_detectionObjects.interactsWithObjectsList.size() == 1 && m_detectionObjects.interactsWithObjectsList[0]->size() == 0)
                m_detectionObjects.interactsWithOthers = false;
            break;
        }
    }
}
void InteractiveGameObject::removeInteractionWith(vector<GameObjectGroup*> *groupList,Interaction type)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple200);
    for(size_t i=0; i<groupList->size(); i++)
    {
        removeInteractionWith((*groupList)[i],type);
    }
}

void InteractiveGameObject::setInteractionWith(GameObject *obj, bool enable,Interaction type)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    if(enable)
        addInteractionWith(obj,type);
    else
        removeInteractionWith(obj,type);
}
void InteractiveGameObject::setInteractionWith(GameObjectGroup *group, bool enable,Interaction type)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    if(enable)
        addInteractionWith(group,type);
    else
        removeInteractionWith(group,type);
}
void InteractiveGameObject::setInteractionWith(vector<GameObjectGroup*> *groupList, bool enable,Interaction type)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    if(enable)
        addInteractionWith(groupList,type);
    else
        removeInteractionWith(groupList,type);
}

bool InteractiveGameObject::doesInteractWithOther(Interaction type) const
{
    switch(type)
    {
        case Interaction::collision:
        {
            return m_colliderObjects.interactsWithOthers;
        }
        case Interaction::detection:
        {
            return m_detectionObjects.interactsWithOthers;
        }
    }
}
const vector<GameObjectGroup*> &InteractiveGameObject::getInteractiveObjectsList(Interaction type) const
{
    switch(type)
    {
        case Interaction::collision:
        {
            return m_colliderObjects.interactsWithObjectsList;
        }
        case Interaction::detection:
        {
            return m_detectionObjects.interactsWithObjectsList;
        }
    }
}
const vector<GameObject*> InteractiveGameObject::getInteractiveObjects(Interaction type)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple400);
    vector<GameObject*> possibleInteractionList;
    switch(type)
    {
        case Interaction::collision:
        {
            possibleInteractionList.reserve(m_colliderObjects.interactorAmount);
            m_colliderObjects.objectTree->query(m_gameObject->getCollisionSeachRect(),possibleInteractionList);
            break;
        }
        case Interaction::detection:
        {
            possibleInteractionList.reserve(m_colliderObjects.interactorAmount);
            m_detectionObjects.objectTree->query(m_gameObject->getCollisionSeachRect(),possibleInteractionList);
            break;
        }
    }
    return possibleInteractionList;
}
/*void InteractiveGameObject::drawObjectTree(PixelDisplay &display)
{
    if(m_drawingIsDisabled)
       return;
    m_objectTree->draw(display);
}*/
/*void InteractiveGameObject::subscribeToDisplay(PixelDisplay &display)
{
    display.subscribePainter(m_objectTreePainter);
    m_gameObject->subscribeToDisplay(display);
}
void InteractiveGameObject::unsubscribeToDisplay(PixelDisplay &display)
{
    display.unsubscribePainter(m_objectTreePainter);
    m_gameObject->unsubscribeToDisplay(display);
}*/
void InteractiveGameObject::setVisibility_objectTree(bool isVisible,Interaction type)
{
    switch(type)
    {
        case Interaction::collision:
        {
            m_colliderObjects.objectTreePainter->setVisibility(isVisible);
            break;
        }
        case Interaction::detection:
        {
            m_detectionObjects.objectTreePainter->setVisibility(isVisible);
            break;
        }
    }
}
bool InteractiveGameObject::isVisible_objectTree(Interaction type) const
{
    switch(type)
    {
        case Interaction::collision:
        {
            return m_colliderObjects.objectTreePainter->isVisible();
        }
        case Interaction::detection:
        {
            return m_detectionObjects.objectTreePainter->isVisible();
        }
    }
}
/*
void InteractiveGameObject::draw_chunks(PixelDisplay &display)
{
    if(m_drawingIsDisabled)
       return;
    //m_interactiveObjectsChunkMap->draw_chunks(display);
    m_gameObjectChunkMap->draw_chunks(display);
}
void InteractiveGameObject::setVisibility_chunk(const ChunkID &id,bool isVisible)
{
    m_gameObjectChunkMap->setVisibility_chunk(id,isVisible);
    if(isVisible)
        m_drawingIsDisabled = false;
}
void InteractiveGameObject::setVisibility_chunks(bool isVisible)
{
    m_gameObjectChunkMap->setVisibility_chunks(isVisible);
    if(isVisible)
        m_drawingIsDisabled = false;
}
bool InteractiveGameObject::isVisible_chunk(const ChunkID &id) const
{
    return m_gameObjectChunkMap->isVisible_chunk(id);
}
bool InteractiveGameObject::isVisible_chunks() const
{
    return m_gameObjectChunkMap->isVisible_chunks();
}
*/
// GameObject singals:
void InteractiveGameObject::moved(GameObject* sender,const Vector2f &move)
{
    //qDebug() << "sender: "<<sender << " moved: "<<Vector::toString(move).c_str();
    //m_objectTree->insert(sender);
}
void InteractiveGameObject::rotated(GameObject* sender,const float deltaAngle)
{
   // m_objectTree->insert(sender);
}

// Signals from GameObjectGroup
void InteractiveGameObject::adding(GameObjectGroup* sender,GameObject* obj)
{
    for(size_t i=0; i<m_colliderObjects.interactsWithObjectsList.size(); i++)
    {
        if(m_colliderObjects.interactsWithObjectsList[i] == sender)
        {
            m_colliderObjects.objectTree->insert(obj);
            SIGNAL_SUBSCRIBE(GameObject,obj)
            m_colliderObjects.interactorAmount++;
            return;
        }
    }
    for(size_t i=0; i<m_detectionObjects.interactsWithObjectsList.size(); i++)
    {
        if(m_detectionObjects.interactsWithObjectsList[i] == sender)
        {
            m_detectionObjects.objectTree->insert(obj);
            SIGNAL_SUBSCRIBE(GameObject,obj)
            m_detectionObjects.interactorAmount++;
            return;
        }
    }
}
void InteractiveGameObject::adding(GameObjectGroup* sender,GameObjectGroup* group)
{
    for(size_t i=0; i<m_colliderObjects.interactsWithObjectsList.size(); i++)
    {
        if(m_colliderObjects.interactsWithObjectsList[i] == sender)
        {
            for(size_t j=0; j<group->size(); j++)
            {
                m_colliderObjects.objectTree->insert((*group)[j]);
                SIGNAL_SUBSCRIBE(GameObject,(*group)[j])
            }
            m_colliderObjects.interactorAmount+=group->size();
            return;
        }
    }
    for(size_t i=0; i<m_detectionObjects.interactsWithObjectsList.size(); i++)
    {
        if(m_detectionObjects.interactsWithObjectsList[i] == sender)
        {
            for(size_t j=0; j<group->size(); j++)
            {
                m_detectionObjects.objectTree->insert((*group)[j]);
                SIGNAL_SUBSCRIBE(GameObject,(*group)[j])
            }
            m_detectionObjects.interactorAmount+=group->size();
            return;
        }
    }




}
void InteractiveGameObject::removing(GameObjectGroup* sender,GameObject* obj)
{
    for(size_t i=0; i<m_colliderObjects.interactsWithObjectsList.size(); i++)
    {
        if(m_colliderObjects.interactsWithObjectsList[i] == sender)
        {
            m_colliderObjects.objectTree->removeRecursive(obj);
            SIGNAL_UNSUBSCRIBE(GameObject,obj)
            if(m_colliderObjects.interactorAmount == 0)
                qDebug() << "ERROR: InteractiveGameObject: m_interactorAmount will count wrong";
            else
                m_colliderObjects.interactorAmount --;
            return;
        }
    }
    for(size_t i=0; i<m_detectionObjects.interactsWithObjectsList.size(); i++)
    {
        if(m_detectionObjects.interactsWithObjectsList[i] == sender)
        {
            m_detectionObjects.objectTree->removeRecursive(obj);
            SIGNAL_UNSUBSCRIBE(GameObject,obj)
            if(m_detectionObjects.interactorAmount == 0)
                qDebug() << "ERROR: InteractiveGameObject: m_interactorAmount will count wrong";
            else
                m_detectionObjects.interactorAmount --;
            return;
        }
    }
}
void InteractiveGameObject::removing(GameObjectGroup* sender,GameObjectGroup* group)
{
    for(size_t i=0; i<m_colliderObjects.interactsWithObjectsList.size(); i++)
    {
        if(m_colliderObjects.interactsWithObjectsList[i] == sender)
        {
            for(size_t j=0; j<group->size(); j++)
            {
                m_colliderObjects.objectTree->removeRecursive((*group)[j]);
                SIGNAL_UNSUBSCRIBE(GameObject,(*group)[j])
            }
            if(m_colliderObjects.interactorAmount < group->size())
                qDebug() << "ERROR: InteractiveGameObject: m_interactorAmount will count wrong";
            else
                m_colliderObjects.interactorAmount -= group->size();
            return;
        }
    }
    for(size_t i=0; i<m_detectionObjects.interactsWithObjectsList.size(); i++)
    {
        if(m_detectionObjects.interactsWithObjectsList[i] == sender)
        {
            for(size_t j=0; j<group->size(); j++)
            {
                m_detectionObjects.objectTree->removeRecursive((*group)[j]);
                SIGNAL_UNSUBSCRIBE(GameObject,(*group)[j])
            }
            if(m_detectionObjects.interactorAmount < group->size())
                qDebug() << "ERROR: InteractiveGameObject: m_interactorAmount will count wrong";
            else
                m_detectionObjects.interactorAmount -= group->size();
            return;
        }
    }




}
void InteractiveGameObject::willBeCleared(GameObjectGroup* sender)
{
    for(size_t i=0; i<m_colliderObjects.interactsWithObjectsList.size(); i++)
    {
        if(m_colliderObjects.interactsWithObjectsList[i] == sender)
        {
            for(size_t i=0; i<sender->size(); i++)
            {
                m_colliderObjects.objectTree->removeRecursive((*sender)[i]);
                SIGNAL_UNSUBSCRIBE(GameObject,(*sender)[i])
            }
            if(m_colliderObjects.interactorAmount < sender->size())
                qDebug() << "ERROR: InteractiveGameObject: m_interactorAmount will count wrong";
            else
                m_colliderObjects.interactorAmount -= sender->size();
            return;
        }
    }
    for(size_t i=0; i<m_detectionObjects.interactsWithObjectsList.size(); i++)
    {
        if(m_detectionObjects.interactsWithObjectsList[i] == sender)
        {
            for(size_t i=0; i<sender->size(); i++)
            {
                m_detectionObjects.objectTree->removeRecursive((*sender)[i]);
                SIGNAL_UNSUBSCRIBE(GameObject,(*sender)[i])
            }
            if(m_detectionObjects.interactorAmount < sender->size())
                qDebug() << "ERROR: InteractiveGameObject: m_interactorAmount will count wrong";
            else
                m_detectionObjects.interactorAmount -= sender->size();
            return;
        }
    }
}
void InteractiveGameObject::cleared(GameObjectGroup* sender)
{
    //updateAllList();
}
