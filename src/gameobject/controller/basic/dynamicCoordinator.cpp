#include "dynamicCoordinator.h"


DynamicCoordinator::DynamicCoordinator()
{
    m_movingVector.set(0,0);
    m_vecList.reserve(10);
    m_xStepInterval = 0;
    m_xStepCounter = 1;
    m_yStepInterval = 0;
    m_yStepCounter = 1;
}
DynamicCoordinator::DynamicCoordinator(const DynamicCoordinator &other)
{
    *this = other;
}
DynamicCoordinator::~DynamicCoordinator()
{

}
const DynamicCoordinator &DynamicCoordinator::operator=(const DynamicCoordinator &other)
{
    this->m_vecList         = other.m_vecList;
    this->m_movingVector    = other.m_movingVector;
    this->m_neededSteps     = other.m_neededSteps;
    this->m_xStepInterval   = other.m_xStepInterval;
    this->m_xStepCounter    = other.m_xStepCounter;
    this->m_yStepInterval   = other.m_yStepInterval;
    this->m_yStepCounter    = other.m_yStepCounter;
    return *this;
}

void DynamicCoordinator::tick()
{
    if(m_neededSteps == 0)
    {
        m_movingVector.set(0,0);
        return;
    }

    m_neededSteps--;
    m_xStepCounter++;
    if(m_xStepCounter >= m_xStepInterval)
        m_xStepCounter = 1;
    m_yStepCounter++;
    if(m_yStepCounter >= m_yStepInterval)
        m_yStepCounter = 1;        
}

void DynamicCoordinator::addMovement(const VectorF &vec)
{
    m_vecList.push_back(vec);
}
void DynamicCoordinator::addMovement(const Vector &vec)
{
    m_vecList.push_back(VectorF(vec.getX(),vec.getY()));
}

void DynamicCoordinator::calculateMovement()
{
    EASY_FUNCTION(profiler::colors::Pink600);
    VectorF sum = VectorF::sum(m_vecList);
    this->clearMovement();

    if(m_neededSteps > 0)
    {
        sum += m_movingVector * double(m_neededSteps);
    }
    double length = sum.getLength();
    m_neededSteps = (unsigned int)length;
    /*if(abs(sum.getX())>abs(sum.getY()))
        m_neededSteps = abs(sum.getX());
    else
        m_neededSteps = abs(sum.getY());
*/
    if(length == 0)
        return;

    m_xStepInterval = double(m_neededSteps)/abs(sum.getX());
    m_yStepInterval = double(m_neededSteps)/abs(sum.getY());

    m_movingVector.set(sum.getX()/length,
                       sum.getY()/length);
}

const unsigned int &DynamicCoordinator::getNeededSteps() const
{
    return m_neededSteps;
}
const VectorF      &DynamicCoordinator::getMovingVector() const
{
    return m_movingVector;
}
const double       &DynamicCoordinator::getMovingVector_X() const
{
    return m_movingVector.getX();
}
const double       &DynamicCoordinator::getMovingVector_Y() const
{
    return m_movingVector.getY();
}
Vector        DynamicCoordinator::getRoundedVector() const
{
    EASY_FUNCTION(profiler::colors::Pink500);
    Vector ret(0,0);
    if(m_xStepInterval > 0 && m_neededSteps != 0)
    if(m_xStepCounter % m_xStepInterval == 0)
    {
        if(m_movingVector.getX() > 0)
        {
            ret.setX(1);
        }
        else
        {
            ret.setX(-1);
        }
    }
    if(m_yStepInterval > 0 && m_neededSteps != 0)
    if(m_yStepCounter % m_yStepInterval == 0)
    {
        if(m_movingVector.getY() > 0)
        {
            ret.setY(1);
        }
        else
        {
            ret.setY(-1);
        }
    }

    return ret;
}
int           DynamicCoordinator::getRoundedVector_X() const
{
   // if(m_xStepInterval > 0)
   // if(m_xStepCounter % m_xStepInterval == 0)
        return int(round(m_movingVector.getX()));
   // return 0;
}
int           DynamicCoordinator::getRoundedVector_Y() const
{
   // if(m_yStepInterval > 0)
   // if(m_yStepCounter % m_yStepInterval == 0)
        return int(round(m_movingVector.getY()));
   // return 0;
}
void DynamicCoordinator::clearMovement()
{
    m_vecList.clear();
    m_vecList.reserve(10);
}
