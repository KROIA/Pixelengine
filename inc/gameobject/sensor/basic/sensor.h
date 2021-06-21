#ifndef SENSOR_H
#define SENSOR_H

#include "gameobject.h"
#include "point.h"
#include "rect.h"
#include "hitboxPainter.h"

#include "profiler.h"

class Sensor
{
    public:
        Sensor();
        Sensor(const Sensor &other);

        virtual ~Sensor();
        virtual const Sensor &operator=(const Sensor &other);

        virtual void setOwner(GameObject *owner);
        virtual void setSensorCollider(Collider *collider);

        virtual void checkCollision(const vector<GameObject*> &other);
        virtual void draw(PixelDisplay &display);

        virtual const vector<GameObject*> &getDetectedObjects() const;

        virtual double getRotation() const;
        virtual void setRotation(const double &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();


    protected:
        Collider *m_sensorCollider;
        Painter  *m_sensorPainter;
        vector<GameObject*> m_detected;
        GameObject *m_owner;
    private:
};

#endif
