#ifndef KEYCONTROLLER_H
#define KEYCONTROLLER_H

#include "base.h"
#include "controller.h"
#include "mathFunctions.h"



class KeyController     :   public Controller, SIGNAL_RECEIVES(KeyEvent)
{
    public:
        KeyController();
        KeyController(const KeyController &other);

        virtual ~KeyController();
        virtual const KeyController &operator=(const KeyController &other);

        // From KeyController
        void setKey_forMove_UP(int key);
        void setKey_forMove_LEFT(int key);
        void setKey_forMove_DOWN(int key);
        void setKey_forMove_RIGHT(int key);

        void setStepSize(float size);
        float getStepSize() const;



    protected:
        // Signals from KeyEvent
        SLOT_DECLARATION(KeyEvent,isPressed)
        SLOT_DECLARATION(KeyEvent,toggle)
        SLOT_DECLARATION(KeyEvent,sinking)
        SLOT_DECLARATION(KeyEvent,rising)
        /*virtual void isPressed(KeyEvent *sender,int value);
        virtual void toggle(KeyEvent *sender);
        virtual void sinking(KeyEvent *sender);
        virtual void rising(KeyEvent *sender);*/

        KeyEvent* m_key_forMove_UP_event;
        KeyEvent* m_key_forMove_LEFT_event;
        KeyEvent* m_key_forMove_DOWN_event;
        KeyEvent* m_key_forMove_RIGHT_event;

        float m_stepSize;

        Vector2f m_stepUp;
        Vector2f m_stepLeft;
        Vector2f m_stepDown;
        Vector2f m_stepRight;
    private:

       // void setRotation();
        static void copyKeyFromOther(KeyEvent *thisKey, KeyEvent *otherKey);

};
#endif // KEYCONTROLLER_H
