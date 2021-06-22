#ifndef PIXELENGINE_H
#define PIXELENGINE_H

#include "iostream"
#include "stdio.h"
#include "vector"
#include <windows.h>
#include <ctime>
#include <math.h>
#include <chrono>

#include "pixelDisplay.h"
#include "pixel.h"

#include "gameobject.h"
#include "gameObjectGroup.h"
#include "managedGameObjectGroup.h"
#include "InteractiveGameObject.h"
#include "InteractiveGameObjectGroup.h"
#include "groupManagerInterface.h"
#include "gameObjectEventHandler.h"

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
#include "vector.h"
#include "timer.h"
#include "userEventHandler.h"

#include "profiler.h"

// When this is defined, all completely white pixels in an imported image
// are treated the same as alpha channel pixels
// Object-body is only there, where alpha-chanal-pixelValue > 0
//#define IMAGE_IMPORT_ALPHA_WHITE
#ifdef IMAGE_IMPORT_ALPHA_WHITE
// Set the uper limit for colors. all colors above/equal this value will be invisible
const Color __color_minimalAlphaColor(255,255,255);
#endif

#define NO_TIMED_LOOPS
#define STATISTICS

#include "QDebug"


typedef  void (*p_func)(double,unsigned long long);


class PixelEngine   :   public GameObjectEventHandler//, protected GroupManagerInterface
{


    public:
        struct Statistics
        {
            double  framesPerSecond;
            double  ticksPerSecond;
            unsigned long collisionsPerTick;
            unsigned long collisionChecksPerTick;
            unsigned long objectsInEngine;

            double  collisionCheckTime;
            double  gameObjectTickTime;
            double  checkEventTime;
            double  tickTime;
            double  drawTime;
            double  displayTime;

            double  checkUserEventTime;
            double  userTickTime;
            double  userDisplayTime;
        };
        PixelEngine(const PointU &mapsize,const PointU &displaySize);
        PixelEngine(const PixelEngine &other);
        virtual ~PixelEngine();

        virtual bool running(); // this returns false, if the window is closed.

        virtual const PointU &getWindwoSize() const;
        virtual const PointU &getMapSize() const;

        // Userloops
        virtual void setUserCheckEventLoop(p_func func);
        virtual void setUserDisplayLoop(p_func func);
        virtual void setUserTickLoop(p_func func);

        virtual void checkEvent();
        virtual void tick();
        virtual void display();


        virtual void set_setting_checkEventInterval(const double &seconds);
        virtual const double &get_setting_eventHandleInterval() const;
        virtual void set_setting_gameTickInterval(const double &seconds);
        virtual const double &get_setting_gameTickInterval() const;
        virtual void set_setting_displayInterval(const double &seconds);
        virtual const double &get_setting_displayInterval() const;

        virtual void addGameObject(GameObject *obj);
        virtual void addGameObject(ManagedGameObjectGroup *group);
        virtual void removeGameObject(GameObject *obj);
        virtual void removeGameObject(ManagedGameObjectGroup *group);
        virtual void deleteGameObject(GameObject *obj);
        virtual void deleteGameObject(ManagedGameObjectGroup *group);

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
        virtual void addGroup(ManagedGameObjectGroup *group);
        virtual void removeGroup(ManagedGameObjectGroup *group); // Removes the Group from the engine.
        virtual void deleteGroup(ManagedGameObjectGroup *group); // Removes the Group from the engine and deletes the pointer to the Group.

        // Rendering
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
        virtual void deleteObject(GameObject *obj);
        virtual void collisionOccured(GameObject *obj1,vector<GameObject *> obj2);
        virtual void addDisplayText(DisplayText *text);
        virtual void removeDisplayText(DisplayText *text);

        // General functions
        static double random(double min, double max);
      //  static bool   loadFromImage(const std::string &picture,Collider *collider,Painter *painter,const ImageOrigin &origin = ImageOrigin::topLeftCorner);
      //  static bool   loadFromImage(const std::string &picture,Collider *collider,Painter *painter,const Point &origin);
        //static void   optimize_Hitboxes(vector<Rect> &input,vector<Rect> &outputColliderList,const Point origin);
        virtual const unsigned long long &getTick() const;
        virtual void resetTick();

        // Stats
        virtual const Statistics &get_statistics() const;
        virtual void display_stats(bool enable);
        virtual void display_stats(bool enable,const Color &color);
        virtual void display_stats(bool enable,const Color &color, const Point &pos, const unsigned int size = 0);
        virtual bool display_stats();
    protected:
        virtual void tickX();
        virtual void tickY();
        virtual void tickXY(const Point &dirLock);
        virtual void updateText();
        virtual void checkForUserGroupChanges(); // Check if any Object of a added List was removed or added

    private:
        virtual void addGameObject(GameObjectGroup *group); // won't add the list to de m_userGroups
        virtual void addGameObject(const vector<GameObject *> &list);
        virtual void removeGameObject(const vector<GameObject *> &list);
        virtual void deleteGameObject(const vector<GameObject *> &list);

       // static void optimize_HitboxMap(vector<vector<Rect*>  > &map,vector<Rect> &outputColliderList);


        static void removeObjectFromList(GameObjectGroup &group,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup> &list,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup> &list,GameObjectGroup *obj);
        static void removeObjectFromList(GameObjectGroup* &group,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup*> &list,GameObject* obj);
        static void removeObjectFromList(vector<GameObjectGroup*> &list,GameObjectGroup *obj);

        static void removeObjectFromList_unmanaged(vector<ManagedGameObjectGroup*> &list,GameObject* obj);

        virtual void resetStatistics();
        virtual void updateStatsText();

        PixelDisplay *m_display;
        bool   m_engineIsRunning;
        PointU m_windowSize;
        PointU m_mapSize;

        Timer *m_eventTimer;
        double m_eventInterval; // sec.
        Timer *m_mainTickTimer;
        double m_mainTickInterval; // sec.
        Timer *m_displayTimer;
        double m_displayInterval; // sec.

        //GameObjectGroup         m_masterGameObjectGroup;
        //vector<GameObjectGroup> m_masterGameObjectGroup_collisionInteractiveList;
        InteractiveGameObjectGroup  m_masterGameObjectGroup;

        vector<GameObjectGroup> m_renderLayer;

        vector<ManagedGameObjectGroup*> m_userGroups;

        p_func m_p_func_userCheckEventLoop;
        p_func m_p_func_userDisplayLoop;
        p_func m_p_func_userTickLoop;

        unsigned long long m_tick;

        // Statistics
        Statistics m_statistics;
        double m_statsFilterFactor;
        void filter(double &oldValue, double newValue, double filterFactor = 0.5);
        // -> Timing Stats
#ifdef STATISTICS
        std::chrono::high_resolution_clock::time_point m_stats_fps_timer_start;
        std::chrono::high_resolution_clock::time_point m_stats_fps_timer_end;

        std::chrono::high_resolution_clock::time_point m_stats_tps_timer_start;
        std::chrono::high_resolution_clock::time_point m_stats_tps_timer_end;

        DisplayText *m_stats_text;
#endif
};
#endif // PIXELENGINE_H
