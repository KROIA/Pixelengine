#include "painter.h"

Painter::Painter()
    :   LayerItem()
{
    setPos(0,0);
    setVisibility(true);
}
Painter::Painter(const Painter &other)
    :   LayerItem(other)
{
    this->m_pixelList  = other.m_pixelList;
    this->m_isVisible  = other.m_isVisible;
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
    if(m_pos == pos)
        return;
    //qDebug() << "Painter::setPos: "<<pos.getX()<<"\t"<<pos.getY();
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
    if(m_pos.getX() == x && m_pos.getY() == y)
        return;
    this->setPos(Point(x,y));
}
void Painter::setX(const int &x)
{
    if(m_pos.getX() == x)
        return;
    int deltaX = x - m_pos.getX();
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        m_pixelList[i].setX(m_pixelList[i].getX() + deltaX);
    }
    LayerItem::setX(x);
}
void Painter::setY(const int &y)
{
    if(m_pos.getX() == y)
        return;
    int deltaY = y - m_pos.getY();
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        m_pixelList[i].setY(m_pixelList[i].getY() + deltaY);
    }
    LayerItem::setY(y);
}
void Painter::setVisibility(const bool &isVisible)
{
    m_isVisible = isVisible;
}
const bool &Painter::isVisible() const
{
    return m_isVisible;
}