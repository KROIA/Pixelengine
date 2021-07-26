#ifndef SHAPESENSOR_H
#define SHAPESENSOR_H

#include "base.h"
#include "sensor.h"
#include "colliderPainter.h"

class ShapeSensor    :   public Sensor
{
    public:
        ShapeSensor();
        ShapeSensor(const ShapeSensor &other);
        ~ShapeSensor();
        const ShapeSensor &operator=(const ShapeSensor &other);

       /* void engineCalled_preTick();
        void engineCalled_tick(const Vector2i &direction);
        void engineCalled_postTick();*/


        void setShape(const Shape &shape);

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
#endif // SHAPESENSOR_H
