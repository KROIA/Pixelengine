#ifndef PIXEL_H
#define PIXEL_H

#include <SFML/Graphics/Color.hpp>
#include "layeritem.h"

#include "profiler.h"

using sf::Color;
using sf::Uint8;


class Pixel : public Color, public LayerItem
{
    public:
        Pixel();
        Pixel(const Color &color);
        Pixel(const Vector2i &pos, const Color &color);
        Pixel(const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha = 255);
        Pixel(const int &x, const int & y,
              const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha = 255);
        Pixel(const Pixel &other);

        virtual ~Pixel();
        virtual const Pixel &operator=(const Pixel &other);

        virtual void setColor(const Color &color);

    protected:

    private:
};
#endif // PIXEL_H
