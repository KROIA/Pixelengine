#include "pixelPainter.h"

PixelPainter::PixelPainter()
    :   Painter()
{
    //m_texture   = new sf::Texture;
   // m_image     = new sf::Image;
    setRenderLayer(layer_3);
    m_lastPos = Vector2f(0,0);
}
PixelPainter::~PixelPainter()
{
   // delete m_texture;
   // delete m_image;
}
inline void PixelPainter::render(sf::RenderWindow *window,
                    float viewPortZoom,
                    DisplayStats &stats)
{
    for(size_t x=0; x<m_pixMap.size(); x++)
    {
        for(size_t y=0; y<m_pixMap[x].size(); y++)
        {
            window->draw(m_pixMap[x][y]);
        }
    }
}

void PixelPainter::setPixel(const Pixel &pixel)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    if(pixel.getPos().x < 0 || pixel.getPos().y < 0)
        return;
   // if(unsigned(pixel.getPos().x) >= m_image->getSize().x || unsigned(pixel.getPos().y) >= m_image->getSize().y)
    //    return;
    //m_image->setPixel(pixel.getPos().x,pixel.getPos().y,pixel);
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
   // p.setColor(m_image->getPixel(pixelPos.x,pixelPos.y));
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
}
void PixelPainter::resize(Vector2u size)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
   /* Image tmp = *m_image;
    m_image->create(size.x,size.y,Color(0,0,0,0));
    m_image->copy(tmp,0,0,sf::IntRect(0,0,tmp.getSize().x,tmp.getSize().y),true);
    */
    internal_UpdateOrigin();
    m_pixMap.clear();
    m_pixMap.reserve(size.x);
    for(size_t x=0; x<size.x; x++)
    {
        m_pixMap.push_back(vector<sf::VertexArray>());
        m_pixMap[x].reserve(size.y);
        for(size_t y=0; y<size.y; y++)
        {
            sf::VertexArray pixel(sf::Quads,4);
            pixel[0].position = Vector2f(x,y);
            pixel[1].position = Vector2f(x+1,y);
            pixel[2].position = Vector2f(x+1,y+1);
            pixel[3].position = Vector2f(x,y+1);

            pixel[0].color = sf::Color::Black;
            pixel[1].color = sf::Color::Black;
            pixel[2].color = sf::Color::Black;
            pixel[3].color = sf::Color::Black;

            m_pixMap[x].push_back(pixel);
        }
    }
}
void PixelPainter::clear()
{

    //m_image->create(m_image->getSize().x,m_image->getSize().y,Color(0,0,0,0));
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
    if(unsigned(pixelPos.x) >= m_pixMap.size() || unsigned(pixelPos.y) >= m_pixMap[0].size())
        return;
   // m_image->setPixel(pixelPos.x,pixelPos.y,color);
    m_pixMap[pixelPos.x][pixelPos.y][0].color  = color;
    m_pixMap[pixelPos.x][pixelPos.y][1].color  = color;
    m_pixMap[pixelPos.x][pixelPos.y][2].color  = color;
    m_pixMap[pixelPos.x][pixelPos.y][3].color  = color;
}
void PixelPainter::setPixelColor(unsigned int x,unsigned int y, const Color &color)
{
    EASY_FUNCTION(profiler::colors::Cyan100);
    setPixelColor(Vector2i(x,y),color);
}
void PixelPainter::internalSetPixel(const vector<Pixel> &pixelList)
{
    /*EASY_FUNCTION(profiler::colors::Cyan800);
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

inline void PixelPainter::internal_setPos(const Vector2f &pos)
{
    Vector2f delta = pos - m_lastPos;
    m_lastPos = pos;
    for(size_t x=0; x<m_pixMap.size(); x++)
    {
        for(size_t y=0; y<m_pixMap[x].size(); y++)
        {
            m_pixMap[x][y][0].position += delta;
            m_pixMap[x][y][1].position += delta;
            m_pixMap[x][y][2].position += delta;
            m_pixMap[x][y][3].position += delta;
        }
    }
}
inline float PixelPainter::internal_getRotation() const
{
    return 0;
}
inline void PixelPainter::internal_setRotation(const Vector2f &rotPoint,float deg)
{

}
inline void PixelPainter::internal_setRotation(const float &deg)
{

}
inline void PixelPainter::internal_UpdateOrigin()
{

}
inline void PixelPainter::internal_SetOrigin(const Vector2f &origin)
{

}
inline const Vector2f &PixelPainter::internal_getOrigin() const
{
    return Vector2f(0,0);
}
inline void PixelPainter::internal_CalculateFrame()
{

}
