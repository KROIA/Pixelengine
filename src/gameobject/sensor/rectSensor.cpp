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
    m_sensorPainter->setVisibility_collidedObjects_boundingBox(false);
    m_sensorPainter->setVisibility_collidedObjects_hitBox(true);

    setDetectedColor(Color(0,100,255));
    setSensorColor(Color(0,255,0));

    setRect(RectF(0,0,1,1));
    Submodule::addPainter(m_sensorPainter);
}
RectSensor::RectSensor(const RectSensor &other)
    :   Sensor(other)
{
    m_sensorCollider = new Collider();
    this->operator=(other);
}
RectSensor::~RectSensor()
{
    if(m_owner)
    {
        m_owner->removeSensor(this);
    }
    Submodule::removePainter(m_sensorPainter);
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



void RectSensor::setRect(const RectF rect)
{
    m_sensorCollider->clear();
    m_sensorCollider->addHitbox(rect);
}
void RectSensor::engineCalled_preTick()
{
    m_sensorCollider->tick();
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
void RectSensor::engineCalled_postTick()
{
    m_sensorCollider->setPos(m_pos);
    m_sensorCollider->setRotation(m_rotation);
}
void RectSensor::engineCalled_preDraw()
{
    SENSOR_FUNCTION(profiler::colors::Yellow300);
    m_sensorPainter->update(m_detected);
}
void RectSensor::setDetectedColor(const Color &color)
{
    m_detectedColor = color;
    m_sensorPainter->setColor_collidedObjects_hitBox(m_detectedColor);
}
void RectSensor::setSensorColor(const Color &color)
{
    m_sensorColor = color;
    m_sensorPainter->setColor_hitBox_colliding(m_sensorColor);
    m_sensorPainter->setColor_hitBox_noCollision(m_sensorColor);
}
void RectSensor::setVisibility(bool isVisible)
{
    m_sensorPainter->setVisibility_hitBox(isVisible);
}
void RectSensor::setVisibility_detectedObjects(bool isVisible)
{
    m_sensorPainter->setVisibility_collidedObjects_hitBox(isVisible);
}

bool RectSensor::isVisible() const
{
    return m_sensorPainter->isVisible_collidedObjects_hitBox();
}
bool RectSensor::isVisible_detectedObjects() const
{
    return m_sensorPainter->isVisible_collidedObjects_hitBox();
}
/*
ColliderPainter *RectSensor::getColliderPainter() const
{
    return m_sensorPainter;
}
*/
