#ifndef PIXELENGINE_H
#define PIXELENGINE_H

#include "base.h"

#include "pixelDisplay.h"
#include "pixel.h"

#include "gameobject.h"
#include "gameObjectGroup.h"
#include "InteractiveGameObject.h"
#include "InteractiveGameObjectGroup.h"
#include "groupManagerInterface.h"
#include "engineInterface.h"

#include "collider.h"
#include "controller.h"
#include "keyController.h"
#include "dynamicCoordinator.h"
#include "spritePainter.h"
#include "texturePainter.h"
#include "pixelPainter.h"
#include "textPainter.h"
#include "property.h"
#include "sensor.h"
#include "texture.h"
#include "animatedTexture.h"

#include "event.h"
#include "keyboard.h"
#include "layeritem.h"
#include "rect.h"
#include "timer.h"
#include "userEventHandler.h"

#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <pthread.h>







typedef  void (*p_tickFunc)(float,unsigned long long);
typedef  void (*p_eventFunc)(float,unsigned long long,const vector<sf::Event>&);
typedef  void (*p_displayFunc)(float,unsigned long long,PixelDisplay&);


class PixelEngine   :   public EngineInterface, private GroupSignal
{


    public:
        struct Statistics
        {
            float  framesPerSecond;
            float  ticksPerSecond;
            unsigned long long intersectionCheckPerTick;
            unsigned long long doesIntersectPerTick;
            unsigned long long collisionChecksPerTick;
            unsigned long long collisionsPerTick;
            unsigned long long objectsInEngine;
            unsigned long long eventsInEngine;

            DisplayStats display;

            float  collisionCheckTime;
            float  gameObjectTickTime;
            float  checkEventTime;
            float  tickTime;
            float  preDisplayTime;
            float  displayTime;

            float  checkUserEventTime;
            float  userTickTime;
            float  userDisplayTime;
        };
        struct EngineSettings
        {

            bool  runInSync;
            float time_syncInterval;
            float time_eventInterval;
            float time_tickInterval;
            float time_displayInterval;

            float statsDisplayFilter;

        };

        struct Settings
        {
            EngineSettings                      engine;
            InteractiveGameObject::Settings     gameObject;
            PixelDisplay::Settings              display;
            TextPainter::Settings               text;
        };
        static EngineSettings __defaultEngineSettings;
        static Settings       __defaultSettings;

        PixelEngine();
        PixelEngine(const Settings &settings);
        PixelEngine(const Vector2u  &mapsize,const Vector2u  &displaySize);
        PixelEngine(const PixelEngine &other);
        virtual ~PixelEngine();

        static Settings getSettings();
        static void setSettings(const Settings &settings);

        virtual bool running(); // this returns false, if the window is closed.
        virtual void stop();

        virtual const Vector2u  &getWindowSize() const;
        virtual const Vector2u  &getMapSize() const;
        virtual const RectF &getRenderFrame() const;

        // Userloops
        virtual void setUserCheckEventLoop(p_eventFunc func);
        virtual void setUserDisplayLoop(p_displayFunc func);
        virtual void setUserTickLoop(p_tickFunc func);

        virtual void setup();

        virtual void loop();
        virtual void checkEvent();
        virtual void tick();
        virtual void display();

        virtual const vector<sf::Event> &getLastEvents() const;


        virtual void set_setting_runInSync(bool enable);
        virtual bool get_setting_runInSync() const;
        virtual void set_setting_syncEngineInterval(const float &seconds);
        virtual const float &get_setting_syncEngineInterval() const;
        virtual void set_setting_checkEventInterval(const float &seconds);
        virtual const float &get_setting_eventHandleInterval() const;
        virtual void set_setting_gameTickInterval(const float &seconds);
        virtual const float &get_setting_gameTickInterval() const;
        virtual void set_setting_displayInterval(const float &seconds);
        virtual const float &get_setting_displayInterval() const;

