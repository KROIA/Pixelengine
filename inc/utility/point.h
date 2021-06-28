#ifndef POINT_H
#define POINT_H

#include <QDebug>
#include <math.h>

#include "profiler.h"

template<class T>
class GeneralPoint;

typedef GeneralPoint<unsigned int> PointU;
typedef GeneralPoint<int> Point;
typedef GeneralPoint<float> PointF;


template<class T>
class GeneralPoint
{
    public:
        GeneralPoint();
        GeneralPoint(const T &x, const T &y);
        GeneralPoint(const GeneralPoint<T> &other);
        virtual ~GeneralPoint();
        virtual GeneralPoint<T> &operator=(const GeneralPoint<T> &other);

        virtual void set(const GeneralPoint<T> &other);
        virtual void set(const T &x, const T &y);

        virtual void setX(const T &x);
        virtual void moveX(const T &deltaX);
        virtual const T  &getX() const;
        virtual void setY(const T &y);
        virtual void moveY(const T &deltaY);
        virtual const T  &getY() const;

        virtual void move(const GeneralPoint<T> &dir);
        virtual void move(const T &deltaX, const T &deltaY);


        bool operator==(const GeneralPoint<T> &other) const;
        bool operator!=(const GeneralPoint<T> &other) const;

        virtual T getDistance(const GeneralPoint<T> &other) const;

        static T getDistance(const GeneralPoint<T> &p1,const GeneralPoint<T> &p2);


    protected:
        T m_x;
        T m_y;
    private:

};




template<class T>
GeneralPoint<T>::GeneralPoint()
{
    this->set(0,0);
}
template<class T>
GeneralPoint<T>::GeneralPoint(const T &x, const T &y)
{
    this->set(x,y);
}
template<class T>
GeneralPoint<T>::GeneralPoint(const GeneralPoint<T> &other)
{
    this->set(other);
}
template<class T>
GeneralPoint<T>::~GeneralPoint()
{

}
template<class T>
GeneralPoint<T> &GeneralPoint<T>::operator=(const GeneralPoint<T> &other)
{
    this->set(other);
    return *this;
}
template<class T>
void GeneralPoint<T>::set(const GeneralPoint<T> &other)
{
    this->m_x = other.m_x;
    this->m_y = other.m_y;
}
template<class T>
void GeneralPoint<T>::set(const T &x, const T &y)
{
    this->m_x = x;
    this->m_y = y;
}

template<class T>
void GeneralPoint<T>::setX(const T &x)
{
    m_x = x;
}
template<class T>
void GeneralPoint<T>::moveX(const T &deltaX)
{
    m_x += deltaX;
}
template<class T>
const T &GeneralPoint<T>::getX() const
{
    return m_x;
}
template<class T>
void GeneralPoint<T>::setY(const T &y)
{
    m_y = y;
}
template<class T>
void GeneralPoint<T>::moveY(const T &deltaY)
{
    m_y += deltaY;
}
template<class T>
const T &GeneralPoint<T>::getY() const
{
    return m_y;
}

template<class T>
void GeneralPoint<T>::move(const GeneralPoint<T> &dir)
{
    m_x += dir.m_x;
    m_y += dir.m_y;
}
template<class T>
void GeneralPoint<T>::move(const T &deltaX, const T &deltaY)
{
    m_x += deltaX;
    m_y += deltaY;
}

template<class T>
bool GeneralPoint<T>::operator==(const GeneralPoint<T> &other) const
{
    if(this->m_x == other.m_x &&
       this->m_y == other.m_y)
        return true;
    return false;
}
template<class T>
bool GeneralPoint<T>::operator!=(const GeneralPoint<T> &other) const
{
    if(this->m_x != other.m_x)
        return true;
    if(this->m_y != other.m_y)
        return true;
    return false;
}
template<class T>
T GeneralPoint<T>::getDistance(const GeneralPoint<T> &other) const
{
    return getDistance(*this,other);
}

template<class T>
T GeneralPoint<T>::getDistance(const GeneralPoint<T> &p1,const GeneralPoint<T> &p2)
{
    GeneralPoint<float> _p1(p1.getX(),p1.getY());
    GeneralPoint<float> _p2(p2.getX(),p2.getY());

    return static_cast<T>(sqrt(pow(_p2.getX() - _p1.getX(),2) + pow(_p2.getY() - p1.getY(),2)));
}


#endif // POINT_H
