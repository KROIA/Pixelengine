#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "property.h"
#include "controller.h"
#include "collider.h"
#include "painter.h"
#include "hitboxPainter.h"
#include "dynamicCoordinator.h"

class GameObjectEventHandler;
class GameObject;

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
        virtual void draw(PixelDisplay &display);


        virtual void addController(Controller *controller);
        virtual void setCollider(Collider *collider);
        virtual const Collider &getCollider() const;
        virtual void setPainter(Painter *painter);
        virtual const Painter &getPainter() const;
        virtual void setEventHandler(GameObjectEventHandler *handler);

        virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Point &pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual void moveToPos(const Point &destination,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveToPos(const int &x,const int &y,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const VectorF &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const double &deltaX, const double &deltaY,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveX(const double &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveY(const double &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual const Point getPos() const;

        virtual double getRotation() const;
        virtual void setRotation(const double &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const PointF &rotationPoint,const double &deg);
        virtual void rotate_90(const PointF &rotationPoint);
        virtual void rotate_180(const PointF &rotationPoint);
        virtual void rotate_270(const PointF &rotationPoint);



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
        LayerItem m_layerItem;

        Property::Property m_property;
        GameObjectEventHandler *m_objEventHandler;

        vector<Controller*> m_controllerList;
        //Controller *m_controller;
        DynamicCoordinator m_movementCoordinator;
        Collider   *m_collider;
        Painter    *m_painter;

        Painter    *m_hitboxPainter;

        unsigned int m_rotationDeg;

    private:

        void rotate(const double &rad);


};
#endif // GAMEOBJECT_H
