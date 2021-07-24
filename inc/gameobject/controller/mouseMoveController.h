#ifndef MOUSEMOVECONTROLLER_H
#define MOUSEMOVECONTROLLER_H

#include "controller.h"
#include "mouseMoveEvent.h"
#include "signalEmitter.h"

class MouseMoveController   :   public Controller, SIGNAL_RECEIVES(MouseMoveEvent)
{
    public:
        MouseMoveController();
        MouseMoveController(const MouseMoveController &other);
        ~MouseMoveController();
        const MouseMoveController &operator=(const MouseMoveController &other);

        void checkEvent(float deltaTime);

        void setClipToCoursor(bool enable);
        bool getClipToCoursor() const;

        void setDeltaFactor(float factor);// Defines how strong the distance between the object and the coursor will be added to the moving vector.
        bool getDeltaFactor() const;

        void setRotation(float deg);
        void rotate(float deg);
        void rotate_90();
        void rotate_180();
        void rotate_270();


    protected:
       SLOT_DECLARATION(MouseMoveEvent,moved)
       MouseMoveEvent *m_mouseMoveEvent;
       bool  m_clipToCoursor;
       float m_dumpingFactor;
    private:

};
#endif // MOUSEMOVECONTROLLER_H
