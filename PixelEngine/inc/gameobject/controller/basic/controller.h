#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "layeritem.h"
#include "SFML/System.hpp"
#include <vector>
#include "point.h"
#include "vector.h"

#include "userEventHandler.h"
#include "event.h"

using std::vector;

class Controller    :   public UserEventHandler//, public LayerItem
{
    public:
        Controller();
        Controller(const Controller &other);
        virtual  ~Controller();
        virtual const Controller &operator=(const Controller &other);

        virtual void checkEvent();
       // virtual void tick(const Point &direction);
        virtual void tick();

        /*virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Point &pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);*/

        virtual void moveToPos(const Point &currentPos,const Point &destination);
        virtual void moveToPos(const int &currentX,const int &currentY,
                               const int &destinationX,const int &destinationY);
        virtual void move(const Point &directionVector);
        virtual void move(int x,int y);

        virtual const VectorF &getMovingVector() const;
        virtual const unsigned int &getNeededMovingSteps() const;

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
        unsigned int m_neededStepsForMove;
        unsigned int m_movingStepCounter;

        int m_rotationDeg;
    private:

};
#endif
