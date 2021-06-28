#include "pixelPainter.h"

PixelPainter::PixelPainter()
    :   Painter()
{
   //m_texture->loadFromImage(m_image);
    //m_sprite->setTexture(m_sfTexture);
    m_sprite    = new sf::Sprite;
    m_texture   = new sf::Texture;
    m_image     = new sf::Image;

    //m_sprite->setTexture(*m_texture);
}
PixelPainter::~PixelPainter()
{
    delete m_sprite;
    delete m_texture;
    delete m_image;
}

void PixelPainter::draw(PixelDisplay &display)
{
    EASY_FUNCTION(profiler::colors::Cyan);
    if(m_image->getSize().x == 0 || m_image->getSize().y == 0)
        return;


    m_sprite->setTexture(*m_texture,true);
   // m_sprite->

    Painter::draw(display);
}
void PixelPainter::setPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Cyan);
    internalSetPixel(pixelList);
}
void PixelPainter::addPixel(unsigned int x, unsigned int y, Color color)
{
    EASY_FUNCTION(profiler::colors::Cyan);
    Pixel p;
    p.setPos(x,y);
    p.setColor(color);
    internalAddPixel(p);
}
void PixelPainter::addPixel(const Pixel &pixel)
{
    EASY_FUNCTION(profiler::colors::Cyan);
    internalAddPixel(pixel);
    //updateFrame();
}
void PixelPainter::addPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Cyan);
    for(const Pixel &p : pixelList)
        internalAddPixel(p);
    //updateFrame();
}
/*const Pixel &Painter::getPixel(const size_t &index) const
{
    return m_pixelList[index];
}*/
const Pixel PixelPainter::getPixel(const Point &pixelPos) const
{
    Pixel p;
    p.setPos(pixelPos);
    p.setColor(m_image->getPixel(pixelPos.getX(),pixelPos.getY()));
    return p;
}
const Pixel PixelPainter::getPixel(unsigned int x,unsigned int y) const
{
    Pixel p;
    p.setPos(x,y);
    p.setColor(m_image->getPixel(x,y));
    return p;
}
/*size_t PixelPainter::getPixelAmount() const
{
    return m_pixelList.size();
}*/
/*void PixelPainter::setPixelColor(const size_t &index, const Color &color)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    m_pixelList[index].setColor(color);
}*/
/*void PixelPainter::setPixelColor(const Color &color)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    for(size_t i=0; i<m_pixelList.size(); i++)
        m_pixelList[i].setColor(color);


}*/
void PixelPainter::resize(PointU size)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    Image tmp = *m_image;
    m_image->create(size.getX(),size.getY(),Color(0,0,0,0));
    m_image->copy(tmp,0,0,sf::IntRect(0,0,tmp.getSize().x,tmp.getSize().y),true);
    internalUpdateOrigin();

}
void PixelPainter::clear()
{
    m_image->create(m_image->getSize().x,m_image->getSize().y,Color(0,0,0,0));
}
void PixelPainter::internalUpdateOrigin()
{
    EASY_FUNCTION(profiler::colors::Cyan700);
    switch(m_originType)
    {
        case Origin::topLeft:
            internalSetOrigin(PointF(0,0));
        break;
        case Origin::topRight:
            internalSetOrigin(PointF(m_texture->getSize().x,0));
        break;
        case Origin::bottomLeft:
            internalSetOrigin(PointF(0,m_texture->getSize().y));
        break;
        case Origin::bottomRight:
            internalSetOrigin(PointF(m_texture->getSize().x,m_texture->getSize().y));
        break;
        case Origin::middle:
            internalSetOrigin(PointF(m_texture->getSize().x/2,m_texture->getSize().y/2));
        break;
        default:

        break;
    }
}

void PixelPainter::setPixelColor(const Point &pixelPos, const Color &color)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    if(pixelPos.getX() >= m_image->getSize().x || pixelPos.getY() >= m_image->getSize().y)
        return;
    m_image->setPixel(pixelPos.getX(),pixelPos.getY(),color);
    /*for(Pixel &p : m_pixelList)
    {
        if(p.getPos() == pixelPos)
            p.setColor(color);
    }*/
}
void PixelPainter::setPixelColor(unsigned int x,unsigned int y, const Color &color)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    setPixelColor(Point(x,y),color);
}
void PixelPainter::internalSetPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Cyan800);
    PointU imageSize(m_image->getSize().x,m_image->getSize().y);
    PointU newSize(0,0);
    for(const Pixel &pixel : pixelList)
    {
        if(pixel.getX() >= newSize.getX())
        {
            newSize.setX(pixel.getX()+1);
        }
        if(pixel.getY() >= newSize.getY())
        {
            newSize.setY(pixel.getY()+1);
        }
    }


    /*if(newSize.getX() >= imageSize.getX() || newSize.getY() >= imageSize.getY())
    {
        resize(newSize);
    }*/
    m_image->create(newSize.getX(),newSize.getY());
    for(const Pixel &pixel : pixelList)
    {
        m_image->setPixel(pixel.getX(),pixel.getY(),pixel);
        m_texture->loadFromImage(*m_image);
    }
}
void PixelPainter::internalAddPixel(const Pixel &pixel)
{
    EASY_FUNCTION(profiler::colors::Cyan800);
    PointU newSize(m_image->getSize().x,m_image->getSize().y);
    bool doResize = false;
    if(pixel.getX() >= m_image->getSize().x)
    {
        newSize.setX(pixel.getX()+1);
        doResize = true;
    }
    if(pixel.getY() >= m_image->getSize().y)
    {
        newSize.setY(pixel.getY()+1);
        doResize = true;
    }
    if(doResize)
        resize(newSize);
    m_image->setPixel(pixel.getX(),pixel.getY(),pixel);
    m_texture->loadFromImage(*m_image);

}
void PixelPainter::internalAddPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Cyan800);
    for(const Pixel &p : pixelList)
        internalAddPixel(p);
}
