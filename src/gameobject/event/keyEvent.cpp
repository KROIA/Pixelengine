#include "keyEvent.h"

KeyEvent::KeyEvent()
    :   ButtonEvent()
{
    constructor(-1);
}

KeyEvent::KeyEvent(int key)
    :   ButtonEvent()
{
    constructor(key);
}
KeyEvent::KeyEvent(const KeyEvent &other)
    :   ButtonEvent(other)
{
    *this = other;
}
void KeyEvent::constructor(const int &key)
{
    m_key                 = key;
}
KeyEvent::~KeyEvent()
{

}
KeyEvent &KeyEvent::operator=(const KeyEvent &other)
{
    this->m_key                 = other.m_key;
    ButtonEvent::operator=(other);
    return *this;
}

void KeyEvent::setKey(int key)
{
    m_key = key;
}
const int &KeyEvent::getKey() const
{
    return m_key;
}

void KeyEvent::readCurrentButtonState()
{
    unsigned int state = GetAsyncKeyState(m_key);
    // If state is == 1, button isn't pressed any more.
    // If state is >  1, ( Bit 0x8000 is == 1) button is pressed.
    if(state <= 1)
    {
        m_buttonState = false;
    }
    else
    {
        m_buttonState = true;
    }
}
void KeyEvent::buttonSinking()
{
    SIGNAL_EMIT(KeyEvent,sinking)
}
void KeyEvent::buttonPressed()
{
    SIGNAL_EMIT(KeyEvent,isPressed)
}
void KeyEvent::buttonToggled()
{
    SIGNAL_EMIT(KeyEvent,toggle)
}
void KeyEvent::buttonRising()
{
    SIGNAL_EMIT(KeyEvent,rising)
}

