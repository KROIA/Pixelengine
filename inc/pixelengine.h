#ifndef PIXELENGINE_H
#define PIXELENGINE_H

#include "base.h"

#include "pixelDisplay.h"
#include "pixel.h"

#include "gameobject.h"
#include "gameObjectGroup.h"
#include "managedGameObjectGroup.h"
#include "InteractiveGameObject.h"
#include "InteractiveGameObjectGroup.h"
#include "groupManagerInterface.h"
#include "gameObjectEventHandler.h"
#include "chunkMap.h"

#include "collider.h"
#include "controller.h"
#include "keyController.h"
#include "painter.h"
#include "hitboxPainter.h"
#include "property.h"
#include "sensor.h"
#include "texture.h"
#include "animatedTexture.h"

#include "event.h"
#include "keyboard.h"
#include "layeritem.h"
#include "rect.h"
#include "point.h"
#include "timer.h"
#include "userEventHandler.h"

#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <pthread.h>

// When this is defined, all completely white pixels in an imported image
// are treated the same as alpha channel pixels
// Object-body is only there, where alpha-chanal-pixelValue > 0
//#define IMAGE_IMPORT_ALPHA_WHITE
#ifdef IMAGE_IMPORT_ALPHA_WHITE
// Set the uper limit for colors. all colors above/equal this value will be invisible
const Color __color_minimalAlphaColor(255,255,255);
#endif

//#define NO_TIMED_LOOPS
#define STATISTICS
#define USE_THREADS
#define USE_STD_THREADS

//#define DBUG_THREAD

#ifdef BUILD_WITH_EASY_PROFILER
    #define NO_TIMED_LOOPS
#endif


typedef  void (*p_tickFunc)(float,unsigned long long);
typedef  void (*p_eventFunc)(float,unsigned long long,const vector<sf::Event>&);
typedef  void (*p_displayFunc)(float,unsigned long long,PixelDisplay&);


