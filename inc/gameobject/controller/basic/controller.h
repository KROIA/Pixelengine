#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "base.h"

//#include "layeritem.h"
//#include "userEventHandler.h"
#include "keyEvent.h"
#include "signalEmitter.h"
#include "mathFunctions.h"
#include "displayInterface.h"
#include "layeritem.h"

// Signals for Controller
/*class ControllerSignal
{
    public:
        ControllerSignal(){}

        virtual void moveAvailable(Controller *sender) = 0;
        virtual void eventAdded(Controller *sender,  Event *e) = 0;
        virtual void eventRemoved(Controller *sender,  Event *e) = 0;
        virtual void eventsWillBeCleared(Controller *sender) = 0;
        virtual void eventsCleared(Controller *sender) = 0;
};
// Vector of Signals
class ControllerSubscriberList: public SubscriberList<ControllerSignal>
{
    public:
        ControllerSubscriberList();

        void moveAvailable(Controller *sender);
        void eventAdded(Controller *sender,  Event *e);
        void eventRemoved(Controller *sender,  Event *e);
        void eventsWillBeCleared(Controller *sender);
        void eventsCleared(Controller *sender);
};*/
SIGNAL_DEF(Controller)
    SIGNAL_FUNC(moveAvailable)
    SIGNAL_FUNC(eventAdded,Event*)
    SIGNAL_FUNC(eventRemoved,Event*)
    SIGNAL_FUNC(eventsWillBeCleared)
    SIGNAL_FUNC(eventsCleared)
SIGNAL_DEF_END

SIGNAL_EMITTER_DEF(Controller)
    SIGNAL_EMITTER_FUNC(moveAvailable)
    SIGNAL_EMITTER_FUNC(eventAdded,Event*)
    SIGNAL_EMITTER_FUNC(eventRemoved,Event*)
    SIGNAL_EMITTER_FUNC(eventsWillBeCleared)
    SIGNAL_EMITTER_FUNC(eventsCleared)
SIGNAL_EMITTER_DEF_END


class Controller
{
    SIGNAL_EMITTER(Controller)
    public:
        enum MovingMode
        {
            add,        // Will add the vector to the other movement Vectors
            override,   // Will reset the sum of others, and adds this Vector
        };
        Controller();
        Controller(const Controller &other);
        virtual  ~Controller();
        virtual const Controller &operator=(const Controller &other);

        static void setDisplayInterface(DisplayInterface *display);


        void setActive(bool active);
        bool isActive() const;
        bool addEvent(Event *event);
        bool removeEvent(Event *event);
        void clearEvent();
        bool hasEventsToCheck() const;
        virtual void checkEvent(float deltaTime);
        virtual void engineCalled_preTick();
        virtual void engineCalled_postTick();

        void setMovingMode(MovingMode mode);
        MovingMode getMovingMode() const;

        virtual void moveToPos(const Vector2f &destination, MovingMode mode = MovingMode::add);
        virtual void moveToPos(float destinationX,float destinationY,MovingMode mode = MovingMode::override);
        virtual void move(const Vector2i&directionVector,MovingMode mode = MovingMode::add);
        virtual void move(const Vector2f &directionVector,MovingMode mode = MovingMode::add);
        virtual void move(float x,float y,MovingMode mode = MovingMode::add);
        virtual void moveX(float x,MovingMode mode = MovingMode::add);
        virtual void moveY(float y,MovingMode mode = MovingMode::add);

        Vector2f getMovingVector() const;

        virtual void setPos(const Vector2f &pos);
        virtual void setRotation(float deg);
        virtual void rotate(float deg);
        virtual float getRotation() const;
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();

        virtual void setStepSize(float size);
        float getStepSize() const;
        virtual void useTimescale(bool enable);
        bool getUseTimascale()const;
        /*void subscribe_ControllerSignal(ControllerSignal *subscriber);
        void unsubscribe_ControllerSignal(ControllerSignal *subscriber);
        void unsubscribeAll_ControllerSignal();
*/
        virtual void reset();


    protected:



        Vector2f    m_currentDeltaMove;
        bool        m_overwritable;
        bool        m_active;
        bool        m_useTimeScale;
        Vector2f    m_pos;
        float       m_rotation;
        MovingMode  m_movingMode;

        float m_deltaTime;
        float m_stepSize;

       // ControllerSubscriberList m_controllerSubscriberList;

        static DisplayInterface *m_display_interface;

        HashTable<Event*>   m_eventList;

    private:

};
#endif
