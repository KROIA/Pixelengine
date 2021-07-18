#include "spritePainter.h"

SpritePainter::SpritePainter()
    :   Painter()
{
    m_const_dummy_pixel.setPos(Vector2i(0,0));
    m_const_dummy_pixel.setColor(Color(0,0,0,0));

    m_sprite        = new sf::Sprite;
    //m_image     = nullptr;
}
SpritePainter::SpritePainter(const SpritePainter &other)
    :   Painter()
{
    *this = other;
}

SpritePainter::~SpritePainter()
{
    delete m_sprite;
}
const SpritePainter &SpritePainter::operator=(const SpritePainter &other)
{
    Painter::operator=(other);
    *this->m_sprite         = *other.m_sprite;
    //this->m_texture         = other.m_texture;
    //*this->m_image          = *other.m_image;
    return *this;
}

void SpritePainter::render(sf::RenderWindow *window,
                           float viewPortZoom,
                           DisplayStats &stats)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
  //  if(!m_isVisible || !m_frame.intersects_fast(renderFrame))
  //      return;
    window->draw(*m_sprite);
    stats.renderSprites ++;
}

/*sf::Sprite *SpritePainter::getSprite() const
{
    return m_sprite;
}*/

void SpritePainter::internal_setPos(const Vector2f &pos)
{
    m_sprite->setPosition(pos);
}
float SpritePainter::internal_getRotation() const
{
    return m_sprite->getRotation();
}
void SpritePainter::internal_setRotation(const Vector2f &rotPoint,float deg)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    Vector2f lastOrigin = m_sprite->getOrigin();
    m_sprite->setPosition(rotPoint.x-m_sprite->getOrigin().x,rotPoint.y - m_sprite->getOrigin().y);
    internal_setRotation(deg);
    m_sprite->setOrigin(lastOrigin);
}
void SpritePainter::internal_setRotation(const float &deg)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    m_sprite->setRotation(deg);
}
void SpritePainter::internal_UpdateOrigin()
{
    PAINTER_FUNCTION(profiler::colors::Cyan700);
    if(m_texture == nullptr)
        return;
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
}
void SpritePainter::internal_SetOrigin(const Vector2f &origin)
{
    PAINTER_FUNCTION(profiler::colors::Cyan700);
    m_sprite->setOrigin(origin.x,origin.y);
    internal_CalculateFrame();
}
const Vector2f &SpritePainter::internal_getOrigin() const
{
    return m_sprite->getOrigin();
}
void SpritePainter::internal_CalculateFrame()
{
    Vector2f offset(5,5);
    m_frame.setPos(m_sprite->getPosition() - m_sprite->getOrigin()-offset);
    m_frame.setSize(Vector2f(m_texture->getSize())+offset*2.f);
}
