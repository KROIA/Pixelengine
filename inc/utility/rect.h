#ifndef RECT_H
#define RECT_H

#include "base.h"

#include "mathFunctions.h"
#include "drawUtilities.h"

typedef GeneralRect<unsigned int> RectU;
typedef GeneralRect<int> RectI;
typedef GeneralRect<float> RectF;

template<class T>
class GeneralRect
{
    public:

        GeneralRect();
        GeneralRect(const T &width, const T &height);
        GeneralRect(const Vector2<T> &size);
        GeneralRect(const T &xPos, const T &yPos, const T &width, const T &height);
        GeneralRect(const Vector2<T> &pos, const Vector2<T> &size);
        GeneralRect(const Vector2<T> &topLeft, const Vector2<T> &topRight,
                    const Vector2<T> &bottomLeft, const Vector2<T> &bottomRight);
        GeneralRect(const GeneralRect<T> &other);
        virtual ~GeneralRect();
        virtual GeneralRect<T> &operator=(const GeneralRect<T> &other);

        virtual void move(const Vector2<T> &vec);
        virtual void set(const Vector2<T> &pos, const Vector2<T> &size);
        virtual void set(const T &posX, const T &posY, const T &width, const T &height);
        virtual void set(const Vector2<T> &topLeft, const Vector2<T> &topRight,
                         const Vector2<T> &bottomLeft, const Vector2<T> &bottomRight);
        virtual void setPos(const Vector2<T> &pos);
        virtual void setPos(const T &posX, const T &posY);
        virtual void setX(const T &x);
        virtual void setY(const T &y);
        virtual void setWidth(const T &width);
        virtual void setHeight(const T &height);
        virtual const T &getX() const;
        virtual const T &getY() const;

        virtual const Vector2<T> &getPos() const;

        virtual void setSize(const Vector2<T> &size);
        virtual void setSize(const T &width, const T &height);
        virtual Vector2<T> getSize() const;

        virtual const Vector2<T> &getCornerPoint_TL() const; // Top Left
        virtual const Vector2<T> &getCornerPoint_TR() const; // Top Right
        virtual const Vector2<T> &getCornerPoint_BL() const; // Bottom Left
        virtual const Vector2<T> &getCornerPoint_BR() const; // Bottom Right
        virtual const Vector2<T> &getTop()            const;
        virtual const Vector2<T> &getRight()          const;
        virtual const Vector2<T> &getBottom()         const;
        virtual const Vector2<T> &getLeft()           const;

        virtual void generateColliderData(bool enable);
        virtual vector<VertexPath*> getColliderData();
        virtual void clearColliderData();
        virtual bool intersects(const GeneralRect<T> &other); // returns true if this and ohter are intersecting
        virtual bool intersects_fast(const GeneralRect<T> &other); // returns true if this and ohter are intersecting
        virtual bool contains(const Vector2<T> &point);

        bool operator==(const GeneralRect<T> &other);
        bool operator!=(const GeneralRect<T> &other);

        VertexPath *getDrawable(const sf::Color &color = sf::Color(255,255,255,255)) const;
        VertexPath *getDrawableMesh(const sf::Color &color = sf::Color(255,255,255,255)) const;

        static GeneralRect<T> rotate(GeneralRect<T> rect,const float &deg);
        static GeneralRect<T> rotate(GeneralRect<T> rect,const Vector2<T> &rotationPoint,const float &deg);
        static GeneralRect<T> rotate_90(GeneralRect<T> rect,const Vector2<T> &rotationPoint = Vector2<T>(0,0));
        static GeneralRect<T> rotate_180(GeneralRect<T> rect,const Vector2<T> &rotationPoint = Vector2<T>(0,0));
        static GeneralRect<T> rotate_270(GeneralRect<T> rect,const Vector2<T> &rotationPoint = Vector2<T>(0,0));

        virtual void rotate(const Vector2<T> &rotationPoint,const float &deg);

        // A Rect which includes all rects in the List
        static GeneralRect<T> getFrame(const std::vector<GeneralRect<T> > &list);
        static T getMinX(const std::vector<GeneralRect<T> > &list);
        static T getMaxX(const std::vector<GeneralRect<T> > &list);
        static T getMinY(const std::vector<GeneralRect<T> > &list);
        static T getMaxY(const std::vector<GeneralRect<T> > &list);

