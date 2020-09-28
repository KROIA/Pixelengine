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
Pixel::Pixel(const PointU &pos, const Color &color)
    :   Color(color), PointU(pos)
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
    :   Color(red,green,blue,alpha), PointU(x,y)
{

}
Pixel::Pixel(const Pixel &other)
    :   Color(other), PointU(other)
{
    //this->m_pos = other.m_pos;
}
Pixel::~Pixel()
{

}

/*void Pixel::setPos(const PointU &pos)
{
    m_pos = pos;
}
void Pixel::setPos(const unsigned int &x, const unsigned int &y)
{
    m_pos.setX(x);
    m_pos.setY(y);
}
const PointU &Pixel::getPos() const
{
    return m_pos;
}
*/
