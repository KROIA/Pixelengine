#include "pixelengine.h"

PixelEngine::PixelEngine()
{
    //this->addGroup(GameObjectGroup());
    m_display       = new PixelDisplay(PointU(1500,1000),PointU(150,100));
    m_mainTickTimer = new Timer;
    m_displayTimer  = new Timer;
    this->set_setting_gameTickInterval(0.01);
    this->set_setting_displayInterval(0.01);
}

PixelEngine::PixelEngine(const PixelEngine &other)
{
    *this->m_display            = *other.m_display;

    *this->m_mainTickTimer      = *other.m_mainTickTimer;
    this->m_mainTickInterval    = other.m_mainTickInterval;

    *this->m_displayTimer       = *other.m_displayTimer;
    this->m_displayInterval     = other.m_displayInterval;

    this->m_gameObjectGroup     = other.m_gameObjectGroup;
}

PixelEngine::~PixelEngine()
{
    for(size_t i=0; i<m_gameObjectGroup.size(); i++)
    {
        delete m_gameObjectGroup[i];
    }
    m_gameObjectGroup.clear();

    delete m_display;
    delete m_mainTickTimer;
    delete m_displayTimer;
}


void PixelEngine::tick()
{
    if(!m_mainTickTimer->start(m_mainTickInterval))
        return; // Time not finished

    tickX();
    tickY();
}
void PixelEngine::tickX()
{
    tickXY(Point(1,0));
}
void PixelEngine::tickY()
{
    tickXY(Point(0,1));
}
void PixelEngine::tickXY(const Point &dirLock)
{
    for(size_t j=0; j<m_gameObjectGroup.size(); j++)
    {
        m_gameObjectGroup[j]->tick(dirLock);
        m_gameObjectGroup[j]->checkCollision();
    }
}

void PixelEngine::display()
{
    if(!m_displayTimer->start(m_displayInterval))
        return;


    for(size_t j=0; j<m_gameObjectGroup.size(); j++)
    {
        //if(!m_gameObjectGroup[j]->isVisible())
        //    continue; // Object is not visible
        m_gameObjectGroup[j]->draw(*m_display);
    }

    m_display->display();
    m_display->handleEvents();
}

void PixelEngine::set_setting_gameTickInterval(const double &seconds)
{
    m_mainTickInterval = abs(seconds);
}
void PixelEngine::set_setting_displayInterval(const double &seconds)
{
    m_displayInterval = abs(seconds);
}
void PixelEngine::addGameObject(GameObject *obj)
{
    m_gameObjectGroup.push_back(obj);
}
void PixelEngine::addGroup(const vector<GameObject*> &group)
{
    m_gameObjectGroup.insert(m_gameObjectGroup.end(),group.begin(),group.end());
}
// General functions
double PixelEngine::random(double min, double max)
{
    if(min == max)
    {
        return min;
    }
    if(min > max)
    {   double buf=min;
        min = max;
        max = buf;
    }

    // Generating a timedependend seed
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    int seed = now->tm_year + now->tm_mon + now->tm_mday + now->tm_hour + now->tm_min + now->tm_sec;
    return double((min*1000.0)+((seed*rand())%(int)((max-min)*1000.0)))/1000.0;
}

