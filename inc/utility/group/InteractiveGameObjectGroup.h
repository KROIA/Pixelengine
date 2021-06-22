#ifndef INTERACTIVEGAMEOBJECTGROUP_H
#define INTERACTIVEGAMEOBJECTGROUP_H

#include "InteractiveGameObject.h"
#include "vector"

#define CHECK_FOR_DOUBLE_OBJ

using std::vector;


class InteractiveGameObjectGroup
{
    public:
        InteractiveGameObjectGroup();
        InteractiveGameObjectGroup(const InteractiveGameObjectGroup &other);
        virtual ~InteractiveGameObjectGroup();

        InteractiveGameObject* operator[](size_t index);

        virtual void add(InteractiveGameObject *obj);
        virtual void add(GameObject *obj);

        virtual void remove(InteractiveGameObject *obj);
        virtual void remove(GameObject *obj);
        virtual void deleteObj(InteractiveGameObject *obj);
        virtual void deleteObj(GameObject *obj);

        virtual void clear();

        virtual InteractiveGameObject *getInteractiveObject(const GameObject *obj) const;
        virtual InteractiveGameObject *getInteractiveObject(unsigned int index) const;
        virtual const vector<InteractiveGameObject*> &getInteractiveObjectList() const;

        virtual const vector<GameObjectGroup*> &getInteractiveObjectsList(const GameObject *obj) const;
        virtual const vector<GameObjectGroup*> &getInteractiveObjectsList(size_t index) const;
        virtual const GameObjectGroup getInteractiveObjects(const GameObject *obj) const;
        virtual const GameObjectGroup getInteractiveObjects(size_t index) const;

        virtual void removeAllInteractionsWithObj(GameObject *obj);
        virtual void removeAllInteractionsWithObj(InteractiveGameObject *obj);


        virtual size_t size() const;
    protected:

        vector<InteractiveGameObject*> m_interactiveObjectsList;
        vector<GameObjectGroup*>       m_const_dummy_list;

    private:
};
#endif // INTERACTIVEGAMEOBJECTGROUP_H
