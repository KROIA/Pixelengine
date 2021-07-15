#ifndef COLLIDER_H
#define COLLIDER_H

#include "base.h"

#include "mathFunctions.h"
#include "layeritem.h"
#include "rect.h"
#include "texture.h"


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

        virtual const RectF &getBoundingBox() const;


        virtual void reserve(const size_t &amount);

        virtual void addHitbox(const RectF &box);
        virtual void addHitbox(const vector<RectF> &boxList);
        virtual void addHitbox(const RectI &box);
        virtual void addHitbox(const vector<RectI> &boxList);

        virtual const RectF &getHitbox(const unsigned int &index) const;
        virtual const vector<RectF> &getHitbox() const;

        virtual bool intersectsBoundingBox(const Collider &other);
        virtual bool collides(const Collider &other);

        virtual void tick();

        virtual void erase(const size_t &index);
        virtual void clear();

        virtual const bool &isBoundingBoxUpdated() const;
        virtual void updateBoundingBox();

        virtual size_t getHitboxAmount() const;

        virtual float getRotation() const;
        virtual void rotate(float deg);
        virtual void setRotation(float deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void rotate(const Vector2f &rotationPoint,float deg);
        virtual void setRotation(const Vector2f &rotationPoint,float deg);
        virtual void rotate_90(const Vector2f &rotationPoint);
        virtual void rotate_180(const Vector2f &rotationPoint);
        virtual void rotate_270(const Vector2f &rotationPoint);

        virtual void setHitboxFromTexture(const Texture *texture);

        virtual void generateCollisionData(bool enable);
        virtual VertexPath* getDrawableBoundingBox();
        virtual vector<VertexPath*> getDrawableHitBox();
        virtual vector<VertexPath*> getDrawableColliderVector();

        static void stats_reset();
        static unsigned long long stats_checkIntersectCounter;
        static unsigned long long stats_doesIntersectCounter;
        static unsigned long long stats_checkCollisionCounter;
        static unsigned long long stats_doesCollideCounter;


    protected:

        virtual void setBoundingBox();
        virtual void setBoundingBox(const RectF &box);
        virtual void setBoundingBox(const int &x,const int &y,
                                    const int &width,const int &height);



        RectF  m_boundingBox;
        vector<RectF> m_hitboxList;

        bool m_boundingBoxUpdated;

        RectF m_dummy;

        Color *m_boundingBox_color;
        Color m_boundingBox_standardColor;
        Color m_boundingBox_intersectingColor;

        Color m_hitbox_standardColor;
        Color m_hitbox_intersectingColor;
        vector<bool>    m_hitBoxListDoesIntersect;

        bool m_generate_collisionData;
        vector<VertexPath*> m_collisionData;
    private:

        virtual void internalRotate(const Vector2f &rotPoint,const float &deg);


};
#endif
