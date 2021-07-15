#ifndef GAMEOBJECTGROUP_H
#define GAMEOBJECTGROUP_H
#include "base.h"

#include "gameobject.h"
#include "painter.h"

//                         Will receive GameObject Signals
class GameObjectGroup  :   private ObjSignal//, GroupSignal
{
    public:
        GameObjectGroup();
        GameObjectGroup(const GameObjectGroup &other);
        virtual GameObjectGroup &operator=(const GameObjectGroup &other);

        virtual ~GameObjectGroup();

        virtual void draw(PixelDisplay &display);

        virtual void add(GameObject *object);
        virtual void add(GameObjectGroup *other);
        virtual void remove(GameObject *toRemove);
        virtual void remove(GameObjectGroup *other);
        virtual void remove(const size_t index);
        virtual void clear();
        virtual void reserve(size_t size);
        virtual size_t size() const;
        virtual GameObject *operator[](const size_t &index) const;
        virtual const vector<GameObject*> &getVector() const;

        // GameObject stuff
        virtual void setPosInital(const Vector2f &pos);
        virtual void setPos(int x, int y);
        virtual void setPos(const Vector2i &pos);
        virtual void setPos(float x, float y);
        virtual void setPos(const Vector2f &pos);

        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setX(float x);
        virtual void setY(float y);

        virtual void moveToPos(const Vector2i&destination,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveToPos(const int &x,const int &y,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector2i&vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector2f &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const float &deltaX, const float &deltaY,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveX(const float &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveY(const float &delta,Controller::MovingMode mode = Controller::MovingMode::add);

        virtual void rotate(const float &deg);
        virtual void setRotation(const float &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const Vector2f &rotationPoint,const float &deg);
        virtual void rotate_90(const Vector2f &rotationPoint);
        virtual void rotate_180(const Vector2f &rotationPoint);
        virtual void rotate_270(const Vector2f &rotationPoint);

        virtual void setVisibility(bool isVisible);
        virtual void setVisibility_objectTree(bool isVisible);
       // virtual void setVisibility_chunks(bool isVisible);
       // virtual void setVisibility_chunk(const ChunkID &id, bool isVisible);
        virtual void setVisibility_collider_hitbox(bool isVisible);
        virtual void setVisibility_collider_boundingBox(bool isVisible);
        virtual void setVisibility_collider_collisionData(bool isVisible);
        virtual void setVisibility_collider_isCollidingWith(bool isVisible);

        virtual bool isVisible() const;
        virtual bool isVisible_objectTree() const;
       // virtual bool isVisible_chunks() const;
       // virtual bool isVisible_collider_hitbox() const;
        virtual bool isVisible_collider_boundingBox() const;
        virtual bool isVisible_collider_collisionData() const;
        virtual bool isVisible_collider_isCollidingWith() const;

        virtual long long indexOf(const GameObject* obj);
        static  long long indexOf(const vector<GameObject *> list,const GameObject* obj);

        static void removinguplicates(vector<GameObject *> *list);
        static void removinguplicates(GameObjectGroup *list);

        // Signals
        virtual void subscribeGroupSignal(GroupSignal   *subscriber);
        virtual void unsubscribeGroupSignal(GroupSignal *subscriber);
        virtual void unsubscribeAllGroupSignal();

    protected:
        void addInternal(GameObject *object);
        void removeInternal(GameObject *object);
        void removeInternal(size_t index);

        // GameObject singals:
        virtual void moved(GameObject* sender,const Vector2f &move);
        virtual void rotated(GameObject* sender,const float deltaAngle);

        bool          m_visibility;
        bool          m_visibility_collider_hitbox;
        bool          m_visibility_collider_boundingBox;
        bool          m_visibility_collider_collisionData;
        bool          m_visibility_collider_collidingWith;
        bool          m_visibility_objectTree;
        //bool          m_visibility_chunks;

        vector<GameObject *> m_isInList;
        GroupSubscriberList m_groupSubscriberList;
    private:




        // GameObjectGroup signals:
        // virtual void adding(GameObjectGroup* group,GameObject* obj);

};
#endif // GAMEOBJECTGROUP_H
