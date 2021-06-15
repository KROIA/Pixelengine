#include "controller.h"

Controller::Controller()
    :   UserEventHandler()//, LayerItem()
{
    m_currentDeltaMove.setX(0.0);
    m_currentDeltaMove.setY(0.0);
    //m_neededStepsForMove = 0;
    //m_movingStepCounter = 0;
    m_rotationDeg       = 0;
}
Controller::Controller(const Controller &other)
    :   UserEventHandler()//, LayerItem()
{
    *this = other;
}
 Controller::~Controller()
{

}
const Controller &Controller::operator=(const Controller &other)
{
    UserEventHandler::operator=(other);
    //LayerItem::operator=(other);
    this->m_currentDeltaMove   = other.m_currentDeltaMove;

    //this->m_neededStepsForMove = other.m_neededStepsForMove;
    //this->m_movingStepCounter  = other.m_movingStepCounter;

    this->m_rotationDeg        = other.m_rotationDeg;
    return *this;
}
void Controller::checkEvent()
{
    UserEventHandler::checkEvent();
}
//void Controller::tick(const Point &direction)
void Controller::tick()
{
    m_currentDeltaMove.set(0,0);
   /* if(m_neededStepsForMove == 0)
    {
       //w m_lastPos   = m_pos;
        return;
    }

    // direction: Zwei ticks pro Achsenrichtung 1. Tick = x Bewegung 2. Tick = y Bewegung

    m_movingStepCounter++;
    if(m_movingStepCounter > m_neededStepsForMove)
    {
        m_currentDeltaMove.set(0,0);
        m_neededStepsForMove = 0;
    }*/
}

/*void Controller::setPos(const int &x,const int &y)
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
*/
void Controller::setMovingMode(MovingMode mode)
{
    m_movingMode = mode;
}
Controller::MovingMode Controller::getMovingMode() const
{
    return m_movingMode;
}
void Controller::moveToPos(const Point &currentPos,const Point &destination,MovingMode mode)
{
    this->move(destination.getX() - currentPos.getX(),
               destination.getY() - currentPos.getY());
    setMovingMode(mode);
}
void Controller::moveToPos(const int &currentX,const int &currentY,
                           const int &destinationX,const int &destinationY,MovingMode mode)
{
    this->move(destinationX - currentX, destinationY - currentY);
    setMovingMode(mode);
}
void Controller::move(const Point &directionVector,MovingMode mode)
{
    this->move(directionVector.getX(),directionVector.getY());
    setMovingMode(mode);
}
void Controller::move(const PointF &directionVector,MovingMode mode)
{
    this->move(directionVector.getX(),directionVector.getY());
    setMovingMode(mode);
}
void Controller::move(double x,double y,MovingMode mode)
{
    m_currentDeltaMove += VectorF(x,y);
    setMovingMode(mode);
    /*if(x == 0 && y == 0)
        return;
    if(m_neededStepsForMove > 0)
    {
        x = x + m_currentDeltaMove.getX()*m_neededStepsForMove;
        y = y + m_currentDeltaMove.getY()*m_neededStepsForMove;
    }

    if(abs(x)>abs(y))
        m_neededStepsForMove = abs(x);
    else
        m_neededStepsForMove = abs(y);
    m_movingStepCounter = 0;

    if(m_neededStepsForMove == 0)
    {
        //qDebug() << "div 0";
        return;
    }

    m_currentDeltaMove.set(double(x)/double(m_neededStepsForMove),double(y)/double(m_neededStepsForMove));
    */
    //m_neededStepsForMove*=2; // Zwei ticks pro Achsenrichtung 1. Tick = x Bewegung 2. Tick = y Bewegung
}
void Controller::moveX(double x,MovingMode mode)
{
    m_currentDeltaMove += VectorF(x,0);
    setMovingMode(mode);
}
void Controller::moveY(double y,MovingMode mode)
{
    m_currentDeltaMove += VectorF(0,y);
    setMovingMode(mode);
}
const VectorF &Controller::getMovingVector() const
{
    return m_currentDeltaMove;
}
/*const unsigned int &Controller::getNeededMovingSteps() const
{
    return m_neededStepsForMove;
}*/

void Controller::setRotation(const double &deg)
{
    m_rotationDeg = int(deg) % 360;
}
double Controller::getRotation() const
{
    return m_rotationDeg;
}
void Controller::rotate_90()
{
    m_rotationDeg += 90;
    m_rotationDeg = m_rotationDeg % 360;
}
void Controller::rotate_180()
{
    m_rotationDeg += 180;
    m_rotationDeg = m_rotationDeg % 360;
}
void Controller::rotate_270()
{
    m_rotationDeg += 270;
    m_rotationDeg = m_rotationDeg % 360;
}
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
