#include "pixelPainter.h"

PixelPainter::PixelPainter()
    :   Painter()
{
    m_sprite    = new sf::Sprite;
    m_texture   = new sf::Texture;
    m_image     = new sf::Image;
    //m_sprite->setScale(globalScale);
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
    p.setPos(Vector2i(x,y));
    p.setColor(color);
    internalAddPixel(p);
}
void PixelPainter::addPixel(const Pixel &pixel)
{
    EASY_FUNCTION(profiler::colors::Cyan);
    internalAddPixel(pixel);
}
void PixelPainter::addPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Cyan);
    for(const Pixel &p : pixelList)
        internalAddPixel(p);
}
const Pixel PixelPainter::getPixel(const Vector2i&pixelPos) const
{
    Pixel p;
    p.setPos(pixelPos);
    p.setColor(m_image->getPixel(pixelPos.x,pixelPos.y));
    return p;
}
const Pixel PixelPainter::getPixel(unsigned int x,unsigned int y) const
{
    Pixel p;
    p.setPos(Vector2i(x,y));
    p.setColor(m_image->getPixel(x,y));
    return p;
}

void PixelPainter::update()
{
    EASY_BLOCK("PixelPainter::update() loadFromImage",profiler::colors::Cyan900);
    m_texture->loadFromImage(*m_image);
    EASY_END_BLOCK;
}
void PixelPainter::resize(Vector2u size)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    Image tmp = *m_image;
    m_image->create(size.x,size.y,Color(0,0,0,0));
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
            internalSetOrigin(Vector2f(0,0));
        break;
        case Origin::topRight:
            internalSetOrigin(Vector2f(m_texture->getSize().x,0));
        break;
        case Origin::bottomLeft:
            internalSetOrigin(Vector2f(0,m_texture->getSize().y));
        break;
        case Origin::bottomRight:
            internalSetOrigin(Vector2f(m_texture->getSize().x,m_texture->getSize().y));
        break;
        case Origin::middle:
            internalSetOrigin(Vector2f(m_texture->getSize().x/2,m_texture->getSize().y/2));
        break;
        default:

        break;
    }
}

void PixelPainter::setPixelColor(const Vector2i & pixelPos, const Color &color)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    if(pixelPos.x < 0 || pixelPos.y < 0)
        return;
    if(unsigned(pixelPos.x) >= m_image->getSize().x || unsigned(pixelPos.y) >= m_image->getSize().y)
        return;
    m_image->setPixel(pixelPos.x,pixelPos.y,color);
}
void PixelPainter::setPixelColor(unsigned int x,unsigned int y, const Color &color)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    setPixelColor(Vector2i(x,y),color);
}
void PixelPainter::internalSetPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Cyan800);
    Vector2u imageSize(m_image->getSize().x,m_image->getSize().y);
    Vector2u newSize(0,0);
    for(const Pixel &pixel : pixelList)
    {
        if(unsigned(pixel.getX()) >= newSize.x)
        {
            newSize.x = pixel.getX()+1;
        }
        if(unsigned(pixel.getY()) >= newSize.y)
        {
            newSize.y = pixel.getY()+1;
        }
    }

    m_image->create(newSize.x,newSize.y);
    for(const Pixel &pixel : pixelList)
    {
        m_image->setPixel(pixel.getX(),pixel.getY(),pixel);
        m_texture->loadFromImage(*m_image);
    }
}
void PixelPainter::internalAddPixel(const Pixel &pixel)
{
    EASY_FUNCTION(profiler::colors::Cyan800);
    Vector2u newSize(m_image->getSize().x,m_image->getSize().y);
    bool doResize = false;
    if(unsigned(pixel.getX()) >= m_image->getSize().x)
    {
        newSize.x = pixel.getX()+1;
        doResize = true;
    }
    if(unsigned(pixel.getY()) >= m_image->getSize().y)
    {
        newSize.y = pixel.getY()+1;
        doResize = true;
    }
    if(doResize)
        resize(newSize);
    EASY_BLOCK("setPixel",profiler::colors::Cyan900);
    m_image->setPixel(pixel.getX(),pixel.getY(),pixel);
    EASY_END_BLOCK;
}
void PixelPainter::internalAddPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Cyan800);
    for(const Pixel &p : pixelList)
        internalAddPixel(p);
}
