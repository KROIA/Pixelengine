#include "laserSensor.h"

/*LaserSubscriberList::LaserSubscriberList()
    :   SubscriberList<LaserSignal>()
{}

void LaserSubscriberList::changed(Laser *sender)
{
    SIGNAL_EMIT_INTERN(changed,sender);
}*/

Laser::Laser()
{
    m_origin = Vector2f(0,0);
    m_rotation = 0;
    set(Vector2f(0,0),1,-90);
}
Laser::Laser(const Vector2f &begin, float length, float angle)
{
    set(begin, length, angle);
}

void Laser::set(const Vector2f &begin, float length, float angle)
{
    m_localBegin     = begin;
    m_length         = length;
    m_localRotation  = angle;
    calculateLocal();
    calculateGlobal();
    //m_laserSubscriberList.changed(this);
    SIGNAL_EMIT(Laser,changed)
}
void Laser::setBegin(const Vector2f &begin)
{
    m_localBegin     = begin;
    calculateLocal();
    calculateGlobal();
    //m_laserSubscriberList.changed(this);
    SIGNAL_EMIT(Laser,changed)
}
void Laser::setLength(float length)
{
    m_length         = length;
    calculateLocal();
    calculateGlobal();
    //m_laserSubscriberList.changed(this);
    SIGNAL_EMIT(Laser,changed)
}
void Laser::setRotation(float angle)
{
    m_localRotation  = angle;
    calculateLocal();
    calculateGlobal();
}
void Laser::rotate(float angle)
{
    m_localRotation  += angle;
    calculateLocal();
    calculateGlobal();
}
void Laser::setReference(Vector2f pos, float angle)
{
    m_origin    = pos;
    m_rotation  = angle;
    calculateGlobal();
}

const Vector2f &Laser::getBegin() const
{
    return m_localBegin;
}
const Vector2f &Laser::getDirection() const
{
    return m_localDirectionVec;
}
const Vector2f &Laser::getEnd() const
{
    return m_localEnd;
}
float Laser::getLength() const
{
    return m_length;
}
float Laser::getRotation() const
{
    return m_localRotation;
}
const Vector2f &Laser::getGlobalBegin() const
{
    return m_globalBegin;
}
const Vector2f &Laser::getGlobalDirection() const
{
    return m_globalDirectionVec;
}
const Vector2f &Laser::getGlobalEnd() const
{
    return m_globalEnd;
}
float Laser::getGlobalAngle() const
{
    return m_globalRotation;
}
/*void Laser::subscribe_laserSignal(LaserSignal *subscriber)
{
    m_laserSubscriberList.insert(subscriber);
}
void Laser::unsubscribe_laserSignal(LaserSignal *subscriber)
{
    m_laserSubscriberList.erase(subscriber);
}
void Laser::unsubscribeAll_laserSignal()
{
    m_laserSubscriberList.clear();
}*/
void Laser::calculateLocal()
{
    m_localDirectionVec.x = cos((m_localRotation) * M_PI /180.f) * m_length;
    m_localDirectionVec.y = sin((m_localRotation) * M_PI /180.f) * m_length;

    m_localEnd           = m_localBegin + m_localDirectionVec;
}
void Laser::calculateGlobal()
{
    m_globalDirectionVec = Vector::getRotated(m_localDirectionVec, m_rotation);

    m_globalBegin        = Vector::getRotated(m_localBegin, m_rotation) + m_origin;
    m_globalRotation     = m_rotation + m_localRotation;
    m_globalEnd          = m_globalBegin + m_globalDirectionVec;
}



LaserSensor::LaserSensor()
    :   Sensor()
{
    m_sensorPainter = new VertexPathPainter();
    //setBeam(Vector2f(0,-20),30,-90);
    setDetectedColor(Color(0,100,255));
    setSensorColor(Color(0,255,0));
    m_sensorPainter->setVisibility(true);

    Submodule::addPainter(m_sensorPainter);
}
LaserSensor::~LaserSensor()
{
    if(m_owner)
    {
        m_owner->removeSensor(this);
    }
    Submodule::removePainter(m_sensorPainter);
    delete m_sensorPainter;
    this->clearLaser();
}

