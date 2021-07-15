#include "userEventHandler.h"

UserEventHandler::UserEventHandler()
{
    m_hasEventsToCheck = false;
}
UserEventHandler::UserEventHandler(const UserEventHandler &other)
{
    *this = other;
}
UserEventHandler::~UserEventHandler()
{

}
UserEventHandler &UserEventHandler::operator=(const UserEventHandler &other)
{
    this->m_eventList           = other.m_eventList;
    this->m_hasEventsToCheck    = other.m_hasEventsToCheck;
    return *this;
}

void UserEventHandler::checkEvent()
{
    // Check for all events
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        m_eventList[i]->checkEvent();
    }

    // Execute event receiver functuin
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        if(m_eventList[i]->isSinking())
            this->receive_key_goesDown(m_eventList[i]->getKey());
        if(m_eventList[i]->isPressed())
            this->receive_key_isPressed(m_eventList[i]->getKey());
        if(m_eventList[i]->isToggled())
            this->receive_key_toggle(m_eventList[i]->getKey());
        if(m_eventList[i]->isRising())
            this->receive_key_goesUp(m_eventList[i]->getKey());
    }
}
bool UserEventHandler::hasEventsToCheck() const
{
    return m_hasEventsToCheck;
}

size_t UserEventHandler::addEvent(Event *e)
{
    m_eventList.push_back(e);
    m_hasEventsToCheck = true;
    m_userEventSubscriberList.eventAdded(this,e);
    return m_eventList.size()-1;
}
Event *UserEventHandler::getEvent(const size_t &index) const
{
    if(index >= m_eventList.size())
    {
        qDebug() << "const Event &UserEventHandler::getEvent(const size_t &["<<index<<"]): out of range";
        return nullptr;
    }
    return m_eventList[index];
}
void UserEventHandler::removeEvent(Event* e)
{
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        if(m_eventList[i] == e)
        {
            delete m_eventList[i];
            m_eventList.erase(m_eventList.begin()+i);
        }
    }

    if(m_eventList.size() == 0)
        m_hasEventsToCheck = false;
    m_userEventSubscriberList.eventRemoved(this,e);
}

void UserEventHandler::receive_key_isPressed(const int &key)
{
    qDebug() << "Key: "<<key<<"\receive_key_isPressed";
}
void UserEventHandler::receive_key_toggle(const int &key)
{
    qDebug() << "Key: "<<key<<"\receive_key_toggle";
}
void UserEventHandler::receive_key_goesDown(const int &key)
{
    qDebug() << "Key: "<<key<<"\receive_key_goesDown";
}
void UserEventHandler::receive_key_goesUp(const int &key)
{
    qDebug() << "Key: "<<key<<"\receive_key_goesUp";
}
// Signals
void UserEventHandler::subscribeUserEventSignal(UserEventSignal *subscriber)
{
    if(subscriber == nullptr)
        return;
    for(size_t i=0; i<m_userEventSubscriberList.size(); i++)
    {
        if(m_userEventSubscriberList[i] == subscriber)
        {
            return;
        }
    }
    m_userEventSubscriberList.push_back(subscriber);
}
void UserEventHandler::unsubscribeUserEventSignal(UserEventSignal *subscriber)
{
    for(size_t i=0; i<m_userEventSubscriberList.size(); i++)
    {
        if(m_userEventSubscriberList[i] == subscriber)
        {
            m_userEventSubscriberList.erase(m_userEventSubscriberList.begin()+i);
            return;
        }
    }
}
void UserEventHandler::unsubscribeAllUserEventSignal()
{
    m_userEventSubscriberList.clear();
}
