#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include "base.h"
#include "drawUtilities.h"

namespace Vector{
    template <typename T>
    struct Func2{
            Vector2<T> support;
            Vector2<T> direction;
            T scalar;
            inline Vector2<T> operator()(const T &scalar) const
            {
                return support + (direction * scalar);
            }
            inline Vector2<T> getPoint() const
            {
                return (*this)(scalar);
            }
    };
    typedef Func2<float> Func2f;
    typedef Func2<int> Func2i;


    template <typename T>
    inline float length(const Vector2<T> &vec);
    template <typename T>
    inline Vector2<T> getRotated(const Vector2<T> &vec,const Vector2<T> &rotPoint, float deg);
    inline void rotate(Vector2f &vec,const Vector2f &rotPoint, float deg);
    inline void rotate(vector<Vector2f> &points,const Vector2f &rotPoint, float deg);
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
    inline void print(const Vector2<T> &vec);
    template <typename T>
    inline const string toString(const Vector2<T> &vec);
    template <typename T>
    inline VertexPath* getDrawableVectorFunc(const Func2<T> &vecFunc,const T &scalar,const sf::Color &color = sf::Color(255,255,255));
    template <typename T>
    inline VertexPath* getDrawableVectorFunc(const Vector2<T> &ref,const Func2<T> &vecFunc,const T &scalar,const sf::Color &color = sf::Color(255,255,255));
    template <typename T>
    inline VertexPath* getDrawableVector(const Vector2<T> &begin,const Vector2<T> &end,const sf::Color &color = sf::Color(255,255,255));
    template <typename T>
    inline Vector2<T>  multiply(const Vector2<T> &a,const Vector2<T> &b);

    template <typename T>
    inline T  getMaxX(const vector<Vector2<T>   > &points);
    template <typename T>
    inline T  getMaxY(const vector<Vector2<T>   > &points);
    template <typename T>
    inline T  getMinX(const vector<Vector2<T>   > &points);
    template <typename T>
    inline T  getMinY(const vector<Vector2<T>   > &points);



    template <typename T>
    inline float length(const Vector2<T> &vec)
    {
        return sqrt(pow(vec.x,2) + pow(vec.y,2));
    }

    template <typename T>
    inline Vector2<T> getRotated(const Vector2<T> &vec,const Vector2<T> &rotPoint, float deg)
    {
        sf::Transform t;
        t.rotate(deg, rotPoint);
        return t.transformPoint(vec);
       /*// if(long(100*deg)%36000 == 0)
       //     return vec;


        //float normalX = float(vec.x)-float(rotPoint.x);
        float normalY = float(vec.y)-float(rotPoint.y);
        float lengthV  = length(vec-rotPoint);

        if(lengthV <= 0.00001)
            return vec;

        float newAngle = asin(normalY / lengthV);
        //if(normalX < 0)
        //    newAngle = M_PI - newAngle;
        newAngle += deg * M_PI / 180;
        float xComp = cos(newAngle)*lengthV;
        float yComp = sin(newAngle)*lengthV;

        if(xComp<0.00001 && xComp>-0.00001)
            xComp = 0;
        if(yComp<0.00001 && yComp>-0.00001)
            yComp = 0;
        Vector2<T> res(xComp+rotPoint.x,yComp+rotPoint.y);
        return res;*/
    }

