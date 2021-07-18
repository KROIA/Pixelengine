#include "pixelengine.h"

PixelEngine::PixelEngine()
{
    constructor(__defaultSettings);
}
PixelEngine::PixelEngine(const Settings &settings)
{
    constructor(settings);
}
PixelEngine::PixelEngine(const Vector2u  &mapsize,const Vector2u  &displaySize)
    :   GameObjectEventHandler()
{
    Settings settings               = __defaultSettings;
    settings.display.windowSize     =  displaySize;
    settings.display.pixelMapSize   = mapsize;
    constructor(settings);
}
void PixelEngine::constructor(const Settings &settings)
{
#ifdef BUILD_WITH_EASY_PROFILER
    EASY_PROFILER_ENABLE;
    EASY_MAIN_THREAD;
#endif
    setSettings(settings);
    m_display            = new PixelDisplay(__defaultSettings.display);
    m_engineIsRunning    = true;
    m_drawingEnabled     = true;

    m_drawingEnabled     = true;
    m_nextSyncLoopActive = false;
    m_syncTimer          = new Timer;
    m_eventTimer         = new Timer;
    m_mainTickTimer      = new Timer;
    m_displayTimer       = new Timer;
    m_syncTimer->setAutorestart(true);
    m_eventTimer->setAutorestart(true);
    m_mainTickTimer->setAutorestart(true);
    m_displayTimer->setAutorestart(true);

    this->set_setting_runInSync(__defaultSettings.engine.runInSync);
    this->set_setting_syncEngineInterval(__defaultSettings.engine.time_syncInterval);
    this->set_setting_checkEventInterval(__defaultSettings.engine.time_eventInterval);
    this->set_setting_gameTickInterval(__defaultSettings.engine.time_tickInterval);
    this->set_setting_displayInterval(__defaultSettings.engine.time_displayInterval);

    m_p_func_userCheckEventLoop  = nullptr;
    m_p_func_userDisplayLoop     = nullptr;
    m_p_func_userTickLoop        = nullptr;
    m_setupDone                  = false;

    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());
    m_renderLayer.push_back(GameObjectGroup());

    m_statistics.framesPerSecond        = 0;
    m_statistics.ticksPerSecond         = 0;
    m_statistics.collisionsPerTick      = 0;
    m_statistics.collisionChecksPerTick = 0;
    m_statistics.intersectionCheckPerTick = 0;
    m_statistics.doesIntersectPerTick   = 0;
    m_statistics.objectsInEngine        = 0;
    m_statistics.collisionCheckTime     = 0;
    m_statistics.gameObjectTickTime     = 0;
    m_statistics.checkEventTime         = 0;
    m_statistics.tickTime               = 0;
    m_statistics.displayTime            = 0;
    m_statistics.preDisplayTime         = 0;
    m_statistics.checkUserEventTime     = 0;
    m_statistics.userTickTime           = 0;
    m_statistics.userDisplayTime        = 0;
    m_statistics.eventsInEngine         = 0;
    m_statsFilterFactor                 = __defaultSettings.engine.statsDisplayFilter;

#ifdef PIXELENGINE_STATISTICS
    m_stats_text = new TextPainter();
    m_stats_text->setCharacterSize(25); // in pixels, not points!
    m_stats_text->setScale(Vector2f(0.5,0.5));
    m_stats_text->setLineSpacing(0.8);
    sf::Color col(255,255,255,100); // Transparent white
    display_stats(false,col);
    m_stats_text->setPos(Vector2f(0,0));
    m_stats_text->setPositionFix(true);

    m_display->subscribePainter(m_stats_text);
#endif
    resetTick();
}

PixelEngine::PixelEngine(const PixelEngine &other)
    :   GameObjectEventHandler(other)
{
    *this->m_display               = *other.m_display;

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
#ifdef PIXELENGINE_STATISTICS
    this->m_stats_text             = other.m_stats_text;
#endif
    this->m_tick                   = other.m_tick;
}

PixelEngine::~PixelEngine()
{
#ifdef BUILD_WITH_EASY_PROFILER
    auto blocks_count = profiler::dumpBlocksToFile("profiler.prof");
    std::cout << "Profiler blocks count: " << blocks_count << std::endl;
#endif
    for(size_t i=0; i<m_userGroups.size(); i++)
    {
        delete m_userGroups[i];
    }
    m_renderLayer.clear();
    vector<GameObject*>objList;
    objList.reserve(m_masterGameObjectGroup.size()+m_trashList.size());
    for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
    {
        objList.push_back(m_masterGameObjectGroup[i]->getGameObject());
        delete m_masterGameObjectGroup[i];
    }
    m_masterGameObjectGroup.clear();

    for(size_t i=0; i<m_trashList.size(); i++)
    {
        objList.push_back(m_trashList[i]->getGameObject());
        delete m_trashList[i];
    }
    m_trashList.clear();

    for(size_t i=0; i<objList.size(); i++)
    {
        delete objList[i];
    }


    delete m_display;
    delete m_eventTimer;
    delete m_mainTickTimer;
    delete m_displayTimer;
#ifdef PIXELENGINE_STATISTICS
    delete m_stats_text;
#endif
}
PixelEngine::Settings PixelEngine::getSettings()
{
    return __defaultSettings;
}
void PixelEngine::setSettings(const Settings &settings)
{
    __defaultSettings                           = settings;
    if(settings.gameObject.objectTree.boundry == ObjectTree::__defaultSettings.boundry)
    {
        InteractiveGameObject::__defaultSettings    = settings.gameObject;
        InteractiveGameObject::__defaultSettings.objectTree.boundry  = RectF(0.f,0.f,(float)settings.display.pixelMapSize.x,(float)settings.display.pixelMapSize.y);
    }
    else
    {
        InteractiveGameObject::__defaultSettings    = settings.gameObject;
    }
    TextPainter::__defaultSettings              = settings.text;
    PixelDisplay::__defaultSettings             = settings.display;
    PixelEngine::__defaultEngineSettings        = settings.engine;

}


