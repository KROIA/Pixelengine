#include "pixelengine.h"

PixelEngine::PixelEngine(const PointU &mapsize,const PointU &displaySize)
{
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

    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());

    m_statistics.framesPerSecond        = 0;
    m_statistics.ticksPerSecond         = 0;
    m_statistics.collisionsPerTick      = 0;
    m_statistics.collisionChecksPerTick = 0;
    m_statistics.objectsInEngine        = 0;
    m_statistics.collisionCheckTime     = 0;
    m_statistics.gameObjectTickTime     = 0;
    m_statistics.checkEventTime         = 0;
    m_statistics.tickTime               = 0;
    m_statistics.displayTime            = 0;
    m_statistics.checkUserEventTime     = 0;
    m_statistics.userTickTime           = 0;
    m_statistics.userDisplayTime        = 0;
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

    this->m_statistics             = other.m_statistics;
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
#ifdef STATISTICS
    auto stats_checkUserEvent_timer_start = std::chrono::system_clock::now();
#endif
    if(m_p_func_userCheckEventLoop != nullptr)
        (*m_p_func_userCheckEventLoop)(m_eventInterval,m_tick);
#ifdef STATISTICS
    auto stats_checkEvent_timer_start = std::chrono::system_clock::now();
    std::chrono::duration<double> time_span_checkUserEvent_time = stats_checkEvent_timer_start - stats_checkUserEvent_timer_start;
    m_statistics.checkUserEventTime = time_span_checkUserEvent_time.count();
#endif
    for(size_t i=0; i<m_mastergameObjectGroup.size(); i++)
    {
        m_mastergameObjectGroup[i]->checkEvent();
    }
#ifdef STATISTICS
    auto stats_checkEvent_timer_end = std::chrono::system_clock::now();
    std::chrono::duration<double> time_span_checkEvent_time = stats_checkEvent_timer_end - stats_checkEvent_timer_start;
    m_statistics.checkEventTime = time_span_checkEvent_time.count();
#endif
}
void PixelEngine::tick()
{
    if(!m_mainTickTimer->start(m_mainTickInterval))
        return; // Time not finished
    m_tick++;

#ifdef STATISTICS
    m_statistics.objectsInEngine = m_mastergameObjectGroup.size();
    auto stats_userTick_timer_start = std::chrono::system_clock::now();
#endif
    if(m_p_func_userTickLoop != nullptr)
        (*m_p_func_userTickLoop)(m_mainTickInterval,m_tick);
#ifdef STATISTICS
    m_statistics.collisionsPerTick      = 0;
    m_statistics.collisionChecksPerTick = 0;
    m_statistics.gameObjectTickTime     = 0;
    m_statistics.collisionCheckTime     = 0;
    auto stats_tick_timer_start = std::chrono::system_clock::now();
    std::chrono::duration<double> time_span_userEventEvent_time = stats_tick_timer_start - stats_userTick_timer_start;
    m_statistics.userTickTime = time_span_userEventEvent_time.count();
#endif

    tickX();
    tickY();

#ifdef STATISTICS
    m_stats_tps_timer_end = std::chrono::system_clock::now();
    std::chrono::duration<double> time_span_tick_time = m_stats_tps_timer_end - stats_tick_timer_start;
    m_statistics.tickTime = time_span_tick_time.count();

    std::chrono::duration<double> time_span = m_stats_tps_timer_end - m_stats_tps_timer_start;
    m_stats_tps_timer_start = std::chrono::system_clock::now();
    if(time_span.count() != 0.f)
        m_statistics.ticksPerSecond = 1.f/time_span.count();
#endif
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
#ifdef STATISTICS
        m_statistics.collisionChecksPerTick += m_mastergameObjectGroup_collisionInteractiveList[i].size();
        auto stats_timer_start = std::chrono::system_clock::now();

#endif
        m_mastergameObjectGroup[i]->tick(dirLock);

#ifdef STATISTICS
        auto stats_timer_end = std::chrono::system_clock::now();
        std::chrono::duration<double> stats_time_span = stats_timer_end - stats_timer_start;
        m_statistics.gameObjectTickTime += stats_time_span.count();
        stats_timer_start = std::chrono::system_clock::now();
#endif
        m_statistics.collisionsPerTick += m_mastergameObjectGroup[i]->checkCollision(m_mastergameObjectGroup_collisionInteractiveList[i].getVector());
#ifdef STATISTICS
        stats_timer_end = std::chrono::system_clock::now();
        stats_time_span = stats_timer_end - stats_timer_start;
        m_statistics.collisionCheckTime += stats_time_span.count();
#endif
    }

}

