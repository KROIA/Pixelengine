#include "buttonEvent.h"

ButtonEvent::ButtonEvent()
    :   Event()
{
    m_buttonState         = false;
    m_buttonLastState1    = false;
    m_buttonLastState2    = false;


    m_isPressed           = false;
    m_isToggled           = false;
    m_isSinking           = false;
    m_isRising            = false;

    m_isPressed_counter   = 0;
    m_isToggled_counter   = 0;
    m_isSinking_counter   = 0;
    m_isRising_counter    = 0;
}

ButtonEvent::ButtonEvent(const ButtonEvent &other)
    :   Event(other)
{
    *this = other;
}
ButtonEvent::~ButtonEvent()
{

}
ButtonEvent &ButtonEvent::operator=(const ButtonEvent &other)
{
    this->m_buttonState         = other.m_buttonState;
    this->m_buttonLastState1    = other.m_buttonLastState1;
    this->m_buttonLastState2    = other.m_buttonLastState2;
    this->m_isPressed           = other.m_isPressed;
    this->m_isToggled           = other.m_isToggled;
    this->m_isSinking           = other.m_isSinking;
    this->m_isRising            = other.m_isRising;

    this->m_isPressed_counter   = other.m_isPressed_counter;
    this->m_isToggled_counter   = other.m_isToggled_counter;
    this->m_isSinking_counter   = other.m_isSinking_counter;
    this->m_isRising_counter    = other.m_isRising_counter;
    return *this;
}

void ButtonEvent::checkEvent(float deltaTime)
{
    EVENT_FUNCTION(profiler::colors::Indigo50);

    m_isToggled = false;
    m_isRising  = false;
    m_isSinking = false;

    readCurrentButtonState();

    if(m_buttonState)
    {
        if(m_buttonLastState1)
        {
            // is pressed
            if(!m_isPressed)
                m_isPressed_counter++;
            m_isPressed = true;
            buttonPressed();
        }
        else
        {
            // falling edge
            m_isSinking = true;
            m_isSinking_counter++;
            buttonSinking();
        }
    }
    else if(m_buttonLastState1)
    {
        // rising edge
        m_isRising  = true;
        m_isPressed = false;
        m_isRising_counter++;
        buttonRising();
        if(!m_buttonLastState2)
        {
            // After 3 zycles of this checkEvent function,
            // if it was a toggle event.
            m_isToggled = true;
            m_isToggled_counter++;
            buttonToggled();
        }
    }

    m_buttonLastState2 = m_buttonLastState1;
    m_buttonLastState1 = m_buttonState;
}



const bool &ButtonEvent::isPressed() const
{
    return m_isPressed;
}
const bool &ButtonEvent::isToggled() const
{
    return m_isToggled;
}
const bool &ButtonEvent::isSinking() const
{
    return m_isSinking;
}
const bool &ButtonEvent::isRising() const
{
    return m_isRising;
}

void ButtonEvent::resetCounter()
{
    resetCounter_isPressed();
    resetCounter_isToggled();
    resetCounter_isSinking();
    resetCounter_isRising();
}
void ButtonEvent::resetCounter_isPressed()
{
    m_isPressed_counter = 0;
}
void ButtonEvent::resetCounter_isToggled()
{
    m_isToggled_counter = 0;
}
void ButtonEvent::resetCounter_isSinking()
{
    m_isSinking_counter = 0;
}
void ButtonEvent::resetCounter_isRising()
{
    m_isRising_counter = 0;
}

const unsigned int &ButtonEvent::getCounter_isPressed() const
{
    return m_isPressed_counter;
}
const unsigned int &ButtonEvent::getCounter_isToggled() const
{
    return m_isToggled_counter;
}
const unsigned int &ButtonEvent::getCounter_isSinking() const
{
    return m_isSinking_counter;
}
const unsigned int &ButtonEvent::getCounter_isRising()  const
{
    return m_isRising_counter;
}
