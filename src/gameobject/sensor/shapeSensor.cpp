#include "shapeSensor.h"

ShapeSensor::ShapeSensor()
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

    setShape(Shape({{0,0},{1,0},{1,1},{0,1}}));
    Submodule::addPainter(m_sensorPainter);
}
ShapeSensor::ShapeSensor(const ShapeSensor &other)
    :   Sensor(other)
{
    m_sensorCollider = new Collider();
    this->operator=(other);
}
ShapeSensor::~ShapeSensor()
{
    if(m_owner)
    {
        m_owner->removeSensor(this);
    }
    Submodule::removePainter(m_sensorPainter);
    delete m_sensorCollider;
}
const ShapeSensor &ShapeSensor::operator=(const ShapeSensor &other)
{
    Sensor::operator=(other);
    *this->m_sensorCollider   = *other.m_sensorCollider;
    return *this;
}
/*
void ShapeSensor::engineCalled_preTick()
{
    SENSOR_FUNCTION(profiler::colors::Yellow);
}
void ShapeSensor::engineCalled_tick(const Vector2i &direction)
{
    SENSOR_FUNCTION(profiler::colors::Yellow100);
}
void ShapeSensor::engineCalled_postTick()
{
    SENSOR_FUNCTION(profiler::colors::Yellow200);
}*/



void ShapeSensor::setShape(const Shape &shape)
{
    m_sensorCollider->clear();
    m_sensorCollider->setShape(shape);
}
void ShapeSensor::engineCalled_preTick()
{
    m_sensorCollider->tick();
}
void ShapeSensor::detectObjects(const vector<GameObject*> &other)
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
            //if(m_sensorCollider->collides(otherCollider))
            if(m_sensorCollider->getShape().intersects(otherCollider->getShape()))
            {
                m_detected.push_back(obj);
            }
        }
    }


}
void ShapeSensor::engineCalled_postTick()
{
    m_sensorCollider->setPos(m_pos);
    m_sensorCollider->setRotation(m_rotation);
}
void ShapeSensor::engineCalled_preDraw()
{
    SENSOR_FUNCTION(profiler::colors::Yellow300);
    m_sensorPainter->update(m_detected);
}
void ShapeSensor::setDetectedColor(const Color &color)
{
    m_detectedColor = color;
    m_sensorPainter->setColor_collidedObjects_hitBox(m_detectedColor);
}
void ShapeSensor::setSensorColor(const Color &color)
{
    m_sensorColor = color;
    m_sensorPainter->setColor_hitBox_colliding(m_sensorColor);
    m_sensorPainter->setColor_hitBox_noCollision(m_sensorColor);
}
void ShapeSensor::setVisibility(bool isVisible)
{
    m_sensorPainter->setVisibility_hitBox(isVisible);
}
void ShapeSensor::setVisibility_detectedObjects(bool isVisible)
{
    m_sensorPainter->setVisibility_collidedObjects_hitBox(isVisible);
}

bool ShapeSensor::isVisible() const
{
    return m_sensorPainter->isVisible_collidedObjects_hitBox();
}
bool ShapeSensor::isVisible_detectedObjects() const
{
    return m_sensorPainter->isVisible_collidedObjects_hitBox();
}
/*
ColliderPainter *ShapeSensor::getColliderPainter() const
{
    return m_sensorPainter;
}
*/
