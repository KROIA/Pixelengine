#ifndef EVENT_H
#define EVENT_H

#include <windows.h>
#include <QDebug>
#include "keyboard.h"
//#include "eventhandler.h"



class Event
{
    public:
        /*enum Type{
            KeyEvent = 0,
            MouseEvent = 1
        };*/
        Event();
        //Event(Type);
        Event(const int &key);
        Event(const Event &other);
        virtual ~Event();

        virtual void checkEvent();

        //virtual void setEventReceiver(EventHandler *handler);
        virtual void setKey(const int &key);
        virtual const int &getKey() const;

        virtual const bool &isPressed() const;
        virtual const bool &isToggled() const;
        virtual const bool &isSinking() const;
        virtual const bool &isRising()  const;


    protected:
        //Type m_eventType;
        int m_key;

        //EventHandler *m_handler;

        bool m_isPressed;
        bool m_isToggled;
        bool m_isSinking;
        bool m_isRising;

    private:
};
#endif // EVENT_H
