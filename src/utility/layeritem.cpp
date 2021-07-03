#include "layeritem.h"

LayerItem::LayerItem()
{
    m_pos.x = 0;
    m_pos.y = 0;
    m_lastPos.x = 0;
    m_lastPos.y = 0;

    m_rotation = 0;
    m_lastRotation =0;
}
LayerItem::LayerItem(const LayerItem &other)
{
    *this = other;
}
LayerItem::LayerItem(int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;
    m_lastPos = m_pos;
}
LayerItem::LayerItem(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;
    m_lastPos = m_pos;
}
LayerItem::LayerItem(const Vector2f &pos)
{
    m_pos       = pos;
    m_lastPos   = pos;
}
LayerItem::LayerItem(const Vector2i &pos)
{
    m_pos       = Vector2f(pos);
    m_lastPos   = Vector2f(pos);
}
LayerItem::~LayerItem()
{

}
LayerItem &LayerItem::operator=(const LayerItem &other)
{
    this->m_pos         = other.m_pos;
    this->m_lastPos     = other.m_lastPos;
    this->m_rotation    = other.m_rotation;
    this->m_lastRotation=other.m_lastRotation;
    return  *this;
}
void LayerItem::swapPosToLastPos()
{
    m_lastPos = m_pos;
}
void LayerItem::swapRotationToLastRotation()
{
    m_lastRotation = m_rotation;
}

void LayerItem::setPosInitial(const Vector2f &pos)
{
    this->setPos(pos);
    this->swapPosToLastPos();
}
void LayerItem::setPosInitial(const Vector2i &pos)
{
    this->setPos(pos);
    this->swapPosToLastPos();
}
void LayerItem::setPosInitial(int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;
    this->swapPosToLastPos();
}
void LayerItem::setPosInitial(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;
    this->swapPosToLastPos();
}

void LayerItem::setPos(const Vector2f &pos)
{
    m_pos = pos;
}
void LayerItem::setPos(const Vector2i &pos)
{
    m_pos = Vector2f(pos);
}
const Vector2f &LayerItem::getPos() const
{
    return m_pos;
}
const Vector2f &LayerItem::getLastPos() const
{
    return m_lastPos;
}
Vector2i LayerItem::getPosI() const
{
    return Vector2i(round(m_pos.x),round(m_pos.y));
}
Vector2i LayerItem::getLastPosI() const
{
    return Vector2i(round(m_lastPos.x),round(m_lastPos.y));
}
void LayerItem::setX(int x)
{
    m_pos.x = x;
}
void LayerItem::setY(int y)
{
    m_pos.y = y;
}
void LayerItem::setX(float x)
{
    m_pos.x = x;
}
void LayerItem::setY(float y)
{
    m_pos.y = y;
}

float LayerItem::getX() const
{
    return m_pos.x;
}
float LayerItem::getY() const
{
    return m_pos.y;
}
int LayerItem::getXI() const
{
    return round(m_pos.x);
}
int LayerItem::getYI() const
{
    return round(m_pos.y);
}

void LayerItem::move(const Vector2f &vec)
{
    m_pos += vec;
}
void LayerItem::move(const Vector2i &vec)
{
    m_pos += Vector2f(vec);
}
void LayerItem::rotate(float deg)
{
    m_rotation += deg;
}
void LayerItem::setRotationInitial(float deg)
{
    m_rotation      = deg;
    swapRotationToLastRotation();
}
void LayerItem::setRotation(float deg)
{
    m_rotation = deg;
}

float LayerItem::getRotation() const
{
    return m_rotation;
}

void LayerItem::setToLastPos()
{
    m_pos = m_lastPos;
}
void LayerItem::setToLastRotation()
{
    m_rotation = m_lastRotation;
}
