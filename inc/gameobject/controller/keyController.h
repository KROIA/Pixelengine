#ifndef KEYCONTROLLER_H
#define KEYCONTROLLER_H

#include "controller.h"
#include "vector.h"

class KeyController     :   public Controller
{
    public:
        KeyController();
        KeyController(const KeyController &other);

        virtual ~KeyController();
        virtual const KeyController &operator=(const KeyController &other);

        // From Controller
        virtual void checkEvent();
        virtual void tick();
        virtual void setRotation(const double &deg);
        virtual double getRotation() const;
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();

        // Receiver Signal from Eventhandler
        virtual void receive_key_isPressed(const int &key);
        virtual void receive_key_toggle(const int &key);
        virtual void reveive_key_goesDown(const int &key);
        virtual void reveive_key_goesUp(const int &key);

        // From KeyController
        virtual void setKey_forMove_UP(const int &key);
        virtual void setKey_forMove_LEFT(const int &key);
        virtual void setKey_forMove_DOWN(const int &key);
        virtual void setKey_forMove_RIGHT(const int &key);

        virtual void setStepSize(const unsigned int size);
        virtual const unsigned int &getStepSize() const;



    protected:
        int m_key_forMove_UP;
        Event* m_key_forMove_UP_event;
        int m_key_forMove_LEFT;
        Event* m_key_forMove_LEFT_event;
        int m_key_forMove_DOWN;
        Event* m_key_forMove_DOWN_event;
        int m_key_forMove_RIGHT;
        Event* m_key_forMove_RIGHT_event;

        Vector m_currentMovingVec;

        unsigned int m_stepSize;
        Point m_stepUp;
        Point m_stepLeft;
        Point m_stepDown;
        Point m_stepRight;
    private:

        void setRotation();

};
#endif // KEYCONTROLLER_H
