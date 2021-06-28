#include "pixelengine.h"

PixelEngine::PixelEngine(const Vector2u  &mapsize,const Vector2u  &displaySize)
    :   GameObjectEventHandler()//, GroupManagerInterface()
{
    m_mapSize = mapsize;
    m_windowSize = displaySize;
    m_display       = new PixelDisplay(m_windowSize,m_mapSize);
    m_engineIsRunning = true;
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
    m_statsFilterFactor                 = 0.5;

    //m_display->loadFontFromFile("C:\\Windows\\Fonts\\consolab.ttf");
    m_stats_text = new DisplayText();
    //m_stats_text->setVisibility(false);
    //m_stats_text->setString("");
    m_stats_text->setCharacterSize(m_windowSize.x/80); // in pixels, not points!
    sf::Color col(255,255,255,100); // Transparent white
    display_stats(false,col);
    m_stats_text->setPos(Vector2f(5,5));

    m_display->addText(m_stats_text);
    resetTick();
}

PixelEngine::PixelEngine(const PixelEngine &other)
    :   GameObjectEventHandler(other)//, GroupManagerInterface(other)
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

    this->m_masterGameObjectGroup     = other.m_masterGameObjectGroup;
    //this->m_masterGameObjectGroup_collisionInteractiveList = other.m_masterGameObjectGroup_collisionInteractiveList;

    this->m_renderLayer         = other.m_renderLayer;

    this->m_userGroups          = other.m_userGroups;

    this->m_p_func_userDisplayLoop = other.m_p_func_userDisplayLoop;
    this->m_p_func_userTickLoop    = other.m_p_func_userTickLoop;
    this->m_p_func_userTickLoop    = other.m_p_func_userTickLoop;

    this->m_statistics             = other.m_statistics;
    this->m_statsFilterFactor      = other.m_statsFilterFactor;

    this->m_stats_text             = other.m_stats_text;

    this->m_tick                    = other.m_tick;
}

PixelEngine::~PixelEngine()
{
    for(size_t i=0; i<m_userGroups.size(); i++)
    {
        delete m_userGroups[i];
    }
    for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
    {
        delete m_masterGameObjectGroup[i];
    }
    m_masterGameObjectGroup.clear();

    delete m_display;
    delete m_eventTimer;
    delete m_mainTickTimer;
    delete m_displayTimer;

    delete m_stats_text;
}
bool PixelEngine::running()
{
    return m_engineIsRunning;
}
const Vector2u  &PixelEngine::getWindwoSize() const
{
    return m_windowSize;
}
const Vector2u  &PixelEngine::getMapSize() const
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
#ifndef NO_TIMED_LOOPS
    if(!m_eventTimer->start(m_eventInterval))
       return;// Time not finished
#endif
    EASY_FUNCTION(profiler::colors::Orange);
#ifdef STATISTICS
    auto stats_checkUserEvent_timer_start = std::chrono::system_clock::now();
#endif
    EASY_BLOCK("userCheckEventLoop",profiler::colors::Orange50);
    if(m_p_func_userCheckEventLoop != nullptr)
        (*m_p_func_userCheckEventLoop)(m_eventInterval,m_tick);
    EASY_END_BLOCK;
#ifdef STATISTICS
    auto stats_checkEvent_timer_start = std::chrono::system_clock::now();
    std::chrono::duration<float> time_span_checkUserEvent_time = stats_checkEvent_timer_start - stats_checkUserEvent_timer_start;
    filter(m_statistics.checkUserEventTime,time_span_checkUserEvent_time.count()*1000.f,m_statsFilterFactor);
#endif
    // Check if any Object of a added List was removed or added
    checkForUserGroupChanges();

    // Handle display Events
    switch(m_display->handleEvents().type)
    {
        case sf::Event::Closed:
        {
            qDebug() << "Window closed";
            m_engineIsRunning = false;
            return;
        }
        default:
        {

        }
    }
    EASY_BLOCK("getGameObject->checkEvent",profiler::colors::Orange50);
    for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
    {
        m_masterGameObjectGroup[i]->getGameObject()->checkEvent();
    }
    EASY_END_BLOCK;
