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
        virtual EventHandler &operator=(const EventHandler &other);

        virtual void checkEvent();

        virtual size_t addEvent(const Event &e);            // Adds a Event and returns the index in the list.
        virtual const Event &getEvent(const size_t &index); // returns the Event at the index of the list.
        virtual void removeEvent(const size_t &index);

        // Receiver Signal
        virtual void receive_key_isPressed(const int &key);
        virtual void receive_key_toggle(const int &key);
        virtual void reveive_key_goesDown(const int &key);
        virtual void reveive_key_goesUp(const int &key);
    protected:

    private:
      vector<Event>  m_eventList;
      Event m_dummyEvent;

};
#endif // EVENTHANDLER_H
