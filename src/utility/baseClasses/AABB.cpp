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

void AABB::setPos(Vector2f pos)
{
    m_pos = pos;
}
void AABB::setSize(Vector2f size)
{
    m_size = {abs(size.x),abs(size.y)};
}
Vector2f AABB::getPos() const
{
    return m_pos;
}
Vector2f AABB::getSize() const
{
    return m_size;
}

bool AABB::intersects(const AABB &a, const AABB &b)
{
//    stats_intersectionCheckCounter++;
    return (a.m_pos.x <= b.m_pos.x + b.m_size.x && a.m_pos.x + a.m_size.x >= b.m_pos.x) &&
           (a.m_pos.y <= b.m_pos.y + b.m_size.y && a.m_pos.y + a.m_size.y >= b.m_pos.y);
}
unsigned long AABB::getStats_intersectionCheckCounter()
{
    return stats_intersectionCheckCounter;
}
void AABB::stats_reset()
{
    stats_intersectionCheckCounter = 0;
}

VertexPath* AABB::getDrawable(const Color &color)
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
