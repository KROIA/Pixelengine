#include "objectTree.h"

ObjectTree::ObjectTree(const Settings &settings)
{
    constructor(settings);
}
ObjectTree::ObjectTree(const RectF &boundry, size_t maxObjects, int maxDepth, int parentDepth)
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
    m_isRoot            = false;

    TL                  = nullptr;
    TR                  = nullptr;
    BL                  = nullptr;
    BR                  = nullptr;
    ROOT                = nullptr;
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
const ObjectTree &ObjectTree::operator=(const ObjectTree &other)
{
    this->m_boundry = other.m_boundry;
    this->m_capacity = other.m_capacity;
    this->m_objectList = other.m_objectList;
    this->m_divided = other.m_divided;
    this->m_disableDivider = other.m_disableDivider;
    this->m_depth = other.m_depth;
    this->m_maxDepth = other.m_maxDepth;

    this->TL = other.TL;
    this->TR = other.TR;
    this->BL = other.BL;
    this->BR = other.BR;

    this->ROOT = other.ROOT;

    this->m_isRoot   = other.m_isRoot;
    return *this;
}
void ObjectTree::setAsRoot(bool isRoot)
{
    m_isRoot = isRoot;
    if(m_isRoot)
        ROOT = this;
    else
        ROOT = nullptr;
}

bool ObjectTree::insert(GameObject *obj)
{
    if(!RectF::intersects_fast(obj->getCollider()->getBoundingBox(),m_boundry))
    {
        if(!m_isRoot)
            return false;
        subdivideReverse(obj);
    }
    if(m_isRoot)
    {
        if(RectF::intersects_inverseOf_fast(obj->getCollider()->getBoundingBox(),m_boundry))
        {
            subdivideReverse(obj);
        }
    }
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    if((m_objectList.size()  < m_capacity && !m_divided) || m_disableDivider)
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
    GAME_OBJECT_FUNCTION(profiler::colors::Green300);
    for(size_t i=0; i<m_objectList.size(); i++)
    {
        if(RectF::intersects_fast(m_objectList[i]->getCollider()->getBoundingBox(),region))
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
    GAME_OBJECT_FUNCTION(profiler::colors::Green500);
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
    GAME_OBJECT_FUNCTION(profiler::colors::Green500);
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
    GAME_OBJECT_FUNCTION(profiler::colors::Green400);
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
void ObjectTree::setRoot(ObjectTree *root)
{
    ROOT = root;
    if(m_divided)
    {
        TL->setRoot(ROOT);
        TR->setRoot(ROOT);
        BL->setRoot(ROOT);
        BR->setRoot(ROOT);
    }
}
void ObjectTree::subdivide()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green100);
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

    TL->ROOT = this->ROOT;
    TR->ROOT = this->ROOT;
    BL->ROOT = this->ROOT;
    BR->ROOT = this->ROOT;

    m_divided = true;
}
void ObjectTree::subdivideReverse(GameObject *obj)
{
    int xQuadrant = 0;
    int yQuadrant = 0;
    if(RectF::isBeneathOf(m_boundry,obj->getCollider()->getBoundingBox()) || RectF::intersectsTopOf(m_boundry,obj->getCollider()->getBoundingBox()))
        yQuadrant--;

    if(RectF::isRightOf(m_boundry,obj->getCollider()->getBoundingBox()) || RectF::intersectsLeftOf(m_boundry,obj->getCollider()->getBoundingBox()))
        xQuadrant--;





    RectF newRect = m_boundry;
    float offsetPosX = newRect.getSize().x;
    float offsetPosY = newRect.getSize().y;
    newRect.setPos(newRect.getPos() + Vector2f(xQuadrant * offsetPosX, yQuadrant * offsetPosY));
    Vector2f newBoundryPos = newRect.getPos();

    ObjectTree *nTL = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth-1);
    newRect.setPos(newRect.getPos() + Vector2f(offsetPosX,0));
    ObjectTree *nTR = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth-1);
    newRect.setPos(newRect.getPos() + Vector2f(-offsetPosX,offsetPosY));
    ObjectTree *nBL = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth-1);
    newRect.setPos(newRect.getPos() + Vector2f(offsetPosX,0));
    ObjectTree *nBR = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth-1);

    m_isRoot = false;
    if(xQuadrant == -1 && yQuadrant == -1)
    {
        *nBR = *this;
    }else if(xQuadrant == 0 && yQuadrant == -1)
    {
        *nBL = *this;
    }else if(xQuadrant == -1 && yQuadrant == 0)
    {
        *nTR = *this;
    }else if(xQuadrant == 0 && yQuadrant == 0)
    {
        *nTL = *this;
    }

    m_boundry.setPos(newBoundryPos);
    m_boundry.setSize(m_boundry.getSize() * 2.f);
    m_divided = true;
    m_depth--;
    m_isRoot = true;
    m_objectList.clear();
    TL = nTL;
    TR = nTR;
    BL = nBL;
    BR = nBR;

    //setRoot(this);

    //this->insert(obj);
}

void ObjectTree::moved(GameObject* sender,const Vector2f &move)
{
    removeInLeaf(sender);
    if(ROOT)
        ROOT->insert(sender);
}
void ObjectTree::rotated(GameObject* sender,const float deltaAngle)
{
    removeInLeaf(sender);
    if(ROOT)
        ROOT->insert(sender);
}
