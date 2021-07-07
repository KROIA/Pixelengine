#include "keyController.h"

KeyController::KeyController()
    :   Controller()
{
    m_key_forMove_UP        = -1;
    m_key_forMove_LEFT      = -1;
    m_key_forMove_DOWN      = -1;
    m_key_forMove_RIGHT     = -1;

    this->setStepSize(1);
}
KeyController::KeyController(const KeyController &other)
    :   Controller()
{
    *this = other;
}

KeyController::~KeyController()
{

}
const KeyController &KeyController::operator=(const KeyController &other)
{
    Controller::operator=(other);
    this->m_key_forMove_UP          = other.m_key_forMove_UP;
    this->m_key_forMove_UP_event    = other.m_key_forMove_UP_event;
    this->m_key_forMove_LEFT        = other.m_key_forMove_LEFT;
    this->m_key_forMove_LEFT_event  = other.m_key_forMove_LEFT_event;
    this->m_key_forMove_DOWN        = other.m_key_forMove_DOWN;
    this->m_key_forMove_DOWN_event  = other.m_key_forMove_DOWN_event;
    this->m_key_forMove_RIGHT       = other.m_key_forMove_RIGHT;
    this->m_key_forMove_RIGHT_event = other.m_key_forMove_RIGHT_event;

    this->m_currentMovingVec        = other.m_currentMovingVec;

    this->m_stepSize                = other.m_stepSize;
    this->m_stepUp                  = other.m_stepUp;
    this->m_stepLeft                = other.m_stepLeft;
    this->m_stepDown                = other.m_stepDown;
    this->m_stepRight               = other.m_stepRight;
    return *this;
}
// From Controller
void KeyController::checkEvent()
{
    EASY_FUNCTION(profiler::colors::Pink);
    // KeyController::tick gets called 2 times per GameTick,
    // so only handle events once per GameTick
    m_currentMovingVec.x = 0;
    m_currentMovingVec.y = 0;
    Controller::checkEvent();
    this->move(m_currentMovingVec);
}
void KeyController::tick()
{
    EASY_FUNCTION(profiler::colors::Pink100);
    Controller::tick();
}
void KeyController::rotate(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Pink200);
    Controller::rotate(deg);
    this->setRotation();
}
void KeyController::setRotation(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Pink200);
    Controller::setRotation(deg);
    this->setRotation();
}
float KeyController::getRotation() const
{
    return Controller::getRotation();
}
void KeyController::rotate_90()
{
    EASY_FUNCTION(profiler::colors::Pink200);
    Controller::rotate_90();
    this->setRotation();
}
void KeyController::rotate_180()
{
    EASY_FUNCTION(profiler::colors::Pink200);
    Controller::rotate_180();
    this->setRotation();
}
void KeyController::rotate_270()
{
    EASY_FUNCTION(profiler::colors::Pink200);
    Controller::rotate_270();
    this->setRotation();
}

// Receiver Signal from Eventhandler
void KeyController::receive_key_isPressed(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink300);
   if(key == m_key_forMove_UP)
        m_currentMovingVec += m_stepUp;
    else if(key == m_key_forMove_DOWN)
        m_currentMovingVec += m_stepDown;
    else if(key == m_key_forMove_LEFT)
        m_currentMovingVec += m_stepLeft;
    else if(key == m_key_forMove_RIGHT)
        m_currentMovingVec += m_stepRight;
}
void KeyController::receive_key_toggle(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink300);
}
void KeyController::reveive_key_goesDown(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink300);
}
void KeyController::reveive_key_goesUp(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink300);
}



// From KeyController
void KeyController::setKey_forMove_UP(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink400);
    if(m_key_forMove_UP != -1)
        removeEvent(m_key_forMove_UP_event);
    m_key_forMove_UP = key;
    m_key_forMove_UP_event = new Event(m_key_forMove_UP);
    this->addEvent(m_key_forMove_UP_event);
}
void KeyController::setKey_forMove_LEFT(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink400);
    if(m_key_forMove_LEFT != -1)
        removeEvent(m_key_forMove_LEFT_event);
    m_key_forMove_LEFT = key;
    m_key_forMove_LEFT_event = new Event(m_key_forMove_LEFT);
    this->addEvent(m_key_forMove_LEFT_event);
}
void KeyController::setKey_forMove_DOWN(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink400);
    if(m_key_forMove_DOWN != -1)
        removeEvent(m_key_forMove_DOWN_event);
    m_key_forMove_DOWN = key;
    m_key_forMove_DOWN_event = new Event(m_key_forMove_DOWN);
    this->addEvent(m_key_forMove_DOWN_event);
}
void KeyController::setKey_forMove_RIGHT(const int &key)
{
    EASY_FUNCTION(profiler::colors::Pink400);
    if(m_key_forMove_RIGHT != -1)
        removeEvent(m_key_forMove_RIGHT_event);
    m_key_forMove_RIGHT = key;
    m_key_forMove_RIGHT_event = new Event(m_key_forMove_RIGHT);
    this->addEvent(m_key_forMove_RIGHT_event);
}
void KeyController::setStepSize(const int size)
{
    EASY_FUNCTION(profiler::colors::Pink500);
    m_stepSize = size;

    this->setRotation();
}
int KeyController::getStepSize() const
{
    return m_stepSize;
}


void KeyController::setRotation()
{
    EASY_FUNCTION(profiler::colors::Pink600);
    m_stepUp        = Vector2f(0,-m_stepSize);
    m_stepDown      = Vector2f(0,m_stepSize);
    m_stepLeft      = Vector2f(-m_stepSize,0);
    m_stepRight     = Vector2f(m_stepSize,0);
    Vector2f up     = Vector::getRotated(m_stepUp,m_rotationDeg);
    Vector2f left   = Vector::getRotated(m_stepLeft,m_rotationDeg);
    Vector2f down   = Vector::getRotated(m_stepDown,m_rotationDeg);
    Vector2f right  = Vector::getRotated(m_stepRight,m_rotationDeg);

    m_stepUp        = up;
    m_stepLeft      = left;
    m_stepDown      = down;
    m_stepRight     = right;
}
