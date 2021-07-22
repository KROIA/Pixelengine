#include "controller.h"

ControllerSubscriberList::ControllerSubscriberList()
    :   SubscriberList<ControllerSignal>()
{}

void ControllerSubscriberList::moveAvailable(Controller *sender)
{
    EMIT_SIGNAL(moveAvailable,sender);
}

Controller::Controller()
    :   UserEventHandler()//, LayerItem()
{
    m_currentDeltaMove.x    = 0;
    m_currentDeltaMove.y    = 0;
    m_rotationDeg           = 0;
    m_movingMode            = add;
    m_overwritable          = true;
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
void Controller::checkEvent(float deltaTime)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink);
    if(m_overwritable)
        reset();
    m_deltaTime = deltaTime;
   // qDebug() <<m_deltaTime;
    UserEventHandler::checkEvent();
}
void Controller::tick()
{
    CONTROLLER_FUNCTION(profiler::colors::Pink100);
    m_overwritable = true;
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
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    this->move(destination - currentPos,mode);
}
void Controller::moveToPos(const int &currentX,const int &currentY,
                           const int &destinationX,const int &destinationY,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    this->move(destinationX - currentX, destinationY - currentY, mode);
}
void Controller::move(const Vector2i & directionVector,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(directionVector);
    setMovingMode(mode);
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::move(const Vector2f &directionVector,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += directionVector;
    setMovingMode(mode);
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::move(float x,float y,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(x,y);
    setMovingMode(mode);
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::moveX(float x,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(x,0);
    setMovingMode(mode);
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::moveY(float y,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(0,y);
    setMovingMode(mode);
    m_controllerSubscriberList.moveAvailable(this);
}
Vector2f Controller::getMovingVector() const
{

    if(m_rotationDeg != 0)
        return Vector::getRotated(m_currentDeltaMove,m_rotationDeg) * m_deltaTime;
    return m_currentDeltaMove * m_deltaTime;
}

void Controller::setRotation(const float &deg)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink300);
    m_rotationDeg = float(int(1000*deg) % 360000)/1000.f;
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::rotate(const float &deg)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink300);
    m_rotationDeg += deg;
    m_controllerSubscriberList.moveAvailable(this);
}
float Controller::getRotation() const
{
    return m_rotationDeg;
}
void Controller::rotate_90()
{
    CONTROLLER_FUNCTION(profiler::colors::Pink300);
    m_rotationDeg += 90;
    m_rotationDeg = float(int(1000*m_rotationDeg) % 360000)/1000.f;
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::rotate_180()
{
    CONTROLLER_FUNCTION(profiler::colors::Pink300);
    m_rotationDeg += 180;
    m_rotationDeg = float(int(1000*m_rotationDeg) % 360000)/1000.f;
    m_controllerSubscriberList.moveAvailable(this);
}
void Controller::rotate_270()
{
    CONTROLLER_FUNCTION(profiler::colors::Pink300);
    m_rotationDeg += 270;
    m_rotationDeg = float(int(1000*m_rotationDeg) % 360000)/1000.f;
    m_controllerSubscriberList.moveAvailable(this);
}
// Eventhandler
void Controller::receive_key_isPressed(const int &key)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink400);
    qDebug() << "Key: "<<key<<"\tController::receive_key_isPressed";
}
void Controller::receive_key_toggle(const int &key)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink400);
    qDebug() << "Key: "<<key<<"\tController::receive_key_toggle";
}
void Controller::receive_key_goesDown(const int &key)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink400);
    qDebug() << "Key: "<<key<<"\tController::receive_key_goesDown";
}
void Controller::receive_key_goesUp(const int &key)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink400);
    qDebug() << "Key: "<<key<<"\tController::receive_key_goesUp";
}

void Controller::reset()
{
    m_currentDeltaMove.x    = 0;
    m_currentDeltaMove.y    = 0;
    //m_rotationDeg           = 0;
    m_overwritable = false;
}
// Signals
void Controller::subscribe_ControllerSignal(ControllerSignal *subscriber)
{
    if(subscriber == nullptr)
        return;
    m_controllerSubscriberList.insert(subscriber);
}
void Controller::unsubscribe_ControllerSignal(ControllerSignal *subscriber)
{
    m_controllerSubscriberList.erase(subscriber);
}
void Controller::unsubscribeAll_ControllerSignal()
{
    m_controllerSubscriberList.clear();
}