bool PixelEngine::running()
{
    return m_engineIsRunning;
}
void PixelEngine::stop()
{
    qDebug() << "Stop Engine";
#ifdef PIXELENGINE_USE_THREADS
    for(size_t i=0; i<m_std_threadList.size(); i++)
    {
        pthread_mutex_lock(&m_threadParamList[i]->mutex);
        threadExit = true;
        pthread_cond_broadcast( &cv );
        pthread_mutex_unlock(&m_threadParamList[i]->mutex);
        m_std_threadList.clear();
        m_threadParamList.clear();
    }
#endif
    m_engineIsRunning = false;

}
const Vector2u  &PixelEngine::getWindowSize() const
{
    return m_display->getWindowSize();
}
const Vector2u  &PixelEngine::getMapSize() const
{
    return m_display->getMapSize();
}
const RectF &PixelEngine::getRenderFrame() const
{
    return m_display->getRenderFrame();
}

// Userloops
void PixelEngine::setUserCheckEventLoop(p_eventFunc func)
{
    m_p_func_userCheckEventLoop = func;
}
void PixelEngine::setUserDisplayLoop(p_displayFunc func)
{
    m_p_func_userDisplayLoop = func;
}
void PixelEngine::setUserTickLoop(p_tickFunc func)
{
    m_p_func_userTickLoop = func;
}

