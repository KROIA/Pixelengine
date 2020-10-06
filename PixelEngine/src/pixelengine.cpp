#include "pixelengine.h"

PixelEngine::PixelEngine(const PointU &mapsize,const PointU &displaySize)
{
    //this->addGroup(GameObjectGroup());
    m_mapSize = mapsize;
    m_windowSize = displaySize;
    m_display       = new PixelDisplay(m_windowSize,m_mapSize);
    m_eventTimer    = new Timer;
    m_mainTickTimer = new Timer;
    m_displayTimer  = new Timer;
    this->set_setting_checkEventInterval(0.01);
    this->set_setting_gameTickInterval(0.01);
    this->set_setting_displayInterval(0.01);

    m_p_func_userCheckEventLoop  = nullptr;
    m_p_func_userDisplayLoop     = nullptr;
    m_p_func_userTickLoop        = nullptr;

    m_stats_collisionCheckTimer  = new Timer;
    m_stats_collisionCheckTime   = 0;

    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());
}

PixelEngine::PixelEngine(const PixelEngine &other)
{
    *this->m_display            = *other.m_display;
    this->m_windowSize          = other.m_windowSize;
    this->m_mapSize             = other.m_mapSize;

    *this->m_eventTimer         = *other.m_eventTimer;
    this->m_eventInterval       = other.m_eventInterval;

    *this->m_mainTickTimer      = *other.m_mainTickTimer;
    this->m_mainTickInterval    = other.m_mainTickInterval;

    *this->m_displayTimer       = *other.m_displayTimer;
    this->m_displayInterval     = other.m_displayInterval;

    this->m_mastergameObjectGroup     = other.m_mastergameObjectGroup;
    this->m_mastergameObjectGroup_collisionInteractiveList = other.m_mastergameObjectGroup_collisionInteractiveList;

    this->m_renderLayer         = other.m_renderLayer;

    this->m_userGroups          = other.m_userGroups;

    this->m_p_func_userDisplayLoop = other.m_p_func_userDisplayLoop;
    this->m_p_func_userTickLoop    = other.m_p_func_userTickLoop;
    this->m_p_func_userTickLoop    = other.m_p_func_userTickLoop;

    *this->m_stats_collisionCheckTimer = *other.m_stats_collisionCheckTimer;
    this->m_stats_collisionCheckTime   = other.m_stats_collisionCheckTime;
}

PixelEngine::~PixelEngine()
{
    for(size_t i=0; i<m_userGroups.size(); i++)
    {
        delete m_userGroups[i];
    }
    for(size_t i=0; i<m_mastergameObjectGroup.size(); i++)
    {
        delete m_mastergameObjectGroup[i];
    }
    m_mastergameObjectGroup.clear();

    delete m_display;
    delete m_eventTimer;
    delete m_mainTickTimer;
    delete m_displayTimer;

    delete m_stats_collisionCheckTimer;
}
const PointU &PixelEngine::getWindwoSize() const
{
    return m_windowSize;
}
const PointU &PixelEngine::getMapSize() const
{
    return m_mapSize;
}

// Userloops
void PixelEngine::setUserCheckEventLoop(p_func func)
{
    m_p_func_userCheckEventLoop = func;
}
void PixelEngine::setUserDisplayLoop(p_func func)
{
    m_p_func_userDisplayLoop = func;
}
void PixelEngine::setUserTickLoop(p_func func)
{
    m_p_func_userTickLoop = func;
}
void PixelEngine::checkEvent()
{
    if(!m_eventTimer->start(m_eventInterval))
        return;// Time not finished
    if(m_p_func_userCheckEventLoop != nullptr)
        (*m_p_func_userCheckEventLoop)(m_eventInterval);

    for(size_t i=0; i<m_mastergameObjectGroup.size(); i++)
    {
        m_mastergameObjectGroup[i]->checkEvent();
    }
}
void PixelEngine::tick()
{
    if(!m_mainTickTimer->start(m_mainTickInterval))
        return; // Time not finished
    if(m_p_func_userTickLoop != nullptr)
        (*m_p_func_userTickLoop)(m_mainTickInterval);

    m_stats_collisionCheckTime = 0;
    tickX();
    tickY();
}
void PixelEngine::tickX()
{
    tickXY(Point(1,0));
}
void PixelEngine::tickY()
{
    tickXY(Point(0,1));
}
void PixelEngine::tickXY(const Point &dirLock)
{

    for(size_t i=0; i<m_mastergameObjectGroup.size(); i++)
    {
        m_mastergameObjectGroup[i]->tick(dirLock);

        m_stats_collisionCheckTimer->start(1000);
        m_mastergameObjectGroup[i]->checkCollision(m_mastergameObjectGroup_collisionInteractiveList[i].getVector());
        m_stats_collisionCheckTime += m_stats_collisionCheckTimer->getTime();
        m_stats_collisionCheckTimer->stop();
    }
}

