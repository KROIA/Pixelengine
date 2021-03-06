#include "pixel.h"

Pixel::Pixel()
    :   Color()
{
    PointU(0,0);
}
Pixel::Pixel(const Color &color)
    :   Color(color)
{
    PointU(0,0);
}
Pixel::Pixel(const Point &pos, const Color &color)
    :   Color(color), LayerItem(pos)
{

}
Pixel::Pixel(const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha)
    :   Color(red,green,blue,alpha)
{
    PointU(0,0);
}
Pixel::Pixel(const unsigned int &x, const unsigned int & y,
             const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha)
    :   Color(red,green,blue,alpha), LayerItem(Point(x,y))
{

}
Pixel::Pixel(const Pixel &other)
    :   Color(other), LayerItem(other)
{

}
Pixel::~Pixel()
{

}
const Pixel &Pixel::operator=(const Pixel &other)
{
    Color::operator=(other);
    LayerItem::operator=(other);
    return *this;
}
void Pixel::setColor(const Color &color)
{
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
}