void PixelEngine::setup()
{
    if(m_setupDone)
        return;
    ENGINE_BLOCK("PixelEngine::setup()",profiler::colors::Orange);
    m_masterGameObjectGroup.buildCache();

    GameObject *obj;
    for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
    {
        obj = m_masterGameObjectGroup[i]->getGameObject();
        if(!obj->isBoundingBoxUpdated())
            obj->updateBoundingBox();
        obj->setEventHandler(this);
        obj->setDisplayInterface(m_display);
        m_masterGameObjectGroup[i]->subscribeToDisplay(*m_display);
        obj->engineCalled_setup();
    }

    m_setupDone = true;
}
void PixelEngine::loop()
{
    ENGINE_FUNCTION(profiler::colors::Orange);
    this->checkEvent();
    this->tick();
    this->display();
}
void PixelEngine::checkEvent()
{
#ifndef PIXELENGINE_NO_TIMED_LOOPS
    if(m_runInSync)
    {
        if(!m_syncTimer->start(m_syncInterval))
           return;// Time not finished
        m_nextSyncLoopActive = true;
    }
    else
    {
        if(!m_eventTimer->start(m_eventInterval))
           return;// Time not finished
    }
#endif
    ENGINE_FUNCTION(profiler::colors::Orange);
#ifdef PIXELENGINE_STATISTICS
    auto stats_checkUserEvent_timer_start = std::chrono::system_clock::now();
#endif
    removeGameObjectsIntern();
    m_display->handleEvents();
    if(m_display->getRenderWindow()->hasFocus())
        for(auto pair : m_eventContainer)
            pair.second->checkEvent(); // Check keyEvents only if the window has focus

    vector<sf::Event> eventList = m_display->getLastEvents();
    ENGINE_BLOCK("userCheckEventLoop",profiler::colors::Orange50);
    if(m_p_func_userCheckEventLoop != nullptr)
        (*m_p_func_userCheckEventLoop)(m_eventInterval,m_tick,eventList);
    ENGINE_END_BLOCK;

#ifdef PIXELENGINE_STATISTICS
    auto stats_checkEvent_timer_start = std::chrono::system_clock::now();
    std::chrono::duration<float> time_span_checkUserEvent_time = stats_checkEvent_timer_start - stats_checkUserEvent_timer_start;
    filter(m_statistics.checkUserEventTime,time_span_checkUserEvent_time.count()*1000.f,m_statsFilterFactor);
#endif

    // Handle display Events
    for(size_t i=0;i<eventList.size(); i++)
    {
        switch(eventList[i].type)
        {
            case sf::Event::Closed:
            {
                ENGINE_BLOCK("sf::Event::Closed",profiler::colors::Orange);
                stop();

                return;
            }
            default:
            {

            }
        }
    }
#ifdef PIXELENGINE_ENABLE_GAME_OBJECT_EVENTS
#ifdef PIXELENGINE_STATISTICS
    stats_checkEvent_timer_start = std::chrono::system_clock::now();
#endif
    ENGINE_BLOCK("getGameObject->checkEvent",profiler::colors::Orange50);
    GameObject *obj;
    for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
    {
        obj = m_masterGameObjectGroup[i]->getGameObject();
        if(obj->hasEventsToCheck())
            obj->engineCalled_checkEvent();
    }
    ENGINE_END_BLOCK;

#ifdef PIXELENGINE_STATISTICS
    auto stats_checkEvent_timer_end = std::chrono::system_clock::now();
    std::chrono::duration<float> time_span_checkEvent_time = stats_checkEvent_timer_end - stats_checkEvent_timer_start;
    filter(m_statistics.checkEventTime,time_span_checkEvent_time.count()*1000.f,m_statsFilterFactor);
#endif
#endif
}
void PixelEngine::tick()
{
#ifndef PIXELENGINE_NO_TIMED_LOOPS
    if(m_runInSync)
    {
        if(!m_nextSyncLoopActive)
            return;
    }else if(!m_mainTickTimer->start(m_mainTickInterval))
        return; // Time not finished
#endif
     ENGINE_FUNCTION(profiler::colors::Orange100);

#ifdef PIXELENGINE_STATISTICS
    m_statistics.objectsInEngine = m_masterGameObjectGroup.size();
    auto stats_userTick_timer_start = std::chrono::system_clock::now();
#endif
    ENGINE_BLOCK("userTickLoop",profiler::colors::Orange200);
    if(m_p_func_userTickLoop != nullptr)
        (*m_p_func_userTickLoop)(m_mainTickInterval,m_tick);
    ENGINE_END_BLOCK;
    m_tick++;
#ifdef PIXELENGINE_STATISTICS

    m_statistics.collisionsPerTick      = 0;
    m_statistics.collisionChecksPerTick = 0;
    m_statistics.gameObjectTickTime     *= m_statsFilterFactor;
    m_statistics.collisionCheckTime     *= m_statsFilterFactor;
    m_statistics.preDisplayTime         *= m_statsFilterFactor;
    auto stats_tick_timer_start = std::chrono::system_clock::now();
    std::chrono::duration<float> time_span_userEventEvent_time = stats_tick_timer_start - stats_userTick_timer_start;
    filter(m_statistics.userTickTime, time_span_userEventEvent_time.count()*1000.f,m_statsFilterFactor);
#endif

    ENGINE_DEEP_TICK_BLOCK("tick X-Y",profiler::colors::Orange200);
    tickX();
    tickY();
    ENGINE_DEEP_TICK_END_BLOCK;

#ifdef PIXELENGINE_STATISTICS
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
    ENGINE_DEEP_TICK_FUNCTION(profiler::colors::Orange300);
    tickXY(Vector2i(1,0));
}
void PixelEngine::tickY()
{
    ENGINE_DEEP_TICK_FUNCTION(profiler::colors::Orange300);
    tickXY(Vector2i(0,1));
}
void PixelEngine::tickXY(const Vector2i &dirLock)
{
    ENGINE_DEEP_TICK_FUNCTION(profiler::colors::Orange400);
#ifdef PIXELENGINE_USE_THREADS
    if(!m_threadsCreated)
    {
        ENGINE_DEEP_TICK_BLOCK("Create Threads",profiler::colors::Orange500);
        unsigned int threadAmount = std::thread::hardware_concurrency();
        if(threadAmount > 4)
            threadAmount -= 2;
        if(threadAmount == 0)
        {
            if(m_masterGameObjectGroup.size() >= 4)
                threadAmount = 4;
            else
                threadAmount = 1;
        }
        qDebug() << "create "<<threadAmount<< " Threads";
        for(unsigned int i=0; i<threadAmount; i++)
        {
            m_threadParamList.push_back(new ThreadParam());
            m_threadParamList[m_threadParamList.size()-1]->index = i;
            m_threadParamList[m_threadParamList.size()-1]->isRunning = false;
            m_threadParamList[m_threadParamList.size()-1]->drawingEnabled = m_drawingEnabled;
            m_threadParamList[m_threadParamList.size()-1]->globalMutex = &m_threadGlobalMutex;
#ifdef PIXELENGINE_STATISTICS
            m_threadParamList[m_threadParamList.size()-1]->stats = &m_statistics;
            m_threadParamList[m_threadParamList.size()-1]->statsFilter = m_statsFilterFactor;
#endif
            m_threadParamList[m_threadParamList.size()-1]->mutex = PTHREAD_MUTEX_INITIALIZER;
            m_threadParamList[m_threadParamList.size()-1]->cv = &cv;
            m_threadParamList[m_threadParamList.size()-1]->exit = &threadExit;
            m_std_threadList.push_back(new pthread_t());
            int rc = pthread_create(m_std_threadList[i], nullptr, &PixelEngine::thread_tick, static_cast<void *>(m_threadParamList[m_threadParamList.size()-1]));


        }
        sf::sleep(sf::milliseconds(2));
        m_threadsCreated = true;
        m_thread_lastObjAmount = 0;
    }
    size_t threadAmount = m_std_threadList.size();



    if(m_masterGameObjectGroup.size() != m_thread_lastObjAmount)
    {
        ENGINE_DEEP_TICK_BLOCK("Ajust Threads",profiler::colors::Orange500);
       // qDebug() << "Ajust Threads";
        size_t iterator = 0;
        size_t objectAmount = m_masterGameObjectGroup.size();
        size_t objPerThread = objectAmount/threadAmount;
        for(size_t i=0; i<threadAmount; i++)
        {
            if(i == threadAmount-1)
               objPerThread =  objectAmount - iterator;

            m_threadParamList[i]->obj_begin = iterator;
            m_threadParamList[i]->obj_end = iterator + objPerThread;
            m_threadParamList[i]->group = &m_masterGameObjectGroup;
            m_threadParamList[i]->isRunning = false;

            iterator += objPerThread;
        }
        m_thread_lastObjAmount = objectAmount;
    }
    ENGINE_DEEP_TICK_BLOCK("Set Thread parameter",profiler::colors::Orange500);
    for(size_t i=0; i<threadAmount; i++)
    {
        m_threadParamList[i]->dirLock = dirLock;
    }
    ENGINE_DEEP_TICK_END_BLOCK;
    ENGINE_DEEP_TICK_BLOCK("Enable Threads",profiler::colors::Orange500);


    for(size_t i=0; i<threadAmount; i++)
    {
        pthread_mutex_lock(&m_threadParamList[i]->mutex);
        m_threadParamList[i]->isRunning = true;
        pthread_mutex_unlock(&m_threadParamList[i]->mutex);
    }

    pthread_mutex_lock(&m_threadGlobalMutex);
    pthread_cond_broadcast( &cv );
    pthread_mutex_unlock(&m_threadGlobalMutex);


    ENGINE_DEEP_TICK_END_BLOCK;

    bool isRunning = false;

    ENGINE_DEEP_TICK_BLOCK("Wait for Threads",profiler::colors::Orange500);
    size_t finishedCounter = 0;
    while(finishedCounter != m_threadParamList.size())
    {
        ENGINE_DEEP_TICK_BLOCK("Wait",profiler::colors::Orange500);
        isRunning = true;
        finishedCounter = 0;
        for(size_t i=0; i<m_threadParamList.size(); i++)
        {
            pthread_mutex_lock(&m_threadGlobalMutex);
            isRunning = m_threadParamList[i]->isRunning;
            pthread_mutex_unlock(&m_threadGlobalMutex);
            if(!isRunning)
                finishedCounter++;
        }
        ENGINE_DEEP_TICK_END_BLOCK;
    }
    ENGINE_DEEP_TICK_END_BLOCK;
#else
    for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
    {
        ENGINE_DEEP_TICK_BLOCK("For each m_masterGameObjectGroup index",profiler::colors::Orange500);
        InteractiveGameObject* interactiveObject = m_masterGameObjectGroup[i];
        GameObject *obj = interactiveObject->getGameObject();
#ifdef PIXELENGINE_STATISTICS
        auto stats_timer_start = std::chrono::system_clock::now();

#endif
        if(dirLock.x)
            interactiveObject->engineCalled_preTick();
        obj->engineCalled_tick(dirLock);

#ifdef PIXELENGINE_STATISTICS
        auto stats_timer_end = std::chrono::system_clock::now();
        std::chrono::duration<float> stats_time_span = stats_timer_end - stats_timer_start;
        m_statistics.gameObjectTickTime += stats_time_span.count()*1000.f*(1.f-m_statsFilterFactor);
        stats_timer_start = std::chrono::system_clock::now();
#endif
        m_statistics.collisionsPerTick += obj->checkCollision(interactiveObject->getInteractiveObjects());

        if(dirLock.y)
            interactiveObject->engineCalled_postTick();
#ifdef PIXELENGINE_STATISTICS
        stats_timer_end = std::chrono::system_clock::now();
        stats_time_span = stats_timer_end - stats_timer_start;
        m_statistics.collisionCheckTime += stats_time_span.count()*1000.f*(1.f-m_statsFilterFactor);
#endif
        if(m_drawingEnabled)
        {
            if(dirLock.y)
                interactiveObject->engineCalled_preDraw();

#ifdef PIXELENGINE_STATISTICS
        stats_timer_start = std::chrono::system_clock::now();
        stats_time_span   = stats_timer_start - stats_timer_end;
        m_statistics.collisionCheckTime    += stats_time_span.count()*1000*(1.f-m_statsFilterFactor);
#endif
        }
    }

#endif

}
#ifdef PIXELENGINE_USE_THREADS
void *PixelEngine::thread_tick(void *p)
{
    THREAD("thread_tick");
    struct ThreadParam *param;
    param = static_cast<struct ThreadParam *>(p);
#ifdef PIXELENGINE_DBUG_THREAD
    string threadIdentifier = "Thread: "+std::to_string(param->index);
    qDebug() << "thread_tick: "<<threadIdentifier.c_str();
#endif
    bool exit = false;
    try {
#ifdef PIXELENGINE_STATISTICS
    std::chrono::system_clock::time_point stats_timer_start;
    std::chrono::system_clock::time_point stats_timer_end;
    std::chrono::duration<float> stats_time_span;
#endif
    while(!exit)
    {

        THREAD_BLOCK("waiting");
#ifdef PIXELENGINE_DBUG_THREAD
        qDebug() << threadIdentifier.c_str() << " waiting";
#endif
        pthread_mutex_lock(&param->mutex);
        pthread_mutex_unlock(&param->mutex);
        pthread_mutex_lock(param->globalMutex);
        param->isRunning = false;
        pthread_cond_wait( param->cv, param->globalMutex);
        exit = *param->exit;
        pthread_mutex_unlock(param->globalMutex);
        if(exit)
            break;


        THREAD_END_BLOCK;
        THREAD_BLOCK("working");
#ifdef PIXELENGINE_DBUG_THREAD
        qDebug() << threadIdentifier.c_str() << " working";
#endif
#ifdef PIXELENGINE_STATISTICS
        unsigned long collisionsPerTick = 0;
        double gameObjectTickTime = 0;
        double collisionCheckTime = 0;
        double preDisplayTime = 0;
#endif
        for(size_t i=param->obj_begin; i<param->obj_end; i++)
        {
            THREAD_BLOCK("For each m_masterGameObjectGroup index",profiler::colors::Orange500);
            InteractiveGameObject* interactiveObject = (*param->group)[i];
            GameObject *obj = interactiveObject->getGameObject();
    #ifdef PIXELENGINE_STATISTICS
            stats_timer_start = std::chrono::system_clock::now();
    #endif
            if(param->dirLock.x)
                interactiveObject->engineCalled_preTick();
            obj->engineCalled_tick(param->dirLock);

#ifdef PIXELENGINE_STATISTICS
         stats_timer_end = std::chrono::system_clock::now();
         stats_time_span = stats_timer_end - stats_timer_start;
         gameObjectTickTime += stats_time_span.count();
#endif
#ifdef PIXELENGINE_ENABLE_COLLISION
   #ifdef PIXELENGINE_STATISTICS
            stats_timer_start = std::chrono::system_clock::now();
            if(interactiveObject->doesInteractWithOther())
            {
                vector<GameObject*> other = interactiveObject->getInteractiveObjects();
                collisionsPerTick += obj->checkCollision(other);
            }
        stats_timer_end     = std::chrono::system_clock::now();
        stats_time_span     = stats_timer_end - stats_timer_start;
        collisionCheckTime += stats_time_span.count();

    #else
            if(interactiveObject->doesInteractWithOther())
            {
                vector<GameObject*> other = interactiveObject->getInteractiveObjects();
                obj->checkCollision(other);
            }
    #endif
#endif
            if(param->dirLock.y)
                interactiveObject->engineCalled_postTick();

            if(param->drawingEnabled)
            {
                if(param->dirLock.y)
                    interactiveObject->engineCalled_preDraw();

    #ifdef PIXELENGINE_STATISTICS
            stats_timer_start = std::chrono::system_clock::now();
            stats_time_span   = stats_timer_start - stats_timer_end;
            preDisplayTime    += stats_time_span.count();
    #endif

            }
        }

    #ifdef PIXELENGINE_STATISTICS
        pthread_mutex_lock(param->globalMutex);
        param->stats->collisionsPerTick  += collisionsPerTick;
        param->stats->collisionCheckTime += collisionCheckTime*1000.f*(1.f-param->statsFilter);
        param->stats->gameObjectTickTime += gameObjectTickTime*1000.f*(1.f-param->statsFilter);
        param->stats->preDisplayTime     += preDisplayTime*1000.f*(1.f-param->statsFilter);
        pthread_mutex_unlock(param->globalMutex);
    #endif
        THREAD_END_BLOCK;
        THREAD_BLOCK("ende");
#ifdef PIXELENGINE_DBUG_THREAD
        qDebug() << threadIdentifier.c_str() << " ende";
#endif

        THREAD_END_BLOCK;
    }
    }  catch (...) {
        qDebug() << "Thread error: Thread: "<<param->index;
    }
#ifdef PIXELENGINE_DBUG_THREAD
        qDebug() << threadIdentifier.c_str() << " closing";
#endif
    THREAD_BLOCK("closing");
    sf::sleep(sf::milliseconds(1));
    THREAD_END_BLOCK;
    pthread_exit(nullptr);
}
#endif
void PixelEngine::updateText()
{
    ENGINE_FUNCTION(profiler::colors::Orange600);
#ifdef PIXELENGINE_STATISTICS
    if(m_stats_text->isVisible())
        updateStatsText();
#endif
}


