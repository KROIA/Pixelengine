#ifndef SENSOR_H
#define SENSOR_H

#include "gameobject.h"
#include "point.h"
#include "rect.h"
#include "hitboxPainter.h"

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

    protected:

    private:

        Collider *m_sensorCollider;
        Painter  *m_sensorPainter;
        vector<GameObject*> m_detected;
        GameObject *m_owner;
};

#endif