    inline void rotate(Vector2f &vec,const Vector2f &rotPoint, float deg)
    {
        sf::Transform t;
        t.rotate(deg, rotPoint);
        vec = t.transformPoint(vec);
    }
    inline void rotate(vector<Vector2f> &points,const Vector2f &rotPoint, float deg)
    {
        sf::Transform t;
        t.rotate(deg, rotPoint);
        for(size_t i=0; i<points.size(); i++)
            points[i] = t.transformPoint(points[i]);
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
    inline void print(const Vector2<T> &vec)
    {
        qDebug() << toString(vec);
    }
    template <typename T>
    inline const string toString(const Vector2<T> &vec)
    {
        return "Vector: X="+std::to_string(vec.x)+"\tY="+std::to_string(vec.y);
    }

    template <typename T>
    inline VertexPath* getDrawableVectorFunc(const Func2<T> &vecFunc,const T &scalar,const sf::Color &color)
    {
        return getDrawableVectorFunc(Vector2<T>(0,0),vecFunc,scalar,color);
    }
    template <typename T>
    inline VertexPath* getDrawableVectorFunc(const Vector2<T> &ref,const Func2<T> &vecFunc,const T &scalar,const sf::Color &color)
    {
        VertexPath *path = new VertexPath();
        path->length = 4;
        path->type   = sf::Lines;
        path->line = new sf::Vertex[path->length]
        {
            sf::Vertex(Vector2f(ref)),
            sf::Vertex(Vector2f(vecFunc.support + ref)),

            sf::Vertex(Vector2f(vecFunc.support + ref)),
            sf::Vertex(Vector2f(vecFunc(scalar) + ref))
        };
        for(std::size_t i=0; i<path->length; i++)
            path->line[i].color = color;
        return path;
    }
    template <typename T>
    inline VertexPath* getDrawableVector(const Vector2<T> &begin,const Vector2<T> &end,const sf::Color &color)
    {

        VertexPath* path = new VertexPath;
        path->length = 2;
        path->type   = sf::Lines;
        path->line = new sf::Vertex[path->length]
        {
            sf::Vertex(Vector2f(begin)),
            sf::Vertex(Vector2f(end))
        };
        for(std::size_t i=0; i<path->length; i++)
            path->line[i].color = color;
        return path;
    }

    template <typename T>
    inline Vector2<T>  multiply(const Vector2<T> &a,const Vector2<T> &b)
    {
        Vector2<T> res = a;
        res.x *= b.x;
        res.y *= b.y;
        return res;
    }


    template <typename T>
    inline T  getMaxX(const vector<Vector2<T>   > &points)
    {
        T maxX = 0;
        if(points.size() == 0)
            return maxX;
        maxX = points[0].x;
        for(size_t i=1; i < points.size(); i++)
        {
            if(maxX < points[i].x)
                maxX = points[i].x;
        }
        return maxX;
    }
    template <typename T>
    inline T  getMaxY(const vector<Vector2<T>   > &points)
    {
        T maxY = 0;
        if(points.size() == 0)
            return maxY;
        maxY = points[0].y;
        for(size_t i=1; i < points.size(); i++)
        {
            if(maxY < points[i].y)
                maxY = points[i].y;
        }
        return maxY;
    }
    template <typename T>
    inline T  getMinX(const vector<Vector2<T>   > &points)
    {
        T minX = 0;
        if(points.size() == 0)
            return minX;
        minX = points[0].x;
        for(size_t i=1; i < points.size(); i++)
        {
            if(minX > points[i].x)
                minX = points[i].x;
        }
        return minX;
    }
    template <typename T>
    inline T  getMinY(const vector<Vector2<T>   > &points)
    {
        T minY = 0;
        if(points.size() == 0)
            return minY;
        minY = points[0].y;
        for(size_t i=1; i < points.size(); i++)
        {
            if(minY > points[i].y)
                minY = points[i].y;
        }
        return minY;
    }

}
namespace Hash{
    template <typename T>
    inline size_t  getHashOfList(const vector<T> &list);
    template <typename T>
    inline size_t  getHash(const T &obj);


    template <typename T>
    inline size_t  getHashOfList(const vector<T> &list)
    {
        size_t hash = 0;
        for(size_t i=0; i<list.size(); i++)
            hash += getHash(list[i]);
        return hash;
    }
    template <typename T>
    inline size_t  getHash(const T &obj)
    {
        return std::hash<T>{}(obj);
    }
}

#endif // MATH_H
