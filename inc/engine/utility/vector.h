#ifndef GeneralVector_H
#define GeneralVector_H

#include "point.h"
#include <vector>

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
        GeneralVector(T x,T y);
        GeneralVector(const GeneralPoint<T> &other);
        GeneralVector(const GeneralVector<T> &other);
        virtual ~GeneralVector();

        GeneralVector<T> &operator+=(const GeneralVector<T> &vec); // adds a GeneralVector to it
        GeneralVector<T> &operator+=(const std::vector<GeneralVector<T>> &vecList);
        GeneralVector<T> operator+(const GeneralVector<T> &vec) const; // adds it self and the other GeneralVector and gives the resault back
        GeneralVector<T> &operator++(); // doubles its length

        GeneralVector<T> &operator-=(const GeneralVector<T> &vec); // subtracts a GeneralVector to it
        GeneralVector<T> &operator-=(const std::vector<GeneralVector<T>> &vecList);
        GeneralVector<T> operator-(const GeneralVector<T> &vec) const; // subtracts it self and the other GeneralVector and gives the resault back

        GeneralVector<T> &operator*=(const T &scalar); // scales its length
        GeneralVector<T> operator*(const T &scalar) const; // scales its length and gives the resault back

        GeneralVector<T> &operator=(const GeneralVector<T> &vec);

        GeneralPoint<T> toPoint() const;

    protected:

    private:

};



template<class T>
GeneralVector<T>::GeneralVector()
    : GeneralPoint<T>()
{

}
template<class T>
GeneralVector<T>::GeneralVector(T x,T y)
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
GeneralPoint<T> GeneralVector<T>::toPoint() const
{
    return *this;
}

#endif // GeneralVector_H
