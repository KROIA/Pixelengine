#ifndef ENGINE_INTERFACE_H
#define ENGINE_INTERFACE_H

#include "base.h"

class EngineInterface
{
    public:
        EngineInterface(){};

        virtual void kill(GameObject *obj) = 0;
        virtual void removeFromEngine(GameObject *obj) = 0;
        //virtual void deleteObject(GameObject *obj) = 0;
        virtual void collisionOccured(GameObject *obj1,vector<GameObject *> obj2) = 0;

     //   virtual void addPainterToDisplay(Painter *painter) = 0;
     //   virtual void removePainterFromDisplay(Painter *painter) = 0;
        virtual float getDeltaTime() const = 0;

        virtual void addEvent(Event *event) = 0;
        virtual void removeEvent(Event *event) = 0;
};
#endif // ENGINE_INTERFACE_H
