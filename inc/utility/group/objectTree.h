#ifndef OBJECTTREE_H
#define OBJECTTREE_H

#include "base.h"
#include "gameobject.h"
#include "pixelDisplay.h"
#include "signalSubscriber.h"

class ObjectTree    :   private ObjSignal
{
    public:
        ObjectTree(const RectF &boundry, unsigned int maxAmount,size_t depth = 0);
        virtual ~ObjectTree();

        virtual bool insert(GameObject *obj);

        virtual void query(const RectF &region,vector<GameObject*> &buffer);
        //void query(RectF &region,std::unordered_map<GameObject*, GameObject*> &buffer);
        virtual void draw(PixelDisplay &display);
        virtual void clear();
        virtual void removeInLeaf(GameObject *obj);
        virtual void removeRecursive(GameObject *obj);


    private:
        void subdivide();


        // Signals from obj's
        virtual void moved(GameObject* sender,const Vector2f &move);
        virtual void rotated(GameObject* sender,const float deltaAngle);


        RectF m_boundry;
        unsigned int m_capacity;
        vector<GameObject*> m_objectList;
        bool m_divided;
        size_t m_depth;


        ObjectTree *TL;
        ObjectTree *TR;
        ObjectTree *BL;
        ObjectTree *BR;
};
#endif // OBJECTTREE_H
