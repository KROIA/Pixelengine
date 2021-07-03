#ifndef GAMEOBJECTEVENTHANDLER_H
#define GAMEOBJECTEVENTHANDLER_H

#include "base.h"

class GameObjectEventHandler
{
    public:
        GameObjectEventHandler(){};

        virtual void kill(GameObject *obj) = 0;
        virtual void removeFromEngine(GameObject *obj) = 0;
        //virtual void deleteObject(GameObject *obj) = 0;
        virtual void collisionOccured(GameObject *obj1,vector<GameObject *> obj2) = 0;

        virtual void addDisplayText(DisplayText *text) = 0;
        virtual void removingisplayText(DisplayText *text) = 0;
};
#endif // GAMEOBJECTEVENTHANDLER_H
