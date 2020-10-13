#ifndef GAMEOBJECTGROUP_H
#define GAMEOBJECTGROUP_H

#include <vector.h>
#include "gameobject.h"
#include "painter.h"

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

        virtual void setRotation(const double &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();

        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;
        virtual void setHitboxVisibility(const bool &isVisible);
        virtual const bool &isHitboxVisible() const;



    protected:
        bool m_isVisible;
        bool m_hitboxIsVisible;

        vector<GameObject *> m_list;
    private:

};
#endif // GAMEOBJECTGROUP_H
