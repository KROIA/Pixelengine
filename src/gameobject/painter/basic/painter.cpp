#include "painter.h"

Painter::Painter()
    :   LayerItem()
{
    m_const_dummy_pixel.setPos(0,0);
    m_const_dummy_pixel.setColor(Color(0,0,0,0));
    setPos(0,0);
    setVisibility(true);

    m_sprite    = nullptr;
    m_texture   = nullptr;
    m_image     = nullptr;


    m_originType = Origin::middle;
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
    *this->m_sprite          = *other.m_sprite;
    *this->m_texture         = *other.m_texture;
    *this->m_image           = *other.m_image;
    this->m_originType      = other.m_originType;
    return *this;
}

void Painter::draw(PixelDisplay &display)
{
    EASY_FUNCTION(profiler::colors::Cyan200);
    if(m_isVisible)
    {
        display.addSprite(*m_sprite);
    }
}

void Painter::setPos(const Point &pos)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    if(LayerItem::getPos() == pos)
        return;
    //m_sprite->setPosition(pos.getX()-m_sprite->getOrigin().x,pos.getY()-m_sprite->getOrigin().y);
    m_sprite->setPosition(pos.getX(),pos.getY());
    LayerItem::setPos(pos);
}
void Painter::setPos(int x, int y)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    if(LayerItem::getX() == x && LayerItem::getY() == y)
        return;
    //m_sprite->setPosition(x-m_sprite->getOrigin().x,y-m_sprite->getOrigin().y);
    m_sprite->setPosition(x,y);
    LayerItem::setPos(x,y);
}
void Painter::setX(int x)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    if(LayerItem::getX() == x)
        return;
    //m_sprite->setPosition(x-m_sprite->getOrigin().x,m_sprite->getPosition().y-m_sprite->getOrigin().y);
    m_sprite->setPosition(x,m_sprite->getPosition().y);
    LayerItem::setX(x);
}
void Painter::setY(int y)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    if(LayerItem::getX() == y)
        return;
   //m_sprite->setPosition(m_sprite->getPosition().x-m_sprite->getOrigin().x,y-m_sprite->getOrigin().y);
    m_sprite->setPosition(m_sprite->getPosition().x,y);
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
void Painter::internal_rotate(const PointF &rotPoint,const float &deg)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    Vector2f lastOrigin = m_sprite->getOrigin();
    m_sprite->setPosition(rotPoint.getX()-m_sprite->getOrigin().x,rotPoint.getY()-m_sprite->getOrigin().y);
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
void Painter::setRotation(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    m_sprite->setRotation(deg);
    //this->internal_rotate(PointF(this->getX(),this->getY()),(deg*M_PI/180.f) - m_rotationRad);
}
void Painter::rotate(const float &deg)
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
void Painter::setRotation(const PointF &rotPoint,const float &deg)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    Vector2f lastOrigin = m_sprite->getOrigin();
    m_sprite->setPosition(rotPoint.getX(),rotPoint.getY());
    setRotation(deg);
    m_sprite->setOrigin(lastOrigin);
}
void Painter::rotate_90(const PointF &rotPoint)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    this->internal_rotate(rotPoint,90);
}
void Painter::rotate_180(const PointF &rotPoint)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    this->internal_rotate(rotPoint,180);
}
void Painter::rotate_270(const PointF &rotPoint)
{
    EASY_FUNCTION(profiler::colors::Cyan600);
    this->internal_rotate(rotPoint,270);
}

/*void Painter::setTexture(Texture *texture)
{
    EASY_FUNCTION(profiler::colors::Cyan700);

    delete m_texture;
    m_texture = texture;
    m_sprite.setTexture(m_texture->getTexture());
    m_sprite.setPosition(this->getX(),this->getY());
    internalUpdateOrigin();
    //m_sprite.setOrigin(Vector2f(m_texture->getOrigin().getX(),m_texture->getOrigin().getY()));
    //setRotation(texture->getRotation());
    //setTexture(texture->getTexture());

}*/
void Painter::updateOrigin()
{
    internalUpdateOrigin();
}
void Painter::setOrigin(const PointF &origin)
{
    internalSetOrigin(origin);
    m_originType = Origin::costumPos;
    //m_sprite->setOrigin(origin.getX(),origin.getY());
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
const PointF Painter::getOrigin() const
{
    return PointF(m_sprite->getOrigin().x,m_sprite->getOrigin().y);
}
void Painter::internalUpdateOrigin()
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
void Painter::internalSetOrigin(const PointF &origin)
{
    EASY_FUNCTION(profiler::colors::Cyan700);
    m_sprite->setOrigin(origin.getX(),origin.getY());
   // m_sprite->setPosition(m_floatingPos.getX()-origin.getX(),m_floatingPos.getY()-origin.getY());
}

/*void Painter::setTexture(const sf::Texture &texture)
{
    EASY_FUNCTION(profiler::colors::Cyan700);
    m_sprite.setTexture(texture);
    m_sprite.setPosition(this->getX(),this->getY());
}*/
/*void Painter::internalSetPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Cyan800);
    m_pixelList = pixelList;
}
void Painter::internalAddPixel(const Pixel &pixel)
{
    EASY_FUNCTION(profiler::colors::Cyan800);
    m_pixelList.push_back(pixel);
}
void Painter::internalAddPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Cyan800);
    for(const Pixel &p : pixelList)
        internalAddPixel(p);
}*/
/*void Painter::updateFrame()
{
    EASY_FUNCTION(profiler::colors::Cyan900);
    vector<Rect> pixelRects(m_pixelList.size(),Rect(Point(0,0),Point(1,1)));
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        pixelRects[i].setPos(m_pixelList[i].getPos());
    }
    m_frame = Rect::getFrame(pixelRects);
}*/
