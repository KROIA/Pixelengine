#ifndef PIXEL_H
#define PIXEL_H

#include <SFML/Graphics/Color.hpp>
#include "layeritem.h"

using sf::Color;
using sf::Uint8;


class Pixel : public Color, public LayerItem
{
    public:
        Pixel();
        Pixel(const Color &color);
        Pixel(const Point &pos, const Color &color);
        Pixel(const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha = 255);
        Pixel(const unsigned int &x, const unsigned int & y,
              const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha = 255);
        Pixel(const Pixel &other);

        virtual ~Pixel();


    protected:

    private:
        //PointU m_pos;
};
#endif // PIXEL_H