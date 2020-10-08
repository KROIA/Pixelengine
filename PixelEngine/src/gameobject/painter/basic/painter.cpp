#include "painter.h"

Painter::Painter()
    :   LayerItem()
{
    setPos(0,0);
    setVisibility(true);
}
Painter::Painter(const Painter &other)
    :   LayerItem()
{
    *this = other;
}

Painter::~Painter()
{

}
const Painter &Painter::operator=(const Painter &other)
{
    LayerItem::operator=(other);
    this->m_pixelList  = other.m_pixelList;
    this->m_isVisible  = other.m_isVisible;
    return *this;
}
void Painter::reserve(const size_t amount)
{
    m_pixelList.reserve(amount);
}
void Painter::addPixel(const Pixel &pixel)
{
    m_pixelList.push_back(pixel);
}
const Pixel &Painter::getPixel(const size_t &index) const
{
    return m_pixelList[index];
}
size_t Painter::getPixelAmount() const
{
    return m_pixelList.size();
}
void Painter::setPixelColor(const size_t &index, const Color &color)
{
    m_pixelList[index].setColor(color);
}
void Painter::setPixelColor(const Color &color)
{
    for(size_t i=0; i<m_pixelList.size(); i++)
        m_pixelList[i].setColor(color);
}

void Painter::draw(PixelDisplay &display)
{
    if(m_isVisible)
        display.setPixel(m_pixelList);
}

void Painter::setPos(const Point &pos)
{
    if(m_pos == pos)
        return;
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
void Painter::erasePixel(const size_t &index)
{
    m_pixelList.erase(m_pixelList.begin()+index);
}
void Painter::clear()
{
    m_pixelList.clear();
}

