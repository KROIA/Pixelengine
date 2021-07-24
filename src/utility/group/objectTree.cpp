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
        //m_objectList[i]->subscribe_ObjSignal(this);
        SIGNAL_SUBSCRIBE(GameObject,m_objectList[i])
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

    PARENT              = nullptr;
    GRANDPARENT         = nullptr;

    m_color = Color((rand()%155)+100,(rand()%155)+100,(rand()%155)+100);
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

    /*if(m_divided)
    {
        this->TL->PARENT = this;
        this->TR->PARENT = this;
        this->BL->PARENT = this;
        this->BR->PARENT = this;

        this->TL->GRANDPARENT = other.PARENT;
        this->TR->GRANDPARENT = other.PARENT;
        this->BL->GRANDPARENT = other.PARENT;
        this->BR->GRANDPARENT = other.PARENT;
    }*/

    this->m_isRoot   = other.m_isRoot;
    return *this;
}
void ObjectTree::setAsRoot(bool isRoot)
{
    m_isRoot = isRoot;
    if(m_isRoot)
    {
        ROOT = this;
        PARENT = this;
        GRANDPARENT = this;
    }
    else
        ROOT = nullptr;
}

bool ObjectTree::insert(GameObject *obj)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    //qDebug() << "insert";
    if(!RectF::intersects_fast(obj->getCollider()->getBoundingBox(),m_boundry))
    {
        if(!m_isRoot)
            return false;
        subdivideReverse(obj);
        return this->insert(obj);
    }
    if(m_isRoot)
    {
        if(RectF::intersects_inverseOf_fast(obj->getCollider()->getBoundingBox(),m_boundry))
        {
            subdivideReverse(obj);
        }
    }


    if((m_objectList.size()  < m_capacity && !m_divided) || m_disableDivider)
    {
        //obj->subscribe_ObjSignal(this);
        SIGNAL_SUBSCRIBE(GameObject,obj)
        m_objectList.push_back(obj);
        return true;
    }
    else
    {
        bool ret = false;
        if(!m_divided)
            subdivide();
        ret |= TL->insert(obj);
        ret |= TR->insert(obj);
        ret |= BL->insert(obj);
        ret |= BR->insert(obj);
        //if(m_isRoot && ret)
        //    obj->subscribe_ObjSignal(this);
        return ret;
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

/*
        drawable.reserve(drawable.size()+m_objectList.size());
        for(size_t i=0; i<m_objectList.size();i++)
        {
            drawable.push_back(m_objectList[i]->getCollider()->getBoundingBox().getDrawable(m_color));
        }

*/
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
        //m_objectList[i]->unsubscribe_ObjSignal(this);
        SIGNAL_UNSUBSCRIBE(GameObject,m_objectList[i])
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
bool ObjectTree::removeInLeaf(GameObject *obj)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green800);
    bool ret = false;
    for(size_t i=0; i<m_objectList.size(); i++)
    {
        if(m_objectList[i] == obj)
        {
            //obj->unsubscribe_ObjSignal(this);
            SIGNAL_UNSUBSCRIBE(GameObject,obj)
            m_objectList.erase(m_objectList.begin() + i);
            i--;
            ret = true;
        }
    }
    return ret;
}
bool ObjectTree::removeRecursive(GameObject *obj)
{
    bool ret = removeInLeaf(obj);
    if(m_divided)
    {
        ret |= TL->removeRecursive(obj);
        ret |= TR->removeRecursive(obj);
        ret |= BL->removeRecursive(obj);
        ret |= BR->removeRecursive(obj);
    }
    return ret;
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
    GRANDPARENT = this;
    PARENT = this;
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

    TL->PARENT = this;
    TR->PARENT = this;
    BL->PARENT = this;
    BR->PARENT = this;

    TL->GRANDPARENT = this->PARENT;
    TR->GRANDPARENT = this->PARENT;
    BL->GRANDPARENT = this->PARENT;
    BR->GRANDPARENT = this->PARENT;

    m_divided = true;
}
void ObjectTree::subdivideReverse(GameObject *obj)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green100);
  //  qDebug() << "subdivide reverse, new depth: "<<m_depth-1;
  //  qDebug() << "old boudry: " << m_boundry.getPos().x << " "<<m_boundry.getPos().y << " size: "<<m_boundry.getSize().x<<" "<<m_boundry.getSize().y;
    int xQuadrant = 0;
    int yQuadrant = 0;

    RectF objBox = obj->getCollider()->getBoundingBox();

    if(objBox.isLeftOf(m_boundry)  || objBox.intersectsLeftOf(m_boundry))
    {
        xQuadrant++;
    }
    if(objBox.isOnTopOf(m_boundry) || objBox.intersectsTopOf(m_boundry))
    {
        yQuadrant++;
    }
  //  qDebug() << "quadrant: "<<xQuadrant << " "<<yQuadrant;
