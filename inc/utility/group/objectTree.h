#ifndef OBJECTTREE_H
#define OBJECTTREE_H

#include "base.h"
#include "gameobject.h"
#include "pixelDisplay.h"

class ObjectTree
{
    public:
        ObjectTree(const RectF &boundry, unsigned int maxAmount,size_t depth = 0);
        ~ObjectTree();

        bool insert(GameObject *obj);

        void query(const RectF &region,vector<GameObject*> &buffer);
        //void query(RectF &region,std::unordered_map<GameObject*, GameObject*> &buffer);
        void draw(PixelDisplay &display);
        void clear();


    private:
        void subdivide();


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
