#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <windows.h>
#include "event.h"
#include <vector>

#include <QDebug>

using std::vector;

class EventHandler
{
    public:
        EventHandler();
        EventHandler(const EventHandler &other);
        virtual ~EventHandler();

        virtual void checkEvent();

        virtual void addEvent(const Event &e);

        // Receiver Signal
        virtual void receive_key_isPressed(const int &key);
        virtual void receive_key_toggle(const int &key);
        virtual void reveive_key_goesDown(const int &key);
        virtual void reveive_key_goesUp(const int &key);
    protected:

    private:
      vector<Event>  m_eventList;

};
#endif // EVENTHANDLER_H
