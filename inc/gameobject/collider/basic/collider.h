#ifndef COLLIDER_H
#define COLLIDER_H

//#include <SFML/Graphics/Rect.hpp>
#include "mathFunctions.h"
#include "layeritem.h"
//#include "point.h"
#include "rect.h"
//#include "vector.h"
#include "texture.h"

#include "profiler.h"

using std::vector;
using sf::Vector2f;

class Collider  :   public LayerItem
{
    public:
        Collider();
        Collider(const Collider &other);
        virtual ~Collider();
        virtual const Collider &operator=(const Collider &other);

        virtual void setPosInitial(const Vector2f &pos);
        virtual void setPosInitial(const Vector2i &pos);
        virtual void setPosInitial(int x, int y);
        virtual void setPosInitial(float x, float y);

        virtual void setPos(const Vector2f &pos);
        virtual void setPos(const Vector2i &pos);

        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setX(float x);
        virtual void setY(float y);

        virtual const RectI &getBoundingBox() const;


        virtual void reserve(const size_t &amount);

        virtual void addHitbox(const RectI &box);
        virtual void addHitbox(const vector<RectI> &boxList);

        virtual const RectI &getHitbox(const unsigned int &index) const;
        virtual const vector<RectI> &getHitbox() const;

        virtual bool intersectsBoundingBox(const Collider &other);
        virtual bool collides(const Collider &other) const;

        virtual void tick();

        virtual void erase(const size_t &index);
        virtual void clear();

        virtual const bool &isBoundingBoxUpdated() const;
        virtual void updateBoundingBox();

        virtual size_t getHitboxAmount() const;

        virtual float getRotation() const;
        virtual void setRotation(const float &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const Vector2f &rotationPoint,const float &deg);
        virtual void rotate_90(const Vector2f &rotationPoint);
        virtual void rotate_180(const Vector2f &rotationPoint);
        virtual void rotate_270(const Vector2f &rotationPoint);

        virtual void setHitboxFromTexture(const Texture *texture);

        virtual VertexPath getDrawableBoundingBox();

    protected:

        virtual void setBoundingBox();
        virtual void setBoundingBox(const RectI &box);
        virtual void setBoundingBox(const int &x,const int &y,
                                    const int &width,const int &height);



        RectI  m_boundingBox;
        vector<RectI> m_hitboxList;

        bool m_boundingBoxUpdated;

        RectI m_dummy;

        float m_rotationDeg;

        Color m_boundingBox_color;
        Color m_boundingBox_standardColor;
        Color m_boundingBox_intersectingColor;
    private:

        virtual void internalRotate(const Vector2f &rotPoint,const float &deg);

};
#endif