#ifdef STATISTICS
    auto stats_checkEvent_timer_end = std::chrono::system_clock::now();
    std::chrono::duration<float> time_span_checkEvent_time = stats_checkEvent_timer_end - stats_checkEvent_timer_start;
    filter(m_statistics.checkEventTime,time_span_checkEvent_time.count()*1000.f,m_statsFilterFactor);

#endif
}
void PixelEngine::tick()
{
#ifndef NO_TIMED_LOOPS
    if(!m_mainTickTimer->start(m_mainTickInterval))
        return; // Time not finished
#endif
     EASY_FUNCTION(profiler::colors::Orange100);

#ifdef STATISTICS
    m_statistics.objectsInEngine = m_masterGameObjectGroup.size();
    auto stats_userTick_timer_start = std::chrono::system_clock::now();
#endif
    EASY_BLOCK("userTickLoop",profiler::colors::Orange200);
    if(m_p_func_userTickLoop != nullptr)
        (*m_p_func_userTickLoop)(m_mainTickInterval,m_tick);
    EASY_END_BLOCK;
#ifdef STATISTICS
    m_tick++;
    m_statistics.collisionsPerTick      = 0;
    m_statistics.collisionChecksPerTick = 0;
    m_statistics.gameObjectTickTime     *= m_statsFilterFactor;
    m_statistics.collisionCheckTime     *= m_statsFilterFactor;
    auto stats_tick_timer_start = std::chrono::system_clock::now();
    std::chrono::duration<float> time_span_userEventEvent_time = stats_tick_timer_start - stats_userTick_timer_start;
    filter(m_statistics.userTickTime, time_span_userEventEvent_time.count()*1000.f,m_statsFilterFactor);
#endif

    EASY_BLOCK("tick X-Y",profiler::colors::Orange200);
    tickX();
    tickY();
    EASY_END_BLOCK;

#ifdef STATISTICS
    m_statistics.collisionChecksPerTick = RectI::stats_getIntersectionCounter();
    RectI::stats_resetIntersectionCounter();
    m_stats_tps_timer_end = std::chrono::system_clock::now();
    std::chrono::duration<float> time_span_tick_time = m_stats_tps_timer_end - stats_tick_timer_start;
    filter(m_statistics.tickTime, time_span_tick_time.count()*1000.f,m_statsFilterFactor);

    std::chrono::duration<float> time_span = m_stats_tps_timer_end - m_stats_tps_timer_start;
    m_stats_tps_timer_start = std::chrono::system_clock::now();
    if(time_span.count() != 0.f)
        filter(m_statistics.ticksPerSecond, 1.f/time_span.count(),m_statsFilterFactor);
#endif
}
void PixelEngine::tickX()
{
    EASY_FUNCTION(profiler::colors::Orange300);
    tickXY(Vector2i(1,0));
}
void PixelEngine::tickY()
{
    EASY_FUNCTION(profiler::colors::Orange300);
    tickXY(Vector2i(0,1));
}
void PixelEngine::tickXY(const Vector2i &dirLock)
{
    EASY_FUNCTION(profiler::colors::Orange400);
    for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
    {
        EASY_BLOCK("For each m_masterGameObjectGroup index",profiler::colors::Orange500);
#ifdef STATISTICS
        auto stats_timer_start = std::chrono::system_clock::now();

#endif
        m_masterGameObjectGroup[i]->getGameObject()->tick(dirLock);

#ifdef STATISTICS
        auto stats_timer_end = std::chrono::system_clock::now();
        std::chrono::duration<float> stats_time_span = stats_timer_end - stats_timer_start;
        m_statistics.gameObjectTickTime += stats_time_span.count()*1000.f*(1.f-m_statsFilterFactor);
        stats_timer_start = std::chrono::system_clock::now();
#endif
       // m_statistics.collisionsPerTick += m_masterGameObjectGroup[i]->checkCollision(m_masterGameObjectGroup_collisionInteractiveList[i].getVector());
        m_statistics.collisionsPerTick += m_masterGameObjectGroup[i]->getGameObject()->checkCollision(m_masterGameObjectGroup[i]->getInteractiveObjects().getVector());
#ifdef STATISTICS
        stats_timer_end = std::chrono::system_clock::now();
        stats_time_span = stats_timer_end - stats_timer_start;
        m_statistics.collisionCheckTime += stats_time_span.count()*1000.f*(1.f-m_statsFilterFactor);
#endif
    }

}
void PixelEngine::updateText()
{
    EASY_FUNCTION(profiler::colors::Orange600);
    if(m_stats_text->isVisible())
        updateStatsText();
}
void PixelEngine::checkForUserGroupChanges()
{
    EASY_FUNCTION(profiler::colors::Orange700);
    int changes = 0;
    int additions = 0;
    int removals = 0;
    for(size_t i=0; i<m_userGroups.size(); i++)
    {
        if(m_userGroups[i]->newObjectsAvailable())
        {
            // There are new GameObjects in the list,
            // which will be added to de Engine now.
            this->addGameObject(m_userGroups[i]->getNewObjects());
            m_userGroups[i]->newObjectsAddedToEngine();
            changes++;
            additions++;
        }
        if(m_userGroups[i]->deletableObjectsAvailable())
        {
            // There are GameObjects in the list,
            // which will be removed now.
            this->removeGameObject(m_userGroups[i]->getDeletableObjects());
            m_userGroups[i]->deletableObjectsRemovedFromEngine();
            changes++;
            removals++;
        }
    }
    if(changes != 0)
    {
        qDebug() << additions << " additions and "<<removals <<" romeved";
    }
}

