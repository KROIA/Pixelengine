#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "controller.h"
#include "collider.h"
#include "painter.h"

class GameObject
{
    public:
        GameObject();
        GameObject(const GameObject &other);
        GameObject(Controller *controller,
                   Collider   *collider,
                   Painter    *painter);

        virtual ~GameObject();

        virtual void tick(const Point &direction);
        virtual void checkCollision(const vector<GameObject*> &other);
        virtual void draw(PixelDisplay &display);


        virtual void setController(Controller *controller);
        virtual void setCollider(Collider *collider);
        virtual void setPainter(Painter *painter);

        //virtual void applyNextPos();


    protected:
        virtual void event_hasCollision(GameObject *other);

    private:
        Controller *m_controller;
        Collider   *m_collider;
        Painter    *m_painter;

};
#endif // GAMEOBJECT_H
