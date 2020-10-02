#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "layeritem.h"
#include "SFML/System.hpp"
#include <vector>
#include "point.h"
#include "vector.h"

using std::vector;

class Controller    :   public LayerItem
{
    public:
        Controller();
        Controller(const Controller &other);
        virtual  ~Controller();

        virtual void tick(const Point direction);

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



        Point  m_movingDestination;
        PointF m_currentMovingPos;
        PointF m_currentDeltaMove;
        unsigned int m_neededStepsForMove;
        unsigned int m_movingStepCounter;
    private:

};
#endif