        T getMinX();
        T getMinY();
        T getMaxX();
        T getMaxY();

        unsigned long stats_intersectionCheckCounter;
    protected:
        virtual inline void update();
        virtual inline void updateFrame();

    private:

        /*

            TL            top           TR
              +---------------------->+
              |                    .  |
              |                  .    |
         left |                .      | right
              |.             .        |
              v            .          v
              +---------------------->+
            BL ..      . bottom   .     BR
                .     .      .
                   .   .
                 +0

         */
        Vector2<T> TL;
        Vector2<T> TR;
        Vector2<T> BL;
        Vector2<T> BR;

        Vector2<T> top;
        Vector2<T> left;
        Vector2<T> bottom;
        Vector2<T> right;

        Vector2<T> frame_pos;
        Vector2<T> frame_size;

        bool colliderDataEnabled;
        vector<VertexPath*> collisionData;
        float rotation;
};

template<class T>
GeneralRect<T>::GeneralRect()
{
    rotation = 0;
    this->setPos(0,0);
    this->setSize(1,1);
    stats_intersectionCheckCounter = 0;
    colliderDataEnabled = false;
}
template<class T>
GeneralRect<T>::GeneralRect(const T &width, const T &height)
{
    rotation = 0;
    this->setSize(width,height);
    stats_intersectionCheckCounter = 0;
    colliderDataEnabled = false;
}
template<class T>
GeneralRect<T>::GeneralRect(const Vector2<T> &size)
{
    rotation = 0;
    this->setSize(size);
    stats_intersectionCheckCounter = 0;
    colliderDataEnabled = false;
}
template<class T>
GeneralRect<T>::GeneralRect(const T &xPos, const T &yPos, const T &width, const T &height)
{
    rotation = 0;
    this->setPos(xPos,yPos);
    this->setSize(width,height);
    stats_intersectionCheckCounter = 0;
    colliderDataEnabled = false;
}
template<class T>
GeneralRect<T>::GeneralRect( const Vector2<T> &pos,const Vector2<T> &size)
{
    rotation = 0;
    this->setPos(pos);
    this->setSize(size);
    stats_intersectionCheckCounter = 0;
    colliderDataEnabled = false;
}
template<class T>
GeneralRect<T>::GeneralRect(const Vector2<T> &topLeft, const Vector2<T> &topRight,
                            const Vector2<T> &bottomLeft, const Vector2<T> &bottomRight)
{
    rotation = 0;
    this->set(topLeft,topRight,bottomLeft,bottomRight);
    stats_intersectionCheckCounter = 0;
    colliderDataEnabled = false;
}
template<class T>
GeneralRect<T>::GeneralRect(const GeneralRect<T> &other)
{
    *this = other;
    stats_intersectionCheckCounter = 0;

}
template<class T>
GeneralRect<T>::~GeneralRect()
{

}
template<class T>
GeneralRect<T> &GeneralRect<T>::operator=(const GeneralRect<T> &other)
{
    this->TL        = other.TL;
    this->TR        = other.TR;
    this->BL        = other.BL;
    this->BR        = other.BR;

    this->top       = other.top;
    this->left      = other.left;
    this->bottom    = other.bottom;
    this->right     = other.right;

    this->frame_pos = other.frame_pos;
    this->frame_size= other.frame_size;
    this->colliderDataEnabled = other.colliderDataEnabled;
    this->rotation  = other.rotation;
    return *this;
}
template<class T>
void GeneralRect<T>::move(const Vector2<T> &vec)
{
    TL += vec;
    TR += vec;
    BL += vec;
    BR += vec;
    updateFrame();
}
template<class T>
void GeneralRect<T>::set(const Vector2<T> &pos, const Vector2<T> &size)
{
    TL = pos;
    TR = TL + Vector2<T>(size.x,0);
    BL = TL + Vector2<T>(0,size.y);
    BR = TL + size;
    rotation = 0;
    this->update();
}
template<class T>
void GeneralRect<T>::set(const T &posX, const T &posY, const T &width, const T &height)
{
    TL = Vector2<T>(posX,posY);
    TR = TL + Vector2<T>(width,0);
    BL = TL + Vector2<T>(0,height);
    BR = TL + Vector2<T>(width,height);
    rotation = 0;
    this->update();
}
template<class T>
void GeneralRect<T>::set(const Vector2<T> &topLeft, const Vector2<T> &topRight,
                         const Vector2<T> &bottomLeft, const Vector2<T> &bottomRight)
{
    TL = topLeft;
    TR = topRight;
    BL = bottomLeft;
    BR = bottomRight;
    this->update();
}
template<class T>
void GeneralRect<T>::setPos(const Vector2<T> &pos)
{
    TL = pos;
    TR = TL + top;
    BL = TL + left;
    BR = TR + right;
    updateFrame();
}
template<class T>
void GeneralRect<T>::setPos(const T &posX, const T &posY)
{
    TL.x = posX;
    TL.y = posY;
    TR = TL + top;
    BL = TL + left;
    BR = TR + right;
    updateFrame();
}
template<class T>
void GeneralRect<T>::setX(const T &x)
{
    TL.x = x;
    TR = TL + top;
    BL = TL + left;
    BR = TR + right;
    updateFrame();
}
template<class T>
void GeneralRect<T>::setY(const T &y)
{
    TL.y = y;
    TR = TL + top;
    BL = TL + left;
    BR = TR + right;
    updateFrame();
}
template<class T>
void GeneralRect<T>::setWidth(const T &width)
{
    float oldRot = rotation;
    this->rotate(TL,-oldRot);

    TR.x = TL.x + width;
    BR.x = BL.x + width;

    this->rotate(TL,oldRot);
    this->update();
}
template<class T>
void GeneralRect<T>::setHeight(const T &height)
{
    float oldRot = rotation;
    this->rotate(TL,-oldRot);

    BL.y = TL.y + height;
    BR.y = TR.y + height;

    this->rotate(TL,oldRot);
    this->update();
}
template<class T>
const T &GeneralRect<T>::getX() const
{
    return TL.x;
}
template<class T>
const T &GeneralRect<T>::getY() const
{
    return TL.y;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getPos() const
{
    return TL;
}

template<class T>
void GeneralRect<T>::setSize(const Vector2<T> &size)
{
    float oldRot = rotation;
    this->rotate(TL,-oldRot);
    TR = TL + Vector2<T>(size.x,0);
    BL = TL + Vector2<T>(0,size.y);
    BR = TL + size;
    this->rotate(TL,oldRot);
    this->update();
}
template<class T>
void GeneralRect<T>::setSize(const T &width, const T &height)
{
    float oldRot = rotation;
    this->rotate(TL,-oldRot);
    this->setSize(Vector2<T>(width,height));
    this->rotate(TL,oldRot);
    this->update();
}
template<class T>
Vector2<T> GeneralRect<T>::getSize() const
{
    return BR - TL;
}

template<class T>
const Vector2<T> &GeneralRect<T>::getCornerPoint_TL() const
{
    return TL;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getCornerPoint_TR() const
{
    return TR;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getCornerPoint_BL() const
{
    return BL;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getCornerPoint_BR() const
{
    return BR;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getTop()            const
{
    return top;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getRight()          const
{
    return right;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getBottom()         const
{
    return bottom;
}
template<class T>
const Vector2<T> &GeneralRect<T>::getLeft()           const
{
    return left;
}
template<class T>
void GeneralRect<T>::generateColliderData(bool enable)
{
    colliderDataEnabled = enable;
    if(!enable)
        clearColliderData();
}
template<class T>
vector<VertexPath*> GeneralRect<T>::getColliderData()
{
    vector<VertexPath*> out = collisionData;
    clearColliderData();
    return out;
}
template<class T>
void GeneralRect<T>::clearColliderData()
{
    collisionData.clear();
    collisionData.reserve(20);
}
template<class T>
bool GeneralRect<T>::intersects(const GeneralRect<T> &other)
{
    /*

        TL            top           TR
          +---------------------->+
          |                    .  |
          |                  .    |
     left |                .      | right
          |.             .        |
          v            .          v
          +---------------------->+
        BL ..      . bottom   .     BR
            .     .      .
               .   .
             +0

     */


    struct Vfunc
    {
        const Vector2<T> *s; // Supportvector
        const Vector2<T> *d; // Directionvector
    };

    vector<Vfunc> frameVecList(4);
    frameVecList[0].s = &TL;
    frameVecList[1].s = &TL;
    frameVecList[2].s = &BL;
    frameVecList[3].s = &TR;

    frameVecList[0].d = &top    ;
    frameVecList[1].d = &left   ;
    frameVecList[2].d = &bottom ;
    frameVecList[3].d = &right  ;

    vector<Vfunc> other_frameVecList(4);
    other_frameVecList[0].s = &other.TL;
    other_frameVecList[1].s = &other.TL;
    other_frameVecList[2].s = &other.BL;
    other_frameVecList[3].s = &other.TR;

    other_frameVecList[0].d = &other.top    ;
    other_frameVecList[1].d = &other.left   ;
    other_frameVecList[2].d = &other.bottom ;
    other_frameVecList[3].d = &other.right  ;




    Vector2<T> intersectionFac;
    size_t frameVecList_size = frameVecList.size();
    size_t other_frameVecList_size = other_frameVecList.size();



    for(size_t i=0; i<frameVecList_size; i++)
    {
        for(size_t j=0; j<other_frameVecList_size; j++)
        {
            if(Vector::doesIntersect(*frameVecList[i].d,*other_frameVecList[j].d))
            {
                intersectionFac = Vector::getIntersection(*frameVecList[i].s,        *frameVecList[i].d,
                                                          *other_frameVecList[j].s,  *other_frameVecList[j].d);
                if(intersectionFac.x > 0 && intersectionFac.x < 1.f &&
                   intersectionFac.y > 0 && intersectionFac.y < 1.f)
                {
                    stats_intersectionCheckCounter =  i * j;
                    if(colliderDataEnabled)
                    {
                        collisionData.push_back(this->getDrawable(sf::Color(0,255,0)));
                        collisionData.push_back(other.getDrawable(sf::Color(255,0,0)));

                        collisionData.push_back(Vector::getDrawableVector(*frameVecList[i].s,*frameVecList[i].s+*frameVecList[i].d*intersectionFac.x,sf::Color(0,255,255)));
                        collisionData.push_back(Vector::getDrawableVector(*other_frameVecList[j].s,*other_frameVecList[j].s+*other_frameVecList[j].d*intersectionFac.y,sf::Color(255,0,255)));
                    }
                    return true;
                }
            }
        }
    }
    stats_intersectionCheckCounter = frameVecList_size * other_frameVecList_size/*+1*/;
    //if(contains(other.TL))
    //    return true;
    return false;
}
template<class T>
bool GeneralRect<T>::intersects_fast(const GeneralRect<T> &other)
{
    // This function will not check the collision using vectors
    // It will check the collision on the Frame of the Rect

    // If one rectangle is on left side of other
    if(frame_pos.x >  other.frame_pos.x + other.frame_size.x ||
       other.frame_pos.x > frame_pos.x + frame_size.x)
    {
        stats_intersectionCheckCounter = 1;
        return false;
    }

    // If one rectangle is above other
    if(frame_pos.y >  other.frame_pos.y + other.frame_size.y ||
       other.frame_pos.y > frame_pos.y + frame_size.y)
    {
        stats_intersectionCheckCounter = 1;
        return false;
    }
    stats_intersectionCheckCounter = 2;
    return true;
}
template<class T>
bool GeneralRect<T>::contains(const Vector2<T> &point)
{
    T divisor = left.x * bottom.y - left.y * bottom.x;
    if(divisor == 0)
        return false;
    divisor = 1.f/divisor;
    float bottomScalar = (point.x * left.y - point.y * left.x - BL.x * left.y + BL.y * left.x) * divisor;
    float leftScalar   = (point.x * bottom.y - point.y * bottom.x - BL.x * bottom.y + BL.y * bottom.x) * divisor;
    if(bottomScalar < 1.f && bottomScalar > 0 &&
       leftScalar   < 1.f && leftScalar   > 0)
        return true;
    return false;
}

template<class T>
bool GeneralRect<T>::operator==(const GeneralRect<T> &other)
{
    if(this->TL != other.TL)
        return false;
    if(this->TR != other.TR)
        return false;
    if(this->BL != other.BL)
        return false;
    if(this->BR != other.BR)
        return false;
    return true;
}
template<class T>
bool GeneralRect<T>::operator!=(const GeneralRect<T> &other)
{
    if(this->TL != other.TL)
        return true;
    if(this->TR != other.TR)
        return true;
    if(this->BL != other.BL)
        return true;
    if(this->BR != other.BR)
        return true;
    return false;
}
template<class T>
VertexPath *GeneralRect<T>::getDrawable(const sf::Color &color) const
{
    VertexPath *path = new VertexPath;
    path->length = 8;
    path->type = sf::Lines;
    path->line = new sf::Vertex[path->length]
    {
        sf::Vertex(Vector2f(TL)),
        sf::Vertex(Vector2f(TR)),

        sf::Vertex(Vector2f(TR)),
        sf::Vertex(Vector2f(BR)),

        sf::Vertex(Vector2f(BR)),
        sf::Vertex(Vector2f(BL)),

        sf::Vertex(Vector2f(BL)),
        sf::Vertex(Vector2f(TL))
    };

    for(std::size_t i=0; i<path->length; i++)
        path->line[i].color = color;

    return path;
}

template<class T>
VertexPath *GeneralRect<T>::getDrawableMesh(const sf::Color &color) const
{
    VertexPath *path = new VertexPath;
    path->length = 12;
    path->type = sf::Lines;
    path->line = new sf::Vertex[path->length]
    {
        sf::Vertex(Vector2f(TL)),
        sf::Vertex(Vector2f(TR)),

        sf::Vertex(Vector2f(TR)),
        sf::Vertex(Vector2f(BR)),

        sf::Vertex(Vector2f(BR)),
        sf::Vertex(Vector2f(BL)),

        sf::Vertex(Vector2f(BL)),
        sf::Vertex(Vector2f(TL)),

        sf::Vertex(Vector2f(TL)),
        sf::Vertex(Vector2f(BR)),

        sf::Vertex(Vector2f(TR)),
        sf::Vertex(Vector2f(BL))
    };

    for(std::size_t i=0; i<path->length; i++)
        path->line[i].color = color;

    return path;
}

template<class T>
GeneralRect<T> GeneralRect<T>::rotate(GeneralRect<T> rect,const float &deg)
{
    return GeneralRect<T>::rotate(rect,Vector2<T>(0,0),deg);
}
template<class T>
GeneralRect<T> GeneralRect<T>::rotate(GeneralRect<T> rect,const Vector2<T> &rotationPoint,const float &deg)
{
    rect.rotate(rotationPoint,deg);
    return  rect;
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_90(GeneralRect<T> rect,const Vector2<T> &rotationPoint)
{
    GeneralRect<T>::rotate(rect,rotationPoint,90);
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_180(GeneralRect<T> rect,const Vector2<T> &rotationPoint)
{
    GeneralRect<T>::rotate(rect,rotationPoint,180);
}
template<class T>
GeneralRect<T>  GeneralRect<T>::rotate_270(GeneralRect<T> rect,const Vector2<T> &rotationPoint)
{
    GeneralRect<T>::rotate(rect,rotationPoint,-90);
}
//#include <QDebug>
template<class T>
void GeneralRect<T>::rotate(const Vector2<T> &rotationPoint,const float &deg)
{
    sf::Transform transform;
    transform.rotate(deg,Vector2f(rotationPoint));

    TL = Vector2<T>(transform.transformPoint(Vector2f(TL)));
    TR = Vector2<T>(transform.transformPoint(Vector2f(TR)));
    BL = Vector2<T>(transform.transformPoint(Vector2f(BL)));
    BR = Vector2<T>(transform.transformPoint(Vector2f(BR)));
    rotation += deg;
    this->update();
    /*sf::Rect<float> rect(m_pos.x,m_pos.y,m_size.x,m_size.y);
    sf::Transform transform;
    transform.rotate(deg,Vector2f(rotationPoint));
    rect = transform.transformRect(rect);

    m_pos = Vector2<T>(rect.getPosition());
    m_size = Vector2<T>(rect.getSize());

    qDebug() << "m_pos: "<<m_pos.x<< " "<<m_pos.y;
    qDebug() << "m_size: "<<m_size.x<< " "<<m_size.y;*/
    /*Vector2f vec(m_size);

    //m_size = Vector::getRotated(m_size,rotationPoint,deg);
    Vector::rotate(vec,Vector2f(rotationPoint),deg);

    if(vec.x<0)
    {
        m_pos.x   = m_pos.x+vec.x+1;
        vec.x *= -1;
    }
    if(vec.y<0)
    {
        m_pos.y   = m_pos.y+vec.y+1;
        vec.y *= -1;
    }
    m_size = Vector2<T>(vec);*/
}
template<class T>
GeneralRect<T> GeneralRect<T>::getFrame(const std::vector<GeneralRect<T> > &list)
{
    T minX = GeneralRect<T>::getMinX(list);
    T minY = GeneralRect<T>::getMinY(list);
    T maxX = GeneralRect<T>::getMaxX(list);
    T maxY = GeneralRect<T>::getMaxY(list);

    return GeneralRect<T>(minX,minY,maxX-minX,maxY-minY);
}
template<class T>
T GeneralRect<T>::getMinX(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    T minX = list[0].TL.x;
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].TL.x < minX)
            minX = list[i].TL.x;
        if(list[i].TR.x < minX)
            minX = list[i].TR.x;
        if(list[i].BL.x < minX)
            minX = list[i].BL.x;
        if(list[i].BR.x < minX)
            minX = list[i].BR.x;
    }
    return minX;
}
template<class T>
T GeneralRect<T>::getMaxX(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    T maxX = list[0].TL.x;
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].TL.x > maxX)
            maxX = list[i].TL.x;
        if(list[i].TR.x > maxX)
            maxX = list[i].TR.x;
        if(list[i].BL.x > maxX)
            maxX = list[i].BL.x;
        if(list[i].BR.x > maxX)
            maxX = list[i].BR.x;
    }
    return maxX;
}
template<class T>
T GeneralRect<T>::getMinY(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    T minY = list[0].TL.y;
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].TL.y < minY)
            minY = list[i].TL.y;
        if(list[i].TR.y < minY)
            minY = list[i].TR.y;
        if(list[i].BL.y < minY)
            minY = list[i].BL.y;
        if(list[i].BR.y < minY)
            minY = list[i].BR.y;
    }
    return minY;
}
template<class T>
T GeneralRect<T>::getMaxY(const std::vector<GeneralRect<T> > &list)
{
    if(list.size() == 0)
        return 0;
    T maxY = list[0].TL.y;
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i].TL.y > maxY)
            maxY = list[i].TL.y;
        if(list[i].TR.y > maxY)
            maxY = list[i].TR.y;
        if(list[i].BL.y > maxY)
            maxY = list[i].BL.y;
        if(list[i].BR.y > maxY)
            maxY = list[i].BR.y;
    }
    return maxY;
}
template<class T>
T GeneralRect<T>::getMinX()
{
    T minX = TL.x;

   if(TR.x < minX)
       minX = TR.x;
   if(BL.x < minX)
       minX = BL.x;
   if(BR.x < minX)
       minX = BR.x;
    return minX;
}
template<class T>
T GeneralRect<T>::getMinY()
{
    T minY = TL.y;

   if(TR.y < minY)
       minY = TR.y;
   if(BL.y < minY)
       minY = BL.y;
   if(BR.y < minY)
       minY = BR.y;
    return minY;
}
template<class T>
T GeneralRect<T>::getMaxX()
{
    T maxX = TL.x;

   if(TR.x > maxX)
       maxX = TR.x;
   if(BL.x > maxX)
       maxX = BL.x;
   if(BR.x > maxX)
       maxX = BR.x;
    return maxX;
}
template<class T>
T GeneralRect<T>::getMaxY()
{
    T maxY = TL.y;

   if(TR.y > maxY)
       maxY = TR.y;
   if(BL.x > maxY)
       maxY = BL.y;
   if(BR.y > maxY)
       maxY = BR.y;
    return maxY;
}
template<class T>
void GeneralRect<T>::update()
{
    top              = TR - TL;
    left             = BL - TL;
    bottom           = BR - BL;
    right            = BR - TR;

    updateFrame();
}
template<class T>
void GeneralRect<T>::updateFrame()
{
    frame_pos.x = getMinX();
    frame_pos.y = getMinY();

    frame_size.x = getMaxX() - frame_pos.x;
    frame_size.y = getMaxY() - frame_pos.y;
}

#endif // RECT_H
