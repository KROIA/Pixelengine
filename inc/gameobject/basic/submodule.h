#ifndef SUBMODULE_H
#define SUBMODULE_H
#include "base.h"
#include "layeritem.h"
#include "dynamicCoordinator.h"
#include "collider.h"
#include "controller.h"
#include "painter.h"

#include "signalSubscriber.h"


class Submodule :   public LayerItem
{
    public:
        Submodule();
        ~Submodule();

        void engineCalled_setup();


        bool hasEventsToCheck() const;
        void engineCalled_checkEvent();
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

        virtual Collider* getCollider();
        virtual const Vector2f &getMovingVector() const;

        virtual void subscribe_SubmoduleSignal(SubmoduleSignal *subscriber);
        virtual void unsubscribe_SubmoduleSignal(SubmoduleSignal *subscriber);
        virtual void unsubscribeAll_SubmoduleSignal();

    protected:

        virtual void addEvent(Event *e);
        virtual void removeEvent(Event *e);
        virtual void addPainter(Painter *painter);
        virtual void removePainter(Painter *painter);
        virtual void setCollider(Collider *collider);

   /*     // Signals from UserEventSignal
        virtual void eventAdded(UserEventHandler *sender,  Event *e);
        virtual void eventRemoved(UserEventHandler *sender,  Event *e);

        // Signals from Controller
        virtual void moveAvailable(Controller *sender);*/

      //  virtual void event_hasCollision(vector<GameObject *> other) = 0;


        SubmoduleSubscriberList m_submoduleSubscriberList;

        //bool      m_visibility;

        vector<Event* >     m_eventList;
        vector<Painter* >   m_painterList;

        Collider*           m_collider;

        DynamicCoordinator  m_movementCoordinator;

        bool           m_hasEventsToCheck;
        bool           m_hasMoveToMake;

        Vector2f       m_movingVector;

    private:
};
#endif // SUBMODULE_H
