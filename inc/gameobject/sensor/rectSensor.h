#ifndef RECTSENSOR_H
#define RECTSENSOR_H

#include "base.h"
#include "sensor.h"
#include "colliderPainter.h"

class RectSensor    :   public Sensor
{
    public:
        RectSensor();
        RectSensor(const RectSensor &other);
        ~RectSensor();
        const RectSensor &operator=(const RectSensor &other);

       /* void engineCalled_preTick();
        void engineCalled_tick(const Vector2i &direction);
        void engineCalled_postTick();*/


        void setRect(const RectF rect);

        void engineCalled_preTick();
        void detectObjects(const vector<GameObject*> &other);
        void engineCalled_postTick();
        void engineCalled_preDraw();

        void setDetectedColor(const Color &color);
        void setSensorColor(const Color &color);

        void setVisibility(bool isVisible);
        void setVisibility_detectedObjects(bool isVisible);

        bool isVisible() const;
        bool isVisible_detectedObjects() const;

        //ColliderPainter *getColliderPainter() const;

    protected:
        Collider *m_sensorCollider;
        ColliderPainter *m_sensorPainter;

        Color m_detectedColor;
        Color m_sensorColor;
    private:

};
#endif // RECTSENSOR_H
