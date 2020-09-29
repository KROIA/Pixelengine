#include "painter.h"

Painter::Painter()
    :   LayerItem()
{
    setPos(0,0);
}
Painter::Painter(const Painter &other)
    :   LayerItem(other)
{
    this->m_pixelList  = other.m_pixelList;
}

Painter::~Painter()
{

}
void Painter::addPixel(const Pixel &pixel)
{
    m_pixelList.push_back(pixel);
}

void Painter::draw(PixelDisplay &display)
{
    display.setPixel(m_pixelList);
}

void Painter::setPos(const Point &pos)
{
    Point deltaPos(pos.getX() - m_pos.getX(),
                   pos.getY() - m_pos.getY());
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        m_pixelList[i].setX(m_pixelList[i].getX() + deltaPos.getX());
        m_pixelList[i].setY(m_pixelList[i].getY() + deltaPos.getY());
    }
    LayerItem::setPos(pos);
}
void Painter::setPos(const int &x, const int &y)
{
    this->setPos(Point(x,y));
}