void PixelEngine::removeObjectFromList(GameObjectGroup &group,GameObject* obj)
{
    EASY_FUNCTION(profiler::colors::Orange800);
    group.remove(obj);
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup> &list,GameObject* obj)
{
    EASY_FUNCTION(profiler::colors::Orange800);
    for(size_t i=0; i<list.size(); i++)
    {
        list[i].remove(obj);
    }
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup> &list,GameObjectGroup *obj)
{
    EASY_FUNCTION(profiler::colors::Orange800);
    for(size_t i=0; i<(*obj).size(); i++)
    {
        PixelEngine::removeObjectFromList(list,(*obj)[i]);
    }
}
void PixelEngine::removeObjectFromList(GameObjectGroup* &group,GameObject* obj)
{
    EASY_FUNCTION(profiler::colors::Orange800);
    group->remove(obj);
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup*> &list,GameObject* obj)
{
    EASY_FUNCTION(profiler::colors::Orange800);
    for(size_t i=0; i<list.size(); i++)
    {
        list[i]->remove(obj);
    }
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup*> &list,GameObjectGroup *obj)
{
    EASY_FUNCTION(profiler::colors::Orange800);
    for(size_t i=0; i<(*obj).size(); i++)
    {
        PixelEngine::removeObjectFromList(list,(*obj)[i]);
    }
}
void PixelEngine::removeObjectFromList_unmanaged(vector<ManagedGameObjectGroup*> &list,GameObject* obj)
{
    EASY_FUNCTION(profiler::colors::Orange800);
    for(size_t i=0; i<list.size(); i++)
    {
        list[i]->removeObject_unmanaged(obj);
    }
}

