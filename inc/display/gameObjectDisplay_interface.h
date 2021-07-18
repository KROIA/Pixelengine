#ifndef GAMEOBJECTDISPLAY_INTERFACE_H
#define GAMEOBJECTDISPLAY_INTERFACE_H

#include "base.h"
#include "rect.h"
#include "painter.h"
#include "pixel.h"

class GameObjectDisplay_Interface
{
    public:
        GameObjectDisplay_Interface(){}

        virtual void setPixel(const Vector2u &pos, const Color &color)= 0;
        virtual void setPixel(const Pixel &pixel)= 0;
        virtual void setPixel(const vector<Pixel> &pixelList)= 0;
        virtual void zoomViewAt(sf::Vector2i pixel, float zoom)= 0;
        virtual void setView(const RectF &frame)= 0;
        virtual void setCameraZoom(float zoom) = 0;
        virtual void setCameraPos(const Vector2f &pos) = 0;
        virtual const Vector2u &getWindowSize() const= 0;
        virtual const Vector2u &getMapSize() const= 0;
        virtual void subscribePainter(Painter *painter) = 0;
        virtual void unsubscribePainter(Painter *painter) = 0;
};
#endif // GAMEOBJECTDISPLAY_INTERFACE_H
