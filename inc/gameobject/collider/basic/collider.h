#ifndef COLLIDER_H
#define COLLIDER_H

#include "layeritem.h"
#include "point.h"
#include "rect.h"
#include "vector.h"
#include "texture.h"

#include "profiler.h"

using std::vector;

class Collider  :   public LayerItem
{
    public:
        Collider();
        Collider(const Collider &other);
        virtual ~Collider();
        virtual const Collider &operator=(const Collider &other);

        virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Point &pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual const Rect &getBoundingBox() const;


        virtual void reserve(const size_t &amount);

        virtual void addHitbox(const Rect &box);
        virtual void addHitbox(const vector<Rect> &boxList);

        virtual const Rect &getHitbox(const unsigned int &index) const;
        virtual const vector<Rect> &getHitbox() const;

        virtual bool intersectsBoundingBox(const Collider &other) const;
        virtual bool collides(const Collider &other) const;

        virtual void erase(const size_t &index);
        virtual void clear();

        virtual const bool &isBoundingBoxUpdated() const;
        virtual void updateBoundingBox();

        virtual size_t getHitboxAmount() const;

        virtual double getRotation() const;
        virtual void setRotation(const double &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const PointF &rotationPoint,const double &deg);
        virtual void rotate_90(const PointF &rotationPoint);
        virtual void rotate_180(const PointF &rotationPoint);
        virtual void rotate_270(const PointF &rotationPoint);

        virtual void setHitboxFromTexture(const Texture *texture);


    protected:

        virtual void setBoundingBox();
        virtual void setBoundingBox(const Rect &box);
        virtual void setBoundingBox(const int &x,const int &y,
                                    const int &width,const int &height);



        Rect  m_boundingBox;
        vector<Rect> m_hitboxList;

        bool m_boundingBoxUpdated;

        Rect m_dummy;

        double m_rotationRad;
    private:

        virtual void rotate(const PointF &rotPoint,const double &rad);

};
#endif
