#include "event.h"

Event::Event()
{
    m_isPressed = false;
}
/*Event(Type)
{

}*/
Event::Event(const int &key)
{
    this->setKey(key);
}
Event::Event(const Event &other)
{
    this->m_key         = other.m_key;
    this->m_isPressed   = other.m_isPressed;
    this->m_isToggled   = other.m_isToggled;
    this->m_isSinking   = other.m_isSinking;
    this->m_isRising    = other.m_isRising;
}
Event::~Event()
{

}

void Event::checkEvent()
{
    m_isToggled = false;
    m_isRising  = false;

    unsigned int state = GetAsyncKeyState(m_key);
    if(state == 1 && !m_isPressed)// Key was toggled
    {
        m_isToggled = true;
    } else if(state > 1)          // Key Is Pressed now
    {
        if(!m_isPressed && !m_isSinking) // Key wasn't Pressed before -> sinking
        {
            m_isSinking = true;
        }else if(m_isSinking)
        {
            m_isSinking = false;
            m_isPressed = true;
        }
    }else if(state == 0 && m_isPressed) // Key is no longer pressed -> rising
    {
        m_isPressed = false;
        m_isRising  = true;
    }
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
