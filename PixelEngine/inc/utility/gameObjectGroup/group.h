#ifndef GROUP_H
#define GROUP_H

#include "gameobject.h"
#include "controller.h"
#include "collider.h"
#include "painter.h"
#include <vector>

using std::vector;

template<class T>
class Group;

typedef Group<GameObject*> GameObjectGroup;
//typedef Group<Controller> ControllerGroup;
//typedef Group<Collider>     ColliderGroup;
//typedef Group<Painter>       PainterGroup;

template<class T>
class Group
{
    public:
        Group();
        Group(const Group &other);

        virtual ~Group();

        virtual void add(T obj);
        virtual void add(const vector<T> &list);
        virtual void add(const Group<T> &list);
        virtual T get(const size_t &index) const;
        virtual const vector<T> &getAll() const;
        virtual void set(const vector<T> &list);

        virtual size_t size() const;

    protected:
        // Lsit of Objects which are in this Group
        vector<T> m_objectList;
    private:

};

template<class T>
Group<T>::Group()
{

}
template<class T>
Group<T>::Group(const Group &other)
{
    this->m_objectList = other.m_objectList;
}

template<class T>
Group<T>::~Group()
{
    // Don't delete the objecs, because they arent property of the Group class
    m_objectList.clear();
}

template<class T>
void Group<T>::add(T obj)
{
    if(obj == nullptr)
        throw std::runtime_error(std::string("void Group<T>::add(T *[nullptr])): ")+
                                 "Can't add not existing object to the group");
    for(size_t i=0; i<m_objectList.size(); i++)
    {
        if(m_objectList[i] == obj)
            return; // obj already exists in the list, so don't add it.
    }
    m_objectList.push_back(obj);
}
template<class T>
void Group<T>::add(const vector<T> &list)
{
    m_objectList.reserve(m_objectList.size()+list.size());
    for(size_t i=0; i<list.size(); i++)
    {
        this->add(list[i]);
    }
}
template<class T>
void Group<T>::add(const Group<T> &list)
{
    this->add(list.getAll());
}
template<class T>
T Group<T>::get(const size_t &index) const
{
    if(index >= m_objectList.size())
        throw std::runtime_error("T *Group<T>::get(const size_t &["+std::to_string(index)+"]): "+
                                 "The Group only has "+std::to_string(this->size())+ " elements"); // Out of boundry
    return m_objectList[index];
}
template<class T>
const vector<T > &Group<T>::getAll() const
{
    return m_objectList;
}

template<class T>
void Group<T>::set(const vector<T> &list)
{
    m_objectList = list;
}

template<class T>
size_t Group<T>::size() const
{
    return m_objectList.size();
}
#endif // GAMEOBJECTGROUP_H
