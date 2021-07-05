#include "InteractiveGameObject.h"

InteractiveGameObject::InteractiveGameObject()
{
    m_gameObject = nullptr;
    Vector2i blockSize(16,16);
    m_interactiveObjectsChunkMap   = new ChunkMap(Vector2u(blockSize*8),RectI(blockSize*(-40),blockSize*80));
    m_gameObjectChunkMap           = new ChunkMap(Vector2u(blockSize*8),RectI(blockSize*(-40),blockSize*80));

    m_interactsWithObjectsList.push_back(new GameObjectGroup());
    //m_interactsWithObjectsList[0]->subscribe(this);
}
InteractiveGameObject::InteractiveGameObject(const InteractiveGameObject &other)
{
    this->m_interactsWithObjectsList = other.m_interactsWithObjectsList;
    this->setGameObject(other.m_gameObject);
    this->m_interactiveObjectsChunkMap  = new ChunkMap(*other.m_interactiveObjectsChunkMap);
    this->m_gameObjectChunkMap          = new ChunkMap(*other.m_gameObjectChunkMap);
}
InteractiveGameObject::~InteractiveGameObject()
{
    m_gameObject->unsubscribe(this);
    m_gameObject->setThisInteractiveGameObject(nullptr);
    for(GameObjectGroup* &group : m_interactsWithObjectsList)
        group->unsubscribe(this);
    delete m_interactsWithObjectsList[0];
    delete m_interactiveObjectsChunkMap;
    delete m_gameObjectChunkMap;
    //delete m_gameObject;
}

void InteractiveGameObject::setGameObject(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple50);
    if(obj == nullptr || obj == m_gameObject)
        return;

    if(m_gameObject != nullptr)
    {
        m_gameObject->unsubscribe(this);
        m_gameObjectChunkMap->remove(m_gameObject);
    }
    m_gameObject = obj;
    m_gameObject->subscribe(this);
    m_gameObject->setThisInteractiveGameObject(this);
    m_gameObjectChunkMap->add(m_gameObject);
    //m_interactiveObjectsChunkMap->add(m_gameObject);
}
GameObject *InteractiveGameObject::getGameObject() const
{
    return m_gameObject;
}

void InteractiveGameObject::addInteractionWith(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple100);
    if(obj == nullptr)
        return;

#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        if(m_interactsWithObjectsList[i]->indexOf(obj) != -1)
            return;
    }
#endif

    m_interactsWithObjectsList[0]->add(obj);
    m_interactiveObjectsChunkMap->add(obj);

}
void InteractiveGameObject::addInteractionWith(GameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::Purple100);
    if(group == nullptr)
        return;
#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        if(m_interactsWithObjectsList[i] == group)
            return;
    }
#endif
    m_interactsWithObjectsList.push_back(group);
    m_interactiveObjectsChunkMap->add(group);
    //m_interactiveObjectsChunkMap->add(group);
    group->subscribe(this);
    //updateAllList();
}
void InteractiveGameObject::addInteractionWith(vector<GameObjectGroup*> *groupList)
{
    EASY_FUNCTION(profiler::colors::Purple100);
    for(size_t i=0; i<groupList->size(); i++)
    {
        addInteractionWith((*groupList)[i]);
    }
}

void InteractiveGameObject::removeInteractionWith(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    if(obj == nullptr)
        return;

   m_interactsWithObjectsList[0]->remove(obj);
   m_interactiveObjectsChunkMap->remove(obj);
#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=1; i<m_interactsWithObjectsList.size(); i++)
    {
        m_interactsWithObjectsList[i]->remove(obj);
    }
#endif
    //m_interactiveObjectsChunkMap->remove(obj);
}
void InteractiveGameObject::removeInteractionWith(GameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        if(m_interactsWithObjectsList[i] == group)
        {
            m_interactsWithObjectsList[i]->unsubscribe(this);
            m_interactiveObjectsChunkMap->remove(group);
            m_interactsWithObjectsList.erase(m_interactsWithObjectsList.begin()+i);
        }
    }
    //m_interactiveObjectsChunkMap->remove(group);
}
void InteractiveGameObject::removeInteractionWith(vector<GameObjectGroup*> *groupList)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    for(size_t i=0; i<groupList->size(); i++)
    {
        removeInteractionWith((*groupList)[i]);
    }
}

void InteractiveGameObject::setInteractionWith(GameObject *obj, bool doesCollide)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    if(doesCollide)
        addInteractionWith(obj);
    else
        removeInteractionWith(obj);
}
void InteractiveGameObject::setInteractionWith(GameObjectGroup *group, bool doesCollide)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    if(doesCollide)
        addInteractionWith(group);
    else
        removeInteractionWith(group);
}
void InteractiveGameObject::setInteractionWith(vector<GameObjectGroup*> *groupList, bool doesCollide)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    if(doesCollide)
        addInteractionWith(groupList);
    else
        removeInteractionWith(groupList);
}

const vector<GameObjectGroup*> &InteractiveGameObject::getInteractiveObjectsList() const
{
    return m_interactsWithObjectsList;
}
const vector<GameObject*> &InteractiveGameObject::getInteractiveObjects()
{
    EASY_FUNCTION(profiler::colors::Purple400);
    return m_interactiveObjectsChunkMap->getGameObjectGroup(m_gameObject->getChunkID());
    //return m_allList;
}
void InteractiveGameObject::draw_chunks(PixelDisplay &display)
{
    m_interactiveObjectsChunkMap->draw_chunks(display);
    m_gameObjectChunkMap->draw_chunks(display);
}
void InteractiveGameObject::setVisibility_chunk(const ChunkID &id,bool isVisible)
{
    m_gameObjectChunkMap->setVisibility_chunk(id,isVisible);
}
void InteractiveGameObject::setVisibility_chunks(bool isVisible)
{
    m_gameObjectChunkMap->setVisibility_chunks(isVisible);
}
bool InteractiveGameObject::isVisible_chunk(const ChunkID &id) const
{
    return m_gameObjectChunkMap->isVisible_chunk(id);
}
bool InteractiveGameObject::isVisible_chunks() const
{
    return m_gameObjectChunkMap->isVisible_chunks();
}

// GameObject singals:
void InteractiveGameObject::moved(GameObject* sender,const Vector2f &move)
{
    //qDebug() << "sender: "<<sender << " moved: "<<Vector::toString(move).c_str();
}

// Signals from GameObjectGroup
void InteractiveGameObject::adding(GameObjectGroup* sender,GameObject* obj)
{
    //qDebug() << "sender: "<<sender << " adding: "<<obj;
    //updateAllList();
    m_interactiveObjectsChunkMap->add(obj);
}
void InteractiveGameObject::adding(GameObjectGroup* sender,GameObjectGroup* group)
{
    //updateAllList();
    m_interactiveObjectsChunkMap->add(group);
}
void InteractiveGameObject::removing(GameObjectGroup* sender,GameObject* obj)
{
    //qDebug() << "sender: "<<sender << " removing: "<<obj;
    //updateAllList();
    m_interactiveObjectsChunkMap->remove(obj);
}
void InteractiveGameObject::removing(GameObjectGroup* sender,GameObjectGroup* group)
{
    //updateAllList();
    m_interactiveObjectsChunkMap->remove(group);
}
void InteractiveGameObject::willBeCleared(GameObjectGroup* sender)
{
    m_interactiveObjectsChunkMap->remove(sender);
}
void InteractiveGameObject::cleared(GameObjectGroup* sender)
{
    //updateAllList();
}
