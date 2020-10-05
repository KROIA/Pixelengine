#ifndef COLLIDER_H
#define COLLIDER_H

#include "layeritem.h"
#include "point.h"
#include "rect.h"
#include "vector.h"

using std::vector;

class Collider  :   public LayerItem
{
    public:
        Collider();
        Collider(const Collider &other);
        virtual ~Collider();

        virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Point &pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual const Rect &getBoundingBox() const;


        virtual void addHitBox(Rect box);
        virtual void addHitBox(const vector<Rect> &boxList);

        virtual const Rect &getHitBox(const unsigned int &index) const;
        virtual const vector<Rect> &getHitBox() const;

        virtual bool intersectsBoundingBox(const Collider &other) const;
        virtual bool collides(const Collider &other) const;

        virtual void erase(const size_t &index);
        virtual void clear();

    protected:

        virtual void setBoundingBox();
        virtual void setBoundingBox(const Rect &box);
        virtual void setBoundingBox(const int &x,const int &y,
                                    const int &width,const int &height);

        virtual int getMinX();
        virtual int getMaxX();
        virtual int getMinY();
        virtual int getMaxY();

        Rect  m_boundingBox;
        vector<Rect> m_hitBoxList;


        Rect m_dummy;
    private:

};
#endif
