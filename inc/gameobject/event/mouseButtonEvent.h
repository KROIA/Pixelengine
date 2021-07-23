#ifndef MOUSEBUTTONEVENT_H
#define MOUSEBUTTONEVENT_H

#include "base.h"
#include "buttonEvent.h"
#include "signalEmitter.h"

SIGNAL_DEF(MouseButtonEvent)
    SIGNAL_FUNC(isPressed)
    SIGNAL_FUNC(toggle)
    SIGNAL_FUNC(sinking)
    SIGNAL_FUNC(rising)
SIGNAL_DEF_END

SIGNAL_EMITTER_DEF(MouseButtonEvent)
    SIGNAL_EMITTER_FUNC(isPressed)
    SIGNAL_EMITTER_FUNC(toggle)
    SIGNAL_EMITTER_FUNC(sinking)
    SIGNAL_EMITTER_FUNC(rising)
SIGNAL_EMITTER_DEF_END

class MouseButtonEvent  :   public ButtonEvent
{
    SIGNAL_EMITTER(MouseButtonEvent)
    public:
        MouseButtonEvent();
        MouseButtonEvent(sf::Mouse::Button button);
        MouseButtonEvent(const MouseButtonEvent &other);
        ~MouseButtonEvent();
        MouseButtonEvent &operator=(const MouseButtonEvent &other);

        void setButton(sf::Mouse::Button button);
        enum sf::Mouse::Button getButton() const;

    protected:
        void readCurrentButtonState();
        void buttonSinking();
        void buttonPressed();
        void buttonToggled();
        void buttonRising();

        sf::Mouse::Button m_button;

    private:
        void constructor(sf::Mouse::Button button);
};
#endif // MOUSEBUTTONEVENT_H
