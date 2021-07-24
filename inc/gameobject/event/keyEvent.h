#ifndef KEYEVENT_H
#define KEYEVENT_H
#include "base.h"

#include "buttonEvent.h"
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


class KeyEvent  :   public ButtonEvent
{
    SIGNAL_EMITTER(KeyEvent)
    public:
        KeyEvent();
        KeyEvent(int key);
        KeyEvent(const KeyEvent &other);
        ~KeyEvent();
        KeyEvent &operator=(const KeyEvent &other);

        void setKey(int key);
        const int &getKey() const;

    protected:
        void readCurrentButtonState();
        void buttonSinking();
        void buttonPressed();
        void buttonToggled();
        void buttonRising();

        int m_key;

    private:
        void constructor(const int &key);
};
#endif // KEYEVENT_H
