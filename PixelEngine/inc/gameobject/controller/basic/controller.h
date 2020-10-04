#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "layeritem.h"
#include "SFML/System.hpp"
#include <vector>
#include "point.h"
#include "vector.h"

#include "eventhandler.h"
#include "event.h"

using std::vector;

class Controller    :   public EventHandler, public LayerItem
{
    public:
        Controller();
        Controller(const Controller &other);
        virtual  ~Controller();

        virtual void tick(const Point &direction);

        virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Point &pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual void moveToPos(const Point &destination);
        virtual void moveToPos(const int &x,const int &y);
        virtual void move(const Point &directionVector);
        virtual void move(const int &x,const int &y);

        virtual void setToLastPos();
        virtual const unsigned int &getNeededMovingSteps() const;


    protected:
        // Receiver Signal from Eventhandler
        virtual void receive_key_isPressed(const int &key);
        virtual void receive_key_toggle(const int &key);
        virtual void reveive_key_goesDown(const int &key);
        virtual void reveive_key_goesUp(const int &key);


        PointF m_currentMovingPos;
        PointF m_currentDeltaMove;
        unsigned int m_neededStepsForMove;
        unsigned int m_movingStepCounter;
    private:

};
#endif
