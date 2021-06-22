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
    m_currentMovingVec.set(0,0);
    Controller::checkEvent();
    this->move(m_currentMovingVec);
}
void KeyController::tick()
{
    EASY_FUNCTION(profiler::colors::Pink100);
    Controller::tick();
}
void KeyController::setRotation(const double &deg)
{
    EASY_FUNCTION(profiler::colors::Pink200);
    Controller::setRotation(deg);
    this->setRotation();
}
double KeyController::getRotation() const
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
        m_currentMovingVec.move(m_stepUp);
    else if(key == m_key_forMove_DOWN)
        m_currentMovingVec.move(m_stepDown);
    else if(key == m_key_forMove_LEFT)
        m_currentMovingVec.move(m_stepLeft);
    else if(key == m_key_forMove_RIGHT)
        m_currentMovingVec.move(m_stepRight);
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
void KeyController::setStepSize(const unsigned int size)
{
    EASY_FUNCTION(profiler::colors::Pink500);
    m_stepSize = size;

    this->setRotation();
}
const unsigned int &KeyController::getStepSize() const
{
    return m_stepSize;
}


void KeyController::setRotation()
{
    EASY_FUNCTION(profiler::colors::Pink600);
    double rotRad = double(m_rotationDeg)*M_PI/180;
    m_stepUp.set(0,-m_stepSize);
    m_stepDown.set(0,m_stepSize);
    m_stepLeft.set(-m_stepSize,0);
    m_stepRight.set(m_stepSize,0);
    VectorF up    = VectorF::rotate(VectorF(m_stepUp.getX(),m_stepUp.getY()),rotRad);
    VectorF left  = VectorF::rotate(VectorF(m_stepLeft.getX(),m_stepLeft.getY()),rotRad);
    VectorF down  = VectorF::rotate(VectorF(m_stepDown.getX(),m_stepDown.getY()),rotRad);
    VectorF right = VectorF::rotate(VectorF(m_stepRight.getX(),m_stepRight.getY()),rotRad);

    m_stepUp.set(round(up.getX()),round(up.getY()));
    m_stepLeft.set(round(left.getX()),round(left.getY()));
    m_stepDown.set(round(down.getX()),round(down.getY()));
    m_stepRight.set(round(right.getX()),round(right.getY()));
}
