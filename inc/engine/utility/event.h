#ifndef EVENT_H
#define EVENT_H

#include <windows.h>
#include <QDebug>





class Event
{
    public:
        enum Type{
            KeyEvent = 0,
            MouseEvent = 1
        };
        Event(Type);
        Event(const Event &other);
        virtual ~Event();




    protected:
        Type m_eventType;
        int m_key;

    private:
};
#endif // EVENT_H