bool LaserSensor::addLaser(const Vector2f &begin, float length, float angle)
{
    Laser *laser = new Laser(begin,length,angle);
    m_privateLaserPTR.push_back(laser);
    return this->addLaser(laser);
}
bool LaserSensor::addLaser(Laser *laser)
{
    if(laser)
    {
        for(size_t i=0; i<m_laserList.size(); i++)
        {
            if(m_laserList[i] == laser)
            {
                return false;
            }
        }
        m_laserList.push_back(laser);
        //laser->subscribe_laserSignal(this);
        SIGNAL_SUBSCRIBE(Laser,laser)
        m_recalculateColliderSearchFrame = true;
        return true;
    }
    return false;
}
bool LaserSensor::removeLaser(Laser *laser)
{
    for(size_t i=0; i<m_laserList.size(); i++)
    {
        if(m_laserList[i] == laser)
        {
            m_laserList.erase(m_laserList.begin() + i);
            //laser->unsubscribe_laserSignal(this);
            SIGNAL_UNSUBSCRIBE(Laser,laser)
            if(m_laserList.size() == 0)
                m_detected.clear();
            return true;
        }
    }
    return false;
}
void LaserSensor::clearLaser()
{
    for(size_t i=0; i<m_laserList.size(); i++)
    {
        //m_laserList[i]->unsubscribe_laserSignal(this);
        SIGNAL_UNSUBSCRIBE(Laser,m_laserList[i])
    }
    m_laserList.clear();
    for(size_t i=0; i<m_privateLaserPTR.size(); i++)
    {
        delete m_privateLaserPTR[i];
    }
    m_privateLaserPTR.clear();
    m_detected.clear();
}

