#ifndef COLLIDERPAINTER_H
#define COLLIDERPAINTER_H

#include "vertexPathPainter.h"
#include "collider.h"
#include "gameobject.h"

class ColliderPainter   :   public VertexPathPainter
{
    public:
        ColliderPainter();
        ColliderPainter(Collider *collider);

        void setCollider(Collider *collider);
        void update(const vector<GameObject* > &collided);

        void setVisibility_boundingBox(bool isVisible);
        void setVisibility_hitBox(bool isVisible);
        void setVisibility_collisionData(bool isVisible);
        void setVisibility_collidedObjects_boundingBox(bool isVisible);
        void setVisibility_collidedObjects_hitBox(bool isVisible);

        bool isVisible_boundingBox();
        bool isVisible_hitBox();
        bool isVisible_collisionData();
        bool isVisible_collidedObjects_boundingBox();
        bool isVisible_collidedObjects_hitBox();

        void setColor_boundingBox_noIntersection(const Color &color);
        void setColor_boundingBox_intersecting(const Color &color);
        void setColor_hitBox_noCollision(const Color &color);
        void setColor_hitBox_colliding(const Color &color);
        void setColor_collidedObjects_boundingBox(const Color &color);
        void setColor_collidedObjects_hitBox(const Color &color);


        const Color &getColor_boundingBox_noIntersection() const;
        const Color &getColor_boundingBox_intersecting() const;
        const Color &getColor_hitBox_noCollision() const;
        const Color &getColor_hitBox_colliding() const;
        const Color &getColor_collidedObjects_boundingBox() const;
        const Color &getColor_collidedObjects_hitBox() const;

    protected:
        void setRotation(float deg);
        void rotate(float deg);
        void rotate_90();
        void rotate_180();
        void rotate_270();
        void setRotation(const Vector2f &rotPoint,float deg);
        void rotate(const Vector2f &rotPoint,float deg);
        void rotate_90(const Vector2f &rotPoint);
        void rotate_180(const Vector2f &rotPoint);
        void rotate_270(const Vector2f &rotPoint);

        void checkIfPainterIsVisible();
        Collider *m_collider;
        bool m_visibility_boundingBox;
        bool m_visibility_hitbox;
        bool m_visibility_collisionData;
        bool m_visibility_collidedObjects_boundingBox;
        bool m_visibility_collidedObjects_hitBox;

        Color m_collidedObjectsColor_boundingBox;
        Color m_collidedObjectsColor_hitBox;
        Color m_dummyColor;
        size_t m_hashed_colliderObjectsList;
    private:

};
#endif // COLLIDERPAINTER_H
