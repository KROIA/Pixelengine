#ifndef GAMEOBJECTGROUP_H
#define GAMEOBJECTGROUP_H

#include <vector.h>
#include "gameobject.h"
#include "painter.h"

#include "profiler.h"

using std::vector;

class GameObjectGroup
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
        virtual size_t size() const;
        virtual GameObject *operator[](const size_t &index) const;
        virtual const vector<GameObject*> &getVector() const;

        // GameObject stuff
       // virtual void setPosInitial(const Vector2i&pos);
       // virtual void setPosInitial(const int &x, const int &y);

        virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Vector2i&pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual void moveToPos(const Vector2i&destination,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveToPos(const int &x,const int &y,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector2i&vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector2f &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const float &deltaX, const float &deltaY,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveX(const float &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveY(const float &delta,Controller::MovingMode mode = Controller::MovingMode::add);

        virtual void setRotation(const float &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const Vector2f &rotationPoint,const float &deg);
        virtual void rotate_90(const Vector2f &rotationPoint);
        virtual void rotate_180(const Vector2f &rotationPoint);
        virtual void rotate_270(const Vector2f &rotationPoint);

        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;
        virtual void setHitboxVisibility(const bool &isVisible);
        virtual const bool &isHitboxVisible() const;

        virtual long long indexOf(const GameObject* obj);
        static  long long indexOf(const vector<GameObject *> list,const GameObject* obj);

        static void removeDuplicates(vector<GameObject *> *list);
        static void removeDuplicates(GameObjectGroup *list);

    protected:
        bool m_isVisible;
        bool m_hitboxIsVisible;

        vector<GameObject *> m_isInList;
    private:


};
#endif // GAMEOBJECTGROUP_H
