#include "painter.h"

Painter::Painter()
{
    setPos(0,0);
}
Painter::Painter(const Painter &other)
{
    this->m_bodyPos    = other.m_bodyPos;
    this->m_pixelList  = other.m_pixelList;
}

Painter::~Painter()
{

}

void Painter::draw(PixelDisplay &display)
{
    display.setPixel(m_pixelList);
}

void Painter::setPos(const Point &pos)
{
    Point deltaPos(pos.getX() - m_bodyPos.getX(),
                   pos.getY() - m_bodyPos.getY());
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        m_pixelList[i].setX(m_pixelList[i].getX() + deltaPos.getX());
        m_pixelList[i].setY(m_pixelList[i].getY() + deltaPos.getY());
    }
    m_bodyPos = pos;
}
void Painter::setPos(const int &x, const int &y)
{
    this->setPos(Point(x,y));
}
const Point &Painter::getPos() const
{
    return m_bodyPos;
}
