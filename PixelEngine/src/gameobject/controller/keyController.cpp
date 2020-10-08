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
    this->m_key_forMove_UP_index    = other.m_key_forMove_UP_index;
    this->m_key_forMove_LEFT        = other.m_key_forMove_LEFT;
    this->m_key_forMove_LEFT_index  = other.m_key_forMove_LEFT_index;
    this->m_key_forMove_DOWN        = other.m_key_forMove_DOWN;
    this->m_key_forMove_DOWN_index  = other.m_key_forMove_DOWN_index;
    this->m_key_forMove_RIGHT       = other.m_key_forMove_RIGHT;
    this->m_key_forMove_RIGHT_index = other.m_key_forMove_RIGHT_index;

    this->m_currentMovingVec        = other.m_currentMovingVec;

    this->m_stepSize                = other.m_stepSize;
    return *this;
}
// From Controller
void KeyController::checkEvent()
{
    // KeyController::tick gets called 2 times per GameTick,
    // so only handle events once per GameTick
    m_currentMovingVec.set(0,0);
    Controller::checkEvent();
    this->move(m_currentMovingVec);
}
void KeyController::tick(const Point &direction)
{
    Controller::tick(direction);
}
/*void KeyController::move(const int &x,const int &y)
{

}*/
// Receiver Signal from Eventhandler
void KeyController::receive_key_isPressed(const int &key)
{
    if(key == m_key_forMove_UP)
        m_currentMovingVec.moveY(-m_stepSize);
    else if(key == m_key_forMove_DOWN)
        m_currentMovingVec.moveY(m_stepSize);
    else if(key == m_key_forMove_LEFT)
        m_currentMovingVec.moveX(-m_stepSize);
    else if(key == m_key_forMove_RIGHT)
        m_currentMovingVec.moveX(m_stepSize);

    //qDebug() << "KeyController Key: "<<key<<"\receive_key_isPressed";
}
void KeyController::receive_key_toggle(const int &key)
{
    //qDebug() << "Key: "<<key<<"\receive_key_toggle";
}
void KeyController::reveive_key_goesDown(const int &key)
{
    //qDebug() << "Key: "<<key<<"\reveive_key_goesDown";
}
void KeyController::reveive_key_goesUp(const int &key)
{
    //qDebug() << "Key: "<<key<<"\reveive_key_goesUp";
}


// From KeyController
void KeyController::setKey_forMove_UP(const int &key)
{
    if(m_key_forMove_UP != -1)
        removeEvent(m_key_forMove_UP_index);
    m_key_forMove_UP = key;
    m_key_forMove_UP_index = this->addEvent(Event(m_key_forMove_UP));
}
void KeyController::setKey_forMove_LEFT(const int &key)
{
    if(m_key_forMove_LEFT != -1)
        removeEvent(m_key_forMove_LEFT_index);
    m_key_forMove_LEFT = key;
    m_key_forMove_LEFT_index = this->addEvent(Event(m_key_forMove_LEFT));
}
void KeyController::setKey_forMove_DOWN(const int &key)
{
    if(m_key_forMove_DOWN != -1)
        removeEvent(m_key_forMove_DOWN_index);
    m_key_forMove_DOWN = key;
    m_key_forMove_DOWN_index = this->addEvent(Event(m_key_forMove_DOWN));
}
void KeyController::setKey_forMove_RIGHT(const int &key)
{
    if(m_key_forMove_RIGHT != -1)
        removeEvent(m_key_forMove_RIGHT_index);
    m_key_forMove_RIGHT = key;
    m_key_forMove_RIGHT_index = this->addEvent(Event(m_key_forMove_RIGHT));
}
void KeyController::setStepSize(const unsigned int size)
{
    m_stepSize = size;
}
const unsigned int &KeyController::getStepSize() const
{
    return m_stepSize;
}
