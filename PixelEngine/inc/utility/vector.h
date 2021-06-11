#ifndef GeneralVector_H
#define GeneralVector_H

#include "point.h"
#include <vector>
#include <math.h>

template<class T>
class GeneralVector;

typedef GeneralVector<unsigned int> VectorU;
typedef GeneralVector<int>          Vector;
typedef GeneralVector<double>       VectorF;



template<class T>
class GeneralVector : public GeneralPoint<T>
{
    public:
        GeneralVector();
        GeneralVector(const T &x, const T &y);
        GeneralVector(const GeneralPoint<T> &other);
        GeneralVector(const GeneralVector<T> &other);
        virtual ~GeneralVector();

        GeneralVector<T> &operator+=(const GeneralVector<T> &vec); // adds a GeneralVector to it
        GeneralVector<T> &operator+=(const std::vector<GeneralVector<T>> &vecList);
        GeneralVector<T> operator+(const GeneralVector<T> &vec) const; // adds it self and the other GeneralVector and gives the resault back
        GeneralVector<T> &operator++(); // doubles its length
        static GeneralVector<T> sum(const std::vector<GeneralVector<T> >   &vecList);

        GeneralVector<T> &operator-=(const GeneralVector<T> &vec); // subtracts a GeneralVector to it
        GeneralVector<T> &operator-=(const std::vector<GeneralVector<T>> &vecList);
        GeneralVector<T> operator-(const GeneralVector<T> &vec) const; // subtracts it self and the other GeneralVector and gives the resault back

        GeneralVector<T> &operator*=(const T &scalar); // scales its length
        GeneralVector<T> operator*(const T &scalar) const; // scales its length and gives the resault back

        GeneralVector<T> &operator=(const GeneralVector<T> &vec);

        bool operator==(const GeneralVector<T> &other) const;
        bool operator!=(const GeneralVector<T> &other) const;

        GeneralPoint<T> toPoint() const;

        double getLength() const;
        static GeneralVector<T> rotate(const GeneralVector<T> &vec,const double &angleRad);
        static GeneralVector<T> rotate(const GeneralVector<T> &vec,const GeneralPoint<T> &rotationPoint,const double &angleRad);
        static GeneralVector<T> rotate_90(const GeneralVector<T> &vec);
        static GeneralVector<T> rotate_180(const GeneralVector<T> &vec);
        static GeneralVector<T> rotate_270(const GeneralVector<T> &vec);

    protected:

    private:

};



template<class T>
GeneralVector<T>::GeneralVector()
    : GeneralPoint<T>()
{

}
template<class T>
GeneralVector<T>::GeneralVector(const T &x, const T &y)
    : GeneralPoint<T> (x,y)
{

}
template<class T>
GeneralVector<T>::GeneralVector(const GeneralPoint<T> &other)
    : GeneralPoint<T> (other)
{

}
template<class T>
GeneralVector<T>::GeneralVector(const GeneralVector<T> &other)
    : GeneralPoint<T> (other)
{

}
template<class T>
GeneralVector<T>::~GeneralVector()
{

}


template<class T>
GeneralVector<T> &GeneralVector<T>::operator+=(const GeneralVector<T> &vec)
{
    GeneralVector sum = *this+vec;
    this->set(sum);
    return *this;
}
template<class T>
GeneralVector<T> &GeneralVector<T>::operator+=(const std::vector<GeneralVector<T>> &vecList)
{
    if(vecList.size() == 0)
        return *this;
    GeneralVector<T> sum = *this;
    for(size_t element=0; element<vecList.size(); element++)
    {
        sum += vecList[element];
    }
    *this = sum;
    return *this;
}
template<class T>
GeneralVector<T> GeneralVector<T>::operator+(const GeneralVector<T> &vec) const
{
    T x1 = this->getX();
    T y1 = this->getY();

    T x2 = vec.getX();
    T y2 = vec.getY();

    T x3 = x1 + x2;
    T y3 = y1 + y2;
    GeneralVector<T> res;
    res.setX(x3);
    res.setY(y3);
    return res;
}
template<class T>
GeneralVector<T> &GeneralVector<T>::operator++()
{
    *this*=2;
    return *this;
}
template<class T>
GeneralVector<T> GeneralVector<T>::sum(const std::vector<GeneralVector<T> >   &vecList)
{
    GeneralVector<T> sum(0,0);
    for(size_t i=0; i<vecList.size(); i++)
        sum += vecList[i];

    return sum;
}

