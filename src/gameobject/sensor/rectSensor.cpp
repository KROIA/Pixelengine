#include "rectSensor.h"

RectSensor::RectSensor()
    :   Sensor()
{
    m_sensorCollider = new Collider();
    m_sensorPainter  = new ColliderPainter();
    m_sensorPainter->setCollider(m_sensorCollider);
    m_sensorPainter->setVisibility(true);
    m_sensorPainter->setVisibility_boundingBox(false);
    m_sensorPainter->setVisibility_hitBox(true);
    m_sensorPainter->setVisibility_collidedObjects(true);

    setDetectedColor(Color(0,100,255));
    setSensorColor(Color(0,255,0));

    setRect(RectF(0,0,1,1));
    Submodule::setCollider(m_sensorCollider);
    Submodule::addPainter(m_sensorPainter);
}
RectSensor::RectSensor(const RectSensor &other)
{
    m_sensorCollider = new Collider();
    Submodule::setCollider(m_sensorCollider);
    this->operator=(other);
}
RectSensor::~RectSensor()
{
    delete m_sensorCollider;
}
const RectSensor &RectSensor::operator=(const RectSensor &other)
{
    Sensor::operator=(other);
    *this->m_sensorCollider   = *other.m_sensorCollider;
    return *this;
}
/*
void RectSensor::engineCalled_preTick()
{
    SENSOR_FUNCTION(profiler::colors::Yellow);
}
void RectSensor::engineCalled_tick(const Vector2i &direction)
{
    SENSOR_FUNCTION(profiler::colors::Yellow100);
}
void RectSensor::engineCalled_postTick()
{
    SENSOR_FUNCTION(profiler::colors::Yellow200);
}*/
void RectSensor::engineCalled_preDraw()
{
    SENSOR_FUNCTION(profiler::colors::Yellow300);
    m_sensorPainter->update(m_detected);
}


void RectSensor::setRect(const RectF rect)
{
    m_sensorCollider->clear();
    m_sensorCollider->addHitbox(rect);
}

void RectSensor::detectObjects(const vector<GameObject*> &other)
{
    SENSOR_FUNCTION(profiler::colors::Yellow400);
    size_t lastDetected = m_detected.size();
    m_detected.clear();
    m_detected.reserve(lastDetected);


    for(auto obj : other)
    {
        Collider *otherCollider = obj->getCollider();
        if(m_sensorCollider->intersectsBoundingBox(otherCollider))
        {
            if(m_sensorCollider->collides(otherCollider))
            {
                m_detected.push_back(obj);
            }
        }
    }


}
void RectSensor::setDetectedColor(const Color &color)
{
    m_detectedColor = color;
    m_sensorPainter->setColor_collidedObjects(m_detectedColor);
}
void RectSensor::setSensorColor(const Color &color)
{
    m_sensorColor = color;
    m_sensorPainter->setColor_hitBox_colliding(m_sensorColor);
    m_sensorPainter->setColor_hitBox_noCollision(m_sensorColor);
}
