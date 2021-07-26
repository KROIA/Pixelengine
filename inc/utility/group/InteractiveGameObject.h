#ifndef INTERACTIVEGAMEOBJECT_H
#define INTERACTIVEGAMEOBJECT_H

#include "base.h"
#include "gameobject.h"
#include "gameObjectGroup.h"
#include "objectTree.h"

#define CHECK_FOR_DOUBLE_OBJ
enum Interaction
{
    collision,
    detection
};
class InteractiveGameObject : SIGNAL_RECEIVES(GameObjectGroup), SIGNAL_RECEIVES(GameObject)
{
    public:
        struct Settings
        {
           // ChunkMap::Settings chunkMap;
            ObjectTree::Settings    objectTree;
        };

        struct InteractiveObjects
        {
            Interaction type;
            ObjectTree  *objectTree;
            VertexPathPainter *objectTreePainter;

            vector<GameObjectGroup*> interactsWithObjectsList;
            size_t  interactorAmount;
            bool    drawingIsDisabled;
            bool    interactsWithOthers;
        };

        static Settings __defaultSettings;
        InteractiveGameObject();
        InteractiveGameObject(const Settings &settings);
        InteractiveGameObject(const InteractiveGameObject &other);
        virtual ~InteractiveGameObject();

        virtual const InteractiveGameObject &operator=(const InteractiveGameObject &other);
        virtual Settings getSettings() const;


        virtual void engineCalled_preTick();
        virtual void engineCalled_postTick();
        virtual void engineCalled_preDraw();

        virtual void setGameObject(GameObject *obj);
        virtual GameObject *getGameObject() const;

        virtual void addInteractionWith(GameObject *obj,Interaction type);
        virtual void addInteractionWith(GameObjectGroup *group,Interaction type);
        virtual void addInteractionWith(vector<GameObjectGroup*> *groupList,Interaction type);

        virtual void removeInteractionWith(GameObject *obj,Interaction type);
        virtual void removeInteractionWith(GameObjectGroup *group,Interaction type);
        virtual void removeInteractionWith(vector<GameObjectGroup*> *groupList,Interaction type);

        virtual void setInteractionWith(GameObject *obj, bool enable,Interaction type);
        virtual void setInteractionWith(GameObjectGroup *group, bool enable,Interaction type);
        virtual void setInteractionWith(vector<GameObjectGroup*> *groupList, bool enable,Interaction type);

        virtual bool doesInteractWithOther(Interaction type) const;
        virtual const vector<GameObjectGroup*> &getInteractiveObjectsList(Interaction type) const;
        virtual const vector<GameObject*> getInteractiveObjects(Interaction type);


        //virtual void drawObjectTree(PixelDisplay &display);
       // virtual void subscribeToDisplay(PixelDisplay &display);
       // virtual void unsubscribeToDisplay(PixelDisplay &display);
        virtual void setVisibility_objectTree(bool isVisible,Interaction type);
        virtual bool isVisible_objectTree(Interaction type) const;
        /*virtual void draw_chunks(PixelDisplay &display);
        virtual void setVisibility_chunk(const ChunkID &id,bool isVisible);
        virtual void setVisibility_chunks(bool isVisible);
        virtual bool isVisible_chunk(const ChunkID &id) const;
        virtual bool isVisible_chunks() const;
*/


    protected:

        SLOT_DECLARATION(GameObject,moved,const Vector2f &)
        SLOT_DECLARATION(GameObject,rotated,float)

        SLOT_DECLARATION(GameObjectGroup,adding,GameObject*)
        SLOT_DECLARATION(GameObjectGroup,adding,GameObjectGroup*)
        SLOT_DECLARATION(GameObjectGroup,removing,GameObject*)
        SLOT_DECLARATION(GameObjectGroup,removing,GameObjectGroup*)
        SLOT_DECLARATION(GameObjectGroup,willBeCleared)
        SLOT_DECLARATION(GameObjectGroup,cleared)
       /* // GameObject singals:
        virtual void moved(GameObject* sender,const Vector2f &move);
        virtual void rotated(GameObject* sender,const float deltaAngle);

        // Signals from GameObjectGroup
        virtual void adding(GameObjectGroup* sender,GameObject* obj);
        virtual void adding(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void removing(GameObjectGroup* sender,GameObject* obj);
        virtual void removing(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void willBeCleared(GameObjectGroup* sender);
        virtual void cleared(GameObjectGroup* sender);*/

        GameObject *m_gameObject;
        /*ObjectTree   *m_objectTree;
        VertexPathPainter *m_objectTreePainter;

        vector<GameObjectGroup*> m_interactsWithObjectsList;*/
        InteractiveObjects  m_colliderObjects;
        InteractiveObjects  m_detectionObjects;

    private:
        void constructor(const Settings &settings);

};
#endif // INTERACTIVEGAMEOBJECT_H
