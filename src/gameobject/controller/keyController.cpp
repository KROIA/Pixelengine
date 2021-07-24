#include "keyController.h"

KeyController::KeyController()
    :   Controller()
{
    m_key_forMove_UP_event      = nullptr;
    m_key_forMove_LEFT_event    = nullptr;
    m_key_forMove_DOWN_event    = nullptr;
    m_key_forMove_RIGHT_event   = nullptr;
}
KeyController::KeyController(const KeyController &other)
    :   Controller()
{
    *this = other;
}

KeyController::~KeyController()
{
    if(m_key_forMove_UP_event) delete m_key_forMove_UP_event;
    if(m_key_forMove_LEFT_event) delete m_key_forMove_LEFT_event;
    if(m_key_forMove_DOWN_event) delete m_key_forMove_DOWN_event;
    if(m_key_forMove_RIGHT_event) delete m_key_forMove_RIGHT_event;
}
const KeyController &KeyController::operator=(const KeyController &other)
{
    Controller::operator=(other);

    copyKeyFromOther(this->m_key_forMove_UP_event,      other.m_key_forMove_UP_event);
    copyKeyFromOther(this->m_key_forMove_LEFT_event,    other.m_key_forMove_LEFT_event);
    copyKeyFromOther(this->m_key_forMove_DOWN_event,    other.m_key_forMove_DOWN_event);
    copyKeyFromOther(this->m_key_forMove_RIGHT_event,   other.m_key_forMove_RIGHT_event);

    this->m_stepSize                    = other.m_stepSize;
    this->m_stepUp                      = other.m_stepUp;
    this->m_stepLeft                    = other.m_stepLeft;
    this->m_stepDown                    = other.m_stepDown;
    this->m_stepRight                   = other.m_stepRight;
    return *this;
}

// From KeyController
void KeyController::setKey_forMove_UP(int key)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink400);
    if(!m_key_forMove_UP_event)
    {
        m_key_forMove_UP_event = new KeyEvent();
        SIGNAL_SUBSCRIBE(KeyEvent,m_key_forMove_UP_event)
        //m_key_forMove_UP_event->subscribe_KeyEventSignal(this);
        this->addEvent(m_key_forMove_UP_event);
    }
    m_key_forMove_UP_event->setKey(key);
}
void KeyController::setKey_forMove_LEFT(int key)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink400);
    if(!m_key_forMove_LEFT_event)
    {
        m_key_forMove_LEFT_event = new KeyEvent();
        SIGNAL_SUBSCRIBE(KeyEvent,m_key_forMove_LEFT_event)
        //m_key_forMove_LEFT_event->subscribe_KeyEventSignal(this);
        this->addEvent(m_key_forMove_LEFT_event);
    }
    m_key_forMove_LEFT_event->setKey(key);
}
void KeyController::setKey_forMove_DOWN(int key)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink400);
    if(!m_key_forMove_DOWN_event)
    {
        m_key_forMove_DOWN_event = new KeyEvent();
        SIGNAL_SUBSCRIBE(KeyEvent,m_key_forMove_DOWN_event)
        //m_key_forMove_DOWN_event->subscribe_KeyEventSignal(this);
        this->addEvent(m_key_forMove_DOWN_event);
    }
    m_key_forMove_DOWN_event->setKey(key);
}
void KeyController::setKey_forMove_RIGHT(int key)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink400);    
    if(!m_key_forMove_RIGHT_event)
    {
        m_key_forMove_RIGHT_event = new KeyEvent();
        SIGNAL_SUBSCRIBE(KeyEvent,m_key_forMove_RIGHT_event)
        //m_key_forMove_RIGHT_event->subscribe_KeyEventSignal(this);
        this->addEvent(m_key_forMove_RIGHT_event);
    }
    m_key_forMove_RIGHT_event->setKey(key);
}
void KeyController::setStepSize(float size)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink500);
    Controller::setStepSize(size);

    m_stepUp        = Vector2f(0,-m_stepSize);
    m_stepDown      = Vector2f(0,m_stepSize);
    m_stepLeft      = Vector2f(-m_stepSize,0);
    m_stepRight     = Vector2f(m_stepSize,0);
}
float KeyController::getStepSize() const
{
    return m_stepSize;
}
SLOT_DEFINITION(KeyController,KeyEvent,isPressed)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink600);
    if(sender == m_key_forMove_UP_event)
    {
        Controller::move(m_stepUp);
        return;
    }
    if(sender == m_key_forMove_LEFT_event)
    {
        Controller::move(m_stepLeft);
        return;
    }
    if(sender == m_key_forMove_DOWN_event)
    {
        Controller::move(m_stepDown);
        return;
    }
    if(sender == m_key_forMove_RIGHT_event)
    {
        Controller::move(m_stepRight);
    }
}

SLOT_DEFINITION(KeyController,KeyEvent,toggle)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink600);
}

SLOT_DEFINITION(KeyController,KeyEvent,sinking)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink600);
}

SLOT_DEFINITION(KeyController,KeyEvent,rising)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink600);
}
/*void KeyController::isPressed(KeyEvent *sender,int value)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink600);
    if(sender == m_key_forMove_UP_event)
    {
        Controller::move(m_stepUp);
        return;
    }
    if(sender == m_key_forMove_LEFT_event)
    {
        Controller::move(m_stepLeft);
        return;
    }
    if(sender == m_key_forMove_DOWN_event)
    {
        Controller::move(m_stepDown);
        return;
    }
    if(sender == m_key_forMove_RIGHT_event)
    {
        Controller::move(m_stepRight);
    }
}*/
/*
void KeyController::toggle(KeyEvent *sender)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink600);
}
void KeyController::sinking(KeyEvent *sender)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink600);
}
void KeyController::rising(KeyEvent *sender)
{
    CONTROLLER_FUNCTION(profiler::colors::Pink600);
}
*/
void KeyController::copyKeyFromOther(KeyEvent *thisKey, KeyEvent *otherKey)
{
    if(otherKey && thisKey)
    {
        *thisKey = *otherKey;
    }else if(otherKey && !thisKey)
    {
        thisKey = new KeyEvent(*otherKey);
    }else if(!otherKey && thisKey)
    {
        delete thisKey;
    }
}
