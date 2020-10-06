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

        // From Controller
        virtual void checkEvent();
        virtual void tick(const Point &direction);
        //virtual void move(const int &x,const int &y);

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
        size_t m_key_forMove_UP_index;
        int m_key_forMove_LEFT;
        size_t m_key_forMove_LEFT_index;
        int m_key_forMove_DOWN;
        size_t m_key_forMove_DOWN_index;
        int m_key_forMove_RIGHT;
        size_t m_key_forMove_RIGHT_index;

        Vector m_currentMovingVec;

        unsigned int m_stepSize;
    private:

};
#endif // KEYCONTROLLER_H
