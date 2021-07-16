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
        virtual void getDrawable(vector<VertexPath*> &drawable,const Color &color = Color(255,255,255));
        //virtual void draw(PixelDisplay &display);
        virtual void clear();
        virtual void removeInLeaf(GameObject *obj);
        virtual void removeRecursive(GameObject *obj);

        /*virtual void subscribeToDisplay(PixelDisplay &display);
        virtual void unsubscribeToDisplay(PixelDisplay &display);
        virtual void setVisibility(bool isVisible);
        virtual bool isVisible() const;*/


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

       // VertexPathPainter *m_painter;
};
#endif // OBJECTTREE_H
