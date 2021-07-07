#ifndef MANAGEDGAMEOBJECTGROUP_H
#define MANAGEDGAMEOBJECTGROUP_H

#include "gameObjectGroup.h"
#include "groupManagerInterface.h"

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

        virtual void newObjectsaddingToEngine();
        virtual void deletableObjectsremovingFromEngine();

        virtual void removeObject_unmanaged(GameObject *obj);

        virtual void reserve(size_t size);
        virtual void add(GameObject *object);
        virtual void add(GameObjectGroup *other);
        virtual void remove(const size_t index);

        virtual const vector<GameObject*> &getVector() const;


    protected:

        vector<GameObject *> m_toBeadding; // To be adding to the engine
        vector<GameObject *> m_toBeremoving; // To be removing from the engine
    private:


};
#endif // ManagedGameObjectGroup_H
