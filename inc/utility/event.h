#ifndef EVENT_H
#define EVENT_H
#include "base.h"

#include <windows.h>
#include "keyboard.h"


class Event
{
    public:
        Event();
        Event(const int &key);
        Event(const Event &other);
        virtual ~Event();
        virtual Event &operator=(const Event &other);


        virtual void checkEvent();

        virtual void setKey(const int &key);
        virtual const int &getKey() const;

        virtual const bool &isPressed() const;
        virtual const bool &isToggled() const;
        virtual const bool &isSinking() const;
        virtual const bool &isRising()  const;

        virtual void resetCounter();
        virtual void resetCounter_isPressed();
        virtual void resetCounter_isToggled();
        virtual void resetCounter_isSinking();
        virtual void resetCounter_isRising();

        virtual const unsigned int &getCounter_isPressed() const;
        virtual const unsigned int &getCounter_isToggled() const;
        virtual const unsigned int &getCounter_isSinking() const;
        virtual const unsigned int &getCounter_isRising()  const;

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

    private:
};
#endif // EVENT_H
