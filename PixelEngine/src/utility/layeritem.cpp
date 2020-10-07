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
    //qDebug() << "LayerItem::setPos"<<pos.getX()<<"\t"<<pos.getY();
    m_lastPos   = m_pos;
    m_pos       = pos;
    //qDebug() << "LayerItem::setPos="<<m_pos.getX()<<"\t"<<m_pos.getY();
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
    this->setPos(bufferPos.getX(),bufferPos.getY());
    m_lastPos = bufferPos;
}
