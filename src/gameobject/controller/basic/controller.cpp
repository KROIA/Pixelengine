#include "controller.h"

/*
ControllerSubscriberList::ControllerSubscriberList()
    :   SubscriberList<ControllerSignal>()
{}

void ControllerSubscriberList::moveAvailable(Controller *sender)
{
    SIGNAL_EMIT_INTERN(moveAvailable,sender);
}
void ControllerSubscriberList::eventAdded(Controller *sender,  Event *e)
{
    SIGNAL_EMIT_INTERN(eventAdded,sender,e);
}
void ControllerSubscriberList::eventRemoved(Controller *sender,  Event *e)
{
    SIGNAL_EMIT_INTERN(eventRemoved,sender,e);
}
void ControllerSubscriberList::eventsWillBeCleared(Controller *sender)
{
    SIGNAL_EMIT_INTERN(eventsWillBeCleared,sender);
}
void ControllerSubscriberList::eventsCleared(Controller *sender)
{
    SIGNAL_EMIT_INTERN(eventsCleared,sender);
}*/

//const PixelDisplay *Controller::m_display = nullptr;
DisplayInterface *Controller::m_display_interface = nullptr;
Controller::Controller()
{
    m_currentDeltaMove.x    = 0;
    m_currentDeltaMove.y    = 0;
    m_rotation              = 0;
    m_movingMode            = add;
    m_overwritable          = true;
    this->setActive(true);
    this->setStepSize(1);
    this->useTimescale(true);
    if(m_display_interface == nullptr)
    {
        qDebug() << "Controller::m_display_interface == nullptr, can cause problems";
    }
}
Controller::Controller(const Controller &other)
{
    *this = other;
}
 Controller::~Controller()
{

}
const Controller &Controller::operator=(const Controller &other)
{
   // UserEventHandler::operator=(other);
    this->m_currentDeltaMove   = other.m_currentDeltaMove;
    this->m_overwritable       = other.m_overwritable;
    this->m_rotation           = other.m_rotation;
    this->m_movingMode         = other.m_movingMode;
    this->m_deltaTime          = other.m_deltaTime;
    this->m_active             = other.m_active;
    this->m_useTimeScale       = other.m_useTimeScale;
    return *this;
}
/*void Controller::setDisplay(const PixelDisplay *display)
{
    m_display = display;
}*/
void Controller::setDisplayInterface(DisplayInterface *display)
{
    m_display_interface = display;
}
void Controller::setActive(bool active)
{
    m_active  = active;
    this->reset();
}
bool Controller::isActive() const
{
    return m_active;
}
bool Controller::addEvent(Event *event)
{
    if(!event)
        return false; // event is nullptr
    if(m_eventList.find(event) != m_eventList.end())
        return false; // event already added
    m_eventList.insert({event,event});
    //m_controllerSubscriberList.eventAdded(this,event);
    SIGNAL_EMIT(Controller,eventAdded,event)
    return true;
}
bool Controller::removeEvent(Event *event)
{
    if(!event)
        return false; // event is nullptr
    if(m_eventList.find(event) == m_eventList.end())
        return false; // event not in list
    m_eventList.erase(event);
    //m_controllerSubscriberList.eventRemoved(this,event);
    SIGNAL_EMIT(Controller,eventRemoved,event)
    return true;
}
void Controller::clearEvent()
{
    SIGNAL_EMIT(Controller,eventsWillBeCleared)
   // m_controllerSubscriberList.eventsWillBeCleared(this);
    m_eventList.clear();
    SIGNAL_EMIT(Controller,eventsWillBeCleared)
   // m_controllerSubscriberList.eventsCleared(this);
}
bool Controller::hasEventsToCheck() const
{
    if(m_eventList.size() > 0)
        return true;
    return false;
}
void Controller::checkEvent(float deltaTime)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink);
    if(!m_active)
        return;
    if(m_overwritable)
        reset();
    m_deltaTime = deltaTime;
    for(auto eventPair : m_eventList)
        eventPair.second->checkEvent(deltaTime);
   // qDebug() <<m_deltaTime;
  //  UserEventHandler::checkEvent(deltaTime);
}
void Controller::engineCalled_preTick()
{
    CONTROLLER_FUNCTION(profiler::colors::Pink100);

}
void Controller::engineCalled_postTick()
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
void Controller::moveToPos(const Vector2f &destination,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    this->move(destination - m_pos,mode);
}
void Controller::moveToPos(float destinationX,float destinationY,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    this->move(destinationX - m_pos.x, destinationY - m_pos.y, mode);
}
void Controller::move(const Vector2i & directionVector,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(directionVector);
    setMovingMode(mode);
   // m_controllerSubscriberList.moveAvailable(this);
    SIGNAL_EMIT(Controller,moveAvailable)
}
void Controller::move(const Vector2f &directionVector,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += directionVector;
    setMovingMode(mode);
    //m_controllerSubscriberList.moveAvailable(this);
    SIGNAL_EMIT(Controller,moveAvailable)
}
void Controller::move(float x,float y,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(x,y);
    setMovingMode(mode);
    //m_controllerSubscriberList.moveAvailable(this);
    SIGNAL_EMIT(Controller,moveAvailable)
}
void Controller::moveX(float x,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(x,0);
    setMovingMode(mode);
   // m_controllerSubscriberList.moveAvailable(this);
    SIGNAL_EMIT(Controller,moveAvailable)
}
void Controller::moveY(float y,MovingMode mode)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink200);
    m_currentDeltaMove += Vector2f(0,y);
    setMovingMode(mode);
   // m_controllerSubscriberList.moveAvailable(this);
    SIGNAL_EMIT(Controller,moveAvailable)
}
Vector2f Controller::getMovingVector() const
{
    if(!m_active)
        return Vector2f(0,0);
    if(m_useTimeScale)
    {
        if(m_rotation != 0)
            return Vector::getRotated(m_currentDeltaMove,m_rotation) * m_deltaTime;
        return m_currentDeltaMove * m_deltaTime;
    }
    else
    {
        if(m_rotation != 0)
            return Vector::getRotated(m_currentDeltaMove,m_rotation);
        return m_currentDeltaMove;
    }

}

