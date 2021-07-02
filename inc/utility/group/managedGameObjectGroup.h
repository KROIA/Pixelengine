#ifndef MANAGEDGAMEOBJECTGROUP_H
#define MANAGEDGAMEOBJECTGROUP_H

#include "gameObjectGroup.h"
#include "groupManagerInterface.h"

using std::vector;

class ManagedGameObjectGroup    :   public GameObjectGroup,  GroupManagerInterface
{
    public:
        ManagedGameObjectGroup();
        ManagedGameObjectGroup(const ManagedGameObjectGroup &other);

        virtual GameObject *operator[](const size_t &index) const;
        virtual bool newObjectsAvailable();
        virtual bool deletableObjectsAvailable();

        virtual const vector<GameObject *> &getNewObjects();
        virtual const vector<GameObject *> &getDeletableObjects();

        virtual void newObjectsAddedToEngine();
        virtual void deletableObjectsRemovedFromEngine();

        virtual void removeObject_unmanaged(GameObject *obj);

        virtual void reserve(size_t size);
        virtual void add(GameObject *object);
        virtual void add(GameObjectGroup *other);
        virtual void remove(const size_t index);

        virtual const vector<GameObject*> &getVector() const;


    protected:

        vector<GameObject *> m_toBeAdded; // To be added to the engine
        vector<GameObject *> m_toBeRemoved; // To be removed from the engine
    private:


};
#endif // ManagedGameObjectGroup_H
