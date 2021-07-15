#include "controller.h"

Controller::Controller()
    :   UserEventHandler()//, LayerItem()
{
    m_currentDeltaMove.x    = 0;
    m_currentDeltaMove.y    = 0;
    m_rotationDeg           = 0;
    m_movingMode            = add;
    //m_nothingToDo           = true;
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
    this->m_currentDeltaMove   = other.m_currentDeltaMove;

    this->m_rotationDeg        = other.m_rotationDeg;
    return *this;
}
void Controller::checkEvent()
{
    EASY_FUNCTION(profiler::colors::Pink);
    UserEventHandler::checkEvent();
}
void Controller::tick()
{
    EASY_FUNCTION(profiler::colors::Pink100);
    m_currentDeltaMove.x    = 0;
    m_currentDeltaMove.y    = 0;
}


void Controller::setMovingMode(MovingMode mode)
{
    m_movingMode = mode;
}
Controller::MovingMode Controller::getMovingMode() const
{
    return m_movingMode;
}
void Controller::moveToPos(const Vector2i&currentPos,const Vector2i&destination,MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Pink200);
    this->move(destination - currentPos);
    setMovingMode(mode);
}
void Controller::moveToPos(const int &currentX,const int &currentY,
                           const int &destinationX,const int &destinationY,MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Pink200);
    this->move(destinationX - currentX, destinationY - currentY);
    setMovingMode(mode);
}
void Controller::move(const Vector2i & directionVector,MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(directionVector);
    setMovingMode(mode);
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::move(const Vector2f &directionVector,MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += directionVector;
    setMovingMode(mode);
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::move(float x,float y,MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(x,y);
    setMovingMode(mode);
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::moveX(float x,MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(x,0);
    setMovingMode(mode);
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::moveY(float y,MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(0,y);
    setMovingMode(mode);
    m_controllerSubscriberList.moveAvailable(this);
}
const Vector2f &Controller::getMovingVector() const
{
    return m_currentDeltaMove;
}

void Controller::setRotation(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Pink300);
    m_rotationDeg = int(deg) % 360;
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::rotate(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Pink300);
    m_rotationDeg += deg;
    m_controllerSubscriberList.moveAvailable(this);
}
float Controller::getRotation() const
{
    return m_rotationDeg;
}
void Controller::rotate_90()
{
    EASY_FUNCTION(profiler::colors::Pink300);
    m_rotationDeg += 90;
    m_rotationDeg = m_rotationDeg % 360;
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::rotate_180()
{
    EASY_FUNCTION(profiler::colors::Pink300);
    m_rotationDeg += 180;
    m_rotationDeg = m_rotationDeg % 360;
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::rotate_270()
{
    EASY_FUNCTION(profiler::colors::Pink300);
    m_rotationDeg += 270;
    m_rotationDeg = m_rotationDeg % 360;
    m_controllerSubscriberList.moveAvailable(this);
}
// Eventhandler
void Controller::receive_key_isPressed(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink400);
    qDebug() << "Key: "<<key<<"\tController::receive_key_isPressed";
}
void Controller::receive_key_toggle(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink400);
    qDebug() << "Key: "<<key<<"\tController::receive_key_toggle";
}
void Controller::receive_key_goesDown(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink400);
    qDebug() << "Key: "<<key<<"\tController::receive_key_goesDown";
}
void Controller::receive_key_goesUp(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink400);
    qDebug() << "Key: "<<key<<"\tController::receive_key_goesUp";
}
// Signals
void Controller::subscribeControllerSignal(ControllerSignal *subscriber)
{
    if(subscriber == nullptr)
        return;
    for(size_t i=0; i<m_controllerSubscriberList.size(); i++)
    {
        if(m_controllerSubscriberList[i] == subscriber)
        {
            return;
        }
    }
    m_controllerSubscriberList.push_back(subscriber);
}
void Controller::unsubscribeControllerSignal(ControllerSignal *subscriber)
{
    for(size_t i=0; i<m_controllerSubscriberList.size(); i++)
    {
        if(m_controllerSubscriberList[i] == subscriber)
        {
            m_controllerSubscriberList.erase(m_controllerSubscriberList.begin()+i);
            return;
        }
    }
}
void Controller::unsubscribeAllControllerSignal()
{
    m_controllerSubscriberList.clear();
}
