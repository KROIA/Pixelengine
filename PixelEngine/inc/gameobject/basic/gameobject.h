#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "controller.h"
#include "collider.h"
#include "painter.h"
#include "hitboxPainter.h"

class GameObject
{
    public:
        GameObject();
        GameObject(const GameObject &other);
        GameObject(Controller *controller,
                   Collider   *collider,
                   Painter    *painter);

        virtual ~GameObject();

        virtual void checkEvent();
        virtual void tick(const Point &direction);
        //virtual void checkCollision(); // Checks collision with this->m_collisionInteractionGroup
        virtual void checkCollision(const vector<GameObject*> &other);
        virtual void draw(PixelDisplay &display);


        virtual void setController(Controller *controller);
        virtual void setCollider(Collider *collider);
        virtual void setPainter(Painter *painter);


        // Collider settings
        //virtual void addInteraction_collision_with(GameObject *other);
        //virtual void addInteraction_collision_with(const vector<GameObject *> otherList);

        // Painter settings
        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;
        virtual void setHitboxVisibility(const bool &isVisible);
        virtual const bool &isHitboxVisible() const;

       /* virtual void remove();
        virtual void reActivate();
        virtual const bool &isRemoved() const;*/

    protected:
        virtual void event_hasCollision(GameObject *other);

        // List of objects, which can collide whit this object
        //vector<GameObject*> m_collisionInteractionGroup;

    private:
        Controller *m_controller;
        Collider   *m_collider;
        Painter    *m_painter;

        Painter    *m_hitboxPainter;

        //bool m_isRemoved;
};
#endif // GAMEOBJECT_H
