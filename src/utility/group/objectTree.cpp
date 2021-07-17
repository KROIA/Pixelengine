#include "objectTree.h"

ObjectTree::ObjectTree(const Settings &settings)
{
    constructor(settings);
}
ObjectTree::ObjectTree(const RectF &boundry, size_t maxObjects, size_t maxDepth, size_t parentDepth)
{
    Settings s;
    s.boundry       = boundry;
    s.maxDepth      = maxDepth;
    s.maxObjects    = maxObjects;
    s.parentDepth   = parentDepth;
    constructor(s);
}
ObjectTree::ObjectTree(const ObjectTree &other)
{
    this->m_boundry         = other.m_boundry;
    this->m_capacity        = other.m_capacity;
    this->m_objectList      = other.m_objectList;
    this->m_divided         = other.m_divided;
    this->m_disableDivider  = other.m_disableDivider;
    this->m_depth           = other.m_depth;
    this->m_maxDepth        = other.m_maxDepth;

    for(size_t i=0; i<m_objectList.size(); i++)
    {
        m_objectList[i]->subscribe_ObjSignal(this);
    }

    if(m_divided)
    {
        TL = new ObjectTree(*other.TL);
        TR = new ObjectTree(*other.TR);
        BL = new ObjectTree(*other.BL);
        BR = new ObjectTree(*other.BR);
    }
}

void ObjectTree::constructor(const Settings &settings)
{
   // m_painter           = new VertexPathPainter();
   // m_painter->setVisibility(false);
    m_boundry           = settings.boundry;
    m_capacity          = settings.maxObjects;
    m_depth             = settings.parentDepth+1;
    m_maxDepth          = settings.maxDepth;
    m_objectList.reserve(m_capacity);
    m_divided           = false;
    m_disableDivider    = m_depth >= m_maxDepth;

}
ObjectTree::~ObjectTree()
{
    clear();
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
    if(m_objectList.size()  < m_capacity || m_disableDivider)
    {
        obj->subscribe_ObjSignal(this);
        m_objectList.push_back(obj);
        return true;
    }
    else
    {
        if(!m_divided)
            subdivide();
        TL->insert(obj);
        TR->insert(obj);
        BL->insert(obj);
        BR->insert(obj);
        return true;
    }
    return false;
}
void ObjectTree::query(const RectF &region,vector<GameObject*> &buffer)
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
void ObjectTree::getDrawable(vector<VertexPath*> &drawable,const Color &color)
{
    EASY_FUNCTION(profiler::colors::Green500);
    drawable.push_back(m_boundry.getDrawable(color));
    if(m_divided)
    {
        drawable.reserve(drawable.size() + 4);
        TL->getDrawable(drawable,color);
        TR->getDrawable(drawable,color);
        BL->getDrawable(drawable,color);
        BR->getDrawable(drawable,color);
    }
}
/*void ObjectTree::draw(PixelDisplay &display)
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
}*/
void ObjectTree::clear()
{
    EASY_FUNCTION(profiler::colors::Green400);
    for(size_t i=0; i<m_objectList.size(); i++)
    {
        m_objectList[i]->unsubscribe_ObjSignal(this);
    }
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
void ObjectTree::removeInLeaf(GameObject *obj)
{
    for(size_t i=0; i<m_objectList.size(); i++)
    {
        if(m_objectList[i] == obj)
        {
            obj->unsubscribe_ObjSignal(this);
            m_objectList.erase(m_objectList.begin() + i);
            i--;
        }
    }
}
void ObjectTree::removeRecursive(GameObject *obj)
{
    removeInLeaf(obj);
    if(m_divided)
    {
        TL->removeRecursive(obj);
        TR->removeRecursive(obj);
        BL->removeRecursive(obj);
        BR->removeRecursive(obj);
    }
}
/*void ObjectTree::subscribeToDisplay(PixelDisplay &display)
{
    display.subscribePainter(m_painter);
}
void ObjectTree::unsubscribeToDisplay(PixelDisplay &display)
{
    display.unsubscribePainter(m_painter);
}
void ObjectTree::setVisibility(bool isVisible)
{
    m_painter->setVisibility(isVisible);
}
bool ObjectTree::isVisible() const
{
    return m_painter->isVisible();
}*/

void ObjectTree::subdivide()
{
    EASY_FUNCTION(profiler::colors::Green100);
    RectF newRect = m_boundry;
    newRect.setWidth(m_boundry.getSize().x/2.f);
    newRect.setHeight(m_boundry.getSize().y/2.f);
    float offsetPosX = newRect.getSize().x;
    float offsetPosY = newRect.getSize().y;

    TL = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth);
    newRect.setPos(newRect.getPos() + Vector2f(offsetPosX,0));
    TR = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth);
    newRect.setPos(newRect.getPos() + Vector2f(-offsetPosX,offsetPosY));
    BL = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth);
    newRect.setPos(newRect.getPos() + Vector2f(offsetPosX,0));
    BR = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth);
    m_divided = true;
}


void ObjectTree::moved(GameObject* sender,const Vector2f &move)
{
    removeInLeaf(sender);
}
void ObjectTree::rotated(GameObject* sender,const float deltaAngle)
{
    removeInLeaf(sender);
}
