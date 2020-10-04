#ifndef INTERACTIVEGROUP_H
#define INTERACTIVEGROUP_H

#include "group.h"
#include <vector>

using std::vector;

template<class T>
class InteractiveGroup;
/*
typedef InteractiveGroup<GameObject> GameObjectGroupInteractive;
typedef InteractiveGroup<Controller> ControllerGroupInteractive;
typedef InteractiveGroup<Collider>     ColliderGroupInteractive;
typedef InteractiveGroup<Painter>       PainterGroupInteractive;
*/
template<class T>
class InteractiveGroup  :   public Group<T>
{
    public:
        InteractiveGroup();
        InteractiveGroup(const InteractiveGroup &other);

        virtual ~InteractiveGroup();

        virtual void interactWith(Group<T> *other);
        virtual const vector<Group<T> *> &getInteractiveList() const;

    protected:
        // List of Groups which shuld interact with this group
        vector<Group<T> *>m_interactiveList;
    private:

};

template<class T>
InteractiveGroup<T>::InteractiveGroup()
    :   Group<T>()
{

}
template<class T>
InteractiveGroup<T>::InteractiveGroup(const InteractiveGroup &other)
    :   Group<T>(other)
{
    this->m_interactiveList = other.m_interactiveList;
}
template<class T>
InteractiveGroup<T>::~InteractiveGroup()
{
    m_interactiveList.clear();
}

template<class T>
void InteractiveGroup<T>::interactWith(Group<T> *other)
{
    for(size_t i=0; i<m_interactiveList.size(); i++)
    {
        if(m_interactiveList[i] == other)
            return; // obj already exists in the list, so don't add it.
    }
    m_interactiveList.push_back(other);
}
template<class T>
const vector<Group<T> *> &InteractiveGroup<T>::getInteractiveList() const
{
    return m_interactiveList;
}
#endif // INTERACTIVEGROUP_H
