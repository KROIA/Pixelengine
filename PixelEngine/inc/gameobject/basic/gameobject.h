#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "property.h"
#include "controller.h"
#include "collider.h"
#include "painter.h"
#include "hitboxPainter.h"

class GameObjectEventHandler;
class GameObject;

//typedef  void (GameObject::*collisionSlot)(GameObject *);

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
        static vector<GameObject*> getCollidedObjects(GameObject *owner, Collider *collider,const vector<GameObject*> &other);
        //static  void checkCollision(GameObject *owner,collisionSlot slot,Collider *collider,const vector<GameObject*> &other);
        virtual void draw(PixelDisplay &display);


        virtual void setController(Controller *controller);
        virtual const Controller &getController() const;
        virtual void setCollider(Collider *collider);
        virtual const Collider &getCollider() const;
        virtual void setPainter(Painter *painter);
        virtual const Painter &getPainter() const;
        virtual void setEventHandler(GameObjectEventHandler *handler);

        // Controller stuff
        virtual void setPosInitial(const Point &pos);
        virtual void setPosInitial(const int &x, const int &y);

        virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Point &pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual void moveToPos(const Point &destination);
        virtual void moveToPos(const int &x,const int &y);
        virtual void move(const Point &directionVector);
        virtual void move(int x,int y);

        virtual const Point &getPos();


        // Collider settings
        virtual const bool &isBoundingBoxUpdated() const;
        virtual void updateBoundingBox();

        // Painter settings
        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;
        virtual void setHitboxVisibility(const bool &isVisible);
        virtual const bool &isHitboxVisible() const;

        // Properties
        virtual void setProperty(const Property::Property &property);
        virtual const Property::Property &getProperty() const;

    protected:
        virtual void event_hasCollision(GameObject *other);
   /*     virtual void event_hasCollision_slot2(GameObject *other) = 0;
        virtual void event_hasCollision_slot3(GameObject *other) = 0;
        virtual void event_hasCollision_slot4(GameObject *other) = 0;
        virtual void event_hasCollision_slot5(GameObject *other) = 0;
        virtual void event_hasCollision_slot6(GameObject *other) = 0;
*/
        Property::Property m_property;
        GameObjectEventHandler *m_objEventHandler;

        Controller *m_controller;
        Collider   *m_collider;
        Painter    *m_painter;

        Painter    *m_hitboxPainter;

    private:




};
#endif // GAMEOBJECT_H
