#include "userEventHandler.h"

UserEventHandler::UserEventHandler()
{

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
    this->m_eventList   = other.m_eventList;
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
            this->reveive_key_goesDown(m_eventList[i]->getKey());
        if(m_eventList[i]->isPressed())
            this->receive_key_isPressed(m_eventList[i]->getKey());
        if(m_eventList[i]->isToggled())
            this->receive_key_toggle(m_eventList[i]->getKey());
        if(m_eventList[i]->isRising())
            this->reveive_key_goesUp(m_eventList[i]->getKey());
    }
}

size_t UserEventHandler::addEvent(Event *e)
{
    m_eventList.push_back(e);
    return m_eventList.size()-1;
}
Event *UserEventHandler::getEvent(const size_t &index)
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
    /*if(index >= m_eventList.size())
    {
        qDebug() << "const Event &UserEventHandler::removeEvent(const size_t &["<<index<<"]): out of range";
    }
    m_eventList.erase(m_eventList.begin()+index);*/
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        if(m_eventList[i] == e)
        {
            delete m_eventList[i];
            m_eventList.erase(m_eventList.begin()+i);
        }
    }
}

void UserEventHandler::receive_key_isPressed(const int &key)
{
    qDebug() << "Key: "<<key<<"\receive_key_isPressed";
}
void UserEventHandler::receive_key_toggle(const int &key)
{
    qDebug() << "Key: "<<key<<"\receive_key_toggle";
}
void UserEventHandler::reveive_key_goesDown(const int &key)
{
    qDebug() << "Key: "<<key<<"\reveive_key_goesDown";
}
void UserEventHandler::reveive_key_goesUp(const int &key)
{
    qDebug() << "Key: "<<key<<"\reveive_key_goesUp";
}
