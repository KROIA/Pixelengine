#ifndef GAMEOBJECTGROUP_H
#define GAMEOBJECTGROUP_H

#include <vector.h>
#include "gameobject.h"
#include "painter.h"

using std::vector;

class GameObjectGroup  //:   public vector<GameObject*>
{
    public:
        GameObjectGroup();
        GameObjectGroup(const GameObjectGroup &other);

        virtual ~GameObjectGroup();

        virtual void add(GameObject *object);
        virtual void add(GameObjectGroup *other);
        virtual void remove(GameObject *toRemove);
        virtual void remove(GameObjectGroup *other);
        virtual void remove(const size_t index);
        virtual void clear();

        //virtual void push_back(GameObject* obj);
        //virtual void append(const vector<GameObject*> &other);


        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;
        virtual void setHitboxVisibility(const bool &isVisible);
        virtual const bool &isHitboxVisible() const;

        virtual size_t size() const;
        virtual GameObject *operator[](const size_t &index) const;
        virtual const vector<GameObject*> &getVector() const;

    protected:
        bool m_isVisible;
        bool m_hitBoxIsVisible;

        vector<GameObject *> m_list;
    private:

};
#endif // GAMEOBJECTGROUP_H
