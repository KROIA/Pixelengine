#ifndef RECT_H
#define RECT_H

#include <SFML/System/Vector2.hpp>
#include "mathFunctions.h"
#include "drawUtilities.h"

#include "profiler.h"

template<class T>
class GeneralRect;



typedef GeneralRect<unsigned int> RectU;
typedef GeneralRect<int> RectI;
typedef GeneralRect<float> RectF;



template<class T>
class GeneralRect
{
    public:

        GeneralRect();
        GeneralRect(const T &width, const T &height);
        GeneralRect(const Vector2<T> &size);
        GeneralRect(const T &xPos, const T &yPos, const T &width, const T &height);
        GeneralRect(const Vector2<T> &pos, const Vector2<T> &size);
        GeneralRect(const GeneralRect<T> &other);
        virtual ~GeneralRect();
        virtual GeneralRect<T> &operator=(const GeneralRect<T> &other);

        virtual void move(const Vector2<T> &vec);
        virtual void set(const Vector2<T> &pos, const Vector2<T> &size);
        virtual void set(const T &posX, const T &posY, const T &width, const T &height);
        virtual void setPos(const Vector2<T> &pos);
        virtual void setPos(const T &posX, const T &posY);
        virtual void setX(const T &x);
        virtual void setY(const T &y);
        virtual const T &getX() const;
        virtual const T &getY() const;

        virtual const Vector2<T> &getPos() const;

        virtual void setSize(Vector2<T> size);
        virtual void setSize(const T &width, const T &height);
        virtual const Vector2<T> &getSize() const;

        virtual Vector2<T> getCornerPoint_TL() const; // Top Left
        virtual Vector2<T> getCornerPoint_TR() const; // Top Right
        virtual Vector2<T> getCornerPoint_BL() const; // Bottom Left
        virtual Vector2<T> getCornerPoint_BR() const; // Bottom Right

        virtual bool intersectsX(const GeneralRect<T> &other) const; // returns true if this and ohter are intersecting
        virtual bool intersectsY(const GeneralRect<T> &other) const; // returns true if this and ohter are intersecting
        virtual bool intersects(const GeneralRect<T> &other) const; // returns true if this and ohter are intersecting

        bool operator==(const GeneralRect<T> &other);
        bool operator!=(const GeneralRect<T> &other);

        VertexPath getDrawable(const sf::Color &color = sf::Color(255,255,255,255)) const;

        static GeneralRect<T> rotate(GeneralRect<T> rect,const float &deg);
        static GeneralRect<T> rotate(GeneralRect<T> rect,const Vector2f &rotationPoint,const float &deg);
        static GeneralRect<T> rotate_90(GeneralRect<T> rect,const Vector2f &rotationPoint = Vector2f(0,0));
        static GeneralRect<T> rotate_180(GeneralRect<T> rect,const Vector2f &rotationPoint = Vector2f(0,0));
        static GeneralRect<T> rotate_270(GeneralRect<T> rect,const Vector2f &rotationPoint = Vector2f(0,0));

        // A Rect which includes all rects in the List
        static GeneralRect<T> getFrame(const std::vector<GeneralRect<T> > &list);
        static int getMinX(const std::vector<GeneralRect<T> > &list);
        static int getMaxX(const std::vector<GeneralRect<T> > &list);
        static int getMinY(const std::vector<GeneralRect<T> > &list);
        static int getMaxY(const std::vector<GeneralRect<T> > &list);

        static unsigned long long stats_getIntersectionCounter();
        static void stats_resetIntersectionCounter();
        static void stats_reset();


    protected:
        static unsigned long long stats_intersectionCounter;

    private:
        Vector2<T>  m_pos;
        Vector2<T>  m_size;
};
template<class T>
unsigned long long GeneralRect<T>::stats_intersectionCounter = 0;
template<class T>
unsigned long long GeneralRect<T>::stats_getIntersectionCounter()
{
    return GeneralRect<T>::stats_intersectionCounter;
}
template<class T>
void GeneralRect<T>::stats_resetIntersectionCounter(){
    GeneralRect<T>::stats_intersectionCounter = 0;
}
template<class T>
void GeneralRect<T>::stats_reset()
{
    GeneralRect<T>::stats_resetIntersectionCounter();
}

