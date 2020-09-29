#include "layeritem.h"

LayerItem::LayerItem()
{
    setPos(0,0);
}
LayerItem::LayerItem(const LayerItem &other)
{
    this->m_pos = other.m_pos;
}
LayerItem::LayerItem(const Point &pos)
{
    this->m_pos = pos;
}
LayerItem::~LayerItem()
{

}

void LayerItem::setPos(const Point &pos)
{
    m_pos = pos;
}
void LayerItem::setPos(const int &x, const int &y)
{
    m_pos.setX(x);
    m_pos.setY(y);
}
const Point &LayerItem::getPos() const
{
    return m_pos;
}
void LayerItem::setX(const int &x)
{
    m_pos.setX(x);
}
void LayerItem::setY(const int &y)
{
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
