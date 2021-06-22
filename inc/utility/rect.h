#ifndef RECT_H
#define RECT_H

#include "point.h"
#include "vector.h"

#include "profiler.h"

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

        virtual void set(const GeneralPoint<T> &pos, const GeneralPoint<T> &size);
        virtual void set(const T &posX, const T &posY, const T &sizeX, const T &sizeY);
        virtual void setPos(const GeneralPoint<T> &pos);
        virtual void setPos(const T &xPos, const T &yPos);
        virtual void setX(const T &x);
        virtual void setY(const T &y);
        virtual const T &getX() const;
        virtual const T &getY() const;

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

        static GeneralRect<T> rotate(GeneralRect<T> rect,const double &rad);
        static GeneralRect<T> rotate(GeneralRect<T> rect,const PointF &rotationPoint,const double &rad);
        static GeneralRect<T> rotate_90(GeneralRect<T> rect,const PointF &rotationPoint = PointF(0,0));
        static GeneralRect<T> rotate_180(GeneralRect<T> rect,const PointF &rotationPoint = PointF(0,0));
        static GeneralRect<T> rotate_270(GeneralRect<T> rect,const PointF &rotationPoint = PointF(0,0));

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
        GeneralPoint<T>  m_pos;
        GeneralPoint<T>  m_size;
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
void GeneralRect<T>::set(const GeneralPoint<T> &pos, const GeneralPoint<T> &size)
{
    m_pos  = pos;
    m_size = size;
}
template<class T>
void GeneralRect<T>::set(const T &posX, const T &posY, const T &sizeX, const T &sizeY)
{
    m_pos.set(posX,posY);
    m_size.set(sizeX,sizeY);
}
template<class T>
void GeneralRect<T>::setPos(const GeneralPoint<T> &pos)
{
    m_pos = pos;
}
template<class T>
void GeneralRect<T>::setPos(const T &xPos, const T &yPos)
{
    m_pos.set(xPos,yPos);
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
const T &GeneralRect<T>::getX() const
{
    return m_pos.getX();
}
template<class T>
const T &GeneralRect<T>::getY() const
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
    m_size.set(width,height);
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
    GeneralRect<T>::stats_intersectionCounter ++;
    // If one rectangle is on left side of other
    if(this->getCornerPoint_TL().getX() >  other.getCornerPoint_BR().getX() ||
       other.getCornerPoint_TL().getX() > this->getCornerPoint_BR().getX())
        return false;
    return true;
}
template<class T>
bool GeneralRect<T>::intersectsY(const GeneralRect<T> &other) const
{
    GeneralRect<T>::stats_intersectionCounter ++;
    // If one rectangle is above other
    if(this->getCornerPoint_TL().getY() >  other.getCornerPoint_BR().getY() ||
       other.getCornerPoint_TL().getY() > this->getCornerPoint_BR().getY())
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
GeneralRect<T> GeneralRect<T>::rotate(GeneralRect<T> rect,const double &rad)
{
    return GeneralRect<T>::rotate(rect,GeneralPoint<T>(0,0),rad);
}
template<class T>
GeneralRect<T> GeneralRect<T>::rotate(GeneralRect<T> rect,const PointF &rotationPoint,const double &rad)
{
    GeneralVector<T> vec(rect.m_size);
    vec = GeneralVector<T>::rotate(vec,rotationPoint,rad);
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
GeneralRect<T>  GeneralRect<T>::rotate_90(GeneralRect<T> rect,const PointF &rotationPoint)
{
    GeneralRect<T>::rotate(rect,M_PI_2,rotationPoint);
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_180(GeneralRect<T> rect,const PointF &rotationPoint)
{
    GeneralRect<T>::rotate(rect,M_PI,rotationPoint);
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_270(GeneralRect<T> rect,const PointF &rotationPoint)
{
    GeneralRect<T>::rotate(rect,-M_PI_2,rotationPoint);
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
    int minX = list[0].getCornerPoint_TL().getX();
    for(size_t i=1; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_TL().getX() < minX)
            minX = list[i].getCornerPoint_TL().getX();
    }
    return minX;
}
template<class T>
int GeneralRect<T>::getMaxX(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    int maxX = list[0].getCornerPoint_BR().getX();
    for(size_t i=1; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_BR().getX() > maxX)
            maxX = list[i].getCornerPoint_BR().getX();
    }
    return maxX;
}
template<class T>
int GeneralRect<T>::getMinY(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    int minY = list[0].getCornerPoint_TL().getY();
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_TL().getY() < minY)
            minY = list[i].getCornerPoint_TL().getY();
    }
    return minY;
}
template<class T>
int GeneralRect<T>::getMaxY(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    int maxY = list[0].getCornerPoint_BL().getY();
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].getCornerPoint_BL().getY() > maxY)
            maxY = list[i].getCornerPoint_BL().getY();
    }
    return maxY;
}
#endif // RECT_H
