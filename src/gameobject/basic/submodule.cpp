#include "submodule.h"
/*
SubmoduleSubscriberList::SubmoduleSubscriberList()
    :   SubscriberList<SubmoduleSignal>()
{}
void SubmoduleSubscriberList::moved(Submodule* sender,const Vector2f &move)
{
    SIGNAL_EMIT_INTERN(moved,sender,move);
}
void SubmoduleSubscriberList::rotated(Submodule* sender,const float deltaAngle)
{
    SIGNAL_EMIT_INTERN(rotated,sender,deltaAngle);
}
*/
//const PixelDisplay *Submodule::m_display = nullptr;
Submodule::Submodule()
    :   LayerItem()
{
    m_hasEventsToCheck  = false;
    m_hasMoveToMake     = false;
    m_engine_deltaTime  = 1;

   // m_originalCollider  = new Collider();
   // this->setCollider(m_originalCollider);
  /*  if(m_display == nullptr)
    {
        qDebug() << "Submodule::m_display == nullptr, can cause problems";
    }*/
}
Submodule::Submodule(const Submodule &other)
    :   LayerItem(other)
{
    *this = other;
}
Submodule::~Submodule()
{
    //delete m_originalCollider;
}
const Submodule &Submodule::operator=(const Submodule &other)
{
    LayerItem::operator=(other);
    this->m_hasEventsToCheck    = other.m_hasEventsToCheck;
    this->m_hasMoveToMake       = other.m_hasMoveToMake;
    this->m_movingVector        = other.m_movingVector;
    return *this;
}
void Submodule::engineCalled_setup()
{

}
void Submodule::setEngineInterface(EngineInterface *engine)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA400);
    if(m_engine_interface ==  engine)
        return;

    if(engine == nullptr)
    {
       // qDebug()<<"engineInterface == null";
        /*for(auto pair : m_painterList)
            m_engine_interface->removePainterFromDisplay(m_painterList);*/
        /*for(auto pair : m_eventList)
            m_engine_interface->removeEvent(pair.second);*/
    }

    m_engine_interface = engine;
  /*  for(auto pair : m_painterList)
        m_engine_interface->addPainterToDisplay(pair.second);*/
   /* for(auto pair : m_eventList)
        m_engine_interface->addEvent(pair.second);*/
}
EngineInterface *Submodule::getEngineInterface() const
{
    return m_engine_interface;
}
/*void Submodule::setDisplay(const PixelDisplay *display)
{
    m_display = display;
}*/
bool Submodule::hasEventsToCheck() const
{
    return m_hasEventsToCheck;
}
void Submodule::engineCalled_checkEvent(float deltaTime)
{
    SUBMODULE_FUNCTION(profiler::colors::Red);
  //  if(m_engine_interface)
   //     m_engine_deltaTime = m_engine_interface->getDeltaTime();
    m_engine_deltaTime = deltaTime;
    for(auto event  : m_eventList)
        event->checkEvent(deltaTime);
}
void Submodule::engineCalled_preTick()
{
    SUBMODULE_FUNCTION(profiler::colors::Red100);
   // m_collider->tick();

}
void Submodule::engineCalled_tick(const Vector2i &direction)
{
    SUBMODULE_FUNCTION(profiler::colors::Red200);
   // m_collider->setPos(m_pos);
   // m_collider->setRotation(m_rotation);
}
void Submodule::engineCalled_postTick()
{
    SUBMODULE_FUNCTION(profiler::colors::Red300);
   // m_collider->setPos(m_pos);
   // m_collider->setRotation(m_rotation);
}
void Submodule::engineCalled_postNoThreadTick()
{
    SUBMODULE_FUNCTION(profiler::colors::Red400);
    if(m_rotation != m_lastRotation)
       /* if(m_submoduleSubscriberList.size() > 0)
            m_submoduleSubscriberList.rotated(this,m_rotation-m_lastRotation);*/
        SIGNAL_EMIT(Submodule,rotated,m_rotation-m_lastRotation)
}

void Submodule::engineCalled_preDraw()
{
    SUBMODULE_FUNCTION(profiler::colors::Red500);
    for(auto p : m_painterList)
    {
        if(p->getEnableRelativePosition())
            p->setPos(m_pos);
        if(p->getEnableRelativeRotation())
            p->setRotation(m_rotation);
    }
}



void Submodule::setPosInitial(const Vector2f &pos)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    LayerItem::setPosInitial(pos);
   // m_collider->setPosInitial(pos);
}
void Submodule::setPos(float x, float y)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    LayerItem::setPos(x,y);
}
void Submodule::setPos(const Vector2f &pos)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    LayerItem::setPos(pos);
}

void Submodule::setX(float x)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    LayerItem::setX(x);
}
void Submodule::setY(float y)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    LayerItem::setY(y);
}