void PixelEngine::removeObjectFromList(GameObjectGroup &group,GameObject* obj)
{
    ENGINE_FUNCTION(profiler::colors::Orange800);
    group.remove(obj);
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup> &list,GameObject* obj)
{
    ENGINE_FUNCTION(profiler::colors::Orange800);
    for(size_t i=0; i<list.size(); i++)
    {
        list[i].remove(obj);
    }
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup> &list,GameObjectGroup *obj)
{
    ENGINE_FUNCTION(profiler::colors::Orange800);
    for(size_t i=0; i<(*obj).size(); i++)
    {
        PixelEngine::removeObjectFromList(list,(*obj)[i]);
    }
}
void PixelEngine::removeObjectFromList(GameObjectGroup* &group,GameObject* obj)
{
    ENGINE_FUNCTION(profiler::colors::Orange800);
    group->remove(obj);
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup*> &list,GameObject* obj)
{
    ENGINE_FUNCTION(profiler::colors::Orange800);
    for(size_t i=0; i<list.size(); i++)
    {
        list[i]->remove(obj);
    }
}
void PixelEngine::removeObjectFromList(vector<GameObjectGroup*> &list,GameObjectGroup *obj)
{
    ENGINE_FUNCTION(profiler::colors::Orange800);
    for(size_t i=0; i<(*obj).size(); i++)
    {
        PixelEngine::removeObjectFromList(list,(*obj)[i]);
    }
}
void PixelEngine::adding(GameObjectGroup* sender,GameObject* obj)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA200);
    if(obj->getEventHandler() != this && !obj->isTrash())
        this->addGameObject(obj);
    qDebug() << "engine sender: "<<sender << " adding: "<<obj;
}

