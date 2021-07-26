#ifndef COLLIDER_H
#define COLLIDER_H

#include "base.h"

#include "mathFunctions.h"
#include "layeritem.h"
//#include "rect.h"
#include "texture.h"
#include "signalEmitter.h"
#include "AABB.h"
#include "shape.h"


using std::vector;
using sf::Vector2f;

// Signals for GameObjects
/*class ColliderSignal
{
    public:
        ColliderSignal(){}

        virtual void boundingBoxChanged(Collider* sender) = 0;
    protected:

};
// Vector of Signals
class ColliderSubscriberList    : public SubscriberList<ColliderSignal>
{
    public:
        ColliderSubscriberList();

        virtual void boundingBoxChanged(Collider* sender);
};*/
SIGNAL_DEF(Collider)
    SIGNAL_FUNC(boundingBoxChanged)
SIGNAL_DEF_END

SIGNAL_EMITTER_DEF(Collider)
    SIGNAL_EMITTER_FUNC(boundingBoxChanged)
SIGNAL_EMITTER_DEF_END

class Collider  :   public LayerItem
{
    SIGNAL_EMITTER(Collider)
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

        virtual const AABB &getBoundingBox() const;


        virtual void reserve(const size_t &amount);
        virtual void addVertex(Vector2f vertex);
        virtual void setShape(const Shape &shape);
        virtual const Shape &getShape() const;

        /*virtual void addHitbox(const RectF &box);
        virtual void addHitbox(const vector<RectF> &boxList);
        virtual void addHitbox(const RectI &box);
        virtual void addHitbox(const vector<RectI> &boxList);

        virtual const RectF &getHitbox(const unsigned int &index) const;
        virtual const vector<RectF> &getHitbox() const;*/
        virtual const Shape &getHitboxShape() const;

        virtual bool intersectsBoundingBox(const Collider *other);
        virtual bool collides(Collider *other);

        virtual void tick();

        virtual void erase(size_t index);
        virtual void clear();

        virtual const bool &isBoundingBoxUpdated() const;
        virtual void updateBoundingBox();

        //virtual size_t getHitboxAmount() const;

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

        virtual void setColor_boundingBox_noIntersection(const Color &color);
        virtual void setColor_boundingBox_intersecting(const Color &color);
        virtual void setColor_hitBox_noCollision(const Color &color);
        virtual void setColor_hitBox_colliding(const Color &color);

        virtual const Color &getColor_boundingBox_noIntersection() const;
        virtual const Color &getColor_boundingBox_intersecting() const;
        virtual const Color &getColor_hitBox_noCollision() const;
        virtual const Color &getColor_hitBox_colliding() const;

        virtual void generateCollisionData(bool enable);
        virtual VertexPath* getDrawableBoundingBox();
        //virtual vector<VertexPath*> getDrawableHitBox();
        virtual VertexPath* getDrawableHitBox();
        virtual vector<VertexPath*> getDrawableColliderVector();

        static void stats_reset();
        static unsigned long long stats_checkIntersectCounter;
        static unsigned long long stats_doesIntersectCounter;
        static unsigned long long stats_checkCollisionCounter;
        static unsigned long long stats_doesCollideCounter;

        void resetStateChanged();
        bool stateChanged() const;

        // Signals
      /*  virtual void subscribe_ColliderSignal(ColliderSignal *subscriber);
        virtual void unsubscribe_ColliderSignal(ColliderSignal *subscriber);
        virtual void unsubscribeAll_ColliderSignal();*/
    protected:

        virtual void setBoundingBox();
        virtual void setBoundingBox(const AABB &box);
      //  virtual void setBoundingBox(const int &x,const int &y,
      //                              const int &width,const int &height);



        AABB  m_boundingBox;
        Shape m_shape;
        //vector<RectF> m_hitboxList;

        bool m_boundingBoxUpdated;

        //RectF m_dummy;

        Color *m_boundingBox_color;
        Color m_boundingBox_standardColor;
        Color m_boundingBox_intersectingColor;

        Color m_hitbox_standardColor;
        Color m_hitbox_intersectingColor;
        //vector<bool>    m_hitBoxListDoesIntersect;
        bool m_hitShapeDoesIntersect;

        bool m_generate_collisionData;
        vector<VertexPath*> m_collisionData;

        bool m_stateChanged;

      //  ColliderSubscriberList m_colliderSubscriber;
    private:

        virtual void internalRotate(const Vector2f &rotPoint,const float &deg);


};
#endif
