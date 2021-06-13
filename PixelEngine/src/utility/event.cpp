#include "event.h"

Event::Event()
{
    m_isPressed = false;
    m_key       = -1;

    m_keyState = false;
    m_keyLastState1 = false;
    m_keyLastState2 = false;
}
/*Event(Type)
{

}*/
Event::Event(const int &key)
{
    m_isPressed = false;

    m_keyState = false;
    m_keyLastState1 = false;
    m_keyLastState2 = false;
    this->setKey(key);
}
Event::Event(const Event &other)
{
    *this = other;
}
Event::~Event()
{

}
Event &Event::operator=(const Event &other)
{
    this->m_key         = other.m_key;
    this->m_isPressed   = other.m_isPressed;
    this->m_isToggled   = other.m_isToggled;
    this->m_isSinking   = other.m_isSinking;
    this->m_isRising    = other.m_isRising;
    return *this;
}

void Event::checkEvent()
{
    if(m_key < 0)
        return;
    m_isToggled = false;
    m_isRising  = false;
    m_isSinking = false;

    unsigned int state = GetAsyncKeyState(m_key);

    // If state is == 1, key isn't pressed any more.
    // If state is >  1, ( Bit 0x8000 is == 1) key is pressed.
    if(state <= 1)
    {
        m_keyState = false;
    }
    else
    {
        m_keyState = true;
    }

    if(m_keyState)
    {
        if(m_keyLastState1)
        {
            // is pressed
            m_isPressed = true;
        }
        else
        {
            // falling edge
            m_isSinking = true;
        }
    }
    else if(m_keyLastState1)
    {
        // rising edge
        m_isRising  = true;
        m_isPressed = false;
       if(!m_keyLastState2)
       {
           // After 3 zycles of this checkEvent function,
           // if it was a toggle event.
           m_isToggled = true;
       }
    }

    m_keyLastState2 = m_keyLastState1;
    m_keyLastState1 = m_keyState;
}

void Event::setKey(const int &key)
{
    m_key = key;
}
const int &Event::getKey() const
{
    return m_key;
}

const bool &Event::isPressed() const
{
    return m_isPressed;
}
const bool &Event::isToggled() const
{
    return m_isToggled;
}
const bool &Event::isSinking() const
{
    return m_isSinking;
}
const bool &Event::isRising() const
{
    return m_isRising;
}
