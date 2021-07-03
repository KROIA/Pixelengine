#include "InteractiveGameObject.h"

InteractiveGameObject::InteractiveGameObject()
{
    m_gameObject = nullptr;
    m_interactsWithObjectsList.push_back(new GameObjectGroup());
    m_interactsWithObjectsList[0]->subscribe(this);
}
InteractiveGameObject::InteractiveGameObject(const InteractiveGameObject &other)
{
    this->m_interactsWithObjectsList = other.m_interactsWithObjectsList;
    this->m_gameObject               = other.m_gameObject;
}
InteractiveGameObject::~InteractiveGameObject()
{
    m_gameObject->unsubscribe(this);
    for(GameObjectGroup* &group : m_interactsWithObjectsList)
        group->unsubscribe(this);
    delete m_interactsWithObjectsList[0];
    //delete m_gameObject;
}

void InteractiveGameObject::setGameObject(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple50);
    if(obj == nullptr)
        return;
    if(m_gameObject != nullptr)
        m_gameObject->unsubscribe(this);
    m_gameObject = obj;
    m_gameObject->subscribe(this);
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
    group->subscribe(this);
    updateAllList();
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
#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=1; i<m_interactsWithObjectsList.size(); i++)
    {
        m_interactsWithObjectsList[i]->remove(obj);
    }
#endif
}
void InteractiveGameObject::removeInteractionWith(GameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        if(m_interactsWithObjectsList[i] == group)
        {
            m_interactsWithObjectsList[i]->unsubscribe(this);
            m_interactsWithObjectsList.erase(m_interactsWithObjectsList.begin()+i);
            updateAllList();
        }
    }
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
const GameObjectGroup &InteractiveGameObject::getInteractiveObjects()
{
    EASY_FUNCTION(profiler::colors::Purple400);

    return m_allList;
}
void InteractiveGameObject::updateAllList()
{
    EASY_FUNCTION(profiler::colors::Purple400);
    m_allList.clear();
    size_t size = 0;
    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        size += m_interactsWithObjectsList[i]->size();
    }
    m_allList.reserve(size);
    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        m_allList.add(m_interactsWithObjectsList[i]);
    }
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
    updateAllList();
}
void InteractiveGameObject::adding(GameObjectGroup* sender,GameObjectGroup* group)
{
    updateAllList();
}
void InteractiveGameObject::removing(GameObjectGroup* sender,GameObject* obj)
{
    //qDebug() << "sender: "<<sender << " removing: "<<obj;
    updateAllList();
}
void InteractiveGameObject::removing(GameObjectGroup* sender,GameObjectGroup* group)
{
    updateAllList();
}
void InteractiveGameObject::willBeCleared(GameObjectGroup* sender)
{

}
void InteractiveGameObject::cleared(GameObjectGroup* sender)
{
    updateAllList();
}
