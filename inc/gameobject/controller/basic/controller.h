#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "layeritem.h"
#include "SFML/System.hpp"
#include <vector>
#include "point.h"
#include "vector.h"

#include "userEventHandler.h"
#include "event.h"

#include "profiler.h"

using std::vector;

class Controller    :   public UserEventHandler//, public LayerItem
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

        virtual void moveToPos(const Point &currentPos,const Point &destination,MovingMode mode = MovingMode::add);
        virtual void moveToPos(const int &currentX,const int &currentY,
                               const int &destinationX,const int &destinationY,MovingMode mode = MovingMode::override);
        virtual void move(const Point &directionVector,MovingMode mode = MovingMode::add);
        virtual void move(const PointF &directionVector,MovingMode mode = MovingMode::add);
        virtual void move(double x,double y,MovingMode mode = MovingMode::add);
        virtual void moveX(double x,MovingMode mode = MovingMode::add);
        virtual void moveY(double y,MovingMode mode = MovingMode::add);

        virtual const VectorF &getMovingVector() const;

        virtual void setRotation(const double &deg);
        virtual double getRotation() const;
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();

    protected:
        // Receiver Signal from Eventhandler
        virtual void receive_key_isPressed(const int &key);
        virtual void receive_key_toggle(const int &key);
        virtual void reveive_key_goesDown(const int &key);
        virtual void reveive_key_goesUp(const int &key);

        VectorF m_currentDeltaMove;
        int m_rotationDeg;
        MovingMode m_movingMode;
    private:

};
#endif
