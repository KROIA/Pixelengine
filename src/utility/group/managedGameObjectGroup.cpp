#include "managedGameObjectGroup.h"

ManagedGameObjectGroup::ManagedGameObjectGroup()
    :   GameObjectGroup(),
        GroupManagerInterface()
{
    this->setVisibility(true);
    //this->showHitbox(false);
}
ManagedGameObjectGroup::ManagedGameObjectGroup(const ManagedGameObjectGroup &other)
{
    *this = other;
}
GameObject *ManagedGameObjectGroup::operator[](const size_t &index) const
{
    return m_isInList[index];
}
bool ManagedGameObjectGroup::newObjectsAvailable()
{
    if(m_toBeadding.size() > 0)
        return true;
    return false;
}
bool ManagedGameObjectGroup::deletableObjectsAvailable()
{
    if(m_toBeremoving.size() > 0)
        return true;
    return false;
}

const vector<GameObject *> &ManagedGameObjectGroup::getNewObjects()
{
    return m_toBeadding;
}
const vector<GameObject *> &ManagedGameObjectGroup::getDeletableObjects()
{
    return m_toBeremoving;
}

void ManagedGameObjectGroup::newObjectsaddingToEngine()
{
    EASY_FUNCTION(profiler::colors::Purple50);
    m_toBeadding.clear();
}
void ManagedGameObjectGroup::deletableObjectsremovingFromEngine()
{
    EASY_FUNCTION(profiler::colors::Purple100);
    m_toBeremoving.clear();
}
void ManagedGameObjectGroup::removeObject_unmanaged(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        if(m_isInList[i] == obj)
        {
            m_isInList.erase(m_isInList.begin()+i);
        }
    }
}
void ManagedGameObjectGroup::reserve(size_t size)
{
    m_isInList.reserve(size);
    m_toBeadding.reserve(size);
}
void ManagedGameObjectGroup::add(GameObject *object)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    m_isInList.push_back(object);
    m_toBeadding.push_back(object);
}
void ManagedGameObjectGroup::add(GameObjectGroup *other)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    m_toBeadding.reserve(m_toBeadding.size() + other->size());
    m_isInList.reserve(m_isInList.size()   + other->size());
    for(size_t i=0; i<other->size(); i++)
        this->add((*other)[i]);
}

void ManagedGameObjectGroup::remove(const size_t index)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    if(index >= m_isInList.size())
        return;
    m_isInList.erase(m_isInList.begin()+index);
    m_toBeremoving.push_back(m_isInList[index]);
}

const vector<GameObject*> &ManagedGameObjectGroup::getVector() const
{
    return m_isInList;
}

