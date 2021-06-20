#ifndef INTERACTIVEGAMEOBJECT_H
#define INTERACTIVEGAMEOBJECT_H

#include "gameobject.h"
#include "gameObjectGroup.h"
#include "vector"

#define CHECK_FOR_DOUBLE_OBJ

using std::vector;


class InteractiveGameObject
{
    public:
        InteractiveGameObject();
        InteractiveGameObject(const InteractiveGameObject &other);
        virtual ~InteractiveGameObject();

        virtual void setGameObject(GameObject *obj);
        virtual GameObject *getGameObject() const;

        virtual void addInteractionWith(GameObject *obj);
        virtual void addInteractionWith(GameObjectGroup *group);
        virtual void addInteractionWith(vector<GameObjectGroup*> *groupList);

        virtual void removeInteractionWith(GameObject *obj);
        virtual void removeInteractionWith(GameObjectGroup *group);
        virtual void removeInteractionWith(vector<GameObjectGroup*> *groupList);

        virtual void setInteractionWith(GameObject *obj, bool doesCollide = true);
        virtual void setInteractionWith(GameObjectGroup *group, bool doesCollide = true);
        virtual void setInteractionWith(vector<GameObjectGroup*> *groupList, bool doesCollide = true);

        virtual const vector<GameObjectGroup*> &getInteractiveObjectsList() const;
        virtual const GameObjectGroup getInteractiveObjects() const;


    protected:
        GameObject *m_gameObject;
        vector<GameObjectGroup*> m_interactsWithObjectsList;

    private:
};
#endif // INTERACTIVEGAMEOBJECT_H
