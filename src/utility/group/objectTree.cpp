#include "objectTree.h"


ObjectTree::ObjectTree(const RectF &boundry, unsigned int maxAmount,size_t depth)
{
    m_boundry = boundry;
    m_capacity = maxAmount;
    m_objectList.reserve(m_capacity);
    m_divided  = false;
    m_depth = depth+1;
}
ObjectTree::~ObjectTree()
{
    if(!m_divided)
        return;
    delete TL;
    delete TR;
    delete BL;
    delete BR;
}

bool ObjectTree::insert(GameObject *obj)
{
    if(!RectF::intersects_fast(obj->getBoundingBox(),m_boundry))
        return false;
    EASY_FUNCTION(profiler::colors::Green);
    if(m_objectList.size()  < m_capacity)
    {
        m_objectList.push_back(obj);
        return true;
    }
    else
    {
        if(!m_divided)
            subdivide();
        /*if(TL->insert(obj))
            return true;
        if(TR->insert(obj))
            return true;
        if(BL->insert(obj))
            return true;
        if(BR->insert(obj))
            return true;*/
        TL->insert(obj);
        TR->insert(obj);
        BL->insert(obj);
        BR->insert(obj);
        return true;
    }
    return false;
}
void ObjectTree::query(const RectF &region,vector<GameObject*> &buffer)
//void ObjectTree::query(objF &region,std::unordered_map<objF*, objF*> &buffer)
{
    if(!RectF::intersects_fast(region,m_boundry))
        return;
    EASY_FUNCTION(profiler::colors::Green300);
    for(size_t i=0; i<m_objectList.size(); i++)
    {

        if(RectF::intersects_fast(m_objectList[i]->getBoundingBox(),region))
        {
            for(size_t j=0; j<buffer.size(); j++)
            {
                if(buffer[j] == m_objectList[i])
                    goto alreadyExists;
            }
            buffer.push_back(m_objectList[i]);
        }

        alreadyExists:;

        /*if(RectF::intersects_fast(m_objectList[i]->getBoundingBox(),region))
            buffer.insert({m_objectList[i],m_objectList[i]});*/
    }
    if(m_divided)
    {
        TL->query(region,buffer);
        TR->query(region,buffer);
        BL->query(region,buffer);
        BR->query(region,buffer);
    }
}
void ObjectTree::draw(PixelDisplay &display)
{
    EASY_FUNCTION(profiler::colors::Green500);
    display.addVertexLine(m_boundry.getDrawable(Color(255,255,255)));
    if(m_divided)
    {
        TL->draw(display);
        TR->draw(display);
        BL->draw(display);
        BR->draw(display);
    }
}
void ObjectTree::clear()
{
    EASY_FUNCTION(profiler::colors::Green400);
    m_objectList.clear();
    if(m_divided)
    {
        TL->clear();
        TR->clear();
        BL->clear();
        BR->clear();
        delete TL;
        delete TR;
        delete BL;
        delete BR;
        m_divided = false;
    }
}


void ObjectTree::subdivide()
{
    EASY_FUNCTION(profiler::colors::Green100);
    RectF newRect = m_boundry;
    newRect.setWidth(m_boundry.getSize().x/2.f);
    newRect.setHeight(m_boundry.getSize().y/2.f);
    float offsetPos = newRect.getSize().x;

    TL = new ObjectTree(newRect,m_capacity,m_depth);
    newRect.setPos(newRect.getPos() + Vector2f(offsetPos,0));
    TR = new ObjectTree(newRect,m_capacity,m_depth);
    newRect.setPos(newRect.getPos() + Vector2f(-offsetPos,offsetPos));
    BL = new ObjectTree(newRect,m_capacity,m_depth);
    newRect.setPos(newRect.getPos() + Vector2f(offsetPos,0));
    BR = new ObjectTree(newRect,m_capacity,m_depth);
    m_divided = true;
}
