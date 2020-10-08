#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "property.h"
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
        virtual const GameObject &operator=(const GameObject &other);

        virtual void checkEvent();
        virtual void tick(const Point &direction);
        virtual void checkCollision(const vector<GameObject*> &other);
        virtual void draw(PixelDisplay &display);


        virtual void setController(Controller *controller);
        virtual void setCollider(Collider *collider);
        virtual void setPainter(Painter *painter);

        virtual void setPosInitial(const Point &pos);
        virtual void setPosInitial(const int &x, const int &y);


        // Collider settings
        virtual const bool &isBoundingBoxUpdated() const;
        virtual void updateBoundingBox();

        // Painter settings
        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;
        virtual void setHitboxVisibility(const bool &isVisible);
        virtual const bool &isHitboxVisible() const;

        virtual void setProperty(const Property::Property &property);
        virtual const Property::Property &getProperty() const;

    protected:
        virtual void event_hasCollision(GameObject *other);

    private:
        Controller *m_controller;
        Collider   *m_collider;
        Painter    *m_painter;

        Painter    *m_hitboxPainter;

        Property::Property m_property;

};
#endif // GAMEOBJECT_H
