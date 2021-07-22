#include "pixelPainter.h"

PixelPainter::PixelPainter()
    :   SpritePainter()
{
    m_texture   = new sf::Texture;
    m_image     = new sf::Image;
  /*  m_pixels    = nullptr;
    m_width     = 0;
    m_height    = 0;*/

}
PixelPainter::~PixelPainter()
{
    delete m_texture;
    delete m_image;
    //delete[] m_pixels;
}

void PixelPainter::render(sf::RenderWindow *window,
            float viewPortZoom,
            DisplayStats &stats)
{
    this->update();
    SpritePainter::render(window,viewPortZoom,stats);
}
void PixelPainter::setPixel(const Pixel &pixel)
{
    PAINTER_FUNCTION(profiler::colors::Cyan100);
    if(pixel.getPos().x < 0 || pixel.getPos().y < 0)
        return;
    if(unsigned(pixel.getPos().x) >= m_image->getSize().x || unsigned(pixel.getPos().y) >= m_image->getSize().y)
        return;
    if(m_image->getPixel(pixel.getPos().x,pixel.getPos().y) == pixel)
        return;
    m_needsUpdate = true;
    m_image->setPixel(pixel.getPos().x,pixel.getPos().y,pixel);
}
void PixelPainter::setPixel(const vector<Pixel> &pixelList)
{
    PAINTER_FUNCTION(profiler::colors::Cyan);
    internalSetPixel(pixelList);
}
/*void PixelPainter::addPixel(unsigned int x, unsigned int y, Color color)
{
    PAINTER_FUNCTION(profiler::colors::Cyan);
    Pixel p;
    p.setPos(Vector2i(x,y));
    p.setColor(color);
    internalAddPixel(p);
}
void PixelPainter::addPixel(const Pixel &pixel)
{
    PAINTER_FUNCTION(profiler::colors::Cyan);
    internalAddPixel(pixel);
}
void PixelPainter::addPixel(const vector<Pixel> &pixelList)
{
    PAINTER_FUNCTION(profiler::colors::Cyan);
    for(const Pixel &p : pixelList)
        internalAddPixel(p);
}*/
const Pixel PixelPainter::getPixel(const Vector2u &pixelPos) const
{
    Pixel p;
    p.setPos(Vector2i(pixelPos));
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
    if(!m_needsUpdate)
        return;
    PAINTER_BLOCK("PixelPainter::update() glBindTexture",profiler::colors::Cyan900);
   glBindTexture(GL_TEXTURE_2D, m_texture->getNativeHandle());
   PAINTER_BLOCK("PixelPainter::update() glTexSubImage2D",profiler::colors::Cyan900);
   glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_image->getSize().x, m_image->getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, m_image->getPixelsPtr());
   PAINTER_BLOCK("PixelPainter::update() glTexParameteri",profiler::colors::Cyan900);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_texture->isSmooth() ? GL_LINEAR : GL_NEAREST);

   //m_texture->loadFromImage(*m_image);
    PAINTER_BLOCK("PixelPainter::update() setTexture",profiler::colors::Cyan900);
    m_sprite->setTexture(*m_texture);
    m_needsUpdate = false;
}
void PixelPainter::resize(Vector2u size)
{
    PAINTER_FUNCTION(profiler::colors::Cyan100);
    Image tmp = *m_image;
    m_image->create(size.x,size.y,Color(0,0,0,0));
    m_image->copy(tmp,0,0,sf::IntRect(0,0,tmp.getSize().x,tmp.getSize().y),true);
    m_texture->create(size.x,size.y);
   /* if(m_pixels != nullptr)
        delete[] m_pixels;
    m_width = size.x;
    m_height = size.y;
    m_pixels = new Uint8[m_width*m_height*4];*/
    internal_UpdateOrigin();
}
void PixelPainter::clear()
{
    m_image->create(m_image->getSize().x,m_image->getSize().y,Color(0,0,0,0));
}
/*void PixelPainter::internal_UpdateOrigin()
{
    PAINTER_FUNCTION(profiler::colors::Cyan700);
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
        case Origin::center:
            internal_SetOrigin(Vector2f(m_texture->getSize().x/2,m_texture->getSize().y/2));
        break;
        default:
        break;
    }
}*/

void PixelPainter::setPixelColor(const Vector2u & pixelPos, const Color &color)
{
    PAINTER_FUNCTION(profiler::colors::Cyan100);
   /* if(pixelPos.x >= m_image->getSize().x || pixelPos.y >= m_image->getSize().y)
        return;
    if(m_image->getPixel(pixelPos.x,pixelPos.y) == color)
        return;*/
    /*m_pixels[pixelPos.x + pixelPos.y * m_width] = color.r;
    m_pixels[pixelPos.x + pixelPos.y * m_width] = color.g;
    m_pixels[pixelPos.x + pixelPos.y * m_width] = color.b;
    m_pixels[pixelPos.x + pixelPos.y * m_width] = color.a;*/
/*
            Uint8* pixel = &m_pixels[(x + y * m_size.x) * 4];
            *pixel++ = color.r;
            *pixel++ = color.g;
            *pixel++ = color.b;
            *pixel++ = color.a;

*/
    m_needsUpdate = true;
    m_image->setPixel(pixelPos.x,pixelPos.y,color);
}
void PixelPainter::setPixelColor(unsigned int x,unsigned int y, const Color &color)
{
    PAINTER_FUNCTION(profiler::colors::Cyan100);
    if(x >= m_image->getSize().x || y >= m_image->getSize().y)
        return;
    if(m_image->getPixel(x,y) == color)
        return;
    m_needsUpdate = true;
    m_image->setPixel(x,y,color);

}
const Uint8* PixelPainter::getPixelsPtr() const
{
    return m_image->getPixelsPtr();
}
const Uint8* PixelPainter::getPixelsPtr(unsigned int x,unsigned int y) const
{
    const Uint8* px = m_image->getPixelsPtr();
    return px+(x + y * m_image->getSize().x) * 4;
}
void PixelPainter::internalSetPixel(const vector<Pixel> &pixelList)
{
    PAINTER_FUNCTION(profiler::colors::Cyan800);
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
    if(imageSize.x < newSize.x || imageSize.y < newSize.y)
        m_image->create(newSize.x,newSize.y);
    for(const Pixel &pixel : pixelList)
    {
        m_image->setPixel(pixel.getX(),pixel.getY(),pixel);
       // m_texture->loadFromImage(*m_image);
    }
    m_needsUpdate = true;
}
/*void PixelPainter::internalAddPixel(const Pixel &pixel)
{
    PAINTER_FUNCTION(profiler::colors::Cyan800);
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
    PAINTER_BLOCK("setPixel",profiler::colors::Cyan900);
    m_image->setPixel(pixel.getX(),pixel.getY(),pixel);
    PAINTER_END_BLOCK;
}
void PixelPainter::internalAddPixel(const vector<Pixel> &pixelList)
{
    PAINTER_FUNCTION(profiler::colors::Cyan800);
    for(const Pixel &p : pixelList)
        internalAddPixel(p);
}*/
