#include "managedGameObjectGroup.h"

ManagedGameObjectGroup::ManagedGameObjectGroup()
    :   GameObjectGroup(),
        GroupManagerInterface()
{
    this->setVisibility(true);
    this->setHitboxVisibility(false);
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
    if(m_toBeAdded.size() > 0)
        return true;
    return false;
}
bool ManagedGameObjectGroup::deletableObjectsAvailable()
{
    if(m_toBeRemoved.size() > 0)
        return true;
    return false;
}

const vector<GameObject *> &ManagedGameObjectGroup::getNewObjects()
{
    return m_toBeAdded;
}
const vector<GameObject *> &ManagedGameObjectGroup::getDeletableObjects()
{
    return m_toBeRemoved;
}

void ManagedGameObjectGroup::newObjectsAddedToEngine()
{
    EASY_FUNCTION(profiler::colors::Purple50);
    m_toBeAdded.clear();
}
void ManagedGameObjectGroup::deletableObjectsRemovedFromEngine()
{
    EASY_FUNCTION(profiler::colors::Purple100);
    m_toBeRemoved.clear();
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

void ManagedGameObjectGroup::add(GameObject *object)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    m_isInList.push_back(object);
    m_toBeAdded.push_back(object);
}
void ManagedGameObjectGroup::add(GameObjectGroup *other)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    m_toBeAdded.reserve(m_toBeAdded.size() + other->size());
    m_isInList.reserve(m_isInList.size()   + other->size());
    for(size_t i=0; i<other->size(); i++)
        this->add((*other)[i]);
}
/*void ManagedGameObjectGroup::remove(GameObject *toRemove)
{
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        if(m_isInList[i] == toRemove)
        {
            this->remove(i);
        }
    }
}*/
/*void ManagedGameObjectGroup::remove(GameObjectGroup *other)
{
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        this->remove((*other)[i]);
    }
}*/
void ManagedGameObjectGroup::remove(const size_t index)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    if(index >= m_isInList.size())
        return;
    m_isInList.erase(m_isInList.begin()+index);
    m_toBeRemoved.push_back(m_isInList[index]);
}

const vector<GameObject*> &ManagedGameObjectGroup::getVector() const
{
    return m_isInList;
}
/*ManagedGameObjectGroup::~ManagedGameObjectGroup()
{

}
ManagedGameObjectGroup &ManagedGameObjectGroup::operator=(const ManagedGameObjectGroup &other)
{
    this->m_isVisible        = other.m_isVisible;
    this->m_hitboxIsVisible  = other.m_hitboxIsVisible;

    this->m_isInList             = other.m_isInList;
    this->m_toBeAdded            = other.m_toBeAdded;
    this->m_toBeRemoved          = other.m_toBeRemoved;
    return *this;
}
void ManagedGameObjectGroup::draw(PixelDisplay &display)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->draw(display);
}


void ManagedGameObjectGroup::clear()
{
    m_isInList.clear();
    m_toBeAdded.clear();
    m_toBeRemoved.clear();
}

size_t ManagedGameObjectGroup::size() const
{
    return m_isInList.size();
}
GameObject *ManagedGameObjectGroup::operator[](const size_t &index) const
{
    return m_isInList[index];
}
const vector<GameObject*> &ManagedGameObjectGroup::getVector() const
{
    return m_isInList;
}
// GameObject stuff
void ManagedGameObjectGroup::setPos(const int &x,const int &y)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(x,y);
}
void ManagedGameObjectGroup::setPos(const Point &pos)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(pos);
}
void ManagedGameObjectGroup::setX(const int &x)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setX(x);
}
void ManagedGameObjectGroup::setY(const int &y)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setY(y);
}
void ManagedGameObjectGroup::moveToPos(const Point &destination)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveToPos(destination);
}
void ManagedGameObjectGroup::moveToPos(const int &x,const int &y)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveToPos(x,y);
}
void ManagedGameObjectGroup::move(const Point &directionVector)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(directionVector);
}
void ManagedGameObjectGroup::move(int x,int y)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(x,y);
}
void ManagedGameObjectGroup::setRotation(const double &deg)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setRotation(deg);
}
void ManagedGameObjectGroup::rotate_90()
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_90();
}
void ManagedGameObjectGroup::rotate_180()
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_180();
}
void ManagedGameObjectGroup::rotate_270()
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_270();
}
void ManagedGameObjectGroup::setRotation(const PointF &rotationPoint,const double &deg)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setRotation(rotationPoint,deg);
}
void ManagedGameObjectGroup::rotate_90(const PointF &rotationPoint)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_90(rotationPoint);
}
void ManagedGameObjectGroup::rotate_180(const PointF &rotationPoint)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_180(rotationPoint);
}
void ManagedGameObjectGroup::rotate_270(const PointF &rotationPoint)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_270(rotationPoint);
}
void ManagedGameObjectGroup::setVisibility(const bool &isVisible)
{
    m_isVisible = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility(m_isVisible);
    }
}
const bool &ManagedGameObjectGroup::isVisible() const
{
    return m_isVisible;
}
void ManagedGameObjectGroup::setHitboxVisibility(const bool &isVisible)
{
    m_hitboxIsVisible = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setHitboxVisibility(m_hitboxIsVisible);
    }
}
const bool &ManagedGameObjectGroup::isHitboxVisible() const
{
    return m_hitboxIsVisible;
}


bool ManagedGameObjectGroup::__engineUseOnly_newObjAvailable() const
{
    if(m_toBeAdded.size() > 0)
        return true;
    return false;
}
bool ManagedGameObjectGroup::__engineUseOnly_deletableObjAvailable() const
{
    if(m_toBeRemoved.size() > 0)
        return true;
    return false;
}
const vector<GameObject *> &ManagedGameObjectGroup::__engineUseOnly_getAddList() const
{
    return m_toBeAdded;
}
const vector<GameObject *> &ManagedGameObjectGroup::__engineUseOnly_getRemoveList() const
{
    return m_toBeRemoved;
}
void ManagedGameObjectGroup::__engineUseOnly_objsAddedToEngine()
{
    m_toBeAdded.clear();
}
void ManagedGameObjectGroup::__engineUseOnly_objsRemovedFromEngine()
{
    m_toBeRemoved.clear();
}


void ManagedGameObjectGroup::removeDuplicates(vector<GameObject *> *list)
{
    vector<GameObject *> copyList;
    copyList.reserve(list->size());

    for(size_t i=0; i<list->size(); i++)
    {
        bool hasCopy = false;
        for(size_t j=0; j<copyList.size(); j++)
        {
            if((*list)[i] == copyList[j])
            {
                hasCopy = true;
                break; // Jumps to the end of this for loop
            }
        }
        // break jumpt to this Point
        if(!hasCopy)
            copyList.push_back((*list)[i]);
    }
    *list = copyList;
}
void ManagedGameObjectGroup::removeDuplicates(ManagedGameObjectGroup *list)
{
    removeDuplicates(&list->m_toBeAdded);
    removeDuplicates(&list->m_toBeRemoved);
    removeDuplicates(&list->m_isInList);

}
*/
