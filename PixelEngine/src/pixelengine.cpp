#include "pixelengine.h"

PixelEngine::PixelEngine(const PointU &mapsize,const PointU &displaySize)
{
    //this->addGroup(GameObjectGroup());
    m_mapSize = mapsize;
    m_windowSize = displaySize;
    m_display       = new PixelDisplay(m_windowSize,m_mapSize);
    m_mainTickTimer = new Timer;
    m_displayTimer  = new Timer;
    this->set_setting_gameTickInterval(0.01);
    this->set_setting_displayInterval(0.01);

    m_p_func_userDisplayLoop = nullptr;
    m_p_func_userTickLoop    = nullptr;
}

PixelEngine::PixelEngine(const PixelEngine &other)
{
    *this->m_display            = *other.m_display;
    this->m_windowSize          = other.m_windowSize;
    this->m_mapSize             = other.m_mapSize;

    *this->m_mainTickTimer      = *other.m_mainTickTimer;
    this->m_mainTickInterval    = other.m_mainTickInterval;

    *this->m_displayTimer       = *other.m_displayTimer;
    this->m_displayInterval     = other.m_displayInterval;

    this->m_gameObjectGroup     = other.m_gameObjectGroup;

    this->m_p_func_userDisplayLoop = other.m_p_func_userDisplayLoop;
    this->m_p_func_userTickLoop    = other.m_p_func_userTickLoop;
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
const PointU &PixelEngine::getWindwoSize() const
{
    return m_windowSize;
}
const PointU &PixelEngine::getMapSize() const
{
    return m_mapSize;
}

// Userloops
void PixelEngine::setUserDisplayLoop(p_func func)
{
    m_p_func_userDisplayLoop = func;
}
void PixelEngine::setUserTickLoop(p_func func)
{
    m_p_func_userTickLoop = func;
}
void PixelEngine::tick()
{
    if(!m_mainTickTimer->start(m_mainTickInterval))
        return; // Time not finished
    if(m_p_func_userTickLoop != nullptr)
        (*m_p_func_userTickLoop)(m_mainTickInterval);

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
    for(size_t i=0; i<m_gameObjectGroup.size(); i++)
    {
        if(m_gameObjectGroup[i]->isRemoved())
        {
            m_gameObjectGroup.remove(m_gameObjectGroup[i]);
            continue;
        }
        m_gameObjectGroup[i]->tick(dirLock);
        m_gameObjectGroup[i]->checkCollision();
    }
}

void PixelEngine::display()
{
    if(!m_displayTimer->start(m_displayInterval))
        return;
    if(m_p_func_userDisplayLoop != nullptr)
        (*m_p_func_userDisplayLoop)(m_displayInterval);

    for(size_t i=0; i<m_gameObjectGroup.size(); i++)
    {
        if(m_gameObjectGroup[i]->isRemoved())
        {
            m_gameObjectGroup.remove(m_gameObjectGroup[i]);
            continue;
        }
        m_gameObjectGroup[i]->draw(*m_display);
    }

    m_display->display();
    m_display->handleEvents();
}

void PixelEngine::set_setting_gameTickInterval(const double &seconds)
{
    m_mainTickInterval = abs(seconds);
}
const double  &PixelEngine::get_setting_gameTickInterval() const
{
    return m_mainTickInterval;
}
void PixelEngine::set_setting_displayInterval(const double &seconds)
{
    m_displayInterval = abs(seconds);
}
const double  &PixelEngine::get_setting_displayInterval() const
{
    return m_displayInterval;
}
void PixelEngine::addGameObject(GameObject *obj)
{
    if(obj->isRemoved())
        obj->reActivate();
    m_gameObjectGroup.push_back(obj);
}
void PixelEngine::addGameObject(const vector<GameObject*> &group)
{
    m_gameObjectGroup.append(group);
}
void PixelEngine::removeGameObject(GameObject *toRemove)
{
    m_gameObjectGroup.remove(toRemove);
}
void PixelEngine::removeGameObject(const vector<GameObject*> &toRemoveGroup)
{
    m_gameObjectGroup.remove(toRemoveGroup);
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
bool   PixelEngine::loadFromImage(const std::string &picture,Collider *collider,Painter *painter)
{
    Image image;
    if(!image.loadFromFile(picture))
        return false;

    sf::Vector2u size = image.getSize();
    Point middleOffset(-signed(size.x)/2,-signed(size.y)/2);

    collider->clear();
    painter->clear();
    for(unsigned int x=0; x<size.x; x++)
    {
        for(unsigned int y=0; y<size.y; y++)
        {
            Color color = image.getPixel(x,y);
            if(color.a != 0 && !(color.r == 255 && color.g == 255 && color.b == 255))
            {
                collider->addHitBox(Rect(middleOffset.getX()+x,middleOffset.getY()+y,1,1));
                painter->addPixel(Pixel(Point(middleOffset.getX()+x,middleOffset.getY()+y),color));
            }
        }
    }
    return true;
}
