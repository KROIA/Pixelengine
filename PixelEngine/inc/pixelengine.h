#ifndef PIXELENGINE_H
#define PIXELENGINE_H

#include "iostream"
#include "stdio.h"
#include "vector"
#include <windows.h>
#include <ctime>
#include <math.h>

#include "pixelDisplay.h"
#include "point.h"
#include "vector.h"
#include "timer.h"

#include "gameobject.h"
#include "gameObjectGroup.h"

typedef  void (*p_func)(double);

class PixelEngine
{
    public:
        PixelEngine(const PointU &mapsize,const PointU &displaySize);
        PixelEngine(const PixelEngine &other);
        virtual ~PixelEngine();

        virtual const PointU &getWindwoSize() const;
        virtual const PointU &getMapSize() const;

        // Userloops
        virtual void setUserDisplayLoop(p_func func);
        virtual void setUserTickLoop(p_func func);

        virtual void tick();
        virtual void display();

        virtual void set_setting_gameTickInterval(const double &seconds);
        virtual const double &get_setting_gameTickInterval() const;
        virtual void set_setting_displayInterval(const double &seconds);
        virtual const double &get_setting_displayInterval() const;


        virtual void addGameObject(GameObject *obj);
        virtual void addGameObject(const vector<GameObject*> &group);
        virtual void removeGameObject(GameObject *toRemove);
        virtual void removeGameObject(const vector<GameObject*> &toRemoveGroup);

        // General functions
        static double random(double min, double max);
        static bool   loadFromImage(const std::string &picture,Collider *collider,Painter *painter);

    protected:
        virtual void tickX();
        virtual void tickY();
        virtual void tickXY(const Point &dirLock);

    private:
        PixelDisplay *m_display;
        PointU m_windowSize;
        PointU m_mapSize;

        Timer *m_mainTickTimer;
        double m_mainTickInterval; // sec.
        Timer *m_displayTimer;
        double m_displayInterval; // sec.

        GameObjectGroup m_gameObjectGroup;

        p_func m_p_func_userDisplayLoop;
        p_func m_p_func_userTickLoop;

};
#endif // PIXELENGINE_H
