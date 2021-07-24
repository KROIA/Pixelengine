#ifndef MOUSEMOVEEVENT_H
#define MOUSEMOVEEVENT_H

#include "event.h"
#include "signalEmitter.h"
#include "displayInterface.h"

SIGNAL_DEF(MouseMoveEvent)
    SIGNAL_FUNC(moved)
SIGNAL_DEF_END

SIGNAL_EMITTER_DEF(MouseMoveEvent)
    SIGNAL_EMITTER_FUNC(moved)
SIGNAL_EMITTER_DEF_END

class MouseMoveEvent    :   public Event
{
    SIGNAL_EMITTER(MouseMoveEvent)
    public:
        MouseMoveEvent();
        ~MouseMoveEvent();

        static void setDisplayInterface(DisplayInterface *display);

        void checkEvent(float deltaTime);
        Vector2i getPixelPos() const; // Position of pixel on the screen
        Vector2i getPixelPosRelative() const; // Position of Pixel on the Screen relative to the window
        Vector2f getPos() const; // Position of the gameWorld


    protected:
        Vector2i m_currentPosAbsolut;
        Vector2i m_lastPosAbsolut;

        Vector2i m_pixelPosRelative;
        Vector2f m_worldPos;
    private:
        static DisplayInterface *m_displayInterface;
};
#endif // MOUSEMOVEEVENT_H
