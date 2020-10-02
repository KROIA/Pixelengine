#include "controller.h"

Controller::Controller()
    :   LayerItem()
{

    m_movingDestination.setX(m_pos.getX());
    m_movingDestination.setY(m_pos.getY());
    m_currentMovingPos.setX(m_pos.getX());
    m_currentMovingPos.setY(m_pos.getY());
    m_currentDeltaMove.setX(0.0);
    m_currentDeltaMove.setY(0.0);
    m_neededStepsForMove = 0;
    m_movingStepCounter = 0;
}
Controller::Controller(const Controller &other)
    :   LayerItem(other)
{
    this->m_movingDestination = other.m_movingDestination;
    this->m_currentMovingPos  = other.m_currentMovingPos;
    this->m_currentDeltaMove  = other.m_currentDeltaMove;

    this->m_neededStepsForMove = other.m_neededStepsForMove;
    this->m_movingStepCounter = other.m_movingStepCounter;
}
 Controller::~Controller()
{

}

void Controller::tick(const Point direction)
{
    // direction: Zwei ticks pro Achsenrichtung 1. Tick = x Bewegung 2. Tick = y Bewegung
    m_currentMovingPos.move(m_currentDeltaMove.getX()*direction.getX(),
                            m_currentDeltaMove.getY()*direction.getY());
    m_movingStepCounter++;
    if(m_movingStepCounter >= m_neededStepsForMove)
        m_currentDeltaMove.set(0,0);

    this->setPos(round(m_currentMovingPos.getX()),round(m_currentMovingPos.getY()));
}

void Controller::setPos(const int &x,const int &y)
{
    LayerItem::setPos(x,y);
}
void Controller::setPos(const Point &pos)
{
    LayerItem::setPos(pos);
}

void Controller::setX(const int &x)
{
    LayerItem::setX(x);
}
void Controller::setY(const int &y)
{
    LayerItem::setY(y);
}

void Controller::moveToPos(const Point &destination)
{
    this->move(destination.getX() - m_pos.getX(),
               destination.getY() - m_pos.getY());
}
void Controller::moveToPos(const int &x,const int &y)
{
    this->move(x - m_pos.getX(), y - m_pos.getY());
}
void Controller::move(const Point &directionVector)
{
    this->move(directionVector.getX(),directionVector.getY());
}
void Controller::move(const int &x,const int &y)
{
    double length = VectorF(double(x),double(y)).getLength();
    if(x == 0 && y == 0)
        return;
    if(abs(x)>abs(y))
        m_neededStepsForMove = abs(x);
    else
        m_neededStepsForMove = abs(y);
    m_movingStepCounter = 0;

    m_movingDestination.set(m_pos.getX() + x,m_pos.getY() + y);
    m_currentDeltaMove.set(double(x)/double(m_neededStepsForMove),double(y)/double(m_neededStepsForMove));
    m_neededStepsForMove*=2; // Zwei ticks pro Achsenrichtung 1. Tick = x Bewegung 2. Tick = y Bewegung
}
void Controller::setToLastPos()
{
    LayerItem::setToLastPos();
    m_currentMovingPos.set(m_pos.getX(),m_pos.getY());
}

const unsigned int &Controller::getNeededMovingSteps() const
{
    return m_neededStepsForMove;
}
