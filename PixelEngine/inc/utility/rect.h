#ifndef RECT_H
#define RECT_H

#include "point.h"
#include "vector.h"

template<class T>
class GeneralRect;

typedef GeneralRect<unsigned int> RectU;
typedef GeneralRect<int> Rect;
typedef GeneralRect<double> RectF;

template<class T>
class GeneralRect
{
    public:
        GeneralRect();
        GeneralRect(const T &width, const T &height);
        GeneralRect(const GeneralPoint<T> &size);
        GeneralRect(const T &xPos, const T &yPos, const T &width, const T &height);
        GeneralRect(const GeneralPoint<T> &pos, const GeneralPoint<T> &size);
        GeneralRect(const GeneralRect<T> &other);
        virtual ~GeneralRect();
        virtual GeneralRect<T> &operator=(const GeneralRect<T> &other);

        virtual void setPos(GeneralPoint<T> pos);
        virtual void setPos(const T &xPos, const T &yPos);
        virtual void setX(const T &x);
        virtual void setY(const T &y);
        virtual const T &getX();
        virtual const T &getY();

        virtual const GeneralPoint<T> &getPos() const;

        virtual void setSize(GeneralPoint<T> size);
        virtual void setSize(const T &width, const T &height);
        virtual const GeneralPoint<T> &getSize() const;

        virtual GeneralPoint<T> getCornerPoint_TL() const; // Top Left
        virtual GeneralPoint<T> getCornerPoint_TR() const; // Top Right
        virtual GeneralPoint<T> getCornerPoint_BL() const; // Bottom Left
        virtual GeneralPoint<T> getCornerPoint_BR() const; // Bottom Right

        virtual bool intersectsX(const GeneralRect<T> &other) const; // returns true if this and ohter are intersecting
        virtual bool intersectsY(const GeneralRect<T> &other) const; // returns true if this and ohter are intersecting
        virtual bool intersects(const GeneralRect<T> &other) const; // returns true if this and ohter are intersecting

        bool operator==(const GeneralRect<T> &other);
        bool operator!=(const GeneralRect<T> &other);

        static void stats_reset();
        static unsigned int stats_collisionCount;
        static unsigned int stats_collisionCheckCount;

        static GeneralRect<T> rotate(GeneralRect<T> rect,const double &rad);
        static GeneralRect<T> rotate_90(GeneralRect<T> rect);
        static GeneralRect<T> rotate_180(GeneralRect<T> rect);
        static GeneralRect<T> rotate_270(GeneralRect<T> rect);


    protected:

    private:
        GeneralPoint<T>  m_pos;
        GeneralPoint<T>  m_size;
};
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
GeneralRect<T>::GeneralRect(const GeneralPoint<T> &size)
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
GeneralRect<T>::GeneralRect( const GeneralPoint<T> &pos,const GeneralPoint<T> &size)
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
void GeneralRect<T>::setPos(GeneralPoint<T> pos)
{
    m_pos = pos;
}
template<class T>
void GeneralRect<T>::setPos(const T &xPos, const T &yPos)
{
    m_pos.setX(xPos);
    m_pos.setY(yPos);
}
template<class T>
void GeneralRect<T>::setX(const T &x)
{
    m_pos.setX(x);
}
template<class T>
void GeneralRect<T>::setY(const T &y)
{
    m_pos.setY(y);
}
template<class T>
const T &GeneralRect<T>::getX()
{
    return m_pos.getX();
}
template<class T>
const T &GeneralRect<T>::getY()
{
    return m_pos.getY();
}
template<class T>
const GeneralPoint<T> &GeneralRect<T>::getPos() const
{
    return m_pos;
}

template<class T>
void GeneralRect<T>::setSize(GeneralPoint<T> size)
{
    m_size = size;
}
template<class T>
void GeneralRect<T>::setSize(const T &width, const T &height)
{
    m_size.setX(width);
    m_size.setY(height);
}
template<class T>
const GeneralPoint<T> &GeneralRect<T>::getSize() const
{
    return m_size;
}

template<class T>
GeneralPoint<T> GeneralRect<T>::getCornerPoint_TL() const
{
    return m_pos;
}
template<class T>
GeneralPoint<T> GeneralRect<T>::getCornerPoint_TR() const
{
    return GeneralPoint<T>(m_pos.getX() + m_size.getX()-1, m_pos.getY());
}
template<class T>
GeneralPoint<T> GeneralRect<T>::getCornerPoint_BL() const
{
    return GeneralPoint<T>(m_pos.getX(), m_pos.getY() + m_size.getY()-1);
}
template<class T>
GeneralPoint<T> GeneralRect<T>::getCornerPoint_BR() const
{
    return GeneralPoint<T>(m_pos.getX() + m_size.getX()-1, m_pos.getY() + m_size.getY()-1);
}
template<class T>
bool GeneralRect<T>::intersectsX(const GeneralRect<T> &other) const
{
    // If one rectangle is on left side of other
    if(this->getCornerPoint_TL().getX() >  other.getCornerPoint_BR().getX() ||
       other.getCornerPoint_TL().getX() > this->getCornerPoint_BR().getX())
        return false;
    return true;
}
template<class T>
bool GeneralRect<T>::intersectsY(const GeneralRect<T> &other) const
{
    // If one rectangle is above other
    if(this->getCornerPoint_TL().getY() >  other.getCornerPoint_BR().getY() ||
       other.getCornerPoint_TL().getY() > this->getCornerPoint_BR().getY())
        return false;
    return true;
}
template<class T>
bool GeneralRect<T>::intersects(const GeneralRect<T> &other) const
{
    stats_collisionCheckCount++;
    if(intersectsX(other) && intersectsY(other))
    {
        stats_collisionCount++;
        return true;
    }
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
unsigned int GeneralRect<T>::stats_collisionCount = 0;
template<class T>
unsigned int GeneralRect<T>::stats_collisionCheckCount = 0;
template<class T>
void GeneralRect<T>::stats_reset()
{
    stats_collisionCount      = 0;
    stats_collisionCheckCount = 0;
}
template<class T>
GeneralRect<T> GeneralRect<T>::rotate(GeneralRect<T> rect,const double &rad)
{
    GeneralVector<T> vec(rect.m_size);
    vec = GeneralVector<T>::rotate(vec,rad);
    if(vec.getX()<0)
    {
        rect.m_pos.setX(rect.m_pos.getX()+vec.getX()+1);
        vec.setX(-vec.getX());
    }
    if(vec.getY()<0)
    {
        rect.m_pos.setY(rect.m_pos.getY()+vec.getY()+1);
        vec.setY(-vec.getY());
    }
    rect.m_size.set(vec.toPoint());
    return  rect;
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_90(GeneralRect<T> rect)
{
    GeneralRect<T>::rotate(rect,M_PI_2);
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_180(GeneralRect<T> rect)
{
    GeneralRect<T>::rotate(rect,M_PI);
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_270(GeneralRect<T> rect)
{
    GeneralRect<T>::rotate(rect,-M_PI_2);
}
#endif // RECT_H