void PixelEngine::adding(GameObjectGroup* sender,GameObjectGroup* group)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA200);
    GameObjectGroup::removinguplicates(group);
    addGameObjectIntern(group->getVector());
}

void PixelEngine::removing(GameObjectGroup* sender,GameObject* obj)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA400);
    qDebug() << "engine sender: "<<sender << " removing: "<<obj;
}

void PixelEngine::removing(GameObjectGroup* sender,GameObjectGroup* group)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA400);

}
void PixelEngine::willBeCleared(GameObjectGroup* sender)
{

}
void PixelEngine::cleared(GameObjectGroup* sender)
{

}

void PixelEngine::display()
{
#ifndef PIXELENGINE_NO_TIMED_LOOPS
    if(m_runInSync)
    {
        if(!m_nextSyncLoopActive)
            return;
        m_nextSyncLoopActive = false;
    }else if(!m_displayTimer->start(m_displayInterval))
        return;
#endif
    ENGINE_FUNCTION(profiler::colors::Orange900);

#ifdef PIXELENGINE_STATISTICS
    auto stats_timePoint_1 = std::chrono::system_clock::now();
#endif
    ENGINE_BLOCK("userDisplayLoop",profiler::colors::OrangeA100)
    if(m_p_func_userDisplayLoop != nullptr)
        (*m_p_func_userDisplayLoop)(m_displayInterval,m_tick,*m_display);
    ENGINE_END_BLOCK;

    updateText();
    m_display->display();

#ifdef PIXELENGINE_STATISTICS
    m_stats_fps_timer_end = std::chrono::system_clock::now();
    std::chrono::duration<float> m_time_span_display_time = m_stats_fps_timer_end - stats_timePoint_1;
    filter(m_statistics.displayTime, m_time_span_display_time.count()*1000.f,m_statsFilterFactor);

    std::chrono::duration<float> time_span = m_stats_fps_timer_end - m_stats_fps_timer_start;
    m_stats_fps_timer_start = std::chrono::system_clock::now();
    if(time_span.count() != 0.f)
        filter(m_statistics.framesPerSecond, 1.f/time_span.count(),m_statsFilterFactor);
#endif
}
const vector<sf::Event> &PixelEngine::getLastEvents() const
{
    return m_display->getLastEvents();
}
void PixelEngine::set_setting_runInSync(bool enable)
{
    m_runInSync = enable;
}
bool PixelEngine::get_setting_runInSync() const
{
    return m_runInSync;
}
void PixelEngine::set_setting_syncEngineInterval(const float &seconds)
{
    m_syncInterval = abs(seconds);
}
const float &PixelEngine::get_setting_syncEngineInterval() const
{
    return m_syncInterval;
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
    ENGINE_FUNCTION(profiler::colors::OrangeA200);
    for(size_t i=0; i<m_masterGameObjectGroup.size(); i++)
        if(m_masterGameObjectGroup[i]->getGameObject() == obj)
            return; // Object already added to list

    if(!m_setupDone)
        m_masterGameObjectGroup.addToCache(obj);
    else
    {
        if(m_masterGameObjectGroup.add(obj))
        {
            if(!obj->isBoundingBoxUpdated())
                obj->updateBoundingBox();
            obj->setEventHandler(this);
            obj->setDisplayInterface(m_display);
            m_masterGameObjectGroup[m_masterGameObjectGroup.size()-1]->subscribeToDisplay(*m_display);
            obj->engineCalled_setup();
        }
    }
}

