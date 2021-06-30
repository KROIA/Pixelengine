#include "pixelengine.h"

PixelEngine::PixelEngine(const Vector2u  &mapsize,const Vector2u  &displaySize)
    :   GameObjectEventHandler()
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


    m_stats_text = new DisplayText();
    m_stats_text->setCharacterSize(m_windowSize.x/80); // in pixels, not points!
    sf::Color col(255,255,255,100); // Transparent white
    display_stats(false,col);
    m_stats_text->setPos(Vector2f(5,5));
    m_stats_text->setPositionFix(true);

    m_display->addText(m_stats_text);
    resetTick();
}

PixelEngine::PixelEngine(const PixelEngine &other)
    :   GameObjectEventHandler(other)//, GroupManagerInterface(other)
{
    *this->m_display               = *other.m_display;
    this->m_windowSize             = other.m_windowSize;
    this->m_mapSize                = other.m_mapSize;

    *this->m_eventTimer            = *other.m_eventTimer;
    this->m_eventInterval          = other.m_eventInterval;

    *this->m_mainTickTimer         = *other.m_mainTickTimer;
    this->m_mainTickInterval       = other.m_mainTickInterval;

    *this->m_displayTimer          = *other.m_displayTimer;
    this->m_displayInterval        = other.m_displayInterval;

    this->m_masterGameObjectGroup  = other.m_masterGameObjectGroup;

    this->m_renderLayer            = other.m_renderLayer;

    this->m_userGroups             = other.m_userGroups;

    this->m_p_func_userDisplayLoop = other.m_p_func_userDisplayLoop;
    this->m_p_func_userTickLoop    = other.m_p_func_userTickLoop;
    this->m_p_func_userTickLoop    = other.m_p_func_userTickLoop;

    this->m_statistics             = other.m_statistics;
    this->m_statsFilterFactor      = other.m_statsFilterFactor;

    this->m_stats_text             = other.m_stats_text;

    this->m_tick                   = other.m_tick;
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

    for(size_t i=0; i<m_trashList.size(); i++)
    {
        delete m_trashList[i];
    }
    m_trashList.clear();

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
void PixelEngine::stop()
{
    qDebug() << "Stop Engine";
#ifdef USE_THREADS
    for(size_t i=0; i<m_threadList.size(); i++)
    {
        m_threadList[i]->terminate();
        delete m_threadList[i];
        delete m_threadParamList[i];
        m_threadList.clear();
        m_threadParamList.clear();
    }
#endif
    m_engineIsRunning = false;

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
            EASY_BLOCK("sf::Event::Closed",profiler::colors::Orange);
            stop();

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
    m_statistics.intersectionCheckPerTick   = Collider::stats_checkIntersectCounter;
    m_statistics.doesIntersectPerTick       = Collider::stats_doesIntersectCounter;
    m_statistics.collisionChecksPerTick     = Collider::stats_checkCollisionCounter;
    m_statistics.collisionsPerTick          = Collider::stats_doesCollideCounter;
    Collider::stats_reset();

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
#ifdef USE_THREADS
    if(!m_threadsCreated)
    {
        EASY_BLOCK("Create Threads",profiler::colors::Orange500);
        unsigned int threadAmount = m_masterGameObjectGroup.size()/500;
        if(threadAmount == 0)
            threadAmount = 1;
        qDebug() << "create "<<threadAmount<< " Threads";
        for(unsigned int i=0; i<threadAmount; i++)
        {
            m_threadParamList.push_back(new ThreadParam());
            m_threadParamList[m_threadParamList.size()-1]->isRunning = false;
            m_threadParamList[m_threadParamList.size()-1]->globalStart = &m_threadGlobalStart;
            m_threadParamList[m_threadParamList.size()-1]->globalMutex = &m_threadGlobalMutex;
            m_threadParamList[m_threadParamList.size()-1]->stats = &m_statistics;
            m_threadList.push_back(new sf::Thread(&PixelEngine::thread_tick,m_threadParamList[m_threadParamList.size()-1]));
        }
        m_threadsCreated = true;
        m_thread_lastObjAmount = 0;
        for(size_t i=0; i<m_threadList.size(); i++)
        {
            m_threadList[i]->launch();
        }
    }
    if(m_masterGameObjectGroup.size() != m_thread_lastObjAmount)
    {
        EASY_BLOCK("Ajust Threads",profiler::colors::Orange500);
        size_t iterator = 0;
        size_t objectAmount = m_masterGameObjectGroup.size();
        size_t objPerThread = objectAmount/m_threadList.size();
        for(size_t i=0; i<m_threadList.size(); i++)
        {
            if(i == m_threadList.size()-1)
               objPerThread =  objectAmount - iterator;

            m_threadParamList[i]->obj_begin = iterator;
            m_threadParamList[i]->obj_end = iterator + objPerThread;
            m_threadParamList[i]->group = &m_masterGameObjectGroup;
            m_threadParamList[i]->isRunning = false;

            iterator += objPerThread;
        }
        m_thread_lastObjAmount = objectAmount;
    }
    EASY_BLOCK("Set Thread parameter",profiler::colors::Orange500);
    for(size_t i=0; i<m_threadList.size(); i++)
    {
        m_threadParamList[i]->dirLock = dirLock;
    }
    EASY_END_BLOCK;
    EASY_BLOCK("Enable Threads",profiler::colors::Orange500);
    for(size_t i=0; i<m_threadList.size(); i++)
    {
        m_threadParamList[i]->mutex.lock();
        m_threadParamList[i]->isRunning = true;
        m_threadParamList[i]->mutex.unlock();
    }
    EASY_END_BLOCK;

    bool isRunning = false;

    EASY_BLOCK("Wait for Threads",profiler::colors::Orange500);
    for(size_t i=0; i<m_threadParamList.size(); i++)
    {
        EASY_BLOCK("Wait",profiler::colors::Orange500);
        isRunning = true;
        while(isRunning)
        {
            m_threadParamList[i]->mutex.lock();
            isRunning = m_threadParamList[i]->isRunning;
            m_threadParamList[i]->mutex.unlock();
        }
        EASY_END_BLOCK;
    }
    EASY_END_BLOCK;
#else
    for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
    {
        EASY_BLOCK("For each m_masterGameObjectGroup index",profiler::colors::Orange500);
        InteractiveGameObject* interactiveObject = m_masterGameObjectGroup[i];
        GameObject *obj = interactiveObject->getGameObject();
#ifdef STATISTICS
        auto stats_timer_start = std::chrono::system_clock::now();

#endif
        obj->tick(dirLock);

#ifdef STATISTICS
        auto stats_timer_end = std::chrono::system_clock::now();
        std::chrono::duration<float> stats_time_span = stats_timer_end - stats_timer_start;
        m_statistics.gameObjectTickTime += stats_time_span.count()*1000.f*(1.f-m_statsFilterFactor);
        stats_timer_start = std::chrono::system_clock::now();
#endif
        m_statistics.collisionsPerTick += obj->checkCollision(interactiveObject->getInteractiveObjects().getVector());
#ifdef STATISTICS
        stats_timer_end = std::chrono::system_clock::now();
        stats_time_span = stats_timer_end - stats_timer_start;
        m_statistics.collisionCheckTime += stats_time_span.count()*1000.f*(1.f-m_statsFilterFactor);
#endif
    }

#endif

}
#ifdef USE_THREADS
void PixelEngine::thread_tick(ThreadParam *param)
{
    EASY_THREAD("thread_tick");
    bool isRunning = false;
    while(1)
    {

        EASY_BLOCK("waiting");
        while(!isRunning)
        {

            param->mutex.lock();
            isRunning = param->isRunning;
            param->mutex.unlock();

            if(isRunning)
            {
                break;
            }
            sf::sleep(sf::milliseconds(1));
        }
        EASY_END_BLOCK;
        EASY_BLOCK("working");
        unsigned long collisionsPerTick = 0;
        double gameObjectTickTime = 0;
        double collisionCheckTime = 0;
        for(size_t i=param->obj_begin; i<param->obj_end; i++)
        {
            EASY_BLOCK("For each m_masterGameObjectGroup index",profiler::colors::Orange500);
            InteractiveGameObject* interactiveObject = (*param->group)[i];
            GameObject *obj = interactiveObject->getGameObject();
    #ifdef STATISTICS
            auto stats_timer_start = std::chrono::system_clock::now();
    #endif
            obj->tick(param->dirLock);

    #ifdef STATISTICS
            auto stats_timer_end = std::chrono::system_clock::now();
            std::chrono::duration<float> stats_time_span = stats_timer_end - stats_timer_start;
            gameObjectTickTime += stats_time_span.count()*500.f;

            stats_timer_start = std::chrono::system_clock::now();
            collisionsPerTick += obj->checkCollision(interactiveObject->getInteractiveObjects().getVector());
    #else
            obj->checkCollision(interactiveObject->getInteractiveObjects().getVector());
    #endif

    #ifdef STATISTICS
            stats_timer_end = std::chrono::system_clock::now();
            stats_time_span = stats_timer_end - stats_timer_start;
            collisionCheckTime += stats_time_span.count()*500.f;


    #endif
        }
    #ifdef STATISTICS
        param->globalMutex->lock();
        param->stats->collisionsPerTick  += collisionsPerTick;
        param->stats->collisionCheckTime += collisionCheckTime;
        param->stats->gameObjectTickTime += gameObjectTickTime;
        param->globalMutex->unlock();
    #endif
        EASY_END_BLOCK;
        EASY_BLOCK("ende");
        isRunning = false;
        param->mutex.lock();
        param->isRunning = isRunning;
        param->mutex.unlock();
        EASY_END_BLOCK;
    }
    EASY_BLOCK("closing");
    sf::sleep(sf::milliseconds(1));
    EASY_END_BLOCK;
}
#endif
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

void PixelEngine::display_setRenderFramePosCenter(const Vector2f &pos)
{
    m_display->setRenderFramePosCenter(pos);
}
void PixelEngine::display_moveRenderFrame(const Vector2f &vec)
{
    m_display->moveRenderFrame(vec);
}
void PixelEngine::display_setRenderFramePos(const Vector2f &pos)
{
    m_display->setRenderFramePos(pos);
}
void PixelEngine::display_setRenderFrame(const RectF &frame)
{
    m_display->setRenderFrame(frame);
}
const RectF &PixelEngine::display_getRenderFrame() const
{
    return m_display->getRenderFrame();
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
    obj->preRun();
    m_masterGameObjectGroup.add(obj);
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
    m_masterGameObjectGroup.reserve(list.size());
    for(size_t i=0; i<list.size(); i++)
        this->addGameObject(list[i]);
}
void PixelEngine::addToTrash(GameObject *obj)
{
    obj->markAsTrash(true);
    m_trashList.add(obj);
}
void PixelEngine::removeGameObject(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    // Remove the obj out of all lists
    this->removeObjectFromList_unmanaged(m_userGroups,obj);
    obj->setEventHandler(nullptr);
    this->removeObjectFromList(m_renderLayer,obj);
    m_masterGameObjectGroup.removeAllInteractionsWithObj(obj);
    m_masterGameObjectGroup.remove(obj);

    addToTrash(obj);


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

/*void PixelEngine::deleteGameObject(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    this->removeGameObject(obj);
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
}*/
void PixelEngine::setCollisionSingleInteraction(GameObject *obj1,GameObject *obj2, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    if(obj1 == obj2)
        return; // Cann't collide with it self

    InteractiveGameObject *interactive_1 = m_masterGameObjectGroup.getInteractiveObject(obj1);
    interactive_1->setInteractionWith(obj2,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(GameObject *obj1,GameObjectGroup *obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    InteractiveGameObject *interactive_1 = m_masterGameObjectGroup.getInteractiveObject(obj1);
    interactive_1->setInteractionWith(obj2List,doesCollide);
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
}
void PixelEngine::setCollisionMultiInteraction(const vector<GameObject*> &obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    EASY_FUNCTION(profiler::colors::OrangeA700);
    this->setCollisionSingleInteraction(obj1List,obj2List,doesCollide);
    this->setCollisionSingleInteraction(obj2List,obj1List,doesCollide);
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
/*void PixelEngine::deleteGroup(ManagedGameObjectGroup *group)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    for(size_t i=0; i<m_userGroups.size(); i++)
        if(m_userGroups[i] == group)
        {
            m_userGroups.erase(m_userGroups.begin() + i);
            delete group;
        }
}*/

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
    m_renderLayer[0].reserve(objGroup->size());
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
    m_renderLayer[m_renderLayer.size()-1].reserve(objGroup->size());
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
/*void PixelEngine::deleteObject(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::OrangeA400);
    this->deleteGameObject(obj);
}*/
void PixelEngine::collisionOccured(GameObject *obj1,vector<GameObject *> obj2)
{
    EASY_FUNCTION(profiler::colors::Orange100);
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
     "Collider:\n"+
     "  Check Intersections: \t" + to_string(m_statistics.intersectionCheckPerTick)+"/Tick\n"+
     "  Intersecting:        \t" + to_string(m_statistics.doesIntersectPerTick) +   "/Tick\n"+
     "  Collision checks:    \t" + to_string(m_statistics.collisionChecksPerTick) + "/Tick\n"+
     "  Collisions:          \t" + to_string(m_statistics.collisionsPerTick) +      "/Tick\n"+
     "\n"+
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
