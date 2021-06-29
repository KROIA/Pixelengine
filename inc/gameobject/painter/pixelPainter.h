#ifndef PIXELPAINTER_H
#define PIXELPAINTER_H

#include "painter.h"
#include "SFML/Graphics/Rect.hpp"

class PixelPainter  : public Painter
{
    public:
        PixelPainter();
        ~PixelPainter();

        virtual void draw(PixelDisplay &display);

        virtual void setPixel(const vector<Pixel> &pixelList);
        virtual void addPixel(unsigned int x, unsigned int y, Color color);
        virtual void addPixel(const Pixel &pixel);
        virtual void addPixel(const vector<Pixel> &pixelList);
        virtual const Pixel getPixel(const Vector2i&pixelPos) const;
        virtual const Pixel getPixel(unsigned int x,unsigned int y) const;
        virtual void setPixelColor(const Vector2i&pixelPos, const Color &color);
        virtual void setPixelColor(unsigned int x,unsigned int y, const Color &color);

        virtual void update();
        virtual void resize(Vector2u size);
        virtual void clear();

    protected:
        virtual void internalUpdateOrigin();


        virtual void internalSetPixel(const vector<Pixel> &pixelList);
        virtual void internalAddPixel(const Pixel &pixel);
        virtual void internalAddPixel(const vector<Pixel> &pixelList);

    private:





};
#endif // PIXELPAINTER_H
