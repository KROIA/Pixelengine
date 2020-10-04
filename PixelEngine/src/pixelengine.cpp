#include "pixelengine.h"

PixelEngine::PixelEngine()
{
    this->addGroup(GameObjectGroup());
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

    *this->m_displayTimer      = *other.m_displayTimer;
    this->m_displayInterval    = other.m_displayInterval;

    this->m_gameObjectGroupList = other.m_gameObjectGroupList;
    this->m_interactiveColliderGroupList   = other.m_interactiveColliderGroupList;
    //this->m_controllerGroupList = other.m_controllerGroupList;
    //this->m_painterGroupList    = other.m_painterGroupList;
}

PixelEngine::~PixelEngine()
{
    m_interactiveColliderGroupList.clear();
    //m_controllerGroupList.clear();
    //m_painterGroupList.clear();
    for(size_t i=0; i<m_gameObjectGroupList.size(); i++)
    {
        for(size_t j=0; j<m_gameObjectGroupList[i].size(); j++)
        {
            delete m_gameObjectGroupList[i].get(j);
        }
    }
    m_gameObjectGroupList.clear();

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
    for(size_t i=0; i<m_gameObjectGroupList.size(); i++)
    {
        for(size_t j=0; j<m_gameObjectGroupList[i].size(); j++)
        {
            m_gameObjectGroupList[i].get(j)->tick(dirLock);
        }
    }

    for(size_t i=0; i<m_interactiveColliderGroupList.size(); i++)
    {
        GameObjectGroup objectGroup = m_interactiveColliderGroupList[i];
        for(size_t j=0; j<m_interactiveColliderGroupList[i].size(); j++)
        {
            for(size_t z=0; z<m_interactiveColliderGroupList[i].getInteractiveList().size(); z++)
            {
                GameObjectGroup *interacts = m_interactiveColliderGroupList[i].getInteractiveList()[z];
                objectGroup.get(j)->checkCollision(interacts->getAll());
            }
        }
    }
}

void PixelEngine::display()
{
    if(!m_displayTimer->start(m_displayInterval))
        return;
    for(size_t i=0; i<m_painterGroupList.size(); i++)
    {
        if(!m_painterGroupList[i].isVisible())
            continue; // Group is not visible
        for(size_t j=0; j<m_painterGroupList[i].size(); j++)
        {
            m_painterGroupList[i].getAll()[j]->draw(*m_display);
        }
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
    m_gameObjectGroupList[0].add(obj);
}

void PixelEngine::addGroup(const GameObjectGroup &group)
{
    m_gameObjectGroupList.push_back(group);
}

void PixelEngine::addGroup(const InteractiveCollisionGroup   &group)
{
    m_interactiveColliderGroupList.push_back(group);
}

/*void PixelEngine::addGroup(const ControllerGroup &group)
{
    m_controllerGroupList.push_back(group);
}
*/
void PixelEngine::addGroup(const PainterGroup    &group)
{
    m_painterGroupList.push_back(group);
}

