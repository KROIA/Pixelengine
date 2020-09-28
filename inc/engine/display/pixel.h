#ifndef PIXEL_H
#define PIXEL_H

#include <SFML/Graphics/Color.hpp>
#include "point.h"

using sf::Color;
using sf::Uint8;


class Pixel : public Color, public PointU
{
    public:
        Pixel();
        Pixel(const Color &color);
        Pixel(const PointU &pos, const Color &color);
        Pixel(const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha = 255);
        Pixel(const unsigned int &x, const unsigned int & y,
              const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha = 255);
        Pixel(const Pixel &other);

        virtual ~Pixel();

        //virtual void setPos(const PointU &pos);
        //virtual void setPos(const unsigned int &x, const unsigned int &y);
        //virtual const PointU &getPos() const;

    protected:

    private:
        //PointU m_pos;
};
#endif // PIXEL_H
