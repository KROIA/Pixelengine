#ifndef SENSOR_H
#define SENSOR_H

#include "base.h"

#include "gameobject.h"
#include "rect.h"
#include "pixelPainter.h"

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

        virtual void setVisibility_collider_boundingBox(bool isVisible);
        virtual bool isVisible_collider_boundingBox() const;


    protected:
        Collider *m_sensorCollider;
        //PixelPainter  *m_sensorPainter;
        vector<GameObject*> m_detected;
        GameObject *m_owner;

        bool m_visibility_collider_boundingBox;
    private:
};

#endif
