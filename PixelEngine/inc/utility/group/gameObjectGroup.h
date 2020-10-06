#ifndef GAMEOBJECTGROUP_H
#define GAMEOBJECTGROUP_H

#include <vector.h>
#include "gameobject.h"
#include "painter.h"

using std::vector;

class GameObjectGroup  :   public vector<GameObject*>
{
    public:
        GameObjectGroup();
        GameObjectGroup(const GameObjectGroup &other);

        virtual ~GameObjectGroup();

        virtual void push_back(GameObject* obj);
        virtual void append(const vector<GameObject*> &other);
        virtual void remove(GameObject *toRemove);
        virtual void remove(const vector<GameObject*> &other);

        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;
        virtual void setHitboxVisibility(const bool &isVisible);
        virtual const bool &isHitboxVisible() const;

    protected:
        bool m_isVisible;
        bool m_hitBoxIsVisible;
    private:

};
#endif // GAMEOBJECTGROUP_H