void LaserSensor::engineCalled_preTick()
{
    if(m_owner && m_recalculateColliderSearchFrame)
    {
        float searchBoxRadius = m_owner->getCollisionSeachRadius();

        float laserRadius = 0;
        for(auto laser : m_laserList)
        {
            float length = Vector::length(laser->getEnd());
            if(length > laserRadius)
                laserRadius = length;
        }
        if(searchBoxRadius < laserRadius)
            m_owner->setCollisionSeachRadius(laserRadius);
        m_recalculateColliderSearchFrame = false;
    }
    //for(auto laser : m_laserList)
    //    laser->setReference(m_pos,m_rotation);
}
void LaserSensor::detectObjects(const vector<GameObject*> &other)
{
    if(m_laserList.size() == 0)
        return;
    HashTable<GameObject*>  tmpDetected;
    for(auto obj : other)
    {
        RectF  boundingBox = obj->getCollider()->getBoundingBox();

        Vector2f TL = boundingBox.getCornerPoint_TL();
        Vector2f TR = boundingBox.getCornerPoint_TR();
        Vector2f BL = boundingBox.getCornerPoint_BL();

        Vector2f top = boundingBox.getTop();
        Vector2f left = boundingBox.getLeft();
        Vector2f bottom = boundingBox.getBottom();
        Vector2f right = boundingBox.getRight();

        bool boundingBoxDoesCollide = false;
        Vector2f collisionPoint;
        Vector2f collisionFactor;

        for(auto laser : m_laserList)
        {
            Vector2f laserBegin     = laser->getGlobalBegin();
            Vector2f laserDirection = laser->getGlobalDirection();

            collisionPoint = Vector::getCollisionPoint(laserBegin, laserDirection,
                                                       TL,top,
                                                       boundingBoxDoesCollide,collisionFactor);
            if(!boundingBoxDoesCollide)
            {
                collisionPoint = Vector::getCollisionPoint(laserBegin, laserDirection,
                                                           TL,left,
                                                           boundingBoxDoesCollide,collisionFactor);
            }
            if(!boundingBoxDoesCollide)
            {
                collisionPoint = Vector::getCollisionPoint(laserBegin, laserDirection,
                                                           BL,bottom,
                                                           boundingBoxDoesCollide,collisionFactor);
            }
            if(!boundingBoxDoesCollide)
            {
                collisionPoint = Vector::getCollisionPoint(laserBegin, laserDirection,
                                                           TR,right,
                                                           boundingBoxDoesCollide,collisionFactor);
            }
            if(boundingBoxDoesCollide)
            {
                //qDebug() << "bound";
                vector<RectF> hitBoxList = obj->getCollider()->getHitbox();

                for(auto box : hitBoxList)
                {
                    bool doesCollide = false;
                    collisionPoint = Vector::getCollisionPoint(laserBegin, laserDirection,
                                                               box.getCornerPoint_TL(),box.getTop(),
                                                               doesCollide,collisionFactor);
                    if(!doesCollide)
                    {
                        collisionPoint = Vector::getCollisionPoint(laserBegin, laserDirection,
                                                                   box.getCornerPoint_TL(),box.getLeft(),
                                                                   doesCollide,collisionFactor);
                    }
                    if(!doesCollide)
                    {
                        collisionPoint = Vector::getCollisionPoint(laserBegin, laserDirection,
                                                                   box.getCornerPoint_BL(),box.getBottom(),
                                                                   doesCollide,collisionFactor);
                    }
                    if(!doesCollide)
                    {
                        collisionPoint = Vector::getCollisionPoint(laserBegin, laserDirection,
                                                                   box.getCornerPoint_TR(),box.getRight(),
                                                                   doesCollide,collisionFactor);
                    }
                    if(doesCollide)
                    {
                        tmpDetected.insert({obj,obj});
                        goto nextObj;
                    }
                }
            }
            nextObj:;
        }

    }
    size_t lastSize = m_detected.size();
    m_detected.clear();
    m_detected.reserve(lastSize);
    for(auto pair : tmpDetected)
        m_detected.push_back(pair.second);
}

void LaserSensor::engineCalled_preDraw()
{
    for(auto laser : m_laserList)
        laser->setReference(m_pos,m_rotation);
    m_sensorPainter->clear();
    for(auto obj : m_detected)
    {
        m_sensorPainter->addPath(obj->getCollider()->getBoundingBox().getDrawable(m_detectedColor));
    }
    for(auto laser : m_laserList)
        m_sensorPainter->addPath(Vector::getDrawableVector(laser->getGlobalBegin(),laser->getGlobalEnd(),m_sensorColor));
}

bool LaserSensor::setBegin(size_t laserIndex, const Vector2f &begin)
{
    if(laserIndex >= m_laserList.size())
        return false;
    m_laserList[laserIndex]->setBegin(begin);
    return true;
}
bool LaserSensor::setLength(size_t laserIndex, float length)
{
    if(laserIndex >= m_laserList.size())
        return false;
    m_laserList[laserIndex]->setLength(length);
    return true;
}
bool LaserSensor::setLaserRotation(size_t laserIndex, float angle)
{
    if(laserIndex >= m_laserList.size())
        return false;
    m_laserList[laserIndex]->setRotation(angle);
    return true;
}
bool LaserSensor::rotateLaser(size_t laserIndex, float angle)
{
    if(laserIndex >= m_laserList.size())
        return false;
    m_laserList[laserIndex]->rotate(angle);
    return true;
}
void LaserSensor::setDetectedColor(const Color &color)
{
    m_detectedColor = color;
}
void LaserSensor::setSensorColor(const Color &color)
{
    m_sensorColor = color;
}
SLOT_DEFINITION(LaserSensor,Laser,changed)
{
    m_recalculateColliderSearchFrame = true;
}
/*void LaserSensor::changed(Laser *sender)
{
    m_recalculateColliderSearchFrame = true;
}*/
