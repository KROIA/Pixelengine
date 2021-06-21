#ifndef EVENT_H
#define EVENT_H

#include <windows.h>
#include <QDebug>
#include "keyboard.h"

#include "profiler.h"

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


    protected:
        int m_key;
        bool m_keyState;
        bool m_keyLastState1;
        bool m_keyLastState2;


        bool m_isPressed;
        bool m_isToggled;
        bool m_isSinking;
        bool m_isRising;

    private:
};
#endif // EVENT_H