void PixelEngine::display()
{
    if(!m_displayTimer->start(m_displayInterval))
        return;
    if(m_p_func_userDisplayLoop != nullptr)
        (*m_p_func_userDisplayLoop)(m_displayInterval);

    for(size_t i=0; i<m_renderLayer.size(); i++)
    {
        m_renderLayer[i].draw(*m_display);
    }
    /*for(size_t i=0; i<m_mastergameObjectGroup.size(); i++)
    {
        m_mastergameObjectGroup[i]->draw(*m_display);
    }*/

    m_display->display();
    m_display->handleEvents();
}
void PixelEngine::set_setting_checkEventInterval(const double &seconds)
{
    m_eventInterval = abs(seconds);
}
const double &PixelEngine::get_setting_eventHandleInterval() const
{
    return m_eventInterval;
}
void PixelEngine::set_setting_gameTickInterval(const double &seconds)
{
    m_mainTickInterval = abs(seconds);
}
const double  &PixelEngine::get_setting_gameTickInterval() const
{
    return m_mainTickInterval;
}
void PixelEngine::set_setting_displayInterval(const double &seconds)
{
    m_displayInterval = abs(seconds);
}
const double  &PixelEngine::get_setting_displayInterval() const
{
    return m_displayInterval;
}
void PixelEngine::addGameObject(GameObject *obj)
{
    for(size_t i=0; i<m_mastergameObjectGroup.size(); i++)
        if(m_mastergameObjectGroup[i] == obj)
            return; // Group already added to list
    m_mastergameObjectGroup.add(obj);
    m_mastergameObjectGroup_collisionInteractiveList.push_back(GameObjectGroup());
    m_renderLayer[2].add(obj);
}
void PixelEngine::addGameObject(GameObjectGroup *group)
{
    m_mastergameObjectGroup_collisionInteractiveList.reserve(m_mastergameObjectGroup_collisionInteractiveList.size()+group->size());
    for(size_t i=0; i<group->size(); i++)
        this->addGameObject((*group)[i]);
}
void PixelEngine::removeGameObject(GameObject *obj)
{
    // Remove the obj out of the masterList
    for(size_t i=0; i<m_mastergameObjectGroup.size(); i++)
    {
        if(m_mastergameObjectGroup[i] == obj)
        {
            for(size_t j=0; j<m_mastergameObjectGroup.size(); j++)
            {
                this->setCollisionSingleInteraction(m_mastergameObjectGroup[j],obj,false);
            }
            m_mastergameObjectGroup_collisionInteractiveList.erase(m_mastergameObjectGroup_collisionInteractiveList.begin() + i);
            m_mastergameObjectGroup.remove(obj);
            for(size_t j=0; j<m_renderLayer.size(); j++)
                m_renderLayer[j].remove(obj);
       }
    }
    // Remove the obj out of all lists
    for(size_t i=0; i<m_userGroups.size(); i++)
    {
        m_userGroups[i]->remove(obj);
    }
}
void PixelEngine::removeGameObject(GameObjectGroup *group)
{
    for(size_t i=0; i<group->size(); i++)
    {
        this->removeGameObject((*group)[i]);
    }
    /*// Remove the obj out of the masterList
    m_mastergameObjectGroup.remove(group);

    // Remove the obj out of all lists
    for(size_t i=0; i<m_userGroups.size(); i++)
    {
        m_userGroups[i]->remove(group);
    }*/
}
void PixelEngine::deleteGameObject(GameObject *obj)
{
    this->removeGameObject(obj);
    delete obj;
    obj = nullptr;
}
void PixelEngine::deleteGameObject(GameObjectGroup *group)
{
    for(size_t i=0; i<group->size(); i++)
    {
        this->deleteGameObject((*group)[i]);
    }
}
void PixelEngine::setCollisionSingleInteraction(GameObject *obj1,GameObject *obj2, const bool &doesCollide)
{
    if(obj1 == obj2)
        return; // Cann't collide with it self

    GameObject *object1 = nullptr;
    size_t objext1_index;
    GameObject *object2 = nullptr;
    //size_t objext2_index;

    for(size_t x=0; x<m_mastergameObjectGroup.size(); x++)
    {
        if(m_mastergameObjectGroup[x] == obj1)
        {
            object1 = obj1;
            objext1_index = x;
        }else if(m_mastergameObjectGroup[x] == obj2)
        {
            object2 = obj2;
            //objext2_index = x;
        }
    }
    if(object1 != nullptr && object2 != nullptr)
    {
        bool obj2Found = false;
        for(size_t i=0; i<m_mastergameObjectGroup_collisionInteractiveList[objext1_index].size(); i++)
        {
            if(m_mastergameObjectGroup_collisionInteractiveList[objext1_index][i] == object2)
            {
                obj2Found = true;
                if(!doesCollide)
                {
                    // Remove Object2 from the Object1's colliderList
                    // Object1 will no longer collide with Object2
                    m_mastergameObjectGroup_collisionInteractiveList[objext1_index].remove(object2);
                }
            }
        }
        if(!obj2Found && doesCollide)
        {
            // Add Object2 to the Object1's colliderList
            // Object1 will now collide with Object2
            m_mastergameObjectGroup_collisionInteractiveList[objext1_index].add(object2);
        }
/*
        bool obj1Found = false;
        for(size_t i=0; i<m_mastergameObjectGroup_collisionInteractiveList[objext2_index].size(); i++)
        {
            if(m_mastergameObjectGroup_collisionInteractiveList[objext2_index][i] == object1)
            {
                obj2Found = true;
                if(!doesCollide)
                {
                    // Remove Object1 from the Object2's colliderList
                    // Object2 will no longer collide with Object1
                    m_mastergameObjectGroup_collisionInteractiveList[objext2_index].remove(object1);
                }
            }
        }
        if(!obj1Found)
        {
            // Add Object1 to the Object2's colliderList
            // Object2 will now collide with Object1
            m_mastergameObjectGroup_collisionInteractiveList[objext2_index].add(object1);
        }*/
    }
}
void PixelEngine::setCollisionSingleInteraction(GameObject *obj1,GameObjectGroup *obj2List, const bool &doesCollide)
{
   for(size_t i=0; i<obj2List->size(); i++)
       this->setCollisionSingleInteraction(obj1,(*obj2List)[i],doesCollide); // Not very efficient code ;)
}
void PixelEngine::setCollisionSingleInteraction(GameObjectGroup *obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    for(size_t i=0; i<obj1List->size(); i++)
        this->setCollisionSingleInteraction((*obj1List)[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(GameObject *obj1, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
   for(size_t i=0; i<obj2List.size(); i++)
       this->setCollisionSingleInteraction(obj1,obj2List[i],doesCollide); // Not very efficient code ;)
}
void PixelEngine::setCollisionSingleInteraction(GameObjectGroup *obj1List,const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    for(size_t i=0; i<obj1List->size(); i++)
        this->setCollisionSingleInteraction((*obj1List)[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(const vector<GameObject*> &obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    for(size_t i=0; i<obj1List.size(); i++)
        this->setCollisionSingleInteraction(obj1List[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(const vector<GameObject*> &obj1List, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    for(size_t i=0; i<obj1List.size(); i++)
        this->setCollisionSingleInteraction(obj1List[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObject *obj1,GameObject *obj2, const bool &doesCollide)
{
    this->setCollisionSingleInteraction(obj1,obj2, doesCollide);
    this->setCollisionSingleInteraction(obj2,obj1, doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObject *obj1,GameObjectGroup *obj2List, const bool &doesCollide)
{
    for(size_t i=0; i<obj2List->size(); i++)
        this->setCollisionMultiInteraction(obj1,(*obj2List)[i],doesCollide); // Not very efficient code ;)
}
void PixelEngine::setCollisionMultiInteraction(GameObjectGroup *obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    for(size_t i=0; i<obj1List->size(); i++)
        this->setCollisionMultiInteraction((*obj1List)[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObject *obj1, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    for(size_t i=0; i<obj2List.size(); i++)
        this->setCollisionMultiInteraction(obj1,obj2List[i],doesCollide); // Not very efficient code ;)
}
void PixelEngine::setCollisionMultiInteraction(GameObjectGroup *obj1List,const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    for(size_t i=0; i<obj1List->size(); i++)
        this->setCollisionMultiInteraction((*obj1List)[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(const vector<GameObject*> &obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    for(size_t i=0; i<obj1List.size(); i++)
        this->setCollisionMultiInteraction(obj1List[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(const vector<GameObject*> &obj1List, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    for(size_t i=0; i<obj1List.size(); i++)
        this->setCollisionMultiInteraction(obj1List[i],obj2List,doesCollide);
}

// Groups
void PixelEngine::addGroup(GameObjectGroup *group)
{
    for(size_t i=0; i<m_userGroups.size(); i++)
        if(m_userGroups[i] == group)
            return; // Group already added to list
    // Add every Element to the engines main list, if it isn't already in there.
    this->addGameObject(group);

    m_userGroups.push_back(group);
}
void PixelEngine::removeGroup(GameObjectGroup *group)
{
    for(size_t i=0; i<m_userGroups.size(); i++)
        if(m_userGroups[i] == group)
            m_userGroups.erase(m_userGroups.begin() + i);
}
void PixelEngine::deleteGroup(GameObjectGroup *group)
{
    for(size_t i=0; i<m_userGroups.size(); i++)
        if(m_userGroups[i] == group)
        {
            m_userGroups.erase(m_userGroups.begin() + i);
            delete group;
        }
}

// Rendering
void PixelEngine::moveRenderLayer_UP(GameObject *obj)
{
    size_t currentLayer = 0;
    for(size_t i=0; i<m_renderLayer.size(); i++)
    {
        for(size_t j=0; j<m_renderLayer[i].size(); j++)
        {
            if(m_renderLayer[i][j] == obj)
            {
                currentLayer = i;
                m_renderLayer[currentLayer].remove(obj);
                if(m_renderLayer.size() <= currentLayer+1)
                    m_renderLayer.push_back(GameObjectGroup());
                m_renderLayer[currentLayer+1].add(obj);
                return;
            }
        }
    }
}
void PixelEngine::moveRenderLayer_DOWN(GameObject *obj)
{
    size_t currentLayer = 0;
    for(size_t i=0; i<m_renderLayer.size(); i++)
    {
        for(size_t j=0; j<m_renderLayer[i].size(); j++)
        {
            if(m_renderLayer[i][j] == obj)
            {
                currentLayer = i;
                if(currentLayer > 0)
                {
                    m_renderLayer[currentLayer].remove(obj);
                    m_renderLayer[currentLayer-1].add(obj);
                }
                return;
            }
        }
    }
}
void PixelEngine::setRenderLayer_BOTTOM(GameObject *obj)
{
    size_t currentLayer = 0;
    for(size_t i=0; i<m_renderLayer.size(); i++)
    {
        for(size_t j=0; j<m_renderLayer[i].size(); j++)
        {
            if(m_renderLayer[i][j] == obj)
            {
                currentLayer = i;
                if(currentLayer > 0)
                {
                    m_renderLayer[currentLayer].remove(obj);
                    m_renderLayer[0].add(obj);
                }
                return;
            }
        }
    }
}
void PixelEngine::setRenderLayer_TOP(GameObject *obj)
{
    size_t currentLayer = 0;
    for(size_t i=0; i<m_renderLayer.size(); i++)
    {
        for(size_t j=0; j<m_renderLayer[i].size(); j++)
        {
            if(m_renderLayer[i][j] == obj)
            {
                currentLayer = i;
                 if(m_renderLayer.size()-1 > currentLayer)
                {
                    m_renderLayer[currentLayer].remove(obj);
                    m_renderLayer[m_renderLayer.size()-1].add(obj);
                }
                return;
            }
        }
    }
}

// General functions
double PixelEngine::random(double min, double max)
{
    if(min == max)
    {
        return min;
    }
    if(min > max)
    {   double buf=min;
        min = max;
        max = buf;
    }

    // Generating a timedependend seed
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    int seed = now->tm_year + now->tm_mon + now->tm_mday + now->tm_hour + now->tm_min + now->tm_sec;
    return double((min*1000.0)+((seed*rand())%(int)((max-min)*1000.0)))/1000.0;
}
bool   PixelEngine::loadFromImage(const std::string &picture,Collider *collider,Painter *painter)
{
    Image image;
    if(!image.loadFromFile(picture))
        return false;

    sf::Vector2u size = image.getSize();
    Point middleOffset(-signed(size.x)/2,-signed(size.y)/2);

    collider->clear();
    painter->clear();
    for(unsigned int x=0; x<size.x; x++)
    {
        for(unsigned int y=0; y<size.y; y++)
        {
            Color color = image.getPixel(x,y);
            if(color.a != 0 && !(color.r == 255 && color.g == 255 && color.b == 255))
            {
                collider->addHitBox(Rect(middleOffset.getX()+x,middleOffset.getY()+y,1,1));
                painter->addPixel(Pixel(Point(middleOffset.getX()+x,middleOffset.getY()+y),color));
            }
        }
    }
    return true;
}
// Stats
const double &PixelEngine::get_stats_checkCollisionTime() const
{
    return m_stats_collisionCheckTime;
}
