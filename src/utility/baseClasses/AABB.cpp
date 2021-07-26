#include "AABB.h"

unsigned long AABB::stats_intersectionCheckCounter = 0;
AABB::AABB()
{
    setPos({0,0});
    setSize({0,0});
}
AABB::AABB(const AABB &other)
{
    this->m_pos     =   other.m_pos;
    this->m_size    =   other.m_size;
}
AABB::AABB(Vector2f pos, Vector2f size)
{
    setPos(pos);
    setSize(size);
}
AABB::~AABB()
{

}
const AABB &AABB::operator=(const AABB &other)
{
    this->m_pos     =   other.m_pos;
    this->m_size    =   other.m_size;
    return *this;
}
bool AABB::operator==(const AABB &other) const
{
    return this->m_size == other.m_size &&
           this->m_pos  == other.m_pos;
}

void AABB::setPos(Vector2f pos)
{
    m_pos = pos;
}
void AABB::setSize(Vector2f size)
{
    m_size = {abs(size.x),abs(size.y)};
}
void AABB::setWidth(float width)
{
    m_size.x = width;
}
void AABB::setHeight(float height)
{
    m_size.y = height;
}
void AABB::move(Vector2f delta)
{
    m_pos += delta;
}
Vector2f AABB::getPos() const
{
    return m_pos;
}
Vector2f AABB::getSize() const
{
    return m_size;
}
float AABB::getWidth() const
{
    return m_size.x;
}
float AABB::getHeight() const
{
    return m_size.y;
}
bool AABB::intersects(const AABB &b)
{
    return intersects(*this,b);
}
bool AABB::intersectsInverseOf(const AABB &b)
{
    return intersectsInverseOf(*this,b);
}
bool AABB::isLeftOf(const AABB &b)
{
    return isLeftOf(*this,b);
}
bool AABB::isRightOf(const AABB &b)
{
     return isRightOf(*this,b);
}
bool AABB::isOnTopOf(const AABB &b)
{
    return isOnTopOf(*this,b);
}
bool AABB::isBeneathOf(const AABB &b)
{
    return isBeneathOf(*this,b);
}
bool AABB::intersectsTopOf(const AABB &b)
{
    return intersectsTopOf(*this,b);
}
bool AABB::intersectsLeftOf(const AABB &b)
{
    return intersectsLeftOf(*this,b);
}
bool AABB::intersectsBottomOf(const AABB &b)
{
    return intersectsBottomOf(*this,b);
}
bool AABB::intersectsRightOf(const AABB &b)
{
    return intersectsRightOf(*this,b);
}
bool AABB::intersects(const AABB &a, const AABB &b)
{
//    stats_intersectionCheckCounter++;
    return (a.m_pos.x <= b.m_pos.x + b.m_size.x && a.m_pos.x + a.m_size.x >= b.m_pos.x) &&
           (a.m_pos.y <= b.m_pos.y + b.m_size.y && a.m_pos.y + a.m_size.y >= b.m_pos.y);
}
bool AABB::intersectsInverseOf(const AABB &a, const AABB &b)
{
    return !(a.m_pos.x > b.m_pos.x && a.m_pos.x + a.m_size.x < b.m_pos.x + b.m_size.x &&
             a.m_pos.y > b.m_pos.y && a.m_pos.y + a.m_size.y < b.m_pos.y + b.m_size.y);
}
bool AABB::isLeftOf(const AABB &a, const AABB &b)
{
    return b.m_pos.x > a.m_pos.x + a.m_size.x;
}
bool AABB::isRightOf(const AABB &a, const AABB &b)
{
     return a.m_pos.x >  b.m_pos.x + b.m_size.x;
}
bool AABB::isOnTopOf(const AABB &a, const AABB &b)
{
    return b.m_pos.y > a.m_pos.y + a.m_size.y;
}
bool AABB::isBeneathOf(const AABB &a, const AABB &b)
{
    return a.m_pos.y >  b.m_pos.y + b.m_size.y;
}
bool AABB::intersectsTopOf(const AABB &a, const AABB &b)
{
    return a.m_pos.y < b.m_pos.y && a.m_pos.y+a.m_size.y > b.m_pos.y;
}
bool AABB::intersectsLeftOf(const AABB &a, const AABB &b)
{
    return a.m_pos.x < b.m_pos.x && a.m_pos.x+a.m_size.x > b.m_pos.x;
}
bool AABB::intersectsBottomOf(const AABB &a, const AABB &b)
{
    return a.m_pos.y < b.m_pos.y+b.m_size.y && a.m_pos.y+a.m_size.y > b.m_pos.y+b.m_size.y;
}
bool AABB::intersectsRightOf(const AABB &a, const AABB &b)
{
    return a.m_pos.x < b.m_pos.x+b.m_size.x && a.m_pos.x+a.m_size.x > b.m_pos.x+b.m_size.x;
}
unsigned long AABB::getStats_intersectionCheckCounter()
{
    return stats_intersectionCheckCounter;
}
void AABB::stats_reset()
{
    stats_intersectionCheckCounter = 0;
}

AABB AABB::getFrame(const vector<AABB> &list)
{
    Vector2f min, max;
    min.x = std::numeric_limits<float>::max();
    min.y = std::numeric_limits<float>::max();

    max.x = std::numeric_limits<float>::min();
    max.y = std::numeric_limits<float>::min();
    for(size_t i=0; i<list.size(); i++)
    {
        Vector2f pos = list[i].getPos();
        Vector2f size = list[i].getSize();
        if(min.x > pos.x)
            min.x = pos.x;
        if(min.y > pos.y)
            min.y = pos.y;

        if(max.x < size.x)
            max.x = size.x;
        if(max.y < size.y)
            max.y = size.y;
    }
    return AABB(min,max);
}

VertexPath* AABB::getDrawable(const Color &color) const
{
    VertexPath *path = new VertexPath;
    path->length = 5;
    path->type = sf::LineStrip;
    path->line = new sf::Vertex[path->length]
    {
        sf::Vertex(m_pos),
        sf::Vertex(m_pos + Vector2f(m_size.x,0)),
        sf::Vertex(m_pos + m_size),
        sf::Vertex(m_pos + Vector2f(0,m_size.y)),
        sf::Vertex(m_pos)
    };
    path->setColor(color);
    return path;
}