template<class T>
GeneralVector<T> &GeneralVector<T>::operator-=(const GeneralVector<T> &vec)
{
    GeneralVector<T> div = *this-vec;
    this->set(div);
    return *this;
}
template<class T>
GeneralVector<T> &GeneralVector<T>::operator-=(const std::vector<GeneralVector<T>> &vecList)
{
    if(vecList.size() == 0)
        return *this;
    GeneralVector<T> div = *this;
    for(size_t element=0; element<vecList.size(); element++)
    {
        div -= vecList[element];
    }
    *this = div;
    return *this;
}
template<class T>
GeneralVector<T> GeneralVector<T>::operator-(const GeneralVector<T> &vec) const
{
    T x1 = this->getX();
    T y1 = this->getY();

    T x2 = vec.getX();
    T y2 = vec.getY();

    T x3 = x1 - x2;
    T y3 = y1 - y2;
    GeneralVector<T> res;
    res.setX(x3);
    res.setY(y3);
    return res;
}

template<class T>
GeneralVector<T> &GeneralVector<T>::operator*=(const T &scalar)
{
    GeneralVector<T> product = *this*scalar;
    this->set(product);
    return *this;
}
template<class T>
GeneralVector<T> GeneralVector<T>::operator*(const T &scalar) const
{
    return GeneralVector<T>(this->m_x*scalar,this->m_y*scalar);
}

template<class T>
GeneralVector<T> &GeneralVector<T>::operator=(const GeneralVector<T> &vec)
{
    this->m_x = vec.m_x;
    this->m_y = vec.m_y;
    return *this;
}

template<class T>
bool GeneralVector<T>::operator==(const GeneralVector<T> &other) const
{
    if(this->m_x == other.m_x &&
       this->m_y == other.m_y)
        return true;
    return false;
}
template<class T>
bool GeneralVector<T>::operator!=(const GeneralVector<T> &other) const
{
    if(this->m_x != other.m_x)
        return true;
    if(this->m_y != other.m_y)
        return true;
    return false;
}

template<class T>
GeneralPoint<T> GeneralVector<T>::toPoint() const
{
    return *this;
}
template<class T>
double GeneralVector<T>::getLength() const
{
    return sqrt(pow(this->m_x,2) + pow(this->m_y,2));
}
template<class T>
GeneralVector<T> GeneralVector<T>::rotate(const GeneralVector<T> &vec, const double &angleRad)
{
    return GeneralVector<T>::rotate(vec,GeneralPoint<T>(0,0),angleRad);
}
template<class T>
GeneralVector<T> GeneralVector<T>::rotate(const GeneralVector<T> &vec,const GeneralPoint<T> &rotationPoint,const double &angleRad)
{
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
    return res;
}
template<class T>
GeneralVector<T> GeneralVector<T>::rotate_90(const GeneralVector<T> &vec)
{
    return GeneralVector<T>::rotate(vec,M_PI_2);
}
template<class T>
GeneralVector<T> GeneralVector<T>::rotate_180(const GeneralVector<T> &vec)
{
    return GeneralVector<T>::rotate(vec,M_PI);
}
template<class T>
GeneralVector<T> GeneralVector<T>::rotate_270(const GeneralVector<T> &vec)
{
    return GeneralVector<T>::rotate(vec,-M_PI_2);
}
#endif // GeneralVector_H
