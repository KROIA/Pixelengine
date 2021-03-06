#include "sensor.h"


Sensor::Sensor()
{
    m_sensorCollider = new Collider();
    m_sensorPainter  = new Painter();
    m_owner = nullptr;
}

Sensor::Sensor(const Sensor &other)
{
    *this = other;
}


Sensor::~Sensor()
{
    delete m_sensorCollider;
    delete m_sensorPainter;
}

const Sensor &Sensor::operator=(const Sensor &other)
{
    *this->m_sensorCollider = *other.m_sensorCollider;
    *this->m_sensorPainter  = *other.m_sensorPainter;
    this->m_detected        = other.m_detected;
    this->m_owner           = other.m_owner;
    return *this;
}

void Sensor::setOwner(GameObject *owner)
{
    m_owner = owner;
}
void Sensor::setSensorCollider(Collider *collider)
{
    if(m_sensorCollider == collider || collider == nullptr)
        return;
    delete m_sensorCollider;
    m_sensorCollider = collider;
    HitboxPainter::makeVisibleCollider(m_sensorCollider,m_sensorPainter);
}
void Sensor::checkCollision(const vector<GameObject*> &other)
{
    if(m_owner != nullptr)
        m_sensorCollider->setPos(m_owner->getPos());
    m_detected.clear();
    m_detected.reserve(10);
    for(size_t i=0; i<other.size(); i++)
    {
        if(m_sensorCollider->intersectsBoundingBox(other[i]->getCollider()))
        {
            if(m_sensorCollider->collides(other[i]->getCollider()))
            {
                m_detected.push_back(other[i]);
            }
        }
    }
}
void Sensor::draw(PixelDisplay &display)
{
    m_sensorPainter->setPos(m_owner->getPos());
    m_sensorPainter->draw(display);
}
const vector<GameObject*> &Sensor::getDetectedObjects() const
{
    return m_detected;
}

double Sensor::getRotation() const
{
    return m_sensorCollider->getRotation();
}
void Sensor::setRotation(const double &deg)
{
    m_sensorPainter->setRotation(deg);
    m_sensorCollider->setRotation(deg);
}
void Sensor::rotate_90()
{
    m_sensorPainter->rotate_90();
    m_sensorCollider->rotate_90();
}
void Sensor::rotate_180()
{
    m_sensorPainter->rotate_180();
    m_sensorCollider->rotate_180();
}
void Sensor::rotate_270()
{
    m_sensorPainter->rotate_270();
    m_sensorCollider->rotate_270();
}
