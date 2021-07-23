#ifndef DISPLAYINTERFACE_H
#define DISPLAYINTERFACE_H

#include "base.h"
#include "rect.h"
#include "painter.h"
#include "pixel.h"

class DisplayInterface
{
    public:
        DisplayInterface(){}

        virtual void setPixel(const Vector2u &pos, const Color &color)= 0;
        virtual void setPixel(const Pixel &pixel)= 0;
        virtual void setPixel(const vector<Pixel> &pixelList)= 0;
        virtual void zoomViewAt(sf::Vector2i pixel, float zoom)= 0;
        virtual void setView(const RectF &frame)= 0;
        virtual void setCameraZoom(float zoom) = 0;
        virtual void setCameraPos(const Vector2f &pos) = 0;
        virtual const Vector2u &getWindowSize() const= 0;
        virtual Vector2f getViewSize() const = 0;
        virtual sf::View getView() const = 0;
        virtual const Vector2u &getMapSize() const= 0;
        virtual void subscribePainter(Painter *painter) = 0;
        virtual void unsubscribePainter(Painter *painter) = 0;
        virtual void subscribePainter(vector<Painter *> painterList) = 0;
        virtual void unsubscribePainter(vector<Painter *> painterList) = 0;
        virtual Vector2i getWindowPos() const = 0;
        virtual const RectF &getRenderFrame() const = 0;
        virtual Vector2f mapPixelToCoords(const Vector2i &point) const = 0;

};
#endif // DISPLAYINTERFACE_H
