#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "base.h"

#include "submodule.h"
#include "property.h"
#include "controller.h"
#include "dynamicCoordinator.h"
#include "collider.h"
#include "spritePainter.h"
#include "pixelPainter.h"
#include "texturePainter.h"
#include "textPainter.h"
#include "colliderPainter.h"
#include "signalSubscriber.h"
#include "sensor.h"
#include "displayInterface.h"


// Signals for GameObjects
class ObjSignal
{
    public:
        ObjSignal(){}

        virtual void moved(GameObject* sender,const Vector2f &move) = 0;
        virtual void rotated(GameObject* sender,const float deltaAngle) = 0;
    protected:

};
// Vector of Signals
class ObjSubscriberList    : public SubscriberList<ObjSignal>
{
    public:
        ObjSubscriberList();

        virtual void moved(GameObject* sender,const Vector2f &move);
        virtual void rotated(GameObject* sender,const float deltaAngle);
    protected:
};



class GameObject : public Submodule, private ControllerSignal, UserEventSignal, ColliderSignal
{
    public:
        GameObject();
        /*GameObject(const GameObject &other);
        GameObject(Controller *controller,
                   Collider   *collider,
                   Painter    *painter);*/

        virtual ~GameObject();
       // virtual const GameObject &operator=(const GameObject &other);


        // Events
      //  virtual void addEvent(Event *e);
      //  virtual void removeEvent(Event *e);
        void engineCalled_checkEvent();
        virtual void checkEvent();
        //virtual bool hasEventsToCheck() const;
        virtual void killMe();             // Not defined jet in the engine class
        virtual void removeMeFromEngine(); // Removes this obj from the engine, but the obj won't get destroyed


        // called by the Engine
        void engineCalled_setup();
        virtual void setup();
        void engineCalled_preTick();
        virtual void preTick();
        void engineCalled_tick(const Vector2i &direction);
        virtual void tick(const Vector2i &direction);
        void engineCalled_postTick();
        virtual void postTick();
        void engineCalled_postNoThreadTick();
        void engineCalled_preDraw();
        virtual void preDraw();

        virtual unsigned int checkCollision(const vector<GameObject*> &other);
        static vector<GameObject*> getCollidedObjects(GameObject *owner, Collider *collider,const vector<GameObject*> &other);
       // virtual void subscribeToDisplay(PixelDisplay &display);
       // virtual void unsubscribeToDisplay(PixelDisplay &display);
        virtual void setDisplayInterface(DisplayInterface *display);

        // Signals
        virtual void subscribe_ObjSignal(ObjSignal *subscriber);
        virtual void unsubscribe_ObjSignal(ObjSignal *subscriber);
        virtual void unsubscribeAll_ObjSignal();


        // For user call
    //    virtual void addController(Controller *controller);
    //    virtual void clearController();
        virtual void setCollider(Collider *collider);
        virtual Collider *getCollider() const;
        virtual void setCollisionSeachRadius(float radius);
        virtual float getCollisionSeachRadius() const;
        virtual const RectF &getCollisionSeachRect() const;
        virtual void addController(Controller *controller);
        virtual void removeController(Controller *controller);
        virtual const vector<Controller* > &getControllerList() const;

        virtual void addSensor(Sensor *sensor);
        virtual void removeSensor(Sensor *sensor);
        virtual const vector<Sensor*> &getSensorList() const;
    //    virtual const Collider &getCollider() const;
    //    virtual void setPainter(Painter *painter);
    //    virtual const Painter &getPainter() const;


       virtual void setPosInitial(const Vector2f &pos);
      //// virtual void setPos(int x, int y);
//    //   virtual void setPos(const Vector2i &pos);
      // virtual void setPos(float x, float y);
      // virtual void setPos(const Vector2f &pos);
      //
      // virtual void setX(int x);
      // virtual void setY(int y);
      // virtual void setX(float x);
      // virtual void setY(float y);

     //   virtual void moveToPos(const Vector2i&destination,Controller::MovingMode mode = Controller::MovingMode::add);
     //   virtual void moveToPos(const int &x,const int &y,Controller::MovingMode mode = Controller::MovingMode::add);
     //  virtual void move(const Vector2i&vec,Controller::MovingMode mode = Controller::MovingMode::add);
       virtual void move(const Vector2f &vec,Controller::MovingMode mode = Controller::MovingMode::add);
       virtual void move(float deltaX, float deltaY,Controller::MovingMode mode = Controller::MovingMode::add);
       virtual void moveX(float delta,Controller::MovingMode mode = Controller::MovingMode::add);
       virtual void moveY(float delta,Controller::MovingMode mode = Controller::MovingMode::add);

       virtual void rotate(float deg);
       virtual void setRotation(float deg);
       virtual void setRotation(const Vector2f &rotationPoint,float deg);
        //   virtual const Vector2f &getPos() const;
    //   virtual const Vector2f &getMovingVector() const;

