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

class PixelEngine
{
    public:
        PixelEngine();
        PixelEngine(const PixelEngine &other);
        virtual ~PixelEngine();

        virtual void tick();
        virtual void display();

        virtual void set_setting_gameTickInterval(const double &seconds);
        virtual void set_setting_displayInterval(const double &seconds);
        virtual void addGameObject(GameObject *obj);

        virtual void addGroup(const vector<GameObject*> &group);

        // General functions
        static double random(double min, double max);

    protected:
        virtual void tickX();
        virtual void tickY();
        virtual void tickXY(const Point &dirLock);

    private:
        PixelDisplay *m_display;
        Timer *m_mainTickTimer;
        double m_mainTickInterval; // sec.
        Timer *m_displayTimer;
        double m_displayInterval; // sec.

        vector<GameObject*> m_gameObjectGroup;
};
#endif // PIXELENGINE_H
