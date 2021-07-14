#include "painter.h"

Painter::Painter()
    :   LayerItem()
{
    m_const_dummy_pixel.setPos(Vector2i(0,0));
    m_const_dummy_pixel.setColor(Color(0,0,0,0));
    LayerItem::setPos(Vector2f(0,0));
    setVisibility(true);

    m_sprite    = nullptr;
    m_texture   = nullptr;
    m_image     = nullptr;


    m_originType = Origin::middle;
    m_spriteHasSubscribedToDisplay = false;
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
    this->m_isVisible       = other.m_isVisible;
    *this->m_sprite         = *other.m_sprite;
    this->m_texture         = other.m_texture;
    *this->m_image          = *other.m_image;
    this->m_originType      = other.m_originType;
    this->m_frame           = other.m_frame;
    this->m_spriteHasSubscribedToDisplay = other.m_spriteHasSubscribedToDisplay;
    //this->m_renderScale     = other.m_renderScale;
    return *this;
}

RectF Painter::getFrame() const
{
    return m_frame;
}
void Painter::draw(PixelDisplay &display)
{
    EASY_FUNCTION(profiler::colors::Cyan200);
    if(m_isVisible && !m_spriteHasSubscribedToDisplay)
    {
        display.addSprite(m_sprite);
    }
}
void Painter::subscribeToDisplay(PixelDisplay &display)
{
    if(m_sprite != nullptr)
    {
        display.subscribeSprite(this);
        //m_renderScale = display.getRenderScale();
        m_spriteHasSubscribedToDisplay = true;
    }
}
void Painter::unsubscribeToDisplay(PixelDisplay &display)
{
    display.unsubscribeSprite(this);
    m_spriteHasSubscribedToDisplay = false;
}

void Painter::setPos(const Vector2f & pos)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    m_sprite->setPosition(pos.x,pos.y);
    LayerItem::setPos(pos);
    internalCalculateFrame();
}

void Painter::setX(int x)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    m_sprite->setPosition(x,m_sprite->getPosition().y);
    LayerItem::setX(x);
    internalCalculateFrame();
}
void Painter::setY(int y)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    m_sprite->setPosition(m_sprite->getPosition().x,y);
    LayerItem::setY(y);
    internalCalculateFrame();
}
void Painter::setVisibility(const bool &isVisible)
{
    m_isVisible = isVisible;
}
const bool &Painter::isVisible() const
{
    return m_isVisible;
}
void Painter::internal_rotate(const Vector2f &rotPoint,float deg)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    Vector2f lastOrigin = m_sprite->getOrigin();
    m_sprite->setPosition(rotPoint.x-m_sprite->getOrigin().x,rotPoint.y - m_sprite->getOrigin().y);
    internal_rotate(deg);
    m_sprite->setOrigin(lastOrigin);
}
void Painter::internal_rotate(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    m_sprite->rotate(deg);
}

float Painter::getRotation() const
{
    return m_sprite->getRotation();
}
void Painter::setRotation(float deg)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    m_sprite->setRotation(deg);
}
void Painter::rotate(float deg)
{
    internal_rotate(deg);
}
void Painter::rotate_90()
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    this->internal_rotate(90);
}
void Painter::rotate_180()
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    this->internal_rotate(180);
}
void Painter::rotate_270()
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    this->internal_rotate(270);
}
void Painter::setRotation(const Vector2f &rotPoint,float deg)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    Vector2f lastOrigin = m_sprite->getOrigin();
    m_sprite->setPosition(rotPoint.x,rotPoint.y);
    setRotation(deg);
    m_sprite->setOrigin(lastOrigin);
}
void Painter::rotate_90(const Vector2f &rotPoint)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    this->internal_rotate(rotPoint,90);
}
void Painter::rotate_180(const Vector2f &rotPoint)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    this->internal_rotate(rotPoint,180);
}
void Painter::rotate_270(const Vector2f &rotPoint)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    this->internal_rotate(rotPoint,270);
}

void Painter::updateOrigin()
{
    internalUpdateOrigin();
}
void Painter::setOrigin(const Vector2f &origin)
{
    internalSetOrigin(origin);
    m_originType = Origin::costumPos;
}
void Painter::setOriginType(Origin origin)
{
    m_originType = origin;
    internalUpdateOrigin();
}
Origin Painter::getOriginType() const
{
    return m_originType;
}
const Vector2f Painter::getOrigin() const
{
    return m_sprite->getOrigin();
}
sf::Sprite *Painter::getSprite() const
{
    return m_sprite;
}
void Painter::internalUpdateOrigin()
{
    EASY_FUNCTION(profiler::colors::Cyan700);
    if(m_texture == nullptr)
        return;
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
void Painter::internalSetOrigin(const Vector2f &origin)
{
    EASY_FUNCTION(profiler::colors::Cyan700);
    m_sprite->setOrigin(origin.x,origin.y);
    internalCalculateFrame();
}
void Painter::internalCalculateFrame()
{
    Vector2f offset(5,5);
    m_frame.setPos(m_sprite->getPosition() - m_sprite->getOrigin()-offset);
    m_frame.setSize(Vector2f(m_texture->getSize())+offset*2.f);
}