     //  virtual float getRotation() const;
     //  virtual void rotate(const float &deg);
     //  virtual void setRotation(const float &deg);
     //  virtual void rotate_90();
     //  virtual void rotate_180();
     //  virtual void rotate_270();
     //  virtual void setRotation(const Vector2f &rotationPoint,const float &deg);
     //  virtual void rotate_90(const Vector2f &rotationPoint);
     //  virtual void rotate_180(const Vector2f &rotationPoint);
     //  virtual void rotate_270(const Vector2f &rotationPoint);



        // Collider settings
     //   virtual void addHitbox(const RectI &box);
     //   virtual void addHitbox(const vector<RectI> &boxList);
     //   virtual void eraseHitbox(const size_t &index);
     //   virtual void clearCollider();
     //   virtual const bool &isBoundingBoxUpdated() const;
     //   virtual void updateBoundingBox();
     //   virtual void setHitboxFromTexture(const Texture &texture);
     //   virtual const RectF &getBoundingBox() const;


        // Painter
//        virtual void setRenderLayer(size_t layer);
//        virtual size_t getRenderLayer() const;
        virtual bool addPainter(Painter *painter);
        virtual bool removePainter(Painter *painter);
        ColliderPainter *getColliderPainter() const;
        virtual void setVisibility(bool isVisible);
        virtual void setVisibility_objectTree(bool isVisible);
        virtual void setVisibility_colliderSearchRect(bool isVisible);
       /* virtual void setVisibility_collider_hitbox(bool isVisible);
        virtual void setVisibility_collider_boundingBox(bool isVisible);
        virtual void setVisibility_collider_collisionData(bool isVisible);
        virtual void setVisibility_collider_isCollidingWith_boundingBox(bool isVisible);
        virtual void setVisibility_collider_isCollidingWith_hitBox(bool isVisible);*/

        virtual bool isVisible() const;
        virtual bool isVisible_objectTree() const;
        virtual bool isVisible_colliderSearchRect() const;
       /* virtual bool isVisible_collider_hitbox() const;
        virtual bool isVisible_collider_boundingBox() const;
        virtual bool isVisible_collider_collisionData() const;
        virtual bool isVisible_collider_isCollidingWith_boundingBox() const;
        virtual bool isVisible_collider_isCollidingWith_hitBox() const;*/

        // Properties
        virtual void setProperty(const Property::Property &property);
        virtual const Property::Property &getProperty() const;

        // Text visualisation
    //    virtual void addPainter(Painter *painter);
    //    virtual void removePainter(Painter *painter);
     //   virtual void removePainter();

    //    virtual vector<Painter*> getPainterList();

        void markAsTrash(bool isTrash);
        bool isTrash() const;

        void setThisInteractiveGameObject(InteractiveGameObject *parent);
        InteractiveGameObject* getThisInteractiveGameObject();

        virtual void display_setPixel(const Vector2u &pos, const Color &color);
        virtual void display_setPixel(const Pixel &pixel);
        virtual void display_setPixel(const vector<Pixel> &pixelList);
        virtual void display_zoomViewAt(sf::Vector2i pixel, float zoom);
        virtual void display_setView(const RectF &frame);
        virtual void display_setCameraZoom(float zoom);
        virtual void display_setCameraPos(const Vector2f &pos);
        virtual const Vector2u &display_getWindowSize() const;
        virtual const Vector2u &display_getMapSize() const;

    protected:
        virtual void display_subscribePainter(Painter *painter) ;
        virtual void display_unsubscribePainter(Painter *painter) ;

        void checkIfUtilityPainterIsUsed();

        void constructor();
        void constructor(Controller *controller,
                         Collider   *collider,
                         Painter    *painter);
        virtual void event_hasCollision(vector<GameObject *> other);

        // Signals from UserEventSignal
        virtual void eventAdded(UserEventHandler *sender,  Event *e);
        virtual void eventRemoved(UserEventHandler *sender,  Event *e);

        // Signals from Controller
        virtual void moveAvailable(Controller *sender);

        // Signals from Collider
        virtual void boundingBoxChanged(Collider* sender);


      //  LayerItem m_layerItem;

        Property::Property m_property;
        DisplayInterface *m_display_interface;
        ObjSubscriberList m_objSubscriberList;

      //  vector<Controller*> m_controllerList;
      //  bool           m_hasEventsToCheck;
      //  bool           m_hasMoveToMake;
        DynamicCoordinator m_movementCoordinator;
        Collider      *m_collider;
        Collider      *m_originalCollider;
        RectF         m_colliderSearchBox;
        Vector2f      m_colliderSearchBoxRelativePos;
        float         m_colliderSearchBoxRadius;



        // Painter
      //  Painter             *m_painter;
        Controller          *m_controller;
        ColliderPainter     *m_colliderPainter;
        VertexPathPainter   *m_utilityPainter;
        bool                 m_visibility_colliderSearchBox;

     //   PixelPainter        *m_originalPainter;

        bool                m_visibility;

       // HashTable<Painter* >  m_painterList;
       // HashTable<Event*>     m_eventList;
        vector<GameObject*>   m_collidedObjects;
        InteractiveGameObject *m_thisInteractiveObject;

        vector<Controller* > m_controllerList;
        vector<Sensor* >     m_sensorList;

    private:
        bool m_isTrash;
        Vector2u m_dummiVecU;
};
#endif // GAMEOBJECT_H