        virtual void addGameObject(GameObject *obj);
        virtual void addGameObject(GameObjectGroup *group);
        virtual void removeGameObject(GameObject *obj);
        virtual void removeGameObject(GameObjectGroup *group);

        // obj1 only interacts with obj2 not obj2 with obj1
        virtual void setCollisionSingleInteraction(GameObject                *obj1      ,GameObject                *obj2    , const bool &doesCollide = true);
        virtual void setCollisionSingleInteraction(GameObject                *obj1      ,GameObjectGroup           *obj2List, const bool &doesCollide = true);
        virtual void setCollisionSingleInteraction(GameObjectGroup           *obj1List  ,GameObjectGroup           *obj2List, const bool &doesCollide = true);
        virtual void setCollisionSingleInteraction(GameObject                *obj1      ,const vector<GameObject*> &obj2List, const bool &doesCollide = true);
        virtual void setCollisionSingleInteraction(GameObjectGroup           *obj1List  ,const vector<GameObject*> &obj2List, const bool &doesCollide = true);
        virtual void setCollisionSingleInteraction(const vector<GameObject*> &obj1List  ,GameObjectGroup           *obj2List, const bool &doesCollide = true);
        virtual void setCollisionSingleInteraction(const vector<GameObject*> &obj1List  ,const vector<GameObject*> &obj2List, const bool &doesCollide = true);

        // obj1 interacts with obj2 and other way around
        virtual void setCollisionMultiInteraction(GameObject                 *obj1      ,GameObject                *obj2    , const bool &doesCollide = true);
        virtual void setCollisionMultiInteraction(GameObject                 *obj1      ,GameObjectGroup           *obj2List, const bool &doesCollide = true);
        virtual void setCollisionMultiInteraction(GameObjectGroup            *obj1List  ,GameObjectGroup           *obj2List, const bool &doesCollide = true);
        virtual void setCollisionMultiInteraction(GameObject                 *obj1      ,const vector<GameObject*> &obj2List, const bool &doesCollide = true);
        virtual void setCollisionMultiInteraction(GameObjectGroup            *obj1List  ,const vector<GameObject*> &obj2List, const bool &doesCollide = true);
        virtual void setCollisionMultiInteraction(const vector<GameObject*>  &obj1List  ,GameObjectGroup           *obj2List, const bool &doesCollide = true);
        virtual void setCollisionMultiInteraction(const vector<GameObject*>  &obj1List  ,const vector<GameObject*> &obj2List, const bool &doesCollide = true);

        // Rendering
        virtual void display_zoomView(const Vector2i &zoomAt, float zoom);
        virtual void setLayerVisibility(size_t layer, bool visibility);
        virtual bool getLayerVisibility(size_t layer);

        // GameObject Events from EngineInterface
        // These functions will be called from the GameObject's
        virtual void kill(GameObject *obj);
        virtual void removeFromEngine(GameObject *obj);
        virtual void collisionOccured(GameObject *obj1,vector<GameObject *> obj2);
        virtual void addPainterToDisplay(Painter *painter);
        virtual void removePainterFromDisplay(Painter *painter);
        virtual void addEvent(Event *event);
        virtual void removeEvent(Event *event);
        virtual float getDeltaTime() const;

        // General functions
        static float random(float min, float max);
        static long randomL(long min, long max);
        virtual const unsigned long long &getTick() const;
        virtual void resetTick();

        // Stats
        virtual const Statistics &get_statistics() const;
        virtual void display_stats(bool enable);
        virtual void display_stats(bool enable,const Color &color);
        virtual void display_stats(bool enable,const Color &color, const Vector2i &pos, const unsigned int size = 0);
        virtual bool display_stats();
    protected:
        virtual void tickX();
        virtual void tickY();
        virtual void tickXY(const Vector2i &dirLock);
        virtual void updateText();

    private:
        void constructor(const Settings &settings);

