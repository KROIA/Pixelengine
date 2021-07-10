#ifndef GROUPMANAGERINTERFACE_H
#define GROUPMANAGERINTERFACE_H
#include "gameobject.h"

class GroupManagerInterface
{
    public:
        GroupManagerInterface(){};

        virtual bool newObjectsAvailable() = 0;
        virtual bool deletableObjectsAvailable() = 0;

        virtual const vector<GameObject *> &getNewObjects() = 0;
        virtual const vector<GameObject *> &getDeletableObjects() = 0;

        virtual void newObjectsaddingToEngine() = 0;
        virtual void deletableObjectsremovingFromEngine() = 0;

        virtual void removeObject_unmanaged(GameObject *obj) = 0;
    private:

};
#endif // GROUPMANAGERINTERFACE_H
