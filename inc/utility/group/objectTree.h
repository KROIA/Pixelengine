#ifndef OBJECTTREE_H
#define OBJECTTREE_H

#include "base.h"
#include "gameobject.h"
#include "pixelDisplay.h"
#include "signalSubscriber.h"

class ObjectTree    :   private ObjSignal
{
    public:
        struct Settings
        {
            RectF boundry;
            size_t maxObjects;
            size_t maxDepth;
            size_t parentDepth;
        };
        static Settings __defaultSettings;
        ObjectTree(const Settings &settings);
        ObjectTree(const RectF &boundry, size_t maxObjects,size_t maxDepth, size_t parentDepth = 0);
        ObjectTree(const ObjectTree &other);
        virtual ~ObjectTree();

        virtual bool insert(GameObject *obj);

        virtual void query(const RectF &region,vector<GameObject*> &buffer);
        virtual void draw(PixelDisplay &display);
        virtual void clear();
        virtual void removeInLeaf(GameObject *obj);
        virtual void removeRecursive(GameObject *obj);


    private:
        void constructor(const Settings &settings);
        void subdivide();


        // Signals from obj's
        virtual void moved(GameObject* sender,const Vector2f &move);
        virtual void rotated(GameObject* sender,const float deltaAngle);


        RectF m_boundry;
        size_t m_capacity;
        vector<GameObject*> m_objectList;
        bool m_divided;
        bool m_disableDivider;
        size_t m_depth;
        size_t m_maxDepth;


        ObjectTree *TL;
        ObjectTree *TR;
        ObjectTree *BL;
        ObjectTree *BR;
};
#endif // OBJECTTREE_H