void PixelEngine::removeObjectFromList(GameObjectGroup &group,GameObject* obj)
{
    group.remove(obj);
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup> &list,GameObject* obj)
{
    for(size_t i=0; i<list.size(); i++)
    {
        list[i].remove(obj);
    }
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup> &list,GameObjectGroup *obj)
{
    for(size_t i=0; i<(*obj).size(); i++)
    {
        PixelEngine::removeObjectFromList(list,(*obj)[i]);
    }
}
void PixelEngine::removeObjectFromList(GameObjectGroup* &Group,GameObject* obj)
{
    Group->remove(obj);
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup*> &list,GameObject* obj)
{
    for(size_t i=0; i<list.size(); i++)
    {
        list[i]->remove(obj);
    }
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup*> &list,GameObjectGroup *obj)
{
    for(size_t i=0; i<(*obj).size(); i++)
    {
        PixelEngine::removeObjectFromList(list,(*obj)[i]);
    }
}

void PixelEngine::display()
{
    if(!m_displayTimer->start(m_displayInterval))
        return;

#ifdef STATISTICS
    auto stats_userDisplay_timer_start = std::chrono::system_clock::now();
#endif
    if(m_p_func_userDisplayLoop != nullptr)
        (*m_p_func_userDisplayLoop)(m_displayInterval,m_tick);
#ifdef STATISTICS
    auto stats_display_timer_start = std::chrono::system_clock::now();
    std::chrono::duration<double> time_span_userDisplay_time = stats_display_timer_start - stats_userDisplay_timer_start;
    m_statistics.userDisplayTime = time_span_userDisplay_time.count();
#endif

    for(size_t i=0; i<m_renderLayer.size(); i++)
    {
        m_renderLayer[i].draw(*m_display);
    }

    m_display->display();
    m_display->handleEvents();
#ifdef STATISTICS
    m_stats_fps_timer_end = std::chrono::system_clock::now();
    std::chrono::duration<double> m_time_span_display_time = m_stats_fps_timer_end - stats_display_timer_start;
    m_statistics.displayTime = m_time_span_display_time.count();

    std::chrono::duration<double> time_span = m_stats_fps_timer_end - m_stats_fps_timer_start;
    m_stats_fps_timer_start = std::chrono::system_clock::now();
    if(time_span.count() != 0.f)
        m_statistics.framesPerSecond = 1.f/time_span.count();

#endif
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

    if(!obj->isBoundingBoxUpdated())
        obj->updateBoundingBox();
    obj->setEventHandler(this);
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
            this->removeObjectFromList(m_mastergameObjectGroup,obj);
            this->removeObjectFromList(m_renderLayer,obj);
       }
    }
    // Remove the obj out of all lists
    this->removeObjectFromList(m_userGroups,obj);
    obj->setEventHandler(nullptr);
}
void PixelEngine::removeGameObject(GameObjectGroup *group)
{
    for(size_t i=0; i<group->size(); i++)
    {
        this->removeGameObject((*group)[i]);
    }
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

    for(size_t x=0; x<m_mastergameObjectGroup.size(); x++)
    {
        if(m_mastergameObjectGroup[x] == obj1)
        {
            object1 = obj1;
            objext1_index = x;
        }else if(m_mastergameObjectGroup[x] == obj2)
        {
            object2 = obj2;
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
void PixelEngine::moveRenderLayer_UP(GameObjectGroup *objGroup)
{
    for(size_t i=0; i<objGroup->size(); i++)
        this->moveRenderLayer_UP((*objGroup)[i]);
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
void PixelEngine::moveRenderLayer_DOWN(GameObjectGroup *objGroup)
{
    for(size_t i=0; i<objGroup->size(); i++)
        this->moveRenderLayer_DOWN((*objGroup)[i]);
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
void PixelEngine::setRenderLayer_BOTTOM(GameObjectGroup *objGroup)
{
    for(size_t i=0; i<objGroup->size(); i++)
        this->setRenderLayer_BOTTOM((*objGroup)[i]);
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
void PixelEngine::setRenderLayer_TOP(GameObjectGroup *objGroup)
{
    for(size_t i=0; i<objGroup->size(); i++)
        this->setRenderLayer_TOP((*objGroup)[i]);
}

// GameObject Events from GameObjectEventHandler
void PixelEngine::kill(GameObject *obj)
{

}
void PixelEngine::removeFromEngine(GameObject *obj)
{
    this->removeGameObject(obj);
}
void PixelEngine::deleteObject(GameObject *obj)
{
    this->deleteGameObject(obj);
}
void PixelEngine::collisionOccured(GameObject *obj1,GameObject *obj2)
{
   // qDebug() << "collision"<<obj1<<"\t"<<obj2;
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
bool   PixelEngine::loadFromImage(const std::string &picture, Collider *collider, Painter *painter, const ImageOrigin &origin)
{
    Image image;
    if(!image.loadFromFile(picture))
    {
        #ifdef IMAGE_IMPORT_DEBUG
        qDebug() << "Can't load File: \""<<picture.c_str()<<"\"";
        #endif
        return false;
    }
#ifdef IMAGE_IMPORT_DEBUG
    qDebug() << "import image: \""<<picture.c_str()<<"\"";
    Timer dbgTimer;
#endif
    Point originPoint;
    switch(origin)
    {
        case ImageOrigin::topRightCorner:
            originPoint.set(image.getSize().x,0);
        break;
        case ImageOrigin::bottomLeftCorner:
            originPoint.set(0,image.getSize().y);
        break;
        case ImageOrigin::bottomRightCorner:
            originPoint.set(image.getSize().x,image.getSize().y);
        break;
        case ImageOrigin::center:
            originPoint.set(image.getSize().x/2,image.getSize().y/2);
        break;
        case ImageOrigin::topLeftCorner:
        default:
             originPoint.set(0,0);
    }
    return PixelEngine::loadFromImage(picture,collider,painter,originPoint);
}
bool   PixelEngine::loadFromImage(const std::string &picture, Collider *collider, Painter *painter, const Point &origin)
{
    Image image;
    if(!image.loadFromFile(picture))
    {
        #ifdef IMAGE_IMPORT_DEBUG
        qDebug() << "Can't load File: \""<<picture.c_str()<<"\"";
        #endif
        return false;
    }
#ifdef IMAGE_IMPORT_DEBUG
    qDebug() << "import image: \""<<picture.c_str()<<"\"";
    Timer dbgTimer;
#endif
    Timer timer;        // only for stats
    timer.start(1000);  // only for stats
    sf::Vector2u size = image.getSize();

    double progress = 0;
    double maxProgress = size.x * size.y;

    // Reserve the maximum amount of possible pixels
    painter->reserve(size.x * size.y);

    Color color;
    Rect rect;
    rect.setSize(1,1);
    Pixel pixel;
#ifdef IMAGE_IMPORT_DEBUG
    qDebug() << "Imagesize x="<<size.x<<"\ty="<<size.y;
#endif

    // Each pixel in the image is set to Rect with the size of width=1 height=1
    // The list is converted into fewer rects
    vector<Rect> rawRectList;

    // Loop through all Pixels in x-direction
    for(unsigned int x=0; x<size.x; x++)
    {
        // Loop through all Pixels in y-direction
        for(unsigned int y=0; y<size.y; y++)
        {
#ifdef IMAGE_IMPORT_DEBUG
            if(dbgTimer.start(0.01))
                qDebug() << "[\t"<<100.f*progress/maxProgress<<"%\t]";
#endif
            // Get the color of the current pixel
            color = image.getPixel(x,y);

            // Only treat pixels that are not completely invisible (alpha == 0)
            // And only treat pixels that are not white -> So you can use white instead of adding an alpha channel
#ifdef IMAGE_IMPORT_ALPHA_WHITE
            if(color.a != 0 &&
                    !(color.r >= __color_minimalAlphaColor.r &&
                      color.g >= __color_minimalAlphaColor.g &&
                      color.b >= __color_minimalAlphaColor.b))
#else
            if(color.a != 0)
#endif
            {

                pixel.setPos(x-origin.getX(),y-origin.getY());
                rect.setPos(x,y);
                pixel.setColor(color);

                painter->addPixel(pixel);
                rawRectList.push_back(rect);
            }
            progress += 1;
        }
    }
    // This is the new Collider-RectList
    // This list will contain optimized colliders for this picture
    vector<Rect> colliderRects;

    // Converts many small Rect's to a few large ones
    PixelEngine::optimize_Hitboxes(rawRectList,colliderRects,origin);

    collider->addHitbox(colliderRects);
    collider->updateBoundingBox();
#ifdef IMAGE_IMPORT_DEBUG
    qDebug() << "[\t"<<100.f*progress/maxProgress<<"%\t]";
    qDebug() << "import image done. Time: "<<timer.getTime();
    qDebug() << "Pixels:       "<<painter->getPixelAmount();
    qDebug() << "Hitboxamount: "<<collider->getHitboxAmount();
#endif
    return true;
}
void PixelEngine::optimize_Hitboxes(vector<Rect> &input,vector<Rect> &outputColliderList,const Point origin)
{
    size_t width = 0;
    size_t height = 0;

    vector<vector<Rect*>    > map;
    for(size_t i=0; i<input.size(); i++)
    {
        if(width < static_cast<size_t>(input[i].getX()+origin.getX()))
            width = static_cast<size_t>(input[i].getX()+origin.getX());
        if(height < static_cast<size_t>(input[i].getY()+origin.getY()))
            height = static_cast<size_t>(input[i].getY()+origin.getY());
    }
    width++;
    height++;
    map.reserve(width);
    for(size_t x=0; x<width; x++)
    {
        map.push_back(vector<Rect*>());
        map[x].reserve(height);

        for(size_t y=0; y<height; y++)
        {
            map[x].push_back(nullptr);
        }
    }
    for(size_t i=0; i<input.size(); i++)
    {
         map[input[i].getX()][input[i].getY()] = new Rect();
        *map[input[i].getX()][input[i].getY()] = input[i];
    }
    PixelEngine::optimize_HitboxMap(map,outputColliderList);
    for(size_t i=0; i<outputColliderList.size(); i++)
    {
        outputColliderList[i].setPos(outputColliderList[i].getX()-origin.getX(),
                                     outputColliderList[i].getY()-origin.getY());
    }
    for(size_t x=0; x<width; x++)
    {
        for(size_t y=0; y<height; y++)
        {
            delete map[x][y];
        }
    }
}
void PixelEngine::optimize_HitboxMap(vector<vector<Rect*>  > &map,vector<Rect> &outputColliderList)
{
    if(map.size() == 0)
        return;
    if(map[0].size() == 0)
        return;
    outputColliderList.clear();
    size_t width    = map.size();
    size_t height   = map[0].size();

    for(size_t y=0; y<height; y++)
    {
        for(size_t x=0; x<width; x++)
        {
            if(map[x][y] == nullptr)
                continue;
            bool endXloop = false;
            size_t xIterator = 1;
            unsigned int colliderWidth = map[x][y]->getSize().getX();
            vector<Rect**> toDeleteList;
            while(!endXloop)
            {
                if(x+xIterator >= width)
                {
                    endXloop = true;
                    continue;
                }
                if(map[x+xIterator][y] == nullptr)
                {
                    endXloop = true;
                    continue;
                }
                colliderWidth += map[x+xIterator][y]->getSize().getX();
                toDeleteList.push_back(&map[x+xIterator][y]);
                xIterator++;
            }
            for(size_t i=0; i<toDeleteList.size(); i++)
            {
                delete *toDeleteList[i];
                *toDeleteList[i] = nullptr;
            }
            map[x][y]->setSize(colliderWidth,map[x][y]->getSize().getY());
            outputColliderList.push_back(Rect(*map[x][y]));
            x+=xIterator-1;
        }
    }
}

const unsigned long long &PixelEngine::getTick() const
{
    return m_tick;
}
void PixelEngine::resetTick()
{
    m_tick = 0;
}
// Stats
const PixelEngine::Statistics &PixelEngine::get_statistics() const
{
    return m_statistics;
}


void PixelEngine::resetStatistics()
{
    m_statistics.collisionChecksPerTick = 0;
    m_statistics.collisionsPerTick      = 0;
}