/*
    if(RectF::isBeneathOf(m_boundry,obj->getCollider()->getBoundingBox()) || RectF::intersectsTopOf(m_boundry,obj->getCollider()->getBoundingBox()))
        yQuadrant--;

    if(RectF::isRightOf(m_boundry,obj->getCollider()->getBoundingBox()) || RectF::intersectsLeftOf(m_boundry,obj->getCollider()->getBoundingBox()))
        xQuadrant--;
*/




    RectF newRect = m_boundry;
    float offsetPosX = newRect.getSize().x;
    float offsetPosY = newRect.getSize().y;
    newRect.setPos(newRect.getPos() - Vector2f(xQuadrant * offsetPosX, yQuadrant * offsetPosY));
    Vector2f newBoundryPos = newRect.getPos();
  //  qDebug() << "new boudry: " << newBoundryPos.x << " "<<newBoundryPos.y << " size: "<<m_boundry.getSize().x*2<<" "<<m_boundry.getSize().y*2;


    ObjectTree *nTL = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth-1);
    newRect.setPos(newRect.getPos() + Vector2f(offsetPosX,0));
    ObjectTree *nTR = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth-1);
    newRect.setPos(newRect.getPos() + Vector2f(-offsetPosX,offsetPosY));
    ObjectTree *nBL = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth-1);
    newRect.setPos(newRect.getPos() + Vector2f(offsetPosX,0));
    ObjectTree *nBR = new ObjectTree(newRect,m_capacity,m_maxDepth,m_depth-1);

    m_isRoot = false;
    if(xQuadrant == 0 && yQuadrant == 0)
    {
        *nTL = *this;
    }else if(xQuadrant == 1 && yQuadrant == 0)
    {
        *nTR = *this;
    }else if(xQuadrant == 0 && yQuadrant == 1)
    {
        *nBL = *this;
    }else if(xQuadrant == 1 && yQuadrant == 1)
    {
        *nBR = *this;
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

    TL->ROOT = ROOT;
    TR->ROOT = ROOT;
    BL->ROOT = ROOT;
    BR->ROOT = ROOT;

    TL->PARENT = this;
    TR->PARENT = this;
    BL->PARENT = this;
    BR->PARENT = this;

    TL->GRANDPARENT = this->PARENT;
    TR->GRANDPARENT = this->PARENT;
    BL->GRANDPARENT = this->PARENT;
    BR->GRANDPARENT = this->PARENT;

    //setRoot(this);


}
SLOT_DEFINITION(ObjectTree,GameObject,moved,const Vector2f &move)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green600);
    if(!RectF::intersects_fast(sender->getCollider()->getBoundingBox(),m_boundry))
    {
        bool removed;
        if(PARENT)
            removed = PARENT->removeRecursive(sender);
        else
            removed = this->removeInLeaf(sender);
        //sender->unsubscribe_ObjSignal(this);
        //removeInLeaf(sender);
        if(removed)
        {
            bool inserted = false;
            if(GRANDPARENT)
                inserted = GRANDPARENT->insert(sender);
            if(ROOT && !inserted)
                ROOT->insert(sender);
        }
    }
}
SLOT_DEFINITION(ObjectTree,GameObject,rotated,float deltaAngle)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green600);
    /*sender->unsubscribe_ObjSignal(this);
    removeInLeaf(sender);
    if(m_isRoot)
        this->insert(sender);*/
    if(!RectF::intersects_fast(sender->getCollider()->getBoundingBox(),m_boundry))
    {
        bool removed;
        if(PARENT)
            removed = PARENT->removeRecursive(sender);
        else
            removed = this->removeInLeaf(sender);
        //sender->unsubscribe_ObjSignal(this);
        //removeInLeaf(sender);
        if(removed)
        {
            if(GRANDPARENT)
                GRANDPARENT->insert(sender);
            else if(ROOT)
                ROOT->insert(sender);
        }
    }
}
/*void ObjectTree::moved(GameObject* sender,const Vector2f &move)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green600);
    if(!RectF::intersects_fast(sender->getCollider()->getBoundingBox(),m_boundry))
    {
        bool removed;
        if(PARENT)
            removed = PARENT->removeRecursive(sender);
        else
            removed = this->removeInLeaf(sender);
        //sender->unsubscribe_ObjSignal(this);
        //removeInLeaf(sender);
        if(removed)
        {
            bool inserted = false;
            if(GRANDPARENT)
                inserted = GRANDPARENT->insert(sender);
            if(ROOT && !inserted)
                ROOT->insert(sender);
        }
    }
}
void ObjectTree::rotated(GameObject* sender,const float deltaAngle)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green600);
    if(!RectF::intersects_fast(sender->getCollider()->getBoundingBox(),m_boundry))
    {
        bool removed;
        if(PARENT)
            removed = PARENT->removeRecursive(sender);
        else
            removed = this->removeInLeaf(sender);
        //sender->unsubscribe_ObjSignal(this);
        //removeInLeaf(sender);
        if(removed)
        {
            if(GRANDPARENT)
                GRANDPARENT->insert(sender);
            else if(ROOT)
                ROOT->insert(sender);
        }
    }
}*/
