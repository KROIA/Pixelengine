#ifndef POINT_H
#define POINT_H

template<class T>
class GeneralPoint;

typedef GeneralPoint<unsigned int> PointU;
typedef GeneralPoint<int> Point;
typedef GeneralPoint<double> PointF;


template<class T>
class GeneralPoint
{
    public:
        GeneralPoint();
        GeneralPoint(T x, T y);
        GeneralPoint(const GeneralPoint &other);
        virtual ~GeneralPoint();

        virtual void setX(T x);
        virtual const T  &getX() const;
        virtual void setY(T y);
        virtual const T  &getY() const;

        bool operator==(const GeneralPoint<T> &other);
        bool operator!=(const GeneralPoint<T> &other);


    protected:
        T m_x;
        T m_y;
    private:

};




template<class T>
GeneralPoint<T>::GeneralPoint()
{
    this->setX(0);
    this->setY(0);
}
template<class T>
GeneralPoint<T>::GeneralPoint(T x, T y)
{
    this->setX(x);
    this->setY(y);
}
template<class T>
GeneralPoint<T>::GeneralPoint(const GeneralPoint &other)
{
    this->m_x = other.m_x;
    this->m_y = other.m_y;
}
template<class T>
GeneralPoint<T>::~GeneralPoint()
{

}
template<class T>
void GeneralPoint<T>::setX(T x)
{
    m_x = x;
}
template<class T>
const T &GeneralPoint<T>::getX() const
{
    return m_x;
}
template<class T>
void GeneralPoint<T>::setY(T y)
{
    m_y = y;
}
template<class T>
const T &GeneralPoint<T>::getY() const
{
    return m_y;
}

template<class T>
bool GeneralPoint<T>::operator==(const GeneralPoint<T> &other)
{
    if(this->m_x == other.m_x &&
       this->m_y == other.m_y)
        return true;
    return false;
}
template<class T>
bool GeneralPoint<T>::operator!=(const GeneralPoint<T> &other)
{
    if(this->m_x != other.m_x)
        return true;
    if(this->m_y != other.m_y)
        return true;
    return false;
}



#endif // POINT_H
