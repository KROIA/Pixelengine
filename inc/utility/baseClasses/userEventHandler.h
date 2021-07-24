/*#ifndef USEREVENTHANDLER_H
#define USEREVENTHANDLER_H

#include "base.h"

#include "keyEvent.h"
#include "signalSubscriber.h"

// Signals for User Events
class UserEventSignal
{
    public:
        UserEventSignal(){}

        virtual void eventAdded(UserEventHandler *sender,  KeyEvent *e) = 0;
        virtual void eventRemoved(UserEventHandler *sender,  KeyEvent *e) = 0;
    protected:

};
// Vector of Signals
class UserEventSubscriberList    : public SubscriberList<UserEventSignal>
{
    public:
        UserEventSubscriberList();

        virtual void eventAdded(UserEventHandler *sender,  KeyEvent *e);
        virtual void eventRemoved(UserEventHandler *sender,  KeyEvent *e);
    protected:

};

class UserEventHandler
{
    public:
        UserEventHandler();
        UserEventHandler(const UserEventHandler &other);
        virtual ~UserEventHandler();
        virtual UserEventHandler &operator=(const UserEventHandler &other);

        virtual void checkEvent(float deltaTime);
        virtual bool hasEventsToCheck() const;

        virtual size_t addEvent(KeyEvent *e);            // Adds a KeyEvent and returns the index in the list.
        virtual KeyEvent *getEvent(const size_t &index) const; // returns the KeyEvent at the index of the list.
        virtual void removeEvent(KeyEvent *e);

        // Receiver Signal
        virtual void receive_key_isPressed(const int &key);
        virtual void receive_key_toggle(const int &key);
        virtual void receive_key_goesDown(const int &key);
        virtual void receive_key_goesUp(const int &key);

        // Signals
        virtual void subscribe_UserEventSignal(UserEventSignal *subscriber);
        virtual void unsubscribe_UserEventSignal(UserEventSignal *subscriber);
        virtual void unsubscribeAll_UserEventSignal();
    protected:

    private:
      vector<KeyEvent*>  m_eventList;
      KeyEvent m_dummyEvent;
      bool  m_hasEventsToCheck;
      UserEventSubscriberList m_userEventSubscriberList;
};
#endif // EVENTHANDLER_H
*/