void PixelEngine::display()
{

#ifndef NO_TIMED_LOOPS
    if(!m_displayTimer->start(m_displayInterval))
        return;
#endif
    EASY_FUNCTION(profiler::colors::Orange900);

#ifdef STATISTICS
    auto stats_timePoint_1 = std::chrono::system_clock::now();
#endif
    EASY_BLOCK("userDisplayLoop",profiler::colors::OrangeA100)
    if(m_p_func_userDisplayLoop != nullptr)
        (*m_p_func_userDisplayLoop)(m_displayInterval,m_tick);
    EASY_END_BLOCK;
#ifdef STATISTICS
    auto stats_timePoint_2 = std::chrono::system_clock::now();
    std::chrono::duration<float> time_span_userDisplay_time = stats_timePoint_2 - stats_timePoint_1;
    filter(m_statistics.userDisplayTime,time_span_userDisplay_time.count()*1000.f,m_statsFilterFactor);
#endif

    EASY_BLOCK("m_renderLayer->display",profiler::colors::OrangeA100)
    for(size_t i=0; i<m_renderLayer.size(); i++)
    {        
        m_renderLayer[i].draw(*m_display);
    }
    EASY_END_BLOCK;
#ifdef STATISTICS
    stats_timePoint_1 = std::chrono::system_clock::now();
    std::chrono::duration<float> m_time_span_draw_time = stats_timePoint_1 - stats_timePoint_2;
    filter(m_statistics.drawTime, m_time_span_draw_time.count()*1000.f,m_statsFilterFactor);
    updateText();
    m_display->display();

#endif

#ifdef STATISTICS
    m_stats_fps_timer_end = std::chrono::system_clock::now();
    std::chrono::duration<float> m_time_span_display_time = m_stats_fps_timer_end - stats_timePoint_1;
    filter(m_statistics.displayTime, m_time_span_display_time.count()*1000.f,m_statsFilterFactor);

    std::chrono::duration<float> time_span = m_stats_fps_timer_end - m_stats_fps_timer_start;
    m_stats_fps_timer_start = std::chrono::system_clock::now();
    if(time_span.count() != 0.f)
        filter(m_statistics.framesPerSecond, 1.f/time_span.count(),m_statsFilterFactor);

#endif
}
void PixelEngine::set_setting_checkEventInterval(const float &seconds)
{
    m_eventInterval = abs(seconds);
}
const float &PixelEngine::get_setting_eventHandleInterval() const
{
    return m_eventInterval;
}
void PixelEngine::set_setting_gameTickInterval(const float &seconds)
{
    m_mainTickInterval = abs(seconds);
}
const float  &PixelEngine::get_setting_gameTickInterval() const
{
    return m_mainTickInterval;
}
void PixelEngine::set_setting_displayInterval(const float &seconds)
{
    m_displayInterval = abs(seconds);
}
const float  &PixelEngine::get_setting_displayInterval() const
{
    return m_displayInterval;
}
void PixelEngine::addGameObject(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA200);
    for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
        if(m_masterGameObjectGroup[i]->getGameObject() == obj)
            return; // Object already added to list

    if(!obj->isBoundingBoxUpdated())
        obj->updateBoundingBox();
    obj->setEventHandler(this);
    m_masterGameObjectGroup.add(obj);
   // m_masterGameObjectGroup_collisionInteractiveList.push_back(GameObjectGroup());
    m_renderLayer[2].add(obj);
}
void PixelEngine::addGameObject(ManagedGameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::OrangeA200);
    addGroup(group);
}
void PixelEngine::addGameObject(GameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::OrangeA200);
    GameObjectGroup::removeDuplicates(group);
    addGameObject(group->getVector());
}
void PixelEngine::addGameObject(const vector<GameObject *> &list)
{
    EASY_FUNCTION(profiler::colors::OrangeA200);
    //m_masterGameObjectGroup_collisionInteractiveList.reserve(m_masterGameObjectGroup_collisionInteractiveList.size()+list.size());
    for(size_t i=0; i<list.size(); i++)
        this->addGameObject(list[i]);
}
void PixelEngine::removeGameObject(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    // Remove the obj out of the masterList
    /*for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
    {
        if(m_masterGameObjectGroup[i]->getGameObject() == obj)
        {
            for(size_t j=0; j<m_masterGameObjectGroup.size(); j++)
            {
                this->setCollisionSingleInteraction(m_masterGameObjectGroup[j],obj,false);
            }
           // m_masterGameObjectGroup_collisionInteractiveList.erase(m_masterGameObjectGroup_collisionInteractiveList.begin() + i);
           // this->removeObjectFromList(m_masterGameObjectGroup,obj);
            m_masterGameObjectGroup.remove(obj);
            this->removeObjectFromList(m_renderLayer,obj);
       }
    }*/
    this->removeObjectFromList_unmanaged(m_userGroups,obj);
    obj->setEventHandler(nullptr);
    this->removeObjectFromList(m_renderLayer,obj);
    m_masterGameObjectGroup.removeAllInteractionsWithObj(obj);
    m_masterGameObjectGroup.remove(obj);
    // Remove the obj out of all lists

}
void PixelEngine::removeGameObject(ManagedGameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    removeGameObject(group->getVector());
}
void PixelEngine::removeGameObject(const vector<GameObject *> &list)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    for(size_t i=0; i<list.size(); i++)
    {
        this->removeGameObject(list[i]);
    }
}

