#include "spritePainter.h"

Painter::Painter()
    :   LayerItem()
{
    LayerItem::setPos(Vector2f(0,0));
    setVisibility(true);
    m_originType = Origin::middle;
    setRenderLayer(0);
    m_frame = RectF(0,0,0,0);
    //m_display   = nullptr;
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
    this->m_originType      = other.m_originType;
    this->m_frame           = other.m_frame;
    return *this;
}

RectF Painter::getFrame() const
{
    return m_frame;
}
/*void Painter::setDisplay(PixelDisplay *display)
{
    m_display = display;
}*/


void Painter::setVisibility(bool isVisible)
{
    if(m_isVisible == isVisible)
        return;
    m_isVisible = isVisible;
    if(m_isVisible)
        m_signalSubscriber.isVisible(this);
    else
        m_signalSubscriber.isInvisible(this);
}
bool Painter::isVisible() const
{
    return m_isVisible;
}
bool Painter::needsRendering(const RectF &renderRect)
{
    if(!m_isVisible)
        return false;
    return m_frame.intersects_fast(renderRect);
}
void Painter::setPos(const Vector2f & pos)
{
    PAINTER_FUNCTION(profiler::colors::Cyan300);
    LayerItem::setPos(pos);
    internal_setPos(m_pos);
    internal_CalculateFrame();
}
void Painter::move(const Vector2f vec)
{
    LayerItem::move(vec);
    internal_setPos(m_pos);
    internal_CalculateFrame();
}


float Painter::getRotation() const
{
    return internal_getRotation();
}
void Painter::setRotation(float deg)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    internal_setRotation(deg);
}
void Painter::rotate(float deg)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    internal_setRotation(internal_getRotation() + deg);
}
void Painter::rotate_90()
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    this->rotate(90);
}
void Painter::rotate_180()
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    this->rotate(180);
}
void Painter::rotate_270()
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    this->rotate(270);
}
void Painter::setRotation(const Vector2f &rotPoint,float deg)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    internal_setRotation(rotPoint, deg);
}
void Painter::rotate(const Vector2f &rotPoint,float deg)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    internal_setRotation(rotPoint,internal_getRotation() + deg);
}
void Painter::rotate_90(const Vector2f &rotPoint)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    this->rotate(rotPoint,90);
}
void Painter::rotate_180(const Vector2f &rotPoint)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    this->rotate(rotPoint,180);
}
void Painter::rotate_270(const Vector2f &rotPoint)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
    this->rotate(rotPoint,270);
}

void Painter::updateOrigin()
{
    internal_UpdateOrigin();
}
void Painter::setOrigin(const Vector2f &origin)
{
    internal_SetOrigin(origin);
    m_originType = Origin::costumPos;
}
void Painter::setOriginType(Origin origin)
{
    m_originType = origin;
    internal_UpdateOrigin();
}
Origin Painter::getOriginType() const
{
    return m_originType;
}
const Vector2f Painter::getOrigin() const
{
    return internal_getOrigin();
}
void Painter::setRenderLayer(size_t layer)
{
    if(m_renderlayer == layer)
        return;
    size_t lastLayer = m_renderlayer;
    m_renderlayer  = layer;
    m_signalSubscriber.renderLayerChanged(this,lastLayer,m_renderlayer);
}
size_t Painter::getRenderLayer() const
{
    return m_renderlayer;
}
void Painter::subscribe_painterSignal(PainterSignal *subscriber)
{
    m_signalSubscriber.insert(subscriber);
}
void Painter::unsubscribe_painterSignal(PainterSignal *subscriber)
{
    m_signalSubscriber.erase(subscriber);
}
void Painter::unsubscribeAll_painterSignal()
{
    m_signalSubscriber.clear();
}
