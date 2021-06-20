#include "InteractiveGameObject.h"

InteractiveGameObject::InteractiveGameObject()
{
    m_gameObject = nullptr;
    m_interactsWithObjectsList.push_back(new GameObjectGroup());
}
InteractiveGameObject::InteractiveGameObject(const InteractiveGameObject &other)
{
    this->m_interactsWithObjectsList = other.m_interactsWithObjectsList;
    this->m_gameObject               = other.m_gameObject;
}
InteractiveGameObject::~InteractiveGameObject()
{
    delete m_interactsWithObjectsList[0];
   delete m_gameObject;
}

void InteractiveGameObject::setGameObject(GameObject *obj)
{
    m_gameObject = obj;
}
GameObject *InteractiveGameObject::getGameObject() const
{
    return m_gameObject;
}

void InteractiveGameObject::addInteractionWith(GameObject *obj)
{
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
}
void InteractiveGameObject::addInteractionWith(vector<GameObjectGroup*> *groupList)
{
    for(size_t i=0; i<groupList->size(); i++)
    {
        addInteractionWith((*groupList)[i]);
    }
}

void InteractiveGameObject::removeInteractionWith(GameObject *obj)
{
    if(obj == nullptr)
        return;

    m_interactsWithObjectsList[0]->remove(obj);
#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        m_interactsWithObjectsList[i]->remove(obj);
    }
#endif
}
void InteractiveGameObject::removeInteractionWith(GameObjectGroup *group)
{
    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        if(m_interactsWithObjectsList[i] == group)
            m_interactsWithObjectsList.erase(m_interactsWithObjectsList.begin()+i);
    }
}
void InteractiveGameObject::removeInteractionWith(vector<GameObjectGroup*> *groupList)
{
    for(size_t i=0; i<groupList->size(); i++)
    {
        removeInteractionWith((*groupList)[i]);
    }
}

void InteractiveGameObject::setInteractionWith(GameObject *obj, bool doesCollide)
{
    if(doesCollide)
        addInteractionWith(obj);
    else
        removeInteractionWith(obj);
}
void InteractiveGameObject::setInteractionWith(GameObjectGroup *group, bool doesCollide)
{
    if(doesCollide)
        addInteractionWith(group);
    else
        removeInteractionWith(group);
}
void InteractiveGameObject::setInteractionWith(vector<GameObjectGroup*> *groupList, bool doesCollide)
{
    if(doesCollide)
        addInteractionWith(groupList);
    else
        removeInteractionWith(groupList);
}

const vector<GameObjectGroup*> &InteractiveGameObject::getInteractiveObjectsList() const
{
    return m_interactsWithObjectsList;
}
const GameObjectGroup InteractiveGameObject::getInteractiveObjects() const
{
    GameObjectGroup list;
    for(size_t i=0; i<m_interactsWithObjectsList.size(); i++)
    {
        list.add(m_interactsWithObjectsList[i]);
    }
    return list;
}
