#include "eventhandler.h"

EventHandler::EventHandler()
{

}
EventHandler::EventHandler(const EventHandler &other)
{
    *this = other;
}
EventHandler::~EventHandler()
{

}
EventHandler &EventHandler::operator=(const EventHandler &other)
{
    this->m_eventList   = other.m_eventList;
    return *this;
}

void EventHandler::checkEvent()
{
    // Check for all events
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        m_eventList[i].checkEvent();
    }

    // Execute event receiver functuin
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        if(m_eventList[i].isSinking())
            this->reveive_key_goesDown(m_eventList[i].getKey());
        if(m_eventList[i].isPressed())
            this->receive_key_isPressed(m_eventList[i].getKey());
        if(m_eventList[i].isToggled())
            this->receive_key_toggle(m_eventList[i].getKey());
        if(m_eventList[i].isRising())
            this->reveive_key_goesUp(m_eventList[i].getKey());
    }
}

size_t EventHandler::addEvent(const Event &e)
{
    m_eventList.push_back(e);
    return m_eventList.size();
}
const Event &EventHandler::getEvent(const size_t &index)
{
    if(index >= m_eventList.size())
    {
        qDebug() << "const Event &EventHandler::getEvent(const size_t &["<<index<<"]): out of range";
        return m_dummyEvent;
    }
    return m_eventList[index];
}
void EventHandler::removeEvent(const size_t &index)
{
    if(index >= m_eventList.size())
    {
        qDebug() << "const Event &EventHandler::removeEvent(const size_t &["<<index<<"]): out of range";
    }
    m_eventList.erase(m_eventList.begin()+index);
}

void EventHandler::receive_key_isPressed(const int &key)
{
    qDebug() << "Key: "<<key<<"\receive_key_isPressed";
}
void EventHandler::receive_key_toggle(const int &key)
{
    qDebug() << "Key: "<<key<<"\receive_key_toggle";
}
void EventHandler::reveive_key_goesDown(const int &key)
{
    qDebug() << "Key: "<<key<<"\reveive_key_goesDown";
}
void EventHandler::reveive_key_goesUp(const int &key)
{
    qDebug() << "Key: "<<key<<"\reveive_key_goesUp";
}
