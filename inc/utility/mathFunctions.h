#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <vector>

//#include "rect.h"

using sf::Vector2;
using sf::Vector2f;
using sf::Vector2u;
using sf::Vector2i;
using std::vector;

namespace Vector{

    template <typename T>
    inline float length(const Vector2<T> &vec)
    {
        return sqrt(pow(vec.x,2) + pow(vec.y,2));
    }

    template <typename T>
    inline Vector2<T> rotate(const Vector2<T> &vec,const Vector2<T> &rotPoint, float deg)
    {
        if(long(100*deg)%36000 == 0)
            return vec;
        if(length(vec - rotPoint) <= 0.00001)
            return vec;
        float newAngle = asin(float(vec.y-rotPoint.y) / length(vec-rotPoint));
        if((vec.x-rotPoint.x) < 0)
            newAngle = M_PI - newAngle;
        newAngle += deg * M_PI / 180;
        float l = length(vec-rotPoint);
        float xComp = cos(newAngle)*l;
        float yComp = sin(newAngle)*l;

        if(xComp<0.00001 && xComp>-0.00001)
            xComp = 0;
        if(yComp<0.00001 && yComp>-0.00001)
            yComp = 0;
        Vector2<T> res(xComp+rotPoint.x,yComp+rotPoint.y);
        return res;

/*
        if((vec-GeneralVector<T>(rotationPoint)).getLength() == 0)
               return vec;
           double newAngle = asin(double(vec.getY()-rotationPoint.getY())/(vec-GeneralVector<T>(rotationPoint)).getLength());
           if((vec.getX()-rotationPoint.getX()) < 0)
               newAngle = M_PI - newAngle;
           newAngle += angleRad;
           double l = (vec-GeneralVector<T>(rotationPoint)).getLength();
           double xComp = cos(newAngle)*l;
           double yComp = sin(newAngle)*l;
           GeneralVector<T> res(xComp+rotationPoint.getX(),yComp+rotationPoint.getY());
           return res;*/
    }
    template <typename T>
    inline Vector2<T> rotate(const Vector2<T> &vec, float deg)
    {
        return rotate(vec,Vector2<T>(0,0),deg);
    }

    template <typename T>
    inline Vector2<T> sum(const vector<Vector2<T> > &list)
    {
        Vector2<T> result(0,0);
        for(const Vector2<T> &summand : list)
            result += summand;
        return result;
    }
}

/*namespace Rect
{
    template<typename T>
    inline GeneralRect<T> rotate(GeneralRect<T> rect,const Vector2f &rotationPoint,const float &deg)
    {
        Vector2<T> vec(rect.m_size);


        vec = Vector::rotate(vec,rotationPoint,deg);


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
}
*/

#endif // MATH_H