void PixelEngine::addGameObject(GameObjectGroup *group)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA200);
    addGameObjectIntern(group->getVector());
    group->subscribe_GroupSignal(this);
}
void PixelEngine::addGameObjectIntern(const vector<GameObject *> &list)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA200);
    m_masterGameObjectGroup.reserve(list.size());
    for(size_t i=0; i<list.size(); i++)
        this->addGameObject(list[i]);
}
void PixelEngine::removeGameObject(GameObject *obj)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA400);
    m_removeLaterObjectGroup.push_back(obj);
}
void PixelEngine::removeGameObject(GameObjectGroup *group)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA400);
    m_removeLaterObjectGroup.reserve(m_removeLaterObjectGroup.size()+group->size());
    for(size_t i=0; i<group->size(); i++)
    {
        this->removeGameObject((*group)[i]);
    }
    for(size_t i=0; i<m_userGroups.size(); i++)
    {
        if(m_userGroups[i] == group)
            m_userGroups.erase(m_userGroups.begin() + i);
    }
    group->unsubscribe_GroupSignal(this);
}

void PixelEngine::removeGameObjectsIntern()
{
    ENGINE_FUNCTION(profiler::colors::OrangeA400);
    if(m_removeLaterObjectGroup.size() == 0)
        return;
    for(GameObject* &obj : m_removeLaterObjectGroup)
    {
        obj->setEventHandler(nullptr);
        obj->setDisplayInterface(nullptr);
        m_masterGameObjectGroup.removeAllInteractionsWithObj(obj);
        m_masterGameObjectGroup.remove(obj);
        removeObjectFromList(m_userGroups,obj);

        obj->unsubscribeToDisplay(*m_display);

        obj->markAsTrash(true);
        obj->unsubscribeAll_ObjSignal();
        m_trashList.add(obj->getThisInteractiveGameObject());
    }
    m_removeLaterObjectGroup.clear();
    m_removeLaterObjectGroup.reserve(10);
}

