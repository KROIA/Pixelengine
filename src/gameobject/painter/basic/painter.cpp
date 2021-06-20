#include "painter.h"

Painter::Painter()
    :   LayerItem()
{
    m_const_dummy_pixel.setPos(0,0);
    m_const_dummy_pixel.setColor(Color(0,0,0,0));
    setPos(0,0);
    setVisibility(true);
    setFrameVisibility(false);
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
    this->m_frameVisible = other.m_frameVisible;
    this->m_rotationRad= other.m_rotationRad;
    return *this;
}
void Painter::reserve(const size_t amount)
{
    m_pixelList.reserve(amount);
}
void Painter::addPixel(const Pixel &pixel)
{
    internalAddPixel(pixel);
    updateFrame();
}
void Painter::addPixel(const vector<Pixel> &pixelList)
{
    for(const Pixel &p : pixelList)
        internalAddPixel(p);
    updateFrame();
}
const Pixel &Painter::getPixel(const size_t &index) const
{
    return m_pixelList[index];
}
const Pixel &Painter::getPixel(const Point &pixelPos) const
{
    for(const Pixel &p : m_pixelList)
    {
        if(p.getPos() == pixelPos)
            return p;
    }
    return m_const_dummy_pixel;
}
const Pixel &Painter::getPixel(int x, int y) const
{
    return getPixel(Point(x,y));
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
Rect Painter::getFrame() const
{
    return m_frame;
}
void Painter::setFrameVisibility(bool isVisible)
{
    m_frameVisible = isVisible;
}
bool Painter::isFrameVisible()
{
    return m_frameVisible;
}
void Painter::setPixelColor(const Point &pixelPos, const Color &color)
{
    for(Pixel &p : m_pixelList)
    {
        if(p.getPos() == pixelPos)
            p.setColor(color);
    }
}
void Painter::setPixelColor(int x, int y, const Color &color)
{
    setPixelColor(Point(x,y),color);
}

void Painter::draw(PixelDisplay &display)
{
    if(m_isVisible)
    {
        display.setPixel(m_pixelList);
        if(m_frameVisible)
        {
            Color frameColor(255,0,0,255);
            Pixel p1(m_frame.getCornerPoint_TL(),frameColor);
            Pixel p2(m_frame.getCornerPoint_TR(),frameColor);
            Pixel p3(m_frame.getCornerPoint_BL(),frameColor);
            Pixel p4(m_frame.getCornerPoint_BR(),frameColor);
            display.setPixel(p1);
            display.setPixel(p2);
            display.setPixel(p3);
            display.setPixel(p4);
        }
    }
}

void Painter::setPos(const Point &pos)
{
    if(LayerItem::getPos() == pos)
        return;
    Point deltaPos(pos.getX() - LayerItem::getX(),
                   pos.getY() - LayerItem::getY());
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        m_pixelList[i].setPos(Vector(m_pixelList[i].getPos()) + Vector(deltaPos));
   //     m_pixelList[i].setX(m_pixelList[i].getX() + deltaPos.getX());
   //     m_pixelList[i].setY(m_pixelList[i].getY() + deltaPos.getY());
    }
    m_frame.setPos(Vector(m_frame.getPos()) + Vector(deltaPos));
    LayerItem::setPos(pos);
}
void Painter::setPos(int x, int y)
{
    if(LayerItem::getX() == x && LayerItem::getY() == y)
        return;
    this->setPos(Point(x,y));
}
void Painter::setX(int x)
{
    if(LayerItem::getX() == x)
        return;
    int deltaX = x - LayerItem::getX();
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        m_pixelList[i].setX(m_pixelList[i].getX() + deltaX);
    }
    m_frame.setX(m_frame.getPos().getX() + deltaX);
    LayerItem::setX(x);
}
void Painter::setY(int y)
{
    if(LayerItem::getX() == y)
        return;
    int deltaY = y - LayerItem::getY();
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        m_pixelList[i].setY(m_pixelList[i].getY() + deltaY);
    }
    m_frame.setY(m_frame.getPos().getY() + deltaY);
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
    updateFrame();
}
void Painter::erasePixel(const Point &pixelPos)
{
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        if(m_pixelList[i].getPos() == pixelPos)
            erasePixel(i);
    }
}
void Painter::erasePixel(int x, int y)
{
    erasePixel(Point(x,y));
}
void Painter::clear()
{
    m_pixelList.clear();
    m_frame.setPos(0,0);
    m_frame.setSize(0,0);
}
void Painter::rotate(const PointF &rotPoint,const double &rad)
{
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        GeneralVector<double> vec(m_pixelList[i].getPos().getX(),m_pixelList[i].getPos().getY());
        PointF newPos = (GeneralVector<double>::rotate(vec,rotPoint,rad)).toPoint();
        m_pixelList[i].setPos(round(newPos.getX()),round(newPos.getY()));
    }
    m_rotationRad += rad;
    m_rotationRad = double(int(m_rotationRad*1000) % int(2*M_PI *1000))/1000.f;
    updateFrame();
}

double Painter::getRotation() const
{
    return m_rotationRad * 180.f/M_PI;
}
void Painter::setRotation(const double &deg)
{
    this->rotate(PointF(this->getX(),this->getY()),(deg*M_PI/180.f) - m_rotationRad);
}
void Painter::rotate_90()
{
    this->rotate(PointF(this->getX(),this->getY()),M_PI_2);
}
void Painter::rotate_180()
{
    this->rotate(PointF(this->getX(),this->getY()),M_PI);
}
void Painter::rotate_270()
{
    this->rotate(PointF(this->getX(),this->getY()),-M_PI_2);
}
void Painter::setRotation(const PointF &rotationPoint,const double &deg)
{
    this->rotate(rotationPoint,(deg*M_PI/180.f) - m_rotationRad);
}
void Painter::rotate_90(const PointF &rotationPoint)
{
    this->rotate(rotationPoint,M_PI_2);
}
void Painter::rotate_180(const PointF &rotationPoint)
{
    this->rotate(rotationPoint,M_PI);
}
void Painter::rotate_270(const PointF &rotationPoint)
{
    this->rotate(rotationPoint,-M_PI_2);
}

void Painter::setTexture(const Texture *texture)
{
    this->clear();
    Point oldPos = this->getPos();
    this->setPos(Point(0,0));
    this->internalAddPixel(texture->getPixels());
    this->m_frame = texture->getFrame();
    this->setPos(oldPos);
}
void Painter::internalAddPixel(const Pixel &pixel)
{
    m_pixelList.push_back(pixel);
}
void Painter::internalAddPixel(const vector<Pixel> &pixelList)
{
    for(const Pixel &p : pixelList)
        internalAddPixel(p);
}
void Painter::updateFrame()
{
    vector<Rect> pixelRects(m_pixelList.size(),Rect(Point(0,0),Point(1,1)));
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        pixelRects[i].setPos(m_pixelList[i].getPos());
    }
    m_frame = Rect::getFrame(pixelRects);
}
