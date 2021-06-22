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
    this->setPos(pos.getX(),pos.getY());
    this->swapPosToLastPos();
}
LayerItem::LayerItem(const PointF &pos)
{
    this->setPos(pos);
    this->swapPosToLastPos();
}
LayerItem::~LayerItem()
{

}
LayerItem &LayerItem::operator=(const LayerItem &other)
{
    this->m_floatingPos = other.m_floatingPos;
    this->m_lastPos     = other.m_lastPos;
    return  *this;
}
void LayerItem::swapPosToLastPos()
{
    m_lastPos = m_floatingPos;
}
void LayerItem::setPosInitial(const PointU &pos)
{
    this->setPos(pos);
    this->swapPosToLastPos();
}
void LayerItem::setPosInitial(const Point &pos)
{
    this->setPos(pos);
    this->swapPosToLastPos();
}
void LayerItem::setPosInitial(const PointF &pos)
{
    this->setPos(pos);
    this->swapPosToLastPos();
}
void LayerItem::setPosInitial(int x, int y)
{
    this->setPos(double(x),double(y));
    this->swapPosToLastPos();
}
void LayerItem::setPosInitial_F(const double &x, const double &y)
{
    this->setPos(x,y);
    this->swapPosToLastPos();
}

void LayerItem::setPos(const PointU &pos)
{
    m_floatingPos.set(double(pos.getX()),double(pos.getY()));
}
void LayerItem::setPos(const Point &pos)
{
    m_floatingPos.set(double(pos.getX()),double(pos.getY()));
}
void LayerItem::setPos(const PointF &pos)
{
    m_floatingPos       = pos;
}
void LayerItem::setPos(int x, int y)
{
    m_floatingPos.setX(double(x));
    m_floatingPos.setY(double(y));
}
void LayerItem::setPos_F(const double &x, const double &y)
{
    m_floatingPos.setX(x);
    m_floatingPos.setY(y);
}
Point LayerItem::getPos() const
{
    return Point(int(round(m_floatingPos.getX())),
                 int(round(m_floatingPos.getY())));
}
Point LayerItem::getLastPos() const
{
    return Point(int(round(m_lastPos.getX())),
                 int(round(m_lastPos.getY())));
}
void LayerItem::setX(int x)
{
    m_floatingPos.setX(double(x));
}
void LayerItem::setX_F(const double &x)
{
    m_floatingPos.setX(x);
}
void LayerItem::setY(int y)
{
    m_floatingPos.setY(double(y));
}
void LayerItem::setY_F(const double &y)
{
    m_floatingPos.setY(y);
}

int LayerItem::getX() const
{
    EASY_FUNCTION(profiler::colors::Blue500);
    return int(round(m_floatingPos.getX()));
}
int LayerItem::getY() const
{
    EASY_FUNCTION(profiler::colors::Blue500);
    return int(round(m_floatingPos.getY()));
}

void LayerItem::move(const VectorU &vec)
{
    m_floatingPos.move(double(vec.getX()),double(vec.getY()));
}
void LayerItem::move(const Vector &vec)
{
    m_floatingPos.move(double(vec.getX()),double(vec.getY()));
}
void LayerItem::move(const VectorF &vec)
{
    m_floatingPos.move(vec);
}

void LayerItem::move(int deltaX, int deltaY)
{
    m_floatingPos.move(double(deltaX),double(deltaY));
}
void LayerItem::move_F(const double &deltaX, const double &deltaY)
{
    m_floatingPos.move(deltaX,deltaY);
}
void LayerItem::moveX(int delta)
{
    m_floatingPos.moveX(double(delta));
}
void LayerItem::moveX_F(const double &delta)
{
    m_floatingPos.moveX(delta);
}
void LayerItem::moveY(int delta)
{
    m_floatingPos.moveY(double(delta));
}
void LayerItem::moveY_F(const double &delta)
{
    m_floatingPos.moveY(delta);
}
void LayerItem::setToLastPos()
{
    PointF bufferPos = m_lastPos;
    LayerItem::setPos_F(bufferPos.getX(),bufferPos.getY());
    m_lastPos = bufferPos;
}