void PixelEngine::setCollisionSingleInteraction(GameObject *obj1,GameObject *obj2, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    if(obj1 == obj2)
        return; // Cann't collide with it self

    InteractiveGameObject *interactive_1 = m_masterGameObjectGroup.getInteractiveObject(obj1);
    interactive_1->setInteractionWith(obj2,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(GameObject *obj1,GameObjectGroup *obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    InteractiveGameObject *interactive_1 = m_masterGameObjectGroup.getInteractiveObject(obj1);
    interactive_1->setInteractionWith(obj2List,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(GameObjectGroup *obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj1List->size(); i++)
        this->setCollisionSingleInteraction((*obj1List)[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(GameObject *obj1, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
   for(size_t i=0; i<obj2List.size(); i++)
       this->setCollisionSingleInteraction(obj1,obj2List[i],doesCollide); // Not very efficient code ;)
}
void PixelEngine::setCollisionSingleInteraction(GameObjectGroup *obj1List,const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj1List->size(); i++)
        this->setCollisionSingleInteraction((*obj1List)[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(const vector<GameObject*> &obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj1List.size(); i++)
        this->setCollisionSingleInteraction(obj1List[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionSingleInteraction(const vector<GameObject*> &obj1List, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj1List.size(); i++)
        this->setCollisionSingleInteraction(obj1List[i],obj2List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObject *obj1,GameObject *obj2, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    this->setCollisionSingleInteraction(obj1,obj2, doesCollide);
    this->setCollisionSingleInteraction(obj2,obj1, doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObject *obj1,GameObjectGroup *obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    InteractiveGameObject *interactive_1 = m_masterGameObjectGroup.getInteractiveObject(obj1);
    interactive_1->setInteractionWith(obj2List,doesCollide);
    for(size_t i=0; i<obj2List->size(); i++)
        this->setCollisionSingleInteraction(obj2List->getVector()[i],obj1, doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObjectGroup *obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    setCollisionSingleInteraction(obj1List,obj2List,doesCollide);
    setCollisionSingleInteraction(obj2List,obj1List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(GameObject *obj1, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj2List.size(); i++)
        this->setCollisionMultiInteraction(obj1,obj2List[i],doesCollide); // Not very efficient code ;)
}
void PixelEngine::setCollisionMultiInteraction(GameObjectGroup *obj1List,const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    this->setCollisionSingleInteraction(obj2List,obj1List,doesCollide);
    this->setCollisionSingleInteraction(obj1List,obj2List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(const vector<GameObject*> &obj1List,GameObjectGroup *obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    this->setCollisionSingleInteraction(obj1List,obj2List,doesCollide);
    this->setCollisionSingleInteraction(obj2List,obj1List,doesCollide);
}
void PixelEngine::setCollisionMultiInteraction(const vector<GameObject*> &obj1List, const vector<GameObject*> &obj2List, const bool &doesCollide)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA700);
    for(size_t i=0; i<obj1List.size(); i++)
        this->setCollisionMultiInteraction(obj1List[i],obj2List,doesCollide);
}





// Rendering
void PixelEngine::display_zoomView(const Vector2i &zoomAt, float zoom)
{
    m_display->zoomViewAt(zoomAt,zoom);
}
void PixelEngine::setLayerVisibility(size_t layer, bool visibility)
{
    m_display->setLayerVisibility(layer,visibility);
}
bool PixelEngine::getLayerVisibility(size_t layer)
{
    return m_display->getLayerVisibility(layer);
}

// GameObject Events from GameObjectEventHandler
void PixelEngine::kill(GameObject *obj)
{
    ENGINE_FUNCTION(profiler::colors::Orange50);
}
void PixelEngine::removeFromEngine(GameObject *obj)
{
    ENGINE_FUNCTION(profiler::colors::OrangeA400);
    this->removeGameObject(obj);
}
void PixelEngine::collisionOccured(GameObject *obj1,vector<GameObject *> obj2)
{
    ENGINE_FUNCTION(profiler::colors::Orange100);
}
void PixelEngine::addPainterToDisplay(Painter *painter)
{
    ENGINE_FUNCTION(profiler::colors::Orange200);
    m_display->subscribePainter(painter);
};
void PixelEngine::removePainterFromDisplay(Painter *painter)
{
    ENGINE_FUNCTION(profiler::colors::Orange300);
    m_display->unsubscribePainter(painter);
};
void PixelEngine::addEvent(Event *event)
{
    ENGINE_FUNCTION(profiler::colors::Orange300);
    m_eventContainer.insert({event,event});
    m_statistics.eventsInEngine = m_eventContainer.size();
}
void PixelEngine::removeEvent(Event *event)
{
    ENGINE_FUNCTION(profiler::colors::Orange300);
    m_eventContainer.erase(event);
    m_statistics.eventsInEngine = m_eventContainer.size();
}


// General functions
float PixelEngine::random(float min, float max)
{
    ENGINE_FUNCTION(profiler::colors::Orange400);
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
    return float((min*1000.0)+((seed*rand())%(long long)((max-min)*1000.0)))/1000.0;
}
long PixelEngine::randomL(long min, long max)
{
    ENGINE_FUNCTION(profiler::colors::Orange400);
    if(min == max)
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
    return min+seed*rand()%((max-min));
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
    ENGINE_FUNCTION(profiler::colors::Orange500);
#ifdef PIXELENGINE_STATISTICS
     m_stats_text->setVisibility(enable);
#endif
}
void PixelEngine::display_stats(bool enable, const Color &color)
{
    ENGINE_FUNCTION(profiler::colors::Orange600);
#ifdef PIXELENGINE_STATISTICS
    m_stats_text->setColor(color);
    display_stats(enable);
#endif
}
void PixelEngine::display_stats(bool enable,const Color &color, const Vector2i &pos, const unsigned int size)
{
    ENGINE_FUNCTION(profiler::colors::Orange600);
#ifdef PIXELENGINE_STATISTICS
    m_stats_text->setPos(Vector2f(pos));
    if(size > 0)
        m_stats_text->setCharacterSize(size);
    else
        m_stats_text->setCharacterSize(m_display->getWindowSize().x/80);
    display_stats(enable,color);
#endif
}
bool PixelEngine::display_stats()
{
#ifdef PIXELENGINE_STATISTICS
    return m_stats_text->isVisible();
#else
    return false;
#endif
}

void PixelEngine::resetStatistics()
{
    m_statistics.collisionChecksPerTick = 0;
    m_statistics.collisionsPerTick      = 0;
}
void PixelEngine::updateStatsText()
{
#ifdef PIXELENGINE_STATISTICS
    m_statistics.display = m_display->getStats();

    ENGINE_FUNCTION(profiler::colors::Orange700);
    std::string painterList = "";
    for(size_t i=0; i<m_statistics.display.avtivePaintersInLayer.size(); i++)
    {
        painterList += "    Layer: "+to_string(i+1) + "\t   \t\t" + to_string(m_statistics.display.avtivePaintersInLayer[i])+        " stk.\n";
    }
    std::string text =
     "Objects in engine:     \t" + to_string(m_statistics.objectsInEngine) +       " stk.\n"+
     "Events in engine:      \t" + to_string(m_statistics.eventsInEngine) +        " stk.\n"+
     "Ticks:                 \t" + to_string(m_statistics.ticksPerSecond) +        " /s\n"+
     "Display:\n"+
     "  Frames:              \t" + to_string(m_statistics.framesPerSecond) +        " /s\n"+
     "  Active painters:     \t" + to_string(m_statistics.display.activePainters)+        " stk.\n"+
     painterList +
     "  Draw sprites:        \t" + to_string(m_statistics.display.renderSprites) +        " stk.\n"+
     "  Draw vertex paths:   \t" + to_string(m_statistics.display.renderVertexPaths) +    " stk.\n"+
     "  Draw text:           \t" + to_string(m_statistics.display.renderText) +           " stk.\n"+
     "Collider:\n"+
     "  Check intersections: \t" + to_string(m_statistics.intersectionCheckPerTick)+" /Tick\n"+
     "  Intersecting:        \t" + to_string(m_statistics.doesIntersectPerTick) +   " /Tick\n"+
     "  Collision checks:    \t" + to_string(m_statistics.collisionChecksPerTick) + " /Tick\n"+
     "  Colliding:           \t" + to_string(m_statistics.collisionsPerTick) +      " /Tick\n"+
     "  Collision check time:\t" + to_string(m_statistics.collisionCheckTime) +     " ms\n"+
     "Engine Times:\n"+
     "  GameObject tick:     \t" + to_string(m_statistics.gameObjectTickTime) +     " ms\n"+
     "  Check event:         \t" + to_string(m_statistics.checkEventTime) +         " ms\n"+
     "  Tick:                \t" + to_string(m_statistics.tickTime) +               " ms\n"+
     "  Pre display:         \t" + to_string(m_statistics.preDisplayTime) +         " ms\n"+
     "  Display:             \t" + to_string(m_statistics.displayTime) +            " ms\n"+
     "User Times:\n"+
     "  User event:          \t" + to_string(m_statistics.checkUserEventTime) +     " ms\n"+
     "  User tick:           \t" + to_string(m_statistics.userTickTime) +           " ms\n"+
     "  User display:        \t" + to_string(m_statistics.userDisplayTime) +        " ms";
    m_stats_text->setString(text);
#endif
}
void PixelEngine::filter(float &oldValue, float newValue, float filterFactor)
{
    oldValue = oldValue * filterFactor + (1.f-filterFactor) * newValue;
}
