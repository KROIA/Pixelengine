#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "base.h"

#include "layeritem.h"
#include "userEventHandler.h"
#include "event.h"
#include "signalSubscriber.h"
#include "mathFunctions.h"

using std::vector;
using sf::Vector2f;

class Controller    :   public UserEventHandler
{
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

        virtual void checkEvent();
        virtual void tick();

        virtual void setMovingMode(MovingMode mode);
        virtual MovingMode getMovingMode() const;

        virtual void moveToPos(const Vector2i&currentPos,const Vector2i&destination,MovingMode mode = MovingMode::add);
        virtual void moveToPos(const int &currentX,const int &currentY,
                               const int &destinationX,const int &destinationY,MovingMode mode = MovingMode::override);
        virtual void move(const Vector2i&directionVector,MovingMode mode = MovingMode::add);
        virtual void move(const Vector2f &directionVector,MovingMode mode = MovingMode::add);
        virtual void move(float x,float y,MovingMode mode = MovingMode::add);
        virtual void moveX(float x,MovingMode mode = MovingMode::add);
        virtual void moveY(float y,MovingMode mode = MovingMode::add);

        virtual Vector2f getMovingVector() const;

        virtual void setRotation(const float &deg);
        virtual void rotate(const float &deg);
        virtual float getRotation() const;
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();

        virtual void subscribe_ControllerSignal(ControllerSignal *subscriber);
        virtual void unsubscribe_ControllerSignal(ControllerSignal *subscriber);
        virtual void unsubscribeAll_ControllerSignal();

        virtual void reset();


    protected:
        // Receiver Signal from Eventhandler
        virtual void receive_key_isPressed(const int &key);
        virtual void receive_key_toggle(const int &key);
        virtual void receive_key_goesDown(const int &key);
        virtual void receive_key_goesUp(const int &key);



        Vector2f m_currentDeltaMove;
        bool     m_overwritable;
        int m_rotationDeg;
        MovingMode m_movingMode;
        //bool m_nothingToDo;

        ControllerSubscriberList m_controllerSubscriberList;

    private:

};
#endif
