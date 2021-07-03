#ifndef INTERACTIVEGAMEOBJECT_H
#define INTERACTIVEGAMEOBJECT_H

#include "base.h"
#include "gameobject.h"
#include "gameObjectGroup.h"

#define CHECK_FOR_DOUBLE_OBJ

class InteractiveGameObject : private GroupSignal, ObjSignal
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
        virtual const GameObjectGroup &getInteractiveObjects();


    protected:
        virtual void updateAllList();

        GameObject *m_gameObject;
        vector<GameObjectGroup*> m_interactsWithObjectsList;
        GameObjectGroup m_allList;

    private:
        // GameObject singals:
        virtual void moved(GameObject* sender,const Vector2f &move);

        // Signals from GameObjectGroup
        virtual void adding(GameObjectGroup* sender,GameObject* obj);
        virtual void adding(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void removing(GameObjectGroup* sender,GameObject* obj);
        virtual void removing(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void willBeCleared(GameObjectGroup* sender);
        virtual void cleared(GameObjectGroup* sender);
};
#endif // INTERACTIVEGAMEOBJECT_H
