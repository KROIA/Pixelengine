#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <math.h>
#include <vector>
#include <QtDebug>

#include "profiler.h"

//#include "rect.h"

using sf::Vector2;
using sf::Vector2f;
using sf::Vector2u;
using sf::Vector2i;
using std::vector;

namespace Vector{
    template <typename T>
    inline float length(const Vector2<T> &vec);
    template <typename T>
    inline Vector2<T> getRotated(const Vector2<T> &vec,const Vector2<T> &rotPoint, float deg);
    inline void rotate(Vector2f &vec,const Vector2f &rotPoint, float deg);
    template <typename T>
    inline Vector2<T> getRotated(const Vector2<T> &vec, float deg);
    template <typename T>
    inline Vector2<T> sum(const vector<Vector2<T> > &list);
    template <typename T>
    inline bool doesIntersect(const Vector2<T> &directionVector_1,
                              const Vector2<T> &directionVector_2);
    template <typename T>
    inline Vector2<T> getIntersection(const Vector2<T> &supportVector_1,const Vector2<T> &directionVector_1,
                                 const Vector2<T> &supportVector_2,const Vector2<T> &directionVector_2);
    template <typename T>
    inline T getDotProduct(const Vector2<T> &vec1,const Vector2<T> &vec2);
    template <typename T>
    inline T getAngle(const Vector2<T> &vec1,const Vector2<T> &vec2);
    template <typename T>
    inline Vector2<T> getAverage(const vector<Vector2<T> > &list);
    template <typename T>
    inline Vector2<T> print(const Vector2<T> &vec);


    template <typename T>
    inline float length(const Vector2<T> &vec)
    {
        return sqrt(pow(vec.x,2) + pow(vec.y,2));
    }

    template <typename T>
    inline Vector2<T> getRotated(const Vector2<T> &vec,const Vector2<T> &rotPoint, float deg)
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
    }

    inline void rotate(Vector2f &vec,const Vector2f &rotPoint, float deg)
    {
        sf::Transform t;
        t.rotate(deg, rotPoint);
        vec = t.transformPoint(vec);
        //vec = sf::Transform(vec).rotate(deg, rotPoint);
        /*
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
        vec = Vector2<T>(xComp+rotPoint.x,yComp+rotPoint.y);*/
    }
    template <typename T>
    inline Vector2<T> getRotated(const Vector2<T> &vec, float deg)
    {
        return getRotated(vec,Vector2<T>(0,0),deg);
    }

    template <typename T>
    inline Vector2<T> sum(const vector<Vector2<T> > &list)
    {
        Vector2<T> result(0,0);
        for(const Vector2<T> &summand : list)
            result += summand;
        return result;
    }

    template <typename T>
    inline bool doesIntersect(const Vector2<T> &directionVector_1,
                              const Vector2<T> &directionVector_2)
    {
        EASY_FUNCTION(profiler::colors::Blue100);
        if(getAngle(directionVector_1,directionVector_2) == 0)
            return false;
        return true;
    }
    template <typename T>
    inline Vector2<T> getIntersection(const Vector2<T> &supportVector_1,const Vector2<T> &directionVector_1,
                                      const Vector2<T> &supportVector_2,const Vector2<T> &directionVector_2)
    {
        EASY_FUNCTION(profiler::colors::Blue);

        T divisor = directionVector_2.y * directionVector_1.x - directionVector_2.x * directionVector_1.y;
        if(divisor <= 0.00001 && divisor >= -0.00001)
            return Vector2<T>(2,2);

        divisor = 1.f/divisor;

        T deltaX = supportVector_1.x - supportVector_2.x;
        T deltaY = supportVector_1.y - supportVector_2.y;


        // factorA is the intersectionFactor for f(factorA) = supportVector_1 + directionVector_1 * factorA;
        T factorA = (directionVector_2.x * deltaY - directionVector_2.y * deltaX) * divisor;

        // factorB is the intersectionFactor for f(factorB) = supportVector_2 + directionVector_2 * factorB;
        T factorB = (directionVector_1.x * deltaY - directionVector_1.y * deltaX) * divisor;

        return Vector2<T>(factorA,factorB);

    }
    template <typename T>
    inline T getDotProduct(const Vector2<T> &vec1,const Vector2<T> &vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }
    template <typename T>
    inline T getAngle(const Vector2<T> &vec1,const Vector2<T> &vec2)
    {
        float area = length(vec1) * length(vec2);
        if(area == 0)
            return 0;
        return acos(getDotProduct(vec1,vec2) / area);
    }
    template <typename T>
    inline Vector2<T> getAverage(const vector<Vector2<T> > &list)
    {
        Vector2<T> result(0,0);
        if(list.size() == 0)
            return result;
        for(size_t i=0; i<list.size(); i++)
        {
            result += list[i];
        }
        result /= list.size();
        return result;
    }


    template <typename T>
    inline Vector2<T> print(const Vector2<T> &vec)
    {
        qDebug() << "Vector: X="<<vec.x<<"\tY="<<vec.y;
    }
}


#endif // MATH_H
