#ifndef PIXEL_H
#define PIXEL_H

#include "base.h"
#include "layeritem.h"


using sf::Color;
using sf::Uint8;
using sf::Vector2u;


class Pixel : public Color, public LayerItem
{
    public:
        Pixel();
        Pixel(const Color &color);
        Pixel(const Vector2u &pos, const Color &color);
        Pixel(const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha = 255);
        Pixel(const unsigned int &x, const unsigned int & y,
              const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha = 255);
        Pixel(const Pixel &other);

        virtual ~Pixel();
        virtual const Pixel &operator=(const Pixel &other);

        virtual void setColor(const Color &color);
        virtual const Color &getColor();

    protected:

    private:
};
#endif // PIXEL_H
