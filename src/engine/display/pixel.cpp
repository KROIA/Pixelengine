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
    //this->setPos(pos);
}
Pixel::Pixel(const Uint8 &red, const Uint8 &green, const Uint8 &blue, const Uint8 &alpha)
    :   Color(red,green,blue,alpha)
{
    PointU(0,0);
    //this->m_pos = PointU(0,0);
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


