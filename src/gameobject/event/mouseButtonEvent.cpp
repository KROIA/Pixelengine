#include "mouseButtonEvent.h"

MouseButtonEvent::MouseButtonEvent()
    :   ButtonEvent()
{
    constructor(sf::Mouse::Button::ButtonCount);
}

MouseButtonEvent::MouseButtonEvent(sf::Mouse::Button button)
    :   ButtonEvent()
{
    constructor(button);
}
MouseButtonEvent::MouseButtonEvent(const MouseButtonEvent &other)
    :   ButtonEvent(other)
{
    *this = other;
}
void MouseButtonEvent::constructor(sf::Mouse::Button button)
{
    m_button    = button;
}
MouseButtonEvent::~MouseButtonEvent()
{

}
MouseButtonEvent &MouseButtonEvent::operator=(const MouseButtonEvent &other)
{
    this->m_button  = other.m_button;
    ButtonEvent::operator=(other);
    return *this;
}

void MouseButtonEvent::setButton(sf::Mouse::Button button)
{
    m_button    = button;
}
enum sf::Mouse::Button MouseButtonEvent::getButton() const
{
    return m_button;
}

void MouseButtonEvent::readCurrentButtonState()
{
    if(m_button == sf::Mouse::Button::ButtonCount)
        m_buttonState = false;
    else
        m_buttonState = sf::Mouse::isButtonPressed(m_button);
}
void MouseButtonEvent::buttonSinking()
{
    SIGNAL_EMIT(MouseButtonEvent,sinking)
}
void MouseButtonEvent::buttonPressed()
{
    SIGNAL_EMIT(MouseButtonEvent,isPressed)
}
void MouseButtonEvent::buttonToggled()
{
    SIGNAL_EMIT(MouseButtonEvent,toggle)
}
void MouseButtonEvent::buttonRising()
{
    SIGNAL_EMIT(MouseButtonEvent,rising)
}

