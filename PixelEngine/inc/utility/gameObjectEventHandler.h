#ifndef GAMEOBJECTEVENTHANDLER_H
#define GAMEOBJECTEVENTHANDLER_H

class GameObject;

class GameObjectEventHandler
{
    public:
        GameObjectEventHandler(){};

        virtual void kill(GameObject *obj) = 0;
        virtual void removeFromEngine(GameObject *obj) = 0;
        virtual void collisionOccured(GameObject *obj1,GameObject *obj2) = 0;
};
#endif // GAMEOBJECTEVENTHANDLER_H