class PixelEngine   :   public GameObjectEventHandler, private GroupSignal
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

            unsigned long long display_sprites;
            unsigned long long display_vertexPaths;
            unsigned long long display_text;

            float  collisionCheckTime;
            float  gameObjectTickTime;
            float  checkEventTime;
            float  tickTime;
            float  drawTime;
            float  displayTime;

            float  checkUserEventTime;
            float  userTickTime;
            float  userDisplayTime;
        };
        PixelEngine(const Vector2u  &mapsize,const Vector2u  &displaySize);
        PixelEngine(const PixelEngine &other);
        virtual ~PixelEngine();

        virtual bool running(); // this returns false, if the window is closed.
        virtual void stop();

        virtual const Vector2u  &getWindowSize() const;
        virtual const Vector2u  &getMapSize() const;
        virtual const RectF getRenderFrame() const;

        // Userloops
        virtual void setUserCheckEventLoop(p_eventFunc func);
        virtual void setUserDisplayLoop(p_displayFunc func);
        virtual void setUserTickLoop(p_tickFunc func);

        virtual void setup();

        virtual void checkEvent();
        virtual void tick();
        virtual void display();

        virtual const vector<sf::Event> &getLastEvents() const;

       // virtual void display_setRenderFramePosCenter(const Vector2f &pos);
       // virtual void display_moveRenderFrame(const Vector2f &vec);
       // virtual void display_setRenderFramePos(const Vector2f &pos);
       // virtual void display_setRenderFrame(const RectF &frame);
       // virtual const RectF &display_getRenderFrame() const;


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
        //virtual void deleteGameObject(GameObject *obj);
        //virtual void deleteGameObject(ManagedGameObjectGroup *group);

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

        // Groups
        //virtual void addGroup(GameObjectGroup *group);
        //virtual void removeGroup(GameObjectGroup *group); // Removes the Group from the engine.
        //virtual void deleteGroup(ManagedGameObjectGroup *group); // Removes the Group from the engine and deletes the pointer to the Group.

        // Rendering
        virtual void display_zoomView(const Vector2i &zoomAt, float zoom);
        virtual void moveRenderLayer_UP(GameObject *obj);
        virtual void moveRenderLayer_UP(GameObjectGroup *objGroup);
        virtual void moveRenderLayer_DOWN(GameObject *obj);
        virtual void moveRenderLayer_DOWN(GameObjectGroup *objGroup);
        virtual void setRenderLayer_BOTTOM(GameObject *obj);
        virtual void setRenderLayer_BOTTOM(GameObjectGroup *objGroup);
        virtual void setRenderLayer_TOP(GameObject *obj);
        virtual void setRenderLayer_TOP(GameObjectGroup *objGroup);

        // GameObject Events from GameObjectEventHandler
        // These functions will be called from the GameObject's
        virtual void kill(GameObject *obj);
        virtual void removeFromEngine(GameObject *obj);
        //virtual void deleteObject(GameObject *obj);
        virtual void collisionOccured(GameObject *obj1,vector<GameObject *> obj2);
        virtual void addDisplayText(DisplayText *text);
        virtual void removingisplayText(DisplayText *text);

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
        //virtual void checkForUserGroupChanges(); // Check if any Object of a adding List was removing or adding

    private:

        //virtual void addGameObject(GameObjectGroup *group); // won't add the list to de m_userGroups
        virtual void addGameObjectIntern(const vector<GameObject *> &list);
        virtual void removeGameObjectsIntern();
        //virtual void deleteGameObject(const vector<GameObject *> &list);


        static void removeObjectFromList(GameObjectGroup &group,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup> &list,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup> &list,GameObjectGroup *obj);
        static void removeObjectFromList(GameObjectGroup* &group,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup*> &list,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup*> &list,GameObjectGroup *obj);

        //static void removeObjectFromList_unmanaged(vector<ManagedGameObjectGroup*> &list,GameObject* obj);

        // User List Signals
        virtual void adding(GameObjectGroup* sender,GameObject* obj);
        virtual void adding(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void removing(GameObjectGroup* sender,GameObject* obj);
        virtual void removing(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void willBeCleared(GameObjectGroup* sender);
        virtual void cleared(GameObjectGroup* sender);

        virtual void resetStatistics();
        virtual void updateStatsText();

        PixelDisplay *m_display;
        bool   m_engineIsRunning;
        Vector2u m_windowSize;
        Vector2u  m_mapSize;

        Timer *m_eventTimer;
        float m_eventInterval; // sec.
        Timer *m_mainTickTimer;
        float m_mainTickInterval; // sec.
        Timer *m_displayTimer;
        float m_displayInterval; // sec.

        InteractiveGameObjectGroup  m_masterGameObjectGroup;
        GameObjectGroup             m_masterNoInteractionGameObjectList;
        vector<GameObject* >        m_removeLaterObjectGroup;
        //ChunkMap                   *m_chunkMap;

        vector<GameObjectGroup> m_renderLayer;
        InteractiveGameObjectGroup         m_trashList;

        vector<GameObjectGroup*> m_userGroups;

        p_eventFunc m_p_func_userCheckEventLoop;
        p_displayFunc m_p_func_userDisplayLoop;
        p_tickFunc m_p_func_userTickLoop;

        unsigned long long m_tick;
        bool m_setupDone;

        // Statistics
        Statistics m_statistics;
        float m_statsFilterFactor;
        void filter(float &oldValue, float newValue, float filterFactor = 0.5);
        // -> Timing Stats
#ifdef STATISTICS
        std::chrono::high_resolution_clock::time_point m_stats_fps_timer_start;
        std::chrono::high_resolution_clock::time_point m_stats_fps_timer_end;

        std::chrono::high_resolution_clock::time_point m_stats_tps_timer_start;
        std::chrono::high_resolution_clock::time_point m_stats_tps_timer_end;

        DisplayText *m_stats_text;
#endif

#ifdef USE_THREADS
        struct ThreadParam{
                int index;
                Vector2i dirLock;
                size_t obj_begin;
                size_t obj_end;
                InteractiveGameObjectGroup *group;
                bool isRunning;
#ifdef USE_STD_THREADS
                pthread_mutex_t mutex;
                pthread_mutex_t *globalMutex;
                pthread_cond_t *cv;
                bool *exit;
#else
                bool *globalStart;
                sf::Mutex mutex;
                sf::Mutex *globalMutex;
#endif
                Statistics *stats;
        };
        vector<sf::Thread*> m_threadList;
        vector<ThreadParam*> m_threadParamList;
        size_t m_thread_lastObjAmount;
#ifdef USE_STD_THREADS
        // std thread test
        vector<pthread_t*> m_std_threadList;
        pthread_cond_t cv                   = PTHREAD_COND_INITIALIZER;
        pthread_mutex_t m_threadGlobalMutex = PTHREAD_MUTEX_INITIALIZER;
        bool threadExit = false;
#else
        sf::Mutex m_threadGlobalMutex;
#endif

        bool m_threadsCreated = false;
        bool m_threadGlobalStart = false;

        static void *thread_tick(void * p);
#endif
};
#endif // PIXELENGINE_H
