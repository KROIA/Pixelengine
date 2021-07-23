#ifndef BUTTONEVENT_H
#define BUTTONEVENT_H

#include "base.h"
#include "event.h"
#include "signalEmitter.h"

class ButtonEvent   :   public Event
{
    public:
        ButtonEvent();
        ButtonEvent(const ButtonEvent &other);
        ~ButtonEvent();
        ButtonEvent &operator=(const ButtonEvent &other);


        virtual void checkEvent(float deltaTime);

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

    protected:
        virtual void readCurrentButtonState() = 0;
        virtual void buttonSinking() = 0;
        virtual void buttonPressed() = 0;
        virtual void buttonToggled() = 0;
        virtual void buttonRising()  = 0;

        bool m_buttonState;
        bool m_buttonLastState1;
        bool m_buttonLastState2;


        bool m_isPressed;
        bool m_isToggled;
        bool m_isSinking;
        bool m_isRising;

        unsigned int m_isPressed_counter;
        unsigned int m_isToggled_counter;
        unsigned int m_isSinking_counter;
        unsigned int m_isRising_counter;

    private:
};
#endif // BUTTONEVENT_H
