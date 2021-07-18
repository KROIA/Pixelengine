#include "submodule.h"

Submodule::Submodule()
{

    m_hasMoveToMake                             = false;
    m_hasEventsToCheck                          = false;
}
Submodule::~Submodule()
{

}

void Submodule::engineCalled_setup()
{

}

bool Submodule::hasEventsToCheck() const
{
    return m_hasEventsToCheck;
}
void Submodule::engineCalled_checkEvent()
{
     for(auto controller : m_controllerList)
         if(controller->hasEventsToCheck())
             controller->checkEvent();
     for(auto event  : m_eventList)
         event->checkEvent();
}
void Submodule::engineCalled_preTick()
{

}
void Submodule::engineCalled_tick(const Vector2i &direction)
{
    LayerItem::swapPosToLastPos();
    if(!m_hasMoveToMake)
        return;
    if(direction.x > 0)
    {
        m_collider->tick();
        m_movementCoordinator.clearMovement();
        SUBMODULE_BLOCK("for(size_t i=0; i<m_controllerList.size(); i++)",profiler::colors::Green300);
        for(size_t i=0; i<m_controllerList.size(); i++)
        {
            if(m_controllerList[i]->getMovingMode() == Controller::MovingMode::override)
                m_movementCoordinator.clearMovement();
            m_movementCoordinator.addMovement(m_controllerList[i]->getMovingVector());
            m_controllerList[i]->tick(); // Clears the movingVector
        }
        m_movementCoordinator.calculateMovement();
        LayerItem::move(Vector2f(m_movementCoordinator.getMovingVector_X(),0));
        m_collider->setRotation(LayerItem::getRotation());
        SUBMODULE_END_BLOCK;
    }
    else
    {
        LayerItem::move(Vector2f(0,m_movementCoordinator.getMovingVector_Y()));

        //emit signal
        if(m_submoduleSubscriberList.size() > 0)
            if(Vector::length(m_movementCoordinator.getMovingVector()) != 0)
                m_submoduleSubscriberList.moved(this,m_movementCoordinator.getMovingVector());

        m_movementCoordinator.tick();
        LayerItem::swapRotationToLastRotation();
    //    m_painter->setPos(LayerItem::getPos());
    //    m_painter->setRotation(LayerItem::getRotation());
        m_hasMoveToMake    = false;


    }

    m_collider->setPos(m_pos);
}
void Submodule::engineCalled_postTick()
{

}
void Submodule::engineCalled_preDraw()
{
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
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    LayerItem::setPosInitial(pos);
    m_collider->setPosInitial(pos);
 /*   if(m_painter != nullptr)
        m_painter->setPosInitial(pos);*/
}
/*void Submodule::setPos(int x,int y)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    LayerItem::setPos(x,y);
}
void Submodule::setPos(const Vector2i &pos)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    LayerItem::setPos(pos);
}*/
void Submodule::setPos(float x, float y)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    LayerItem::setPos(x,y);
}
void Submodule::setPos(const Vector2f &pos)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    LayerItem::setPos(pos);
}
/*void Submodule::setX(int x)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    LayerItem::setX(x);
}
void Submodule::setY(int y)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    LayerItem::setY(y);
*/
void Submodule::setX(float x)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    LayerItem::setX(x);
}
void Submodule::setY(float y)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    LayerItem::setY(y);
}

