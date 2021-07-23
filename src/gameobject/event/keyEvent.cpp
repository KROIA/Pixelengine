#include "keyEvent.h"
/*void KeyEventSubscriberList::isPressed(KeyEvent *sender)
{
    SIGNAL_EMIT_INTERN(isPressed,sender);
}
void KeyEventSubscriberList::toggle(KeyEvent *sender)
{
    SIGNAL_EMIT_INTERN(toggle,sender);
}
void KeyEventSubscriberList::sinking(KeyEvent *sender)
{
    SIGNAL_EMIT_INTERN(sinking,sender);
}
void KeyEventSubscriberList::rising(KeyEvent *sender)
{
    SIGNAL_EMIT_INTERN(rising,sender);
}

*/
KeyEvent::KeyEvent()
    :   Event()
{
    constructor(-1);
}

KeyEvent::KeyEvent(int key)
    :   Event()
{
    constructor(key);
}
KeyEvent::KeyEvent(const KeyEvent &other)
    :   Event(other)
{
    *this = other;
}
void KeyEvent::constructor(const int &key)
{
    m_key                 = key;
    m_keyState            = false;
    m_keyLastState1       = false;
    m_keyLastState2       = false;


    m_isPressed           = false;
    m_isToggled           = false;
    m_isSinking           = false;
    m_isRising            = false;

    m_isPressed_counter   = 0;
    m_isToggled_counter   = 0;
    m_isSinking_counter   = 0;
    m_isRising_counter    = 0;
}
KeyEvent::~KeyEvent()
{

}
KeyEvent &KeyEvent::operator=(const KeyEvent &other)
{
    this->m_key                 = other.m_key;
    this->m_keyState            = other.m_keyState;
    this->m_keyLastState1       = other.m_keyLastState1;
    this->m_keyLastState2       = other.m_keyLastState2;
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

void KeyEvent::checkEvent(float deltaTime)
{
    EVENT_FUNCTION(profiler::colors::Indigo50);
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
            if(!m_isPressed)
                m_isPressed_counter++;
            m_isPressed = true;
            SIGNAL_EMIT(KeyEvent,isPressed)
            //m_keyEventSubscriberList.isPressed(this);

        }
        else
        {
            // falling edge
            m_isSinking = true;
            m_isSinking_counter++;
            SIGNAL_EMIT(KeyEvent,sinking)
            //m_keyEventSubscriberList.sinking(this);
        }
    }
    else if(m_keyLastState1)
    {
        // rising edge
        m_isRising  = true;
        m_isPressed = false;
        m_isRising_counter++;
        SIGNAL_EMIT(KeyEvent,rising)
        //m_keyEventSubscriberList.rising(this);
        if(!m_keyLastState2)
        {
            // After 3 zycles of this checkEvent function,
            // if it was a toggle event.
            m_isToggled = true;
            m_isToggled_counter++;
            SIGNAL_EMIT(KeyEvent,toggle)
            //m_keyEventSubscriberList.toggle(this);
        }
    }

    m_keyLastState2 = m_keyLastState1;
    m_keyLastState1 = m_keyState;
}

void KeyEvent::setKey(int key)
{
    m_key = key;
}
const int &KeyEvent::getKey() const
{
    return m_key;
}

const bool &KeyEvent::isPressed() const
{
    return m_isPressed;
}
const bool &KeyEvent::isToggled() const
{
    return m_isToggled;
}
const bool &KeyEvent::isSinking() const
{
    return m_isSinking;
}
const bool &KeyEvent::isRising() const
{
    return m_isRising;
}

void KeyEvent::resetCounter()
{
    resetCounter_isPressed();
    resetCounter_isToggled();
    resetCounter_isSinking();
    resetCounter_isRising();
}
void KeyEvent::resetCounter_isPressed()
{
    m_isPressed_counter = 0;
}
void KeyEvent::resetCounter_isToggled()
{
    m_isToggled_counter = 0;
}
void KeyEvent::resetCounter_isSinking()
{
    m_isSinking_counter = 0;
}
void KeyEvent::resetCounter_isRising()
{
    m_isRising_counter = 0;
}

const unsigned int &KeyEvent::getCounter_isPressed() const
{
    return m_isPressed_counter;
}
const unsigned int &KeyEvent::getCounter_isToggled() const
{
    return m_isToggled_counter;
}
const unsigned int &KeyEvent::getCounter_isSinking() const
{
    return m_isSinking_counter;
}
const unsigned int &KeyEvent::getCounter_isRising()  const
{
    return m_isRising_counter;
}
// Signals
/*void KeyEvent::subscribe_KeyEventSignal(KeyEventSignal *subscriber)
{
    m_KeyEventSubscriberList.insert(subscriber);
}
void KeyEvent::unsubscribe_KeyEventSignal(KeyEventSignal *subscriber)
{
    m_KeyEventSubscriberList.erase(subscriber);
}
void KeyEvent::unsubscribeAll_KeyEventSignal()
{
    m_KeyEventSubscriberList.clear();
}
*/