        virtual void addGameObjectIntern(const vector<GameObject *> &list);
        virtual void setupObject(InteractiveGameObject *interObj);
        virtual void runtime_addGameObjectIntern();
        virtual void runtime_removeGameObjectsIntern();


        static void removeObjectFromList(GameObjectGroup &group,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup> &list,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup> &list,GameObjectGroup *obj);
        static void removeObjectFromList(GameObjectGroup* &group,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup*> &list,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup*> &list,GameObjectGroup *obj);

        // User List Signals
        virtual void adding(GameObjectGroup* sender,GameObject* obj);
        virtual void adding(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void removing(GameObjectGroup* sender,GameObject* obj);
        virtual void removing(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void willBeCleared(GameObjectGroup* sender);
        virtual void cleared(GameObjectGroup* sender);

        // Dummy func from GameObjectEngine_Interface
        void engineCalled_checkEvent(){};

        virtual void resetStatistics();
        virtual void updateStatsText();

        PixelDisplay *m_display;
        bool   m_engineIsRunning;
        bool   m_drawingEnabled;


        bool m_runInSync;
        bool m_nextSyncLoopActive;
        Timer *m_syncTimer;
        float m_syncInterval; // sec.
        Timer *m_eventTimer;
        float m_eventInterval; // sec.
        Timer *m_mainTickTimer;
        float m_mainTickInterval; // sec.
        Timer *m_displayTimer;
        float m_displayInterval; // sec.

        InteractiveGameObjectGroup  m_masterGameObjectGroup;
        HashTable<Event*>           m_eventContainer;

        HashTable<GameObject* >     m_addLaterObjectGroup;
        HashTable<GameObject* >     m_removeLaterObjectGroup;

        vector<GameObjectGroup>     m_renderLayer;
        InteractiveGameObjectGroup  m_trashList;

        vector<GameObjectGroup*>    m_userGroups;

        p_eventFunc m_p_func_userCheckEventLoop;
        p_displayFunc m_p_func_userDisplayLoop;
        p_tickFunc m_p_func_userTickLoop;

        unsigned long long m_tick;
        Timer m_mesureTickIntervalTimer;
        float m_realTickInterval;
        bool m_setupDone;


        // Statistics
        Statistics m_statistics;
        float m_statsFilterFactor;
        void filter(float &oldValue, float newValue, float filterFactor = 0.5);
        // -> Timing Stats
#ifdef PIXELENGINE_STATISTICS
        std::chrono::high_resolution_clock::time_point m_stats_fps_timer_start;
        std::chrono::high_resolution_clock::time_point m_stats_fps_timer_end;

        std::chrono::high_resolution_clock::time_point m_stats_tps_timer_start;
        std::chrono::high_resolution_clock::time_point m_stats_tps_timer_end;

        TextPainter *m_stats_text;
#endif

#ifdef PIXELENGINE_USE_THREADS
       struct ThreadParam{
                int index;
                bool drawingEnabled;
                Vector2i dirLock;
                size_t obj_begin;
                size_t obj_end;
                InteractiveGameObjectGroup *group;
                bool isRunning;
                pthread_mutex_t mutex;
                pthread_mutex_t *globalMutex;
                pthread_cond_t *cv;
                bool *exit;
#ifdef PIXELENGINE_STATISTICS
                Statistics *stats;
                float statsFilter;
#endif
        };
        vector<sf::Thread*> m_threadList;
        vector<ThreadParam*> m_threadParamList;
        size_t m_thread_lastObjAmount;
        // std thread test
        vector<pthread_t*> m_std_threadList;
        pthread_cond_t cv                   = PTHREAD_COND_INITIALIZER;
        pthread_mutex_t m_threadGlobalMutex = PTHREAD_MUTEX_INITIALIZER;
        bool threadExit = false;

        bool m_threadsCreated = false;
        bool m_threadGlobalStart = false;

        static void *thread_tick(void * p);
#endif
};
#endif // PIXELENGINE_H
