#ifndef SENSOR_H
#define SENSOR_H

#include "gameobject.h"
#include "point.h"
#include "rect.h"
#include "pixelPainter.h"
//#include "hitboxPainter.h"

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

        virtual float getRotation() const;
        virtual void rotate(const float &deg);
        virtual void setRotation(const float &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();

        virtual void showBoundingBox(bool enable);


    protected:
        Collider *m_sensorCollider;
        PixelPainter  *m_sensorPainter;
        vector<GameObject*> m_detected;
        GameObject *m_owner;

        bool m_boundingBoxIsVisible;
    private:
};

#endif
