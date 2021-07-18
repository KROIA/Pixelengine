#include "sensor.h"


Sensor::Sensor()
{
    m_owner = nullptr;
    setEnableRelativeRotation(true);
    setEnableRelativePosition(true);
}

Sensor::Sensor(const Sensor &other)
{
    *this = other;
}


Sensor::~Sensor()
{}

const Sensor &Sensor::operator=(const Sensor &other)
{
    this->m_detected        = other.m_detected;
    this->m_owner           = other.m_owner;
    return *this;
}

void Sensor::setOwner(GameObject *owner)
{
    m_owner = owner;
}

void Sensor::engineCalled_preTick()
{
    SENSOR_FUNCTION(profiler::colors::Yellow);
    m_collider->setPos(m_pos);
    m_collider->setRotation(m_rotation);
}
void Sensor::engineCalled_tick(const Vector2i &direction)
{
    SENSOR_FUNCTION(profiler::colors::Yellow100);
}
void Sensor::engineCalled_postTick()
{
    SENSOR_FUNCTION(profiler::colors::Yellow200);
}
void Sensor::engineCalled_preDraw()
{
    SENSOR_FUNCTION(profiler::colors::Yellow300);
}

const vector<GameObject*> &Sensor::getDetectedObjects() const
{
    return m_detected;
}
void Sensor::setEnableRelativeRotation(bool enable)
{
    m_enableRelativeRotation = enable;
}
void Sensor::setEnableRelativePosition(bool enable)
{
    m_enableRelativePosition = enable;
}
bool Sensor::getEnableRelativeRotation() const
{
    return m_enableRelativeRotation;
}
bool Sensor::getEnableRelativePosition() const
{
    return m_enableRelativePosition;
}
