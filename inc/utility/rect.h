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
        GeneralRect(const Vector2<T> &topLeft, const Vector2<T> &topRight,
                    const Vector2<T> &bottomLeft, const Vector2<T> &bottomRight);
        GeneralRect(const GeneralRect<T> &other);
        virtual ~GeneralRect();
        virtual GeneralRect<T> &operator=(const GeneralRect<T> &other);

        virtual void move(const Vector2<T> &vec);
        virtual void set(const Vector2<T> &pos, const Vector2<T> &size);
        virtual void set(const T &posX, const T &posY, const T &width, const T &height);
        virtual void set(const Vector2<T> &topLeft, const Vector2<T> &topRight,
                         const Vector2<T> &bottomLeft, const Vector2<T> &bottomRight);
        virtual void setPos(const Vector2<T> &pos);
        virtual void setPos(const T &posX, const T &posY);
        virtual void setX(const T &x);
        virtual void setY(const T &y);
        virtual const T &getX() const;
        virtual const T &getY() const;

        virtual const Vector2<T> &getPos() const;

        virtual void setSize(Vector2<T> size);
        virtual void setSize(const T &width, const T &height);
        virtual Vector2<T> getSize() const;

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
        static GeneralRect<T> rotate(GeneralRect<T> rect,const Vector2<T> &rotationPoint,const float &deg);
        static GeneralRect<T> rotate_90(GeneralRect<T> rect,const Vector2<T> &rotationPoint = Vector2<T>(0,0));
        static GeneralRect<T> rotate_180(GeneralRect<T> rect,const Vector2<T> &rotationPoint = Vector2<T>(0,0));
        static GeneralRect<T> rotate_270(GeneralRect<T> rect,const Vector2<T> &rotationPoint = Vector2<T>(0,0));

        virtual void rotate(const Vector2<T> &rotationPoint,const float &deg);

        // A Rect which includes all rects in the List
        static GeneralRect<T> getFrame(const std::vector<GeneralRect<T> > &list);
        static int getMinX(const std::vector<GeneralRect<T> > &list);
        static int getMaxX(const std::vector<GeneralRect<T> > &list);
        static int getMinY(const std::vector<GeneralRect<T> > &list);
        static int getMaxY(const std::vector<GeneralRect<T> > &list);

        /*static unsigned long long stats_getIntersectionCounter();
        static void stats_resetIntersectionCounter();
        static void stats_reset();*/


    protected:
       // static unsigned long long stats_intersectionCounter;

    private:
       // Vector2<T>  m_pos;
       // Vector2<T>  m_size;
        Vector2<T> TL;
        Vector2<T> TR;
        Vector2<T> BL;
        Vector2<T> BR;
};
/*template<class T>
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
}*/

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
GeneralRect<T>::GeneralRect(const Vector2<T> &topLeft, const Vector2<T> &topRight,
                            const Vector2<T> &bottomLeft, const Vector2<T> &bottomRight)
{
    this->set(topLeft,topRight,bottomLeft,bottomRight);
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
    //this->m_pos  = other.m_pos;
    //this->m_size = other.m_size;
    this->TL = other.TL;
    this->TR = other.TR;
    this->BL = other.BL;
    this->BR = other.BR;
    return *this;
}
template<class T>
void GeneralRect<T>::move(const Vector2<T> &vec)
{
    TL += vec;
    TR += vec;
    BL += vec;
    BR += vec;
   // m_pos += vec;
}
template<class T>
void GeneralRect<T>::set(const Vector2<T> &pos, const Vector2<T> &size)
{
    TL = pos;
    TR = TL + Vector2<T>(size.x,0);
    BL = TL + Vector2<T>(0,size.y);
    BR = TL + size;
   /* m_pos  = pos;
    m_size = size;*/
}
template<class T>
void GeneralRect<T>::set(const T &posX, const T &posY, const T &width, const T &height)
{
    TL = Vector2<T>(posX,posY);
    TR = TL + Vector2<T>(width,0);
    BL = TL + Vector2<T>(0,height);
    BR = TL + Vector2<T>(width,height);
    /*
    m_pos.x = posX;
    m_pos.y = posY;
    m_size.x = width;
    m_size.y = height;*/
}
template<class T>
void GeneralRect<T>::set(const Vector2<T> &topLeft, const Vector2<T> &topRight,
                         const Vector2<T> &bottomLeft, const Vector2<T> &bottomRight)
{
    TL = topLeft;
    TR = topRight;
    BL = bottomLeft;
    BR = bottomRight;
}
template<class T>
void GeneralRect<T>::setPos(const Vector2<T> &pos)
{
    Vector2<T> delta(pos - TL);
    this->move(delta);
    //m_pos = pos;
}
template<class T>
void GeneralRect<T>::setPos(const T &posX, const T &posY)
{
    this->setPos(Vector2<T>(posX,posY));
    //m_pos.x = posX;
    //m_pos.y = posY;
}
template<class T>
void GeneralRect<T>::setX(const T &x)
{
    this->setPos(Vector2<T>(x,TL.y));
    //m_pos.x = x;
}
template<class T>
void GeneralRect<T>::setY(const T &y)
{
    this->setPos(Vector2<T>(TL.x,y));
    //m_pos.y = y;
}
template<class T>
const T &GeneralRect<T>::getX() const
{
    return TL.x;
}
template<class T>
const T &GeneralRect<T>::getY() const
{
    return TL.y;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getPos() const
{
    return TL;
}

template<class T>
void GeneralRect<T>::setSize(Vector2<T> size)
{
    TR = TL + Vector2<T>(size.x,0);
    BL = TL + Vector2<T>(0,size.y);
    BR = TL + size;
    //m_size = size;
}
template<class T>
void GeneralRect<T>::setSize(const T &width, const T &height)
{
    this->setSize(Vector2<T>(width,height));
    //m_size.x = width;
    //m_size.y = height;
}
template<class T>
Vector2<T> GeneralRect<T>::getSize() const
{
    return BR - TL;
    //return m_size;
}

template<class T>
Vector2<T> GeneralRect<T>::getCornerPoint_TL() const
{
    return TL;
}
template<class T>
Vector2<T> GeneralRect<T>::getCornerPoint_TR() const
{
    return TR;
    //return Vector2<T>(m_pos.x + m_size.x-1, m_pos.y);
}
template<class T>
Vector2<T> GeneralRect<T>::getCornerPoint_BL() const
{
    return BL;
    //return Vector2<T>(m_pos.x, m_pos.y + m_size.y-1);
}
template<class T>
Vector2<T> GeneralRect<T>::getCornerPoint_BR() const
{
    return BR;
    //return Vector2<T>(m_pos.x + m_size.x-1, m_pos.y + m_size.y-1);
}
template<class T>
bool GeneralRect<T>::intersectsX(const GeneralRect<T> &other) const
{
   // GeneralRect<T>::stats_intersectionCounter ++;
    // If one rectangle is on left side of other
    if(this->getCornerPoint_TL().x >  other.getCornerPoint_BR().x ||
       other.getCornerPoint_TL().x > this->getCornerPoint_BR().x)
        return false;
    return true;
}
template<class T>
bool GeneralRect<T>::intersectsY(const GeneralRect<T> &other) const
{
    //GeneralRect<T>::stats_intersectionCounter ++;
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
       // GeneralRect<T>::stats_intersectionCounter--;
        return true;
    }
    //GeneralRect<T>::stats_intersectionCounter--; // Because for x and y will be added 2 and now its back at +1
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
GeneralRect<T> GeneralRect<T>::rotate(GeneralRect<T> rect,const Vector2<T> &rotationPoint,const float &deg)
{
    rect.rotate(rotationPoint,deg);
    return  rect;
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_90(GeneralRect<T> rect,const Vector2<T> &rotationPoint)
{
    GeneralRect<T>::rotate(rect,rotationPoint,90);
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_180(GeneralRect<T> rect,const Vector2<T> &rotationPoint)
{
    GeneralRect<T>::rotate(rect,rotationPoint,180);
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_270(GeneralRect<T> rect,const Vector2<T> &rotationPoint)
{
    GeneralRect<T>::rotate(rect,rotationPoint,-90);
}
//#include <QDebug>
template<class T>
void GeneralRect<T>::rotate(const Vector2<T> &rotationPoint,const float &deg)
{
    sf::Transform transform;
    transform.rotate(deg,Vector2f(rotationPoint));

    TL = Vector2<T>(transform.transformPoint(Vector2f(TL)));
    TR = Vector2<T>(transform.transformPoint(Vector2f(TR)));
    BL = Vector2<T>(transform.transformPoint(Vector2f(BL)));
    BR = Vector2<T>(transform.transformPoint(Vector2f(BR)));
    /*sf::Rect<float> rect(m_pos.x,m_pos.y,m_size.x,m_size.y);
    sf::Transform transform;
    transform.rotate(deg,Vector2f(rotationPoint));
    rect = transform.transformRect(rect);

    m_pos = Vector2<T>(rect.getPosition());
    m_size = Vector2<T>(rect.getSize());

    qDebug() << "m_pos: "<<m_pos.x<< " "<<m_pos.y;
    qDebug() << "m_size: "<<m_size.x<< " "<<m_size.y;*/
    /*Vector2f vec(m_size);

    //m_size = Vector::getRotated(m_size,rotationPoint,deg);
    Vector::rotate(vec,Vector2f(rotationPoint),deg);

    if(vec.x<0)
    {
        m_pos.x   = m_pos.x+vec.x+1;
        vec.x *= -1;
    }
    if(vec.y<0)
    {
        m_pos.y   = m_pos.y+vec.y+1;
        vec.y *= -1;
    }
    m_size = Vector2<T>(vec);*/
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
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_TL().x < minX)
            minX = list[i].getCornerPoint_TL().x;
        if(list[i].getCornerPoint_TR().x < minX)
            minX = list[i].getCornerPoint_TR().x;
        if(list[i].getCornerPoint_BL().x < minX)
            minX = list[i].getCornerPoint_BL().x;
        if(list[i].getCornerPoint_BR().x < minX)
            minX = list[i].getCornerPoint_BR().x;
    }
    return minX;
}
template<class T>
int GeneralRect<T>::getMaxX(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    int maxX = list[0].getCornerPoint_TL().x;
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_TL().x > maxX)
            maxX = list[i].getCornerPoint_TL().x;
        if(list[i].getCornerPoint_TR().x > maxX)
            maxX = list[i].getCornerPoint_TR().x;
        if(list[i].getCornerPoint_BL().x > maxX)
            maxX = list[i].getCornerPoint_BL().x;
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
        if(list[i].getCornerPoint_TR().y < minY)
            minY = list[i].getCornerPoint_TR().y;
        if(list[i].getCornerPoint_BL().y < minY)
            minY = list[i].getCornerPoint_BL().y;
        if(list[i].getCornerPoint_BR().y < minY)
            minY = list[i].getCornerPoint_BR().y;
    }
    return minY;
}
template<class T>
int GeneralRect<T>::getMaxY(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    int maxY = list[0].getCornerPoint_TL().y;
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_TL().y > maxY)
            maxY = list[i].getCornerPoint_TL().y;
        if(list[i].getCornerPoint_TR().y > maxY)
            maxY = list[i].getCornerPoint_TR().y;
        if(list[i].getCornerPoint_BL().y > maxY)
            maxY = list[i].getCornerPoint_BL().y;
        if(list[i].getCornerPoint_BR().y > maxY)
            maxY = list[i].getCornerPoint_BR().y;
    }
    return maxY;
}
#endif // RECT_H
