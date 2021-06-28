#include "pixel.h"

Pixel::Pixel()
    :   Color(0,0,0,255), LayerItem(0,0)
{}
Pixel::Pixel(const Color &color)
    :   Color(color), LayerItem(0,0)
{}
Pixel::Pixel(const Vector2i &pos, const Color &color)
    :   Color(color), LayerItem(pos)
{}
Pixel::Pixel(const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha)
    :   Color(red,green,blue,alpha), LayerItem(0,0)
{}
Pixel::Pixel(const int &x, const int & y,
             const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha)
    :   Color(red,green,blue,alpha), LayerItem(x,y)
{}
Pixel::Pixel(const Pixel &other)
    :   Color(other), LayerItem(other)
{}
Pixel::~Pixel()
{}
const Pixel &Pixel::operator=(const Pixel &other)
{
    Color::operator=(other);
    LayerItem::operator=(other);
    return *this;
}
void Pixel::setColor(const Color &color)
{
    Color::operator=(color);
}

