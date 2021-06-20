#ifndef GROUPMANAGERINTERFACE_H
#define GROUPMANAGERINTERFACE_H

#include "vector"
#include "gameobject.h"

using std::vector;

class GroupManagerInterface
{
    public:

   // protected:
        GroupManagerInterface(){};

        virtual bool newObjectsAvailable() = 0;
        virtual bool deletableObjectsAvailable() = 0;

        virtual const vector<GameObject *> &getNewObjects() = 0;
        virtual const vector<GameObject *> &getDeletableObjects() = 0;

        virtual void newObjectsAddedToEngine() = 0;
        virtual void deletableObjectsRemovedFromEngine() = 0;

        virtual void removeObject_unmanaged(GameObject *obj) = 0;
    private:

};
#endif // GROUPMANAGERINTERFACE_H