/*void Submodule::moveToPos(const Vector2i&destination,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    m_controllerList[0]->moveToPos(LayerItem::getPosI(),destination,mode);
}
void Submodule::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    m_controllerList[0]->moveToPos(LayerItem::getXI(),LayerItem::getYI(),x,y,mode);
}
void Submodule::move(const Vector2i&vec,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    m_controllerList[0]->move(vec,mode);
}
void Submodule::move(const Vector2f &vec,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    m_controllerList[0]->move(vec,mode);
}
void Submodule::move(const float &deltaX, const float &deltaY,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    m_controllerList[0]->move(deltaX,deltaY,mode);
}
void Submodule::moveX(const float &delta,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    m_controllerList[0]->moveX(delta,mode);
}
void Submodule::moveY(const float &delta,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::RedA700);
    m_controllerList[0]->moveY(delta,mode);
}

const Vector2f &Submodule::getPos() const
{
    return LayerItem::getPos();
}
const Vector2f &Submodule::getMovingVector() const
{
    return m_movementCoordinator.getMovingVector();
}*/

void Submodule::rotate(float deg)
{
    SUBMODULE_FUNCTION(profiler::colors::Red);
    if((int)(deg*1000) % 360000 == 0)
        return;

    LayerItem::rotate(deg);
   // if(m_submoduleSubscriberList.size() > 0)
   //     m_submoduleSubscriberList.rotated(this,deg);
}

/*float Submodule::getRotation() const
{
    return LayerItem::getRotation();
}*/
void Submodule::setRotation(float deg)
{
    SUBMODULE_FUNCTION(profiler::colors::Red);
    if(m_rotation == deg)
        return;
    //float deltaAngle = deg - m_rotation;

    LayerItem::setRotation(deg);

  //  if(m_submoduleSubscriberList.size() > 0)
   //     m_submoduleSubscriberList.rotated(this,deltaAngle);
}
void Submodule::rotate_90()
{
    SUBMODULE_FUNCTION(profiler::colors::Red);
    rotate(90);
}
void Submodule::rotate_180()
{
    SUBMODULE_FUNCTION(profiler::colors::Red);
    rotate(180);
}
void Submodule::rotate_270()
{
    rotate(270);
    SUBMODULE_FUNCTION(profiler::colors::Red);
}
void Submodule::setRotation(const Vector2f &rotationPoint,float deg)
{
    SUBMODULE_FUNCTION(profiler::colors::Red);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,deg);
    this->setPos(newPos);
    rotate(deg);
}
void Submodule::rotate_90(const Vector2f &rotationPoint)
{
    SUBMODULE_FUNCTION(profiler::colors::Red);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,90);
    this->setPos(newPos);
    rotate(90);
}
void Submodule::rotate_180(const Vector2f &rotationPoint)
{
    SUBMODULE_FUNCTION(profiler::colors::Red);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,180);
    this->setPos(newPos);
    rotate(180);
}
void Submodule::rotate_270(const Vector2f &rotationPoint)
{
    SUBMODULE_FUNCTION(profiler::colors::Red);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,270);
    this->setPos(newPos);
    rotate(270);
}

void Submodule::setRenderLayer(size_t layer)
{
    for(auto p : m_painterList)
        p->setRenderLayer(layer);
}
/*size_t Submodule::getRenderLayer() const
{

}*/

void Submodule::setVisibility(bool isVisible)
{
    for(auto p : m_painterList)
        p->setVisibility(isVisible);
}
/*bool Submodule::isVisible() const
{

}*/

const vector<Event* > &Submodule::getEventList() const
{
    return m_eventList;
}
const vector<Painter* > &Submodule::getPainterList() const
{
    return m_painterList;
}
/*Collider* Submodule::getCollider()
{
    return m_collider;
}*/
const Vector2f &Submodule::getMovingVector() const
{
    return m_movingVector;
    //return m_movementCoordinator.getMovingVector();
}
/*
void Submodule::subscribe_SubmoduleSignal(SubmoduleSignal *subscriber)
{
    if(subscriber == nullptr)
        return;
    m_submoduleSubscriberList.insert(subscriber);
}
void Submodule::unsubscribe_SubmoduleSignal(SubmoduleSignal *subscriber)
{
    m_submoduleSubscriberList.erase(subscriber);
}
void Submodule::unsubscribeAll_SubmoduleSignal()
{
    m_submoduleSubscriberList.clear();
}*/

bool Submodule::addEvent(Event *e)
{
    if(!e)
        return false;
    for(auto listed : m_eventList)
        if(listed == e)
            return false;
    m_hasEventsToCheck = true;
    m_eventList.push_back(e);
    return true;
}
bool Submodule::removeEvent(Event *e)
{
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        if(m_eventList[i] == e)
        {
            m_eventList.erase(m_eventList.begin() + i);
            return true;
        }
    }
    return false;
}
bool Submodule::addPainter(Painter *painter)
{
    if(!painter)
        return false;
    for(auto listed : m_painterList)
        if(listed == painter)
            return false;
    m_painterList.push_back(painter);
    painter->setPos(m_pos);
    return true;
}
bool Submodule::removePainter(Painter *painter)
{
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        if(m_painterList[i] == painter)
        {
            m_painterList.erase(m_painterList.begin() + i);
            return true;
        }
    }
    return false;
}

float Submodule::getEngine_deltaTime() const
{
    return m_engine_deltaTime;
}

/*void Submodule::setCollider(Collider *collider)
{
    m_collider = collider;
    m_collider->setPos(m_pos);
}
Collider *Submodule::getCollider() const
{
    return m_collider;
}*/