void Controller::setPos(const Vector2f &pos)
{
    m_pos = pos;
}
void Controller::setRotation(float deg)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink300);
    m_rotation = float(int(1000*deg) % 360000)/1000.f;
    //m_controllerSubscriberList.moveAvailable(this);
    SIGNAL_EMIT(Controller,moveAvailable)
}
void Controller::rotate(float deg)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink300);
    m_rotation += deg;
    //m_controllerSubscriberList.moveAvailable(this);
    SIGNAL_EMIT(Controller,moveAvailable)
}
float Controller::getRotation() const
{
    return m_rotation;
}
void Controller::rotate_90()
{
    CONTROLLER_FUNCTION(profiler::colors::Pink300);
    m_rotation += 90;
    m_rotation = float(int(1000*m_rotation) % 360000)/1000.f;
    //m_controllerSubscriberList.moveAvailable(this);
    SIGNAL_EMIT(Controller,moveAvailable)
}
void Controller::rotate_180()
{
    CONTROLLER_FUNCTION(profiler::colors::Pink300);
    m_rotation += 180;
    m_rotation = float(int(1000*m_rotation) % 360000)/1000.f;
    //m_controllerSubscriberList.moveAvailable(this);
    SIGNAL_EMIT(Controller,moveAvailable)
}
void Controller::rotate_270()
{
    CONTROLLER_FUNCTION(profiler::colors::Pink300);
    m_rotation += 270;
    m_rotation = float(int(1000*m_rotation) % 360000)/1000.f;
    //m_controllerSubscriberList.moveAvailable(this);
    SIGNAL_EMIT(Controller,moveAvailable)
}
void Controller::setStepSize(float size)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink500);
    m_stepSize = size;
}
float Controller::getStepSize() const
{
    return m_stepSize;
}
void Controller::useTimescale(bool enable)
{
    m_useTimeScale = enable;
}
bool Controller::getUseTimascale()const
{
    return m_useTimeScale;
}
/*// Eventhandler
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
}*/

void Controller::reset()
{
    m_currentDeltaMove.x    = 0;
    m_currentDeltaMove.y    = 0;
    //m_rotation           = 0;
    m_overwritable = false;
}
// Signals
/*void Controller::subscribe_ControllerSignal(ControllerSignal *subscriber)
{
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
*/