/*void Submodule::moveToPos(const Vector2i&destination,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->moveToPos(LayerItem::getPosI(),destination,mode);
}
void Submodule::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->moveToPos(LayerItem::getXI(),LayerItem::getYI(),x,y,mode);
}
void Submodule::move(const Vector2i&vec,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->move(vec,mode);
}
void Submodule::move(const Vector2f &vec,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->move(vec,mode);
}
void Submodule::move(const float &deltaX, const float &deltaY,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->move(deltaX,deltaY,mode);
}
void Submodule::moveX(const float &delta,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->moveX(delta,mode);
}
void Submodule::moveY(const float &delta,Controller::MovingMode mode)
{
    SUBMODULE_FUNCTION(profiler::colors::GreenA700);
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
    SUBMODULE_FUNCTION(profiler::colors::Green);
    if((int)(deg*1000) % 360000 == 0)
        return;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate(deg);
    LayerItem::rotate(deg);
    if(m_submoduleSubscriberList.size() > 0)
        m_submoduleSubscriberList.rotated(this,deg);
}

/*float Submodule::getRotation() const
{
    return LayerItem::getRotation();
}*/
void Submodule::setRotation(float deg)
{
    SUBMODULE_FUNCTION(profiler::colors::Green);
    if(m_rotation == deg)
        return;
    float deltaAngle = deg - m_rotation;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(deg);
    LayerItem::setRotation(deg);

    if(m_submoduleSubscriberList.size() > 0)
        m_submoduleSubscriberList.rotated(this,deltaAngle);
}
void Submodule::rotate_90()
{
    SUBMODULE_FUNCTION(profiler::colors::Green);
    rotate(90);
}
void Submodule::rotate_180()
{
    SUBMODULE_FUNCTION(profiler::colors::Green);
    rotate(180);
}
void Submodule::rotate_270()
{
    rotate(270);
    SUBMODULE_FUNCTION(profiler::colors::Green);
}
void Submodule::setRotation(const Vector2f &rotationPoint,const float &deg)
{
    SUBMODULE_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,deg);
    this->setPos(newPos);
    rotate(deg);
}
void Submodule::rotate_90(const Vector2f &rotationPoint)
{
    SUBMODULE_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,90);
    this->setPos(newPos);
    rotate(90);
}
void Submodule::rotate_180(const Vector2f &rotationPoint)
{
    SUBMODULE_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,180);
    this->setPos(newPos);
    rotate(180);
}
void Submodule::rotate_270(const Vector2f &rotationPoint)
{
    SUBMODULE_FUNCTION(profiler::colors::Green);
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
const vector<Controller* > &Submodule::getControllerList() const
{
    return m_controllerList;
}
Collider* Submodule::getCollider()
{
    return m_collider;
}
const Vector2f &Submodule::getMovingVector() const
{
    return m_movementCoordinator.getMovingVector();
}
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
}

void Submodule::addEvent(Event *e)
{
    if(!e)
        return;
    for(auto listed : m_eventList)
        if(listed == e)
            return;
    m_hasEventsToCheck = true;
    m_eventList.push_back(e);
}
void Submodule::removeEvent(Event *e)
{
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        if(m_eventList[i] == e)
        {
            m_eventList.erase(m_eventList.begin() + i);
            return;
        }
    }
}
void Submodule::addPainter(Painter *painter)
{
    if(!painter)
        return;
    for(auto listed : m_painterList)
        if(listed == painter)
            return;
    m_painterList.push_back(painter);
}
void Submodule::removePainter(Painter *painter)
{
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        if(m_painterList[i] == painter)
        {
            m_painterList.erase(m_painterList.begin() + i);
            return;
        }
    }
}
void Submodule::addController(Controller *controller)
{
    if(!controller)
        return;
    for(auto listed : m_controllerList)
        if(listed == controller)
            return;
    m_controllerList.push_back(controller);
    controller->subscribe_UserEventSignal(this);
    controller->subscribe_ControllerSignal(this);
    if(controller->hasEventsToCheck())
        m_hasEventsToCheck = true;
}
void Submodule::removeController(Controller *controller)
{
    for(size_t i=0; i<m_eventList.size(); i++)
    {
        if(m_controllerList[i] == controller)
        {
            m_controllerList.erase(m_controllerList.begin() + i);
            controller->unsubscribe_UserEventSignal(this);
            controller->unsubscribe_ControllerSignal(this);
            return;
        }
    }
}
void Submodule::setCollider(Collider *collider)
{
    m_collider = collider;
}

void Submodule::eventAdded(UserEventHandler *sender,  Event *e)
{
    m_hasEventsToCheck = true;
}
void Submodule::eventRemoved(UserEventHandler *sender,  Event *e)
{
    m_hasEventsToCheck = false;
    for(auto event : m_controllerList)
        m_hasEventsToCheck |= event->hasEventsToCheck();
}
void Submodule::moveAvailable(Controller *sender)
{
    m_hasMoveToMake = true;
}

