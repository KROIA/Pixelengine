#include "wall.h"

Wall::Wall()
    :   GameObject()
{
    m_collider      = new Collider();
    m_controller    = new Controller();
    m_painter       = new PixelPainter();

    this->setCollider(m_collider);
    this->addController(m_controller);
    this->setPainter(m_painter);

    this->setColor(Color(0,0,0));
    this->setDimension(1,1);
}
Wall::Wall(const Wall &other)
    :   GameObject(other)
{
    this->m_dimension   = other.m_dimension;
    this->m_color       = other.m_color;
}

Wall::~Wall()
{

}

void Wall::setDimension(const Vector2u  &dimension)
{
    m_dimension = dimension;
    this->generateObject();
}
void Wall::setDimension(const unsigned int &width,
                        const unsigned int &height)
{
    m_dimension = Vector2u(width,height);
    this->generateObject();
}
const Vector2u  &Wall::getDimension() const
{
    return m_dimension;
}
const unsigned int &Wall::getWidth() const
{
    return m_dimension.x;
}
const unsigned int &Wall::getHeight() const
{
    return m_dimension.y;
}

void Wall::setColor(const Color &color)
{
    m_color = color;
}
const Color &Wall::getColor() const
{
    return m_color;
}
Controller *Wall::getController()
{
    return m_controller;
}
void Wall::generateObject()
{
    m_collider->clear();
    m_collider->addHitbox(RectI(Vector2i(m_dimension)));
   /* for(unsigned int x=0; x<m_dimension.getX(); x++)
    {
        for(unsigned int y=0; y<m_dimension.getY(); y++)
        {
            m_painter->addPixel(Pixel(Point(x,y),m_color));
        }
    }*/
}
