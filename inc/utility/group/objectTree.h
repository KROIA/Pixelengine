#ifndef OBJECTTREE_H
#define OBJECTTREE_H

#include "base.h"
#include "gameobject.h"
#include "pixelDisplay.h"
#include "signalSubscriber.h"
#include "drawUtilities.h"
//#include "vertexPathPainter.h"

class ObjectTree    :   private ObjSignal
{
    public:
        struct Settings
        {
            RectF boundry;
            size_t maxObjects;
            int maxDepth;
            int parentDepth;
        };
        static Settings __defaultSettings;
        ObjectTree(const Settings &settings);
        ObjectTree(const RectF &boundry, size_t maxObjects,int maxDepth, int parentDepth = 0);
        ObjectTree(const ObjectTree &other);
        virtual ~ObjectTree();
        const ObjectTree &operator=(const ObjectTree &other);

        virtual void setAsRoot(bool isRoot);

        virtual bool insert(GameObject *obj);
        virtual void query(const RectF &region,vector<GameObject*> &buffer);
        virtual void getDrawable(vector<VertexPath*> &drawable,const Color &color = Color(255,255,255));
        //virtual void draw(PixelDisplay &display);
        virtual void clear();
        virtual bool removeInLeaf(GameObject *obj);
        virtual bool removeRecursive(GameObject *obj);

        /*virtual void subscribeToDisplay(PixelDisplay &display);
        virtual void unsubscribeToDisplay(PixelDisplay &display);
        virtual void setVisibility(bool isVisible);
        virtual bool isVisible() const;*/


    private:
        void setRoot(ObjectTree *root);
        void constructor(const Settings &settings);
        void subdivide();
        void subdivideReverse(GameObject *obj);


        // Signals from obj's
        virtual void moved(GameObject* sender,const Vector2f &move);
        virtual void rotated(GameObject* sender,const float deltaAngle);


        RectF m_boundry;
        size_t m_capacity;
        vector<GameObject*> m_objectList;
        bool m_divided;
        bool m_disableDivider;
        int m_depth;
        int m_maxDepth;


        ObjectTree *TL;
        ObjectTree *TR;
        ObjectTree *BL;
        ObjectTree *BR;

        ObjectTree *ROOT;
        ObjectTree *PARENT;
        ObjectTree *GRANDPARENT;

        bool m_isRoot;

       // VertexPathPainter *m_painter;
};
#endif // OBJECTTREE_H
