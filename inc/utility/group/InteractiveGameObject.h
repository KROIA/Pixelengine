#ifndef INTERACTIVEGAMEOBJECT_H
#define INTERACTIVEGAMEOBJECT_H

#include "base.h"
#include "gameobject.h"
#include "gameObjectGroup.h"
#include "objectTree.h"

#define CHECK_FOR_DOUBLE_OBJ

class InteractiveGameObject : private GroupSignal, ObjSignal
{
    public:
        struct Settings
        {
           // ChunkMap::Settings chunkMap;
            ObjectTree::Settings    objectTree;
        };
        static Settings __defaultSettings;
        InteractiveGameObject();
        InteractiveGameObject(const Settings &settings);
        InteractiveGameObject(const InteractiveGameObject &other);
        virtual ~InteractiveGameObject();

        virtual const InteractiveGameObject &operator=(const InteractiveGameObject &other);
        virtual Settings getSettings() const;

        virtual void preTick();
        virtual void postTick();
        virtual inline void preDraw();

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

        virtual bool doesInteractWithOther() const;
        virtual const vector<GameObjectGroup*> &getInteractiveObjectsList() const;
        virtual const vector<GameObject*> getInteractiveObjects();


        //virtual void drawObjectTree(PixelDisplay &display);
        virtual void subscribeToDisplay(PixelDisplay &display);
        virtual void unsubscribeToDisplay(PixelDisplay &display);
        virtual void setVisibility_objectTree(bool isVisible);
        virtual bool isVisible_objectTree() const;
        /*virtual void draw_chunks(PixelDisplay &display);
        virtual void setVisibility_chunk(const ChunkID &id,bool isVisible);
        virtual void setVisibility_chunks(bool isVisible);
        virtual bool isVisible_chunk(const ChunkID &id) const;
        virtual bool isVisible_chunks() const;
*/


    protected:
        // GameObject singals:
        virtual void moved(GameObject* sender,const Vector2f &move);
        virtual void rotated(GameObject* sender,const float deltaAngle);

        // Signals from GameObjectGroup
        virtual void adding(GameObjectGroup* sender,GameObject* obj);
        virtual void adding(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void removing(GameObjectGroup* sender,GameObject* obj);
        virtual void removing(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void willBeCleared(GameObjectGroup* sender);
        virtual void cleared(GameObjectGroup* sender);

        GameObject *m_gameObject;
        ObjectTree   *m_objectTree;
        VertexPathPainter *m_objectTreePainter;

        vector<GameObjectGroup*> m_interactsWithObjectsList;
        size_t      m_interactorAmount;
        bool        m_drawingIsDisabled;
        bool        m_interactsWithOthers;
    private:
        void constructor(const Settings &settings);

};
#endif // INTERACTIVEGAMEOBJECT_H
