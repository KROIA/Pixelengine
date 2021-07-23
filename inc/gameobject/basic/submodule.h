#ifndef SUBMODULE_H
#define SUBMODULE_H
#include "base.h"
#include "layeritem.h"
//#include "dynamicCoordinator.h"
#include "collider.h"
#include "controller.h"
#include "painter.h"
#include "engineInterface.h"

#include "signalEmitter.h"
// Signals for GameObjects
/*class SubmoduleSignal
{
    public:
        SubmoduleSignal(){}

        virtual void moved(Submodule* sender,const Vector2f &move) = 0;
        virtual void rotated(Submodule* sender,const float deltaAngle) = 0;
    protected:

};
// Vector of Signals
class SubmoduleSubscriberList    : public SubscriberList<SubmoduleSignal>
{
    public:
        SubmoduleSubscriberList();

        virtual void moved(Submodule* sender,const Vector2f &move);
        virtual void rotated(Submodule* sender,const float deltaAngle);
    protected:
};*/
SIGNAL_DEF(Submodule)
    SIGNAL_FUNC(moved,const Vector2f &)
    SIGNAL_FUNC(rotated,float)
SIGNAL_DEF_END

SIGNAL_EMITTER_DEF(Submodule)
    SIGNAL_EMITTER_FUNC(moved,const Vector2f &)
    SIGNAL_EMITTER_FUNC(rotated,float)
SIGNAL_EMITTER_DEF_END



class Submodule :   public LayerItem
{
    SIGNAL_EMITTER(Submodule)
    public:
        Submodule();
        Submodule(const Submodule &other);
        ~Submodule();
        const Submodule &operator=(const Submodule &other);

        void engineCalled_setup();
        void setEngineInterface(EngineInterface *engine);
        EngineInterface *getEngineInterface() const;
        //static void setDisplay(const PixelDisplay *display);


        bool hasEventsToCheck() const;
        void engineCalled_checkEvent(float deltaTime);
        void engineCalled_preTick();
        void engineCalled_tick(const Vector2i &direction);
        void engineCalled_postTick();
        void engineCalled_postNoThreadTick();
        void engineCalled_preDraw();

        virtual void setPosInitial(const Vector2f &pos);
      //  virtual void setPos(int x, int y);
      //  virtual void setPos(const Vector2i &pos);
        virtual void setPos(float x, float y);
        virtual void setPos(const Vector2f &pos);

     //   virtual void setX(int x);
     //   virtual void setY(int y);
        virtual void setX(float x);
        virtual void setY(float y);

      /*  virtual void moveToPos(const Vector2i&destination,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveToPos(const int &x,const int &y,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector2i&vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector2f &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const float &deltaX, const float &deltaY,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveX(const float &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveY(const float &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual const Vector2f &getPos() const;
        virtual const Vector2f &getMovingVector() const;*/

        //virtual float getRotation() const;
        virtual void rotate(float deg);
        virtual void setRotation(float deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const Vector2f &rotationPoint,float deg);
        virtual void rotate_90(const Vector2f &rotationPoint);
        virtual void rotate_180(const Vector2f &rotationPoint);
        virtual void rotate_270(const Vector2f &rotationPoint);



        virtual void setRenderLayer(size_t layer);
        //virtual size_t getRenderLayer() const;

        virtual void setVisibility(bool isVisible);
        //virtual bool isVisible() const;

        virtual const vector<Event* > &getEventList() const;
        virtual const vector<Painter* > &getPainterList() const;

        //virtual Collider* getCollider();
        virtual const Vector2f &getMovingVector() const;

        /*virtual void subscribe_SubmoduleSignal(SubmoduleSignal *subscriber);
        virtual void unsubscribe_SubmoduleSignal(SubmoduleSignal *subscriber);
        virtual void unsubscribeAll_SubmoduleSignal();*/

        virtual bool addEvent(Event *e);
        virtual bool removeEvent(Event *e);
        virtual bool addPainter(Painter *painter);
        virtual bool removePainter(Painter *painter);
        //virtual void setCollider(Collider *collider);
        //virtual Collider *getCollider() const;

        virtual float getEngine_deltaTime() const;

    protected:



   /*     // Signals from UserEventSignal
        virtual void eventAdded(UserEventHandler *sender,  KeyEvent *e);
        virtual void eventRemoved(UserEventHandler *sender,  KeyEvent *e);

        // Signals from Controller
        virtual void moveAvailable(Controller *sender);*/

      //  virtual void event_hasCollision(vector<GameObject *> other) = 0;


      //  SubmoduleSubscriberList m_submoduleSubscriberList;

        EngineInterface  *m_engine_interface;

        //bool      m_visibility;

        vector<Event* >     m_eventList;
        vector<Painter* >   m_painterList;

        //Collider*           m_collider;
        //Collider*           m_originalCollider;

        //DynamicCoordinator  m_movementCoordinator;

        bool           m_hasEventsToCheck;
        bool           m_hasMoveToMake;

        Vector2f       m_movingVector;
        float          m_engine_deltaTime;
    private:
};
#endif // SUBMODULE_H
