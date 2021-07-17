#include "pixelPainter.h"

PixelPainter::PixelPainter()
    :   SpritePainter()
{
    m_texture   = new sf::Texture;
    //m_image     = new sf::Image;
    m_pixels = nullptr;

}
PixelPainter::~PixelPainter()
{
    delete m_texture;
//    delete m_image;
}

void PixelPainter::setPixel(const Pixel &pixel)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    if(pixel.getPos().x < 0 || pixel.getPos().y < 0)
        return;
  /*  if(unsigned(pixel.getPos().x) >= m_image->getSize().x || unsigned(pixel.getPos().y) >= m_image->getSize().y)
        return;
    m_image->setPixel(pixel.getPos().x,pixel.getPos().y,pixel);*/
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
  //  p.setColor(m_image->getPixel(pixelPos.x,pixelPos.y));
    return p;
}
const Pixel PixelPainter::getPixel(unsigned int x,unsigned int y) const
{
    Pixel p;
    p.setPos(Vector2i(x,y));
  //  p.setColor(m_image->getPixel(x,y));
    return p;
}

void PixelPainter::update()
{
    EASY_BLOCK("PixelPainter::update() loadFromImage",profiler::colors::Cyan900);
   // m_texture->loadFromImage(*m_image);
   // m_sprite->setTexture(*m_texture);
    m_texture->update(m_pixels);
}
void PixelPainter::resize(Vector2u size)
{
    EASY_FUNCTION(profiler::colors::Cyan100);

    /*Image tmp = *m_image;
    m_image->create(size.x,size.y,Color(0,0,0,0));
    m_image->copy(tmp,0,0,sf::IntRect(0,0,tmp.getSize().x,tmp.getSize().y),true);
    internal_UpdateOrigin();*/

    if(m_pixels != nullptr)
        delete m_pixels;
    m_size = size;
    m_pixels = new sf::Uint8[size.x*size.y*4];
    delete m_sprite;
    m_texture->create(size.x,size.y);
    m_sprite = new sf::Sprite(*m_texture);
}
void PixelPainter::clear()
{
   // m_image->create(m_image->getSize().x,m_image->getSize().y,Color(0,0,0,100));
}
/*void PixelPainter::internal_UpdateOrigin()
{
    EASY_FUNCTION(profiler::colors::Cyan700);
    switch(m_originType)
    {
        case Origin::topLeft:
            internal_SetOrigin(Vector2f(0,0));
        break;
        case Origin::topRight:
            internal_SetOrigin(Vector2f(m_texture->getSize().x,0));
        break;
        case Origin::bottomLeft:
            internal_SetOrigin(Vector2f(0,m_texture->getSize().y));
        break;
        case Origin::bottomRight:
            internal_SetOrigin(Vector2f(m_texture->getSize().x,m_texture->getSize().y));
        break;
        case Origin::middle:
            internal_SetOrigin(Vector2f(m_texture->getSize().x/2,m_texture->getSize().y/2));
        break;
        default:

        break;
    }
}*/

void PixelPainter::setPixelColor(const Vector2i & pixelPos, const Color &color)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    if(pixelPos.x < 0 || pixelPos.y < 0)
        return;
    if(unsigned(pixelPos.x) >= m_size.x || unsigned(pixelPos.y) >= m_size.y)
        return;
   // m_image->setPixel(pixelPos.x,pixelPos.y,color);
    size_t index = pixelPos.x * pixelPos.y;
    m_pixels[index] = color.r;
    m_pixels[index+1] = color.g;
    m_pixels[index+2] = color.b;
    m_pixels[index+3] = color.a;
}
void PixelPainter::setPixelColor(unsigned int x,unsigned int y, const Color &color)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    setPixelColor(Vector2i(x,y),color);
}
void PixelPainter::internalSetPixel(const vector<Pixel> &pixelList)
{
   /* EASY_FUNCTION(profiler::colors::Cyan800);
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
    }*/
}
void PixelPainter::internalAddPixel(const Pixel &pixel)
{
   /* EASY_FUNCTION(profiler::colors::Cyan800);
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
    EASY_END_BLOCK;*/
}
void PixelPainter::internalAddPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Cyan800);
    for(const Pixel &p : pixelList)
        internalAddPixel(p);
}