void PixelEngine::deleteGameObject(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    this->removeGameObject(obj);
    //delete obj;
    //obj = nullptr;
}
void PixelEngine::deleteGameObject(ManagedGameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    deleteGameObject(group->getVector());
}
void PixelEngine::deleteGameObject(const vector<GameObject *> &list)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    for(size_t i=0; i<list.size(); i++)
    {
        this->deleteGameObject(list[i]);
    }
}
void PixelEngine::setCollisionSingleInteraction(GameObject *obj1,GameObject *obj2, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    if(obj1 == obj2)
        return; // Cann't collide with it self

    InteractiveGameObject *interactive_1 = m_masterGameObjectGroup.getInteractiveObject(obj1);
    interactive_1->setInteractionWith(obj2,doesCollide);
    /*GameObject *object1 = nullptr;
    size_t objext1_index;
    GameObject *object2 = nullptr;

    for(size_t x=0; x<m_masterGameObjectGroup.size(); x++)
    {
        if(m_masterGameObjectGroup[x]->getGameObject() == obj1)
        {
            object1 = obj1;
            objext1_index = x;
        }else if(m_masterGameObjectGroup[x]->getGameObject() == obj2)
        {
            object2 = obj2;
        }
    }
    if(object1 != nullptr && object2 != nullptr)
    {
        bool obj2Found = false;
        GameObjectGroup obj1_interactorList = m_masterGameObjectGroup[objext1_index]->getInteractiveObjects();
        for(size_t i=0; i<obj1_interactorList.size(); i++)
        {
            if(obj1_interactorList[i] == object2)
            {
                obj2Found = true;
                if(!doesCollide)
                {
                    // Remove Object2 from the Object1's colliderList
                    // Object1 will no longer collide with Object2
                    m_masterGameObjectGroup[objext1_index]->removeInteractionWith(object2);
                }
            }
        }
        if(!obj2Found && doesCollide)
        {
            // Add Object2 to the Object1's colliderList
            // Object1 will now collide with Object2
            m_masterGameObjectGroup[objext1_index]->addInteractionWith(object2);
        }
    }*/
}
void PixelEngine::setCollisionSingleInteraction(GameObject *obj1,GameObjectGroup *obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    InteractiveGameObject *interactive_1 = m_masterGameObjectGroup.getInteractiveObject(obj1);
    interactive_1->setInteractionWith(obj2List,doesCollide);
   //for(size_t i=0; i<obj2List->size(); i++)
   //    this->setCollisionSingleInteraction(obj1,(*obj2List)[i],doesCollide); // Not very efficient code ;)
}
void PixelEngine::setCollisionSingleInteraction(GameObjectGroup *obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj1List->size(); i++)
        this->setCollisionSingleInteraction((*obj1List)[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(GameObject *obj1, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
   for(size_t i=0; i<obj2List.size(); i++)
       this->setCollisionSingleInteraction(obj1,obj2List[i],doesCollide); // Not very efficient code ;)
}
void PixelEngine::setCollisionSingleInteraction(GameObjectGroup *obj1List,const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj1List->size(); i++)
        this->setCollisionSingleInteraction((*obj1List)[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(const vector<GameObject*> &obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj1List.size(); i++)
        this->setCollisionSingleInteraction(obj1List[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(const vector<GameObject*> &obj1List, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj1List.size(); i++)
        this->setCollisionSingleInteraction(obj1List[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObject *obj1,GameObject *obj2, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    this->setCollisionSingleInteraction(obj1,obj2, doesCollide);
    this->setCollisionSingleInteraction(obj2,obj1, doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObject *obj1,GameObjectGroup *obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    //for(size_t i=0; i<obj2List->size(); i++)
    //    this->setCollisionMultiInteraction(obj1,(*obj2List)[i],doesCollide); // Not very efficient code ;)
    InteractiveGameObject *interactive_1 = m_masterGameObjectGroup.getInteractiveObject(obj1);
    interactive_1->setInteractionWith(obj2List,doesCollide);
    for(size_t i=0; i<obj2List->size(); i++)
        this->setCollisionSingleInteraction(obj2List->getVector()[i],obj1, doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObjectGroup *obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    setCollisionSingleInteraction(obj1List,obj2List,doesCollide);
    setCollisionSingleInteraction(obj2List,obj1List,doesCollide);
    //for(size_t i=0; i<obj1List->size(); i++)
    //    this->setCollisionMultiInteraction((*obj1List)[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObject *obj1, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj2List.size(); i++)
        this->setCollisionMultiInteraction(obj1,obj2List[i],doesCollide); // Not very efficient code ;)
}
void PixelEngine::setCollisionMultiInteraction(GameObjectGroup *obj1List,const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    this->setCollisionSingleInteraction(obj2List,obj1List,doesCollide);
    this->setCollisionSingleInteraction(obj1List,obj2List,doesCollide);
    //for(size_t i=0; i<obj1List->size(); i++)
    //   this->setCollisionMultiInteraction((*obj1List)[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(const vector<GameObject*> &obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    this->setCollisionSingleInteraction(obj1List,obj2List,doesCollide);
    this->setCollisionSingleInteraction(obj2List,obj1List,doesCollide);
    //for(size_t i=0; i<obj1List.size(); i++)
    //    this->setCollisionMultiInteraction(obj1List[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(const vector<GameObject*> &obj1List, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj1List.size(); i++)
        this->setCollisionMultiInteraction(obj1List[i],obj2List,doesCollide);
}

// Groups
void PixelEngine::addGroup(ManagedGameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::OrangeA200);
    for(size_t i=0; i<m_userGroups.size(); i++)
        if(m_userGroups[i] == group)
            return; // Group already added to list
    // Add every Element to the engines main list, if it isn't already in there.
    this->addGameObject(group->getVector());
    group->newObjectsAddedToEngine();
    m_userGroups.push_back(group);
}
void PixelEngine::removeGroup(ManagedGameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    for(size_t i=0; i<m_userGroups.size(); i++)
        if(m_userGroups[i] == group)
            m_userGroups.erase(m_userGroups.begin() + i);
}
void PixelEngine::deleteGroup(ManagedGameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
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
    EASY_FUNCTION(profiler::colors::OrangeA700);
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
    EASY_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<objGroup->size(); i++)
        this->moveRenderLayer_UP((*objGroup)[i]);
}
void PixelEngine::moveRenderLayer_DOWN(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
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
    EASY_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<objGroup->size(); i++)
        this->moveRenderLayer_DOWN((*objGroup)[i]);
}
void PixelEngine::setRenderLayer_BOTTOM(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
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
    EASY_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<objGroup->size(); i++)
        this->setRenderLayer_BOTTOM((*objGroup)[i]);
}
void PixelEngine::setRenderLayer_TOP(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
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
    EASY_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<objGroup->size(); i++)
        this->setRenderLayer_TOP((*objGroup)[i]);
}

// GameObject Events from GameObjectEventHandler
void PixelEngine::kill(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Orange50);
}
void PixelEngine::removeFromEngine(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    this->removeGameObject(obj);
}
void PixelEngine::deleteObject(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    this->deleteGameObject(obj);
}
void PixelEngine::collisionOccured(GameObject *obj1,vector<GameObject *> obj2)
{
    EASY_FUNCTION(profiler::colors::Orange100);
   // qDebug() << "collision"<<obj1<<"\t"<<obj2;
}
void PixelEngine::addDisplayText(DisplayText*text)
{
    EASY_FUNCTION(profiler::colors::Orange200);
    m_display->addText(text);
};
void PixelEngine::removeDisplayText(DisplayText*text)
{
    EASY_FUNCTION(profiler::colors::Orange300);
    m_display->removeText(text);
};


// General functions
float PixelEngine::random(float min, float max)
{
    EASY_FUNCTION(profiler::colors::Orange400);
    if(min == max || abs(min - max) < 0.000001)
    {
        return min;
    }
    if(min > max)
    {   float buf=min;
        min = max;
        max = buf;
    }

    // Generating a timedependend seed
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    int seed = now->tm_year + now->tm_mon + now->tm_mday + now->tm_hour + now->tm_min + now->tm_sec;
    return float((min*1000.0)+((seed*rand())%(int)((max-min)*1000.0)))/1000.0;
}
/*bool   PixelEngine::loadFromImage(const std::string &picture, Collider *collider, Painter *painter, const ImageOrigin &origin)
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
bool   PixelEngine::loadFromImage(const std::string &picture, Collider *collider, Painter *painter, const Vector2i&origin)
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

    float progress = 0;
    float maxProgress = size.x * size.y;

    // Reserve the maximum amount of possible pixels
    painter->reserve(size.x * size.y);

    Color color;
    RectI rect;
    rect.setSize(1,1);
    Pixel pixel;
#ifdef IMAGE_IMPORT_DEBUG
    qDebug() << "Imagesize x="<<size.x<<"\ty="<<size.y;
#endif

    // Each pixel in the image is set to RectI with the size of width=1 height=1
    // The list is converted into fewer rects
    vector<RectI> rawRectList;

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
    vector<RectI> colliderRects;

    // Converts many small RectI's to a few large ones
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
void PixelEngine::optimize_Hitboxes(vector<RectI> &input,vector<RectI> &outputColliderList,const Point origin)
{
    size_t width = 0;
    size_t height = 0;

    vector<vector<RectI*>    > map;
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
        map.push_back(vector<RectI*>());
        map[x].reserve(height);

        for(size_t y=0; y<height; y++)
        {
            map[x].push_back(nullptr);
        }
    }
    for(size_t i=0; i<input.size(); i++)
    {
         map[input[i].getX()][input[i].getY()] = new RectI();
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
void PixelEngine::optimize_HitboxMap(vector<vector<RectI*>  > &map,vector<RectI> &outputColliderList)
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
            vector<RectI**> toDeleteList;
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
            outputColliderList.push_back(RectI(*map[x][y]));
            x+=xIterator-1;
        }
    }
}
*/
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
void PixelEngine::display_stats(bool enable)
{
    EASY_FUNCTION(profiler::colors::Orange500);
     m_stats_text->setVisibility(enable);
}
void PixelEngine::display_stats(bool enable, const Color &color)
{
    EASY_FUNCTION(profiler::colors::Orange600);
    m_stats_text->setColor(color);
    display_stats(enable);
}
void PixelEngine::display_stats(bool enable,const Color &color, const Vector2i &pos, const unsigned int size)
{
    EASY_FUNCTION(profiler::colors::Orange600);
    m_stats_text->setPos(Vector2f(pos));
    if(size > 0)
        m_stats_text->setCharacterSize(size);
    else
        m_stats_text->setCharacterSize(m_windowSize.x/80);
    display_stats(enable,color);
}
bool PixelEngine::display_stats()
{
    return m_stats_text->isVisible();
}

void PixelEngine::resetStatistics()
{
    m_statistics.collisionChecksPerTick = 0;
    m_statistics.collisionsPerTick      = 0;
}
void PixelEngine::updateStatsText()
{
    EASY_FUNCTION(profiler::colors::Orange700);
    std::string text =
     "framesPerSecond:       \t" + to_string(m_statistics.framesPerSecond) +        "\n"+
     "ticksPerSecond:        \t" + to_string(m_statistics.ticksPerSecond) +         "\n"+
     "collisionsPerTick:     \t" + to_string(m_statistics.collisionsPerTick) +      "\n"+
     "collisionChecksPerTick:\t" + to_string(m_statistics.collisionChecksPerTick) + "\n"+
     "objectsInEngine:       \t" + to_string(m_statistics.objectsInEngine) +        "\n"+
     "collisionCheckTime:    \t" + to_string(m_statistics.collisionCheckTime) +     " ms\n"+
     "gameObjectTickTime:    \t" + to_string(m_statistics.gameObjectTickTime) +     " ms\n"+
     "checkEventTime:        \t" + to_string(m_statistics.checkEventTime) +         " ms\n"+
     "tickTime:              \t" + to_string(m_statistics.tickTime) +               " ms\n"+
     "drawTime:              \t" + to_string(m_statistics.drawTime) +               " ms\n"+
     "displayTime:           \t" + to_string(m_statistics.displayTime) +            " ms\n"+
     "checkUserEventTime:    \t" + to_string(m_statistics.checkUserEventTime) +     " ms\n"+
     "userTickTime:          \t" + to_string(m_statistics.userTickTime) +           " ms\n"+
     "userDisplayTime:       \t" + to_string(m_statistics.userDisplayTime) +        " ms";
    m_stats_text->setString(text);
}
void PixelEngine::filter(float &oldValue, float newValue, float filterFactor)
{
    oldValue = oldValue * filterFactor + (1.f-filterFactor) * newValue;
}
