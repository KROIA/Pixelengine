#ifndef EVENT_H
#define EVENT_H

#include "base.h"

class Event
{
    public:
        Event();
        Event(const Event &other);
        virtual ~Event();

        virtual void checkEvent(float deltaTime) = 0;

    protected:

    private:
};
#endif
