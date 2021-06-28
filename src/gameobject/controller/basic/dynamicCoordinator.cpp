#include "dynamicCoordinator.h"


DynamicCoordinator::DynamicCoordinator()
{
    m_movingVector.x = 0;
    m_movingVector.y = 0;
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
        m_movingVector.x = 0;
        m_movingVector.y = 0;
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

void DynamicCoordinator::addMovement(const Vector2f &vec)
{
    m_vecList.push_back(vec);
}

void DynamicCoordinator::calculateMovement()
{
    EASY_FUNCTION(profiler::colors::Pink600);
    Vector2f sum = Vector::sum(m_vecList);
    this->clearMovement();

    if(m_neededSteps > 0)
    {
        sum += m_movingVector * float(m_neededSteps);
    }
    float length = Vector::length(sum);
    m_neededSteps = (unsigned int)length;
    if(length == 0)
        return;

    m_xStepInterval = float(m_neededSteps)/abs(sum.x);
    m_yStepInterval = float(m_neededSteps)/abs(sum.y);

    m_movingVector.x = sum.x/length;
    m_movingVector.y = sum.y/length;
}

const unsigned int &DynamicCoordinator::getNeededSteps() const
{
    return m_neededSteps;
}
const Vector2f      &DynamicCoordinator::getMovingVector() const
{
    return m_movingVector;
}
const float       &DynamicCoordinator::getMovingVector_X() const
{
    return m_movingVector.x;
}
const float       &DynamicCoordinator::getMovingVector_Y() const
{
    return m_movingVector.y;
}
/*Vector2i        DynamicCoordinator::getRoundedVector() const
{
    EASY_FUNCTION(profiler::colors::Pink500);
    Vector2i ret(0,0);
    if(m_xStepInterval > 0 && m_neededSteps != 0)
    if(m_xStepCounter % m_xStepInterval == 0)
    {
        if(m_movingVector.x > 0)
        {
            ret.x = 1;
        }
        else
        {
            ret.x = -1;
        }
    }
    if(m_yStepInterval > 0 && m_neededSteps != 0)
    if(m_yStepCounter % m_yStepInterval == 0)
    {
        if(m_movingVector.y > 0)
        {
            ret.y = 1;
        }
        else
        {
            ret.y = -1;
        }
    }

    return ret;
}
int           DynamicCoordinator::getRoundedVector_X() const
{
   // if(m_xStepInterval > 0)
   // if(m_xStepCounter % m_xStepInterval == 0)
        return int(round(m_movingVector.x));
   // return 0;
}
int           DynamicCoordinator::getRoundedVector_Y() const
{
   // if(m_yStepInterval > 0)
   // if(m_yStepCounter % m_yStepInterval == 0)
        return int(round(m_movingVector.getY()));
   // return 0;
}*/
void DynamicCoordinator::clearMovement()
{
    m_vecList.clear();
    m_vecList.reserve(10);
}
