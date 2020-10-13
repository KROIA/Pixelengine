#include "layeritem.h"

LayerItem::LayerItem()
{
    setPos(0,0);
}
LayerItem::LayerItem(const LayerItem &other)
{
    *this = other;
}
LayerItem::LayerItem(const Point &pos)
{
    this->m_pos = pos;
}
LayerItem::~LayerItem()
{

}
LayerItem &LayerItem::operator=(const LayerItem &other)
{
    this->m_pos = other.m_pos;
    this->m_lastPos = other.m_lastPos;
    return  *this;
}
void LayerItem::setPosInitial(const Point &pos)
{
    this->setPos(pos);
    m_lastPos = m_pos;
}
void LayerItem::setPosInitial(const int &x, const int &y)
{
    this->setPos(x,y);
    m_lastPos = m_pos;
}

void LayerItem::setPos(const Point &pos)
{
    if(m_pos == pos)
        return;
    m_lastPos   = m_pos;
    m_pos       = pos;
}
void LayerItem::setPos(const int &x, const int &y)
{
    if(m_pos.getX() == x && m_pos.getY() == y)
        return;
    m_lastPos   = m_pos;
    m_pos.setX(x);
    m_pos.setY(y);
}
const Point &LayerItem::getPos() const
{
    return m_pos;
}
void LayerItem::setX(const int &x)
{
    if(m_pos.getX() == x)
        return;
    m_lastPos   = m_pos;
    m_pos.setX(x);
}
void LayerItem::setY(const int &y)
{
    if(m_pos.getY() == y)
        return;
    m_lastPos   = m_pos;
    m_pos.setY(y);
}

const int &LayerItem::getX() const
{
    return m_pos.getX();
}
const int &LayerItem::getY() const
{
    return m_pos.getY();
}
void LayerItem::setToLastPos()
{
    Point bufferPos = m_lastPos;
    LayerItem::setPos(bufferPos.getX(),bufferPos.getY());
    m_lastPos = bufferPos;
}
void LayerItem::move(const Vector &vec)
{
    LayerItem::move(vec.getX(),vec.getY());
}

void LayerItem::move(const int &deltaX, const int &deltaY)
{
    if(deltaX == m_pos.getX() && deltaY == m_pos.getY())
        return;
    m_lastPos   = m_pos;
    this->m_pos.move(deltaX,deltaY);
}
void LayerItem::moveX(const int &delta)
{
    LayerItem::setX(m_pos.getX() + delta);
}
void LayerItem::moveY(const int &delta)
{
    LayerItem::setY(m_pos.getY() + delta);
}
