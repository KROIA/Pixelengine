#ifndef USEREVENTHANDLER_H
#define USEREVENTHANDLER_H

#include "base.h"

#include "event.h"
#include "signalSubscriber.h"

using std::vector;

class UserEventHandler
{
    public:
        UserEventHandler();
        UserEventHandler(const UserEventHandler &other);
        virtual ~UserEventHandler();
        virtual UserEventHandler &operator=(const UserEventHandler &other);

        virtual void checkEvent();
        virtual bool hasEventsToCheck() const;

        virtual size_t addEvent(Event *e);            // Adds a Event and returns the index in the list.
        virtual Event *getEvent(const size_t &index) const; // returns the Event at the index of the list.
        virtual void removeEvent(Event *e);

        // Receiver Signal
        virtual void receive_key_isPressed(const int &key);
        virtual void receive_key_toggle(const int &key);
        virtual void receive_key_goesDown(const int &key);
        virtual void receive_key_goesUp(const int &key);

        // Signals
        virtual void subscribeUserEventSignal(UserEventSignal *subscriber);
        virtual void unsubscribeUserEventSignal(UserEventSignal *subscriber);
        virtual void unsubscribeAllUserEventSignal();
    protected:

    private:
      vector<Event*>  m_eventList;
      Event m_dummyEvent;
      bool  m_hasEventsToCheck;
      UserEventSubscriberList m_userEventSubscriberList;
};
#endif // EVENTHANDLER_H
