#include "controller.h"

Controller::Controller()
    :   EventHandler(), LayerItem()
{
    m_currentMovingPos.setX(m_pos.getX());
    m_currentMovingPos.setY(m_pos.getY());
    m_currentDeltaMove.setX(0.0);
    m_currentDeltaMove.setY(0.0);
    m_neededStepsForMove = 0;
    m_movingStepCounter = 0;
}
Controller::Controller(const Controller &other)
    :   EventHandler(), LayerItem()
{
    *this = other;
}
 Controller::~Controller()
{

}
const Controller &Controller::operator=(const Controller &other)
{
    EventHandler::operator=(other);
    LayerItem::operator=(other);
    this->m_currentMovingPos   = other.m_currentMovingPos;
    this->m_currentDeltaMove   = other.m_currentDeltaMove;

    this->m_neededStepsForMove = other.m_neededStepsForMove;
    this->m_movingStepCounter  = other.m_movingStepCounter;
    return *this;
}
void Controller::checkEvent()
{
    EventHandler::checkEvent();
}
void Controller::tick(const Point &direction)
{
    if(m_neededStepsForMove == 0)
    {
        m_lastPos   = m_pos;
        return;
    }

    // direction: Zwei ticks pro Achsenrichtung 1. Tick = x Bewegung 2. Tick = y Bewegung
    if(direction.getX())
    {
        /*this->setNextPos(m_pos.getX() + round(m_currentDeltaMove.getX()),
                         m_nextPos.getY());*/
        this->setX(m_pos.getX() + round(m_currentDeltaMove.getX()));
    }
    else
    {
        //this->setNextPos(m_nextPos.getX(),m_pos.getY() + round(m_currentDeltaMove.getY()));
        this->setY(m_pos.getY() + round(m_currentDeltaMove.getY()));
    }
    m_movingStepCounter++;
    if(m_movingStepCounter >= m_neededStepsForMove)
    {
        m_currentDeltaMove.set(0,0);
        m_neededStepsForMove = 0;
    }
}
/*void Controller::setPosInitial(const Point &pos)
{
    LayerItem::setPosInitial(pos);
    m_nextPos = m_pos;
}
void Controller::setPosInitial(const int &x, const int &y)
{
    LayerItem::setPosInitial(x,y);
    m_nextPos = m_pos;
}*/

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
void Controller::move(int x,int y)
{
    //double length = VectorF(double(x),double(y)).getLength();
    if(x == 0 && y == 0)
        return;
    if(m_neededStepsForMove > 0)
    {
        x = x + m_currentDeltaMove.getX()*m_neededStepsForMove/2;
        y = y + m_currentDeltaMove.getY()*m_neededStepsForMove/2;
    }

    if(abs(x)>abs(y))
        m_neededStepsForMove = abs(x);
    else
        m_neededStepsForMove = abs(y);
    m_movingStepCounter = 0;

    m_currentDeltaMove.set(double(x)/double(m_neededStepsForMove),double(y)/double(m_neededStepsForMove));
    m_neededStepsForMove*=2; // Zwei ticks pro Achsenrichtung 1. Tick = x Bewegung 2. Tick = y Bewegung
}
/*void Controller::setToLastPos()
{
    //m_nextPos = m_pos;
    LayerItem::setToLastPos();
}*/

const unsigned int &Controller::getNeededMovingSteps() const
{
    return m_neededStepsForMove;
}
/*void Controller::setNextPos(const int &x, const int &y)
{
    m_nextPos.set(x,y);
}
const Point &Controller::getNextPos() const
{
    return m_nextPos;
}
void Controller::applyNextPos()
{
    this->setPos(m_nextPos);
}
*/
// Eventhandler
void Controller::receive_key_isPressed(const int &key)
{
    qDebug() << "Key: "<<key<<"\tController::receive_key_isPressed";
}
void Controller::receive_key_toggle(const int &key)
{
    qDebug() << "Key: "<<key<<"\tController::receive_key_toggle";
}
void Controller::reveive_key_goesDown(const int &key)
{
    qDebug() << "Key: "<<key<<"\tController::reveive_key_goesDown";
}
void Controller::reveive_key_goesUp(const int &key)
{
    qDebug() << "Key: "<<key<<"\tController::reveive_key_goesUp";
}
