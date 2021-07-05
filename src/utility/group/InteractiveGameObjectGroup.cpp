#include "InteractiveGameObjectGroup.h"

InteractiveGameObjectGroup::InteractiveGameObjectGroup()
{

}
InteractiveGameObjectGroup::InteractiveGameObjectGroup(const InteractiveGameObjectGroup &other)
{

}
InteractiveGameObjectGroup::~InteractiveGameObjectGroup()
{
    for(InteractiveGameObject* &o : m_interactiveObjectsList)
        delete o;
    m_interactiveObjectsList.clear();
}

InteractiveGameObject* InteractiveGameObjectGroup::operator[](size_t index)
{
    if(m_interactiveObjectsList.size() <= index)
        return nullptr;
    return m_interactiveObjectsList[index];
}
void InteractiveGameObjectGroup::reserve(size_t size)
{
    m_interactiveObjectsList.reserve(size);
}
void InteractiveGameObjectGroup::add(InteractiveGameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple50);
    m_interactiveObjectsList.push_back(obj);
}
void InteractiveGameObjectGroup::add(GameObject *obj)
{
    InteractiveGameObject *j = new InteractiveGameObject();
    j->setGameObject(obj);
    this->add(j);
}

void InteractiveGameObjectGroup::remove(InteractiveGameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple100);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i] == obj)
        {
            m_interactiveObjectsList.erase(m_interactiveObjectsList.begin()+i);
            i--;
        }
    }
}
void InteractiveGameObjectGroup::remove(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple100);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->getGameObject() == obj)
        {
            m_interactiveObjectsList.erase(m_interactiveObjectsList.begin()+i);
            i--;
        }
    }
}
void InteractiveGameObjectGroup::deleteObj(InteractiveGameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i] == obj)
        {
            delete m_interactiveObjectsList[i];
            m_interactiveObjectsList.erase(m_interactiveObjectsList.begin()+i);
            i--;
        }
    }
}
void InteractiveGameObjectGroup::deleteObj(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->getGameObject() == obj)
        {
            delete m_interactiveObjectsList[i];
            m_interactiveObjectsList.erase(m_interactiveObjectsList.begin()+i);
            i--;
        }
    }
}
void InteractiveGameObjectGroup::clear()
{
    EASY_FUNCTION(profiler::colors::Purple300);
    m_interactiveObjectsList.clear();
}

InteractiveGameObject *InteractiveGameObjectGroup::getInteractiveObject(const GameObject *obj) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->getGameObject() == obj)
            return m_interactiveObjectsList[i];
    }
    return nullptr;
}

InteractiveGameObject *InteractiveGameObjectGroup::getInteractiveObject(unsigned int index) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
    if(m_interactiveObjectsList.size() >= index)
        return nullptr;
    return m_interactiveObjectsList[index];
}

const vector<InteractiveGameObject*> &InteractiveGameObjectGroup::getInteractiveObjectList() const
{
    return m_interactiveObjectsList;
}


const vector<GameObjectGroup*> &InteractiveGameObjectGroup::getInteractiveObjectsList(const GameObject *obj) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->getGameObject() == obj)
            return getInteractiveObjectsList(1);
    }
    return m_const_dummy_list;
}
const vector<GameObjectGroup*> &InteractiveGameObjectGroup::getInteractiveObjectsList(size_t index) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
     return m_interactiveObjectsList[index]->getInteractiveObjectsList();
}

const vector<GameObject*> &InteractiveGameObjectGroup::getInteractiveObjects(const GameObject *obj) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->getGameObject() == obj)
            return getInteractiveObjects(i);
    }
    return m_const_dummy_list_2;
}
const vector<GameObject*> &InteractiveGameObjectGroup::getInteractiveObjects(size_t index) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
    if(index<=m_interactiveObjectsList.size())
        return m_const_dummy_list_2;
    return m_interactiveObjectsList[index]->getInteractiveObjects();
}

void InteractiveGameObjectGroup::removeAllInteractionsWithObj(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple500);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        m_interactiveObjectsList[i]->removeInteractionWith(obj);
    }
}
void InteractiveGameObjectGroup::removeAllInteractionsWithObj(InteractiveGameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple500);
    removeAllInteractionsWithObj(obj->getGameObject());
}


size_t InteractiveGameObjectGroup::size() const
{
    return m_interactiveObjectsList.size();
}

/*void InteractiveGameObjectGroup::addInteractionWith(GameObject *obj)
{
    if(obj == nullptr)
        return;
#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->indexOf(obj) != -1)
            return;
    }
#endif
    m_interactiveObjectsList[0]->add(obj);

}
void InteractiveGameObjectGroup::addInteractionWith(GameObjectGroup *group)
{
    if(group == nullptr)
        return;
#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i] == group)
            return;
    }
#endif
    m_interactiveObjectsList.push_back(group);
}
void InteractiveGameObjectGroup::addInteractionWith(vector<GameObjectGroup*> *groupList)
{
    for(size_t i=0; i<groupList->size(); i++)
    {
        addInteractionWith((*groupList)[i]);
    }
}

void InteractiveGameObjectGroup::removeInteractionWith(GameObject *obj)
{
    if(obj == nullptr)
        return;

    m_interactiveObjectsList[0]->remove(obj);
#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        m_interactiveObjectsList[i]->remove(obj);
    }
#endif
}
void InteractiveGameObjectGroup::removeInteractionWith(GameObjectGroup *group)
{
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i] == group)
            m_interactiveObjectsList.erase(m_interactiveObjectsList.begin()+i);
    }
}
void InteractiveGameObjectGroup::removeInteractionWith(vector<GameObjectGroup*> *groupList)
{
    for(size_t i=0; i<groupList->size(); i++)
    {
        removeInteractionWith((*groupList)[i]);
    }
}

const vector<GameObjectGroup*> &InteractiveGameObjectGroup::getInteractiveObjectsList() const
{
    return m_interactiveObjectsList;
}
const GameObjectGroup InteractiveGameObjectGroup::getInteractiveObjects() const
{
    GameObjectGroup list;
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        list.add(m_interactiveObjectsList[i]);
    }
    return list;
}*/
