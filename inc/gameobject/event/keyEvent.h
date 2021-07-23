#ifndef KEYEVENT_H
#define KEYEVENT_H
#include "base.h"

#include "event.h"
#include <windows.h>
#include "keyboard.h"
#include "signalEmitter.h"
/*
// Signals for Controller
class KeyEventSignal
{
        typedef KeyEvent _BASECLASS_;
    public:
        KeyEventSignal(){}
        virtual void isPressed(KeyEvent *sender) = 0;
        virtual void toggle(KeyEvent *sender) = 0;
        virtual void sinking(KeyEvent *sender) = 0;
        virtual void rising(KeyEvent *sender) = 0;
};

// Vector of Signals
class KeyEventSubscriberList: public SubscriberList<KeyEventSignal>
{
        typedef KeyEvent _BASECLASS_;
    public:
        KeyEventSubscriberList() : SubscriberList<KeyEventSignal>(){};

        void isPressed(KeyEvent *sender);
        void toggle(KeyEvent *sender);
        void sinking(KeyEvent *sender);
        void rising(KeyEvent *sender);
};
*/


SIGNAL_DEF(KeyEvent)
    SIGNAL_FUNC(isPressed)
    SIGNAL_FUNC(toggle)
    SIGNAL_FUNC(sinking)
    SIGNAL_FUNC(rising)
SIGNAL_DEF_END

SIGNAL_EMITTER_DEF(KeyEvent)
    SIGNAL_EMITTER_FUNC(isPressed)
    SIGNAL_EMITTER_FUNC(toggle)
    SIGNAL_EMITTER_FUNC(sinking)
    SIGNAL_EMITTER_FUNC(rising)
SIGNAL_EMITTER_DEF_END


class KeyEvent  :   public Event
{
    SIGNAL_EMITTER(KeyEvent)
    public:
        KeyEvent();
        KeyEvent(int key);
        KeyEvent(const KeyEvent &other);
        ~KeyEvent();
        KeyEvent &operator=(const KeyEvent &other);


        void checkEvent(float deltaTime);

        void setKey(int key);
        const int &getKey() const;

        const bool &isPressed() const;
        const bool &isToggled() const;
        const bool &isSinking() const;
        const bool &isRising()  const;

        void resetCounter();
        void resetCounter_isPressed();
        void resetCounter_isToggled();
        void resetCounter_isSinking();
        void resetCounter_isRising();

        const unsigned int &getCounter_isPressed() const;
        const unsigned int &getCounter_isToggled() const;
        const unsigned int &getCounter_isSinking() const;
        const unsigned int &getCounter_isRising()  const;

        /*void subscribe_KeyEventSignal(KeyEventSignal *subscriber);
        void unsubscribe_KeyEventSignal(KeyEventSignal *subscriber);
        void unsubscribeAll_KeyEventSignal();*/

    protected:
        int m_key;
        bool m_keyState;
        bool m_keyLastState1;
        bool m_keyLastState2;


        bool m_isPressed;
        bool m_isToggled;
        bool m_isSinking;
        bool m_isRising;

        unsigned int m_isPressed_counter;
        unsigned int m_isToggled_counter;
        unsigned int m_isSinking_counter;
        unsigned int m_isRising_counter;

        //KeyEventSubscriberList m_keyEventSubscriberList;

    private:
        void constructor(const int &key);
};
#endif // KEYEVENT_H
