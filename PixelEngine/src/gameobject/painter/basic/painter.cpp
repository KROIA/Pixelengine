#include "painter.h"

Painter::Painter()
    :   LayerItem()
{
    setPos(0,0);
    setVisibility(true);
    m_rotationRad = 0;
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
    this->m_rotationRad= other.m_rotationRad;
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
    if(LayerItem::getPos() == pos)
        return;
    Point deltaPos(pos.getX() - LayerItem::getX(),
                   pos.getY() - LayerItem::getY());
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        m_pixelList[i].setX(m_pixelList[i].getX() + deltaPos.getX());
        m_pixelList[i].setY(m_pixelList[i].getY() + deltaPos.getY());
    }
    LayerItem::setPos(pos);
}
void Painter::setPos(const int &x, const int &y)
{
    if(LayerItem::getX() == x && LayerItem::getY() == y)
        return;
    this->setPos(Point(x,y));
}
void Painter::setX(const int &x)
{
    if(LayerItem::getX() == x)
        return;
    int deltaX = x - LayerItem::getX();
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        m_pixelList[i].setX(m_pixelList[i].getX() + deltaX);
    }
    LayerItem::setX(x);
}
void Painter::setY(const int &y)
{
    if(LayerItem::getX() == y)
        return;
    int deltaY = y - LayerItem::getY();
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
void Painter::rotate(const double &rad)
{
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        GeneralVector<double> vec(m_pixelList[i].getPos().getX(),m_pixelList[i].getPos().getY());
        GeneralVector<double> offset(this->getPos().getX(),this->getPos().getY());
        offset.moveX(-0.5);
        offset.moveY(-0.5);
        vec -= offset;
        PointF newPos = (GeneralVector<double>::rotate(vec,rad)+offset).toPoint();
        m_pixelList[i].setPos(round(newPos.getX()),round(newPos.getY()));
    }
    m_rotationRad += rad;
    m_rotationRad = double(int(m_rotationRad*1000) % int(2*M_PI *1000))/1000.f;

}
void Painter::setRotation(const double &deg)
{
    this->rotate((deg*M_PI/180.f) - m_rotationRad);
}
double Painter::getRotation() const
{
    return m_rotationRad * 180.f/M_PI;
}
void Painter::rotate_90()
{
    this->rotate(M_PI_2);
}
void Painter::rotate_180()
{
    this->rotate(M_PI);
}
void Painter::rotate_270()
{
    this->rotate(-M_PI_2);
}