template<class T>
GeneralRect<T>::GeneralRect()
{
    this->setPos(0,0);
    this->setSize(1,1);
}
template<class T>
GeneralRect<T>::GeneralRect(const T &width, const T &height)
{
    this->setSize(width,height);
}
template<class T>
GeneralRect<T>::GeneralRect(const Vector2<T> &size)
{
    this->setSize(size);
}
template<class T>
GeneralRect<T>::GeneralRect(const T &xPos, const T &yPos, const T &width, const T &height)
{
    this->setPos(xPos,yPos);
    this->setSize(width,height);
}
template<class T>
GeneralRect<T>::GeneralRect( const Vector2<T> &pos,const Vector2<T> &size)
{
    this->setPos(pos);
    this->setSize(size);
}
template<class T>
GeneralRect<T>::GeneralRect(const GeneralRect<T> &other)
{
    *this = other;
}
template<class T>
GeneralRect<T>::~GeneralRect()
{

}
template<class T>
GeneralRect<T> &GeneralRect<T>::operator=(const GeneralRect<T> &other)
{
    this->m_pos  = other.m_pos;
    this->m_size = other.m_size;
    return *this;
}
template<class T>
void GeneralRect<T>::move(const Vector2<T> &vec)
{
    m_pos += vec;
}
template<class T>
void GeneralRect<T>::set(const Vector2<T> &pos, const Vector2<T> &size)
{
    m_pos  = pos;
    m_size = size;
}
template<class T>
void GeneralRect<T>::set(const T &posX, const T &posY, const T &width, const T &height)
{
    m_pos.x = posX;
    m_pos.y = posY;
    m_size.x = width;
    m_size.y = height;
}
template<class T>
void GeneralRect<T>::setPos(const Vector2<T> &pos)
{
    m_pos = pos;
}
template<class T>
void GeneralRect<T>::setPos(const T &posX, const T &posY)
{
    m_pos.x = posX;
    m_pos.y = posY;
}
template<class T>
void GeneralRect<T>::setX(const T &x)
{
    m_pos.x = x;
}
template<class T>
void GeneralRect<T>::setY(const T &y)
{
    m_pos.y = y;
}
template<class T>
const T &GeneralRect<T>::getX() const
{
    return m_pos.x;
}
template<class T>
const T &GeneralRect<T>::getY() const
{
    return m_pos.y;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getPos() const
{
    return m_pos;
}

template<class T>
void GeneralRect<T>::setSize(Vector2<T> size)
{
    m_size = size;
}
template<class T>
void GeneralRect<T>::setSize(const T &width, const T &height)
{
    m_size.x = width;
    m_size.y = height;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getSize() const
{
    return m_size;
}

template<class T>
Vector2<T> GeneralRect<T>::getCornerPoint_TL() const
{
    return m_pos;
}
template<class T>
Vector2<T> GeneralRect<T>::getCornerPoint_TR() const
{
    return Vector2<T>(m_pos.x + m_size.x-1, m_pos.y);
}
template<class T>
Vector2<T> GeneralRect<T>::getCornerPoint_BL() const
{
    return Vector2<T>(m_pos.x, m_pos.y + m_size.y-1);
}
template<class T>
Vector2<T> GeneralRect<T>::getCornerPoint_BR() const
{
    return Vector2<T>(m_pos.x + m_size.x-1, m_pos.y + m_size.y-1);
}
template<class T>
bool GeneralRect<T>::intersectsX(const GeneralRect<T> &other) const
{
    GeneralRect<T>::stats_intersectionCounter ++;
    // If one rectangle is on left side of other
    if(this->getCornerPoint_TL().x >  other.getCornerPoint_BR().x ||
       other.getCornerPoint_TL().x > this->getCornerPoint_BR().x)
        return false;
    return true;
}
template<class T>
bool GeneralRect<T>::intersectsY(const GeneralRect<T> &other) const
{
    GeneralRect<T>::stats_intersectionCounter ++;
    // If one rectangle is above other
    if(this->getCornerPoint_TL().y >  other.getCornerPoint_BR().y ||
       other.getCornerPoint_TL().y > this->getCornerPoint_BR().y)
        return false;
    return true;
}
template<class T>
bool GeneralRect<T>::intersects(const GeneralRect<T> &other) const
{

    if(intersectsX(other) && intersectsY(other))
    {
        GeneralRect<T>::stats_intersectionCounter--;
        return true;
    }
    GeneralRect<T>::stats_intersectionCounter--; // Because for x and y will be added 2 and now its back at +1
    return false;
}

template<class T>
bool GeneralRect<T>::operator==(const GeneralRect<T> &other)
{
    if(this->getCornerPoint_TL() != other.getCornerPoint_TL())
        return false;
    if(this->getCornerPoint_TR() != other.getCornerPoint_TR())
        return false;
    if(this->getCornerPoint_BL() != other.getCornerPoint_BL())
        return false;
    if(this->getCornerPoint_BR() != other.getCornerPoint_BR())
        return false;
    return true;
}
template<class T>
bool GeneralRect<T>::operator!=(const GeneralRect<T> &other)
{
    if(this->getCornerPoint_TL() != other.getCornerPoint_TL())
        return true;
    if(this->getCornerPoint_TR() != other.getCornerPoint_TR())
        return true;
    if(this->getCornerPoint_BL() != other.getCornerPoint_BL())
        return true;
    if(this->getCornerPoint_BR() != other.getCornerPoint_BR())
        return true;
    return false;
}
template<class T>
VertexPath GeneralRect<T>::getDrawable(const sf::Color &color) const
{
    VertexPath path;
    path.length = 12;
    path.type = sf::Lines;
    path.line = new sf::Vertex[path.length]
    {
        sf::Vertex(Vector2f(getCornerPoint_TL())),
        sf::Vertex(Vector2f(getCornerPoint_TR()) + Vector2f(1,0)),

        sf::Vertex(Vector2f(getCornerPoint_TR()) + Vector2f(1,0)),
        sf::Vertex(Vector2f(getCornerPoint_BR()) + Vector2f(1,1)),

        sf::Vertex(Vector2f(getCornerPoint_BR()) + Vector2f(1,1)),
        sf::Vertex(Vector2f(getCornerPoint_BL()) + Vector2f(0,1)),

        sf::Vertex(Vector2f(getCornerPoint_BL()) + Vector2f(0,1)),
        sf::Vertex(Vector2f(getCornerPoint_TL())),

        sf::Vertex(Vector2f(getCornerPoint_TL())),
        sf::Vertex(Vector2f(getCornerPoint_BR()) + Vector2f(1,1)),

        sf::Vertex(Vector2f(getCornerPoint_TR()) + Vector2f(1,0)),
        sf::Vertex(Vector2f(getCornerPoint_BL()) + Vector2f(0,1))
    };

    for(std::size_t i=0; i<path.length; i++)
        path.line[i].color = color;

    return path;
}

template<class T>
GeneralRect<T> GeneralRect<T>::rotate(GeneralRect<T> rect,const float &deg)
{
    return GeneralRect<T>::rotate(rect,Vector2<T>(0,0),deg);
}
template<class T>
GeneralRect<T> GeneralRect<T>::rotate(GeneralRect<T> rect,const Vector2f &rotationPoint,const float &deg)
{
    Vector2<T> vec(rect.m_size);

    vec = Vector::rotate(vec,rotationPoint,deg);


    if(vec.x<0)
    {
        rect.m_pos.x = rect.m_pos.x+vec.x+1;
        vec.x *= -1;
    }
    if(vec.y<0)
    {
        rect.m_pos.y = rect.m_pos.y+vec.y+1;
        vec.y *= -1;
    }
    rect.m_size = vec;
    return  rect;
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_90(GeneralRect<T> rect,const Vector2f &rotationPoint)
{
    GeneralRect<T>::rotate(rect,rotationPoint,90);
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_180(GeneralRect<T> rect,const Vector2f &rotationPoint)
{
    GeneralRect<T>::rotate(rect,rotationPoint,180);
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_270(GeneralRect<T> rect,const Vector2f &rotationPoint)
{
    GeneralRect<T>::rotate(rect,rotationPoint,-90);
}

template<class T>
GeneralRect<T> GeneralRect<T>::getFrame(const std::vector<GeneralRect<T> > &list)
{
    T minX = GeneralRect<T>::getMinX(list);
    T minY = GeneralRect<T>::getMinY(list);
    T maxX = GeneralRect<T>::getMaxX(list);
    T maxY = GeneralRect<T>::getMaxY(list);

    return GeneralRect<T>(minX,minY,maxX-minX+1,maxY-minY+1);
}
template<class T>
int GeneralRect<T>::getMinX(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    int minX = list[0].getCornerPoint_TL().x;
    for(size_t i=1; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_TL().x < minX)
            minX = list[i].getCornerPoint_TL().x;
    }
    return minX;
}
template<class T>
int GeneralRect<T>::getMaxX(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    int maxX = list[0].getCornerPoint_BR().x;
    for(size_t i=1; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_BR().x > maxX)
            maxX = list[i].getCornerPoint_BR().x;
    }
    return maxX;
}
template<class T>
int GeneralRect<T>::getMinY(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    int minY = list[0].getCornerPoint_TL().y;
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_TL().y < minY)
            minY = list[i].getCornerPoint_TL().y;
    }
    return minY;
}
template<class T>
int GeneralRect<T>::getMaxY(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    int maxY = list[0].getCornerPoint_BL().y;
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_BL().y > maxY)
            maxY = list[i].getCornerPoint_BL().y;
    }
    return maxY;
}
#endif // RECT_H
