/*#include "vector.h"

template<class T>
GeneralVector<T>::GeneralVector()
    : Point()
{

}
template<class T>
GeneralVector<T>::GeneralVector(T x,T y)
    : Point(x,y)
{

}
template<class T>
GeneralVector<T>::GeneralVector(const Point &other)
    : Point(other)
{

}
template<class T>
GeneralVector<T>::GeneralVector(const GeneralVector &other)
    : Point(other)
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
    unsigned int x1 = this->getX();
    unsigned int y1 = this->getY();

    unsigned int x2 = vec.getX();
    unsigned int y2 = vec.getY();

    unsigned int x3 = x1 + x2;
    unsigned int y3 = y1 + y2;
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
GeneralVector<T> &GeneralVector<T>::operator-=(const GeneralVector<T> &vec)
{
    GeneralVector<T> div = *this-vec;
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
    unsigned int x1 = this->getX();
    unsigned int y1 = this->getY();

    unsigned int x2 = vec.getX();
    unsigned int y2 = vec.getY();

    unsigned int x3 = x1 - x2;
    unsigned int y3 = y1 - y2;
    GeneralVector<T> res;
    res.setX(x3);
    res.setY(y3);
    return res;
}

template<class T>
GeneralVector<T> &GeneralVector<T>::operator*=(const T &scalar)
{
    GeneralVector<T> product = *this*scalar;
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
Point GeneralVector<T>::toPoint() const
{
    return *this;
}
*/
