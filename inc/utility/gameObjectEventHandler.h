#ifndef GAMEOBJECTEVENTHANDLER_H
#define GAMEOBJECTEVENTHANDLER_H

#include "vector"
#include "displayText.h"

using std::vector;

class GameObject;

class GameObjectEventHandler
{
    public:
        GameObjectEventHandler(){};

        virtual void kill(GameObject *obj) = 0;
        virtual void removeFromEngine(GameObject *obj) = 0;
        virtual void deleteObject(GameObject *obj) = 0;
        virtual void collisionOccured(GameObject *obj1,vector<GameObject *> obj2) = 0;

        virtual void addDisplayText(DisplayText *text) = 0;
        virtual void removeDisplayText(DisplayText *text) = 0;
};
#endif // GAMEOBJECTEVENTHANDLER_H
