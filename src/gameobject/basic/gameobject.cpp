#include "gameobject.h"
#include "engineInterface.h"
#include "InteractiveGameObject.h"


ObjSubscriberList::ObjSubscriberList()
    :   SubscriberList<ObjSignal>()
{}


void ObjSubscriberList::moved(GameObject* sender,const Vector2f &move)
{
    EMIT_SIGNAL(moved,sender,move);
}
void ObjSubscriberList::rotated(GameObject* sender,const float deltaAngle)
{
    EMIT_SIGNAL(rotated,sender,deltaAngle);
}

GameObject::GameObject()
{
  //  m_originalCollider      = new Collider();
  //  m_originalPainter       = new PixelPainter();
  //  m_originalPainter->setVisibility(false);
  //  Controller  *controller = new Controller();

  //  constructor(controller,m_originalCollider,m_originalPainter);
    constructor();
}
/*GameObject::GameObject(const GameObject &other)
{
  //  m_originalCollider      = new Collider();
 //   m_originalPainter       = new PixelPainter();
  //  m_originalPainter->setVisibility(false);
    Controller  *controller = new Controller();


   // constructor(controller,m_originalCollider,m_originalPainter);
    m_thisInteractiveObject     = other.m_thisInteractiveObject;

    this->m_layerItem           = other.m_layerItem;
    this->m_property            = other.m_property;

    this->m_engine_interface     = other.m_engine_interface;
    this->m_display_interface   = other.m_display_interface;
    this->m_controllerList      = other.m_controllerList;
    this->m_hasEventsToCheck    = other.m_hasEventsToCheck;
    this->m_hasMoveToMake       = other.m_hasMoveToMake;
    this->m_movementCoordinator = other.m_movementCoordinator;
}
GameObject::GameObject(Controller *controller,
                       Collider   *collider,
                       Painter    *painter)
{
    constructor(controller,collider,painter);
}*/
void GameObject::constructor()
{

    // m_painter                                   = nullptr;
     m_collider                                 = nullptr;
     m_engine_interface                          = nullptr;
     m_display_interface                        = nullptr;
     m_thisInteractiveObject                    = nullptr;

     m_colliderPainter                          = new ColliderPainter();
     Submodule::addPainter(m_colliderPainter);

     m_controller                               = new Controller();
     addController(m_controller);

     m_originalCollider                         = new Collider();
     this->setCollider(m_originalCollider);
     m_utilityPainter                           = new VertexPathPainter();
     Submodule::addPainter(m_utilityPainter);



    this->m_visibility                          = true;
    setVisibility_colliderSearchRect(false);
    m_hasEventsToCheck                          = false;
    m_hasMoveToMake                             = false;
    m_isTrash                                   = false;
    //m_layerItem.setRotationInitial(0);

}
void GameObject::constructor(Controller *controller,
                             Collider   *collider,
                             Painter    *painter)
{



    this->addController(controller);
    this->setCollider(collider);
    this->addPainter(painter);

}

GameObject::~GameObject()
{
    //removePainter();
    //clearController();
    //delete m_originalCollider;
    //delete m_originalPainter;
    delete m_colliderPainter;
    delete m_originalCollider;
}
/*const GameObject &GameObject::operator=(const GameObject &other)
{
    this->m_controllerList      = other.m_controllerList;
    *this->m_collider           = *other.m_collider;
    this->m_painter             = other.m_painter;
    *this->m_colliderPainter    = *other.m_colliderPainter;
    this->m_property            = other.m_property;
    this->m_engine_interface     = other.m_engine_interface;
    this->m_display_interface   = other.m_display_interface;
    this->m_thisInteractiveObject = other.m_thisInteractiveObject;
    this->m_visibility          = other.m_visibility;
    this->m_isTrash = other.m_isTrash;
    return *this;
}*/
/*void GameObject::addEvent(Event *e)
{
    m_eventList.insert({e,e});
}
void GameObject::removeEvent(Event *e)
{
    m_eventList.erase(e);
}*/
void GameObject::engineCalled_checkEvent()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    Submodule::engineCalled_checkEvent();
    for(auto controller : m_controllerList)
        if(controller->hasEventsToCheck())
            controller->checkEvent(m_engine_deltaTime);
   /* for(size_t i=0; i<m_controllerList.size(); i++)
        if(m_controllerList[i]->hasEventsToCheck())
            m_controllerList[i]->checkEvent();*/
   /* for(auto eventPair  : m_eventList)
        eventPair.second->checkEvent();*/
    this->checkEvent();
}
void GameObject::checkEvent()
{

}
/*bool GameObject::hasEventsToCheck() const
{
    return m_hasEventsToCheck;
}*/
void GameObject::killMe()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green50);
    if(m_engine_interface != nullptr)
        m_engine_interface->kill(this);
}
void GameObject::removeMeFromEngine()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green100);
    if(m_engine_interface != nullptr)
        m_engine_interface->removeFromEngine(this);
}
void GameObject::engineCalled_setup()
{
    GAME_OBJECT_FUNCTION("GameObject::setup()",profiler::colors::Green300);
    this->setup();
    this->setPosInitial(m_pos);
}
void GameObject::setup()
{}
void GameObject::engineCalled_preTick()
{
    Submodule::engineCalled_preTick();
    m_collider->tick();
    size_t lastSize = m_collidedObjects.size();
    m_collidedObjects.clear();
    m_collidedObjects.reserve(lastSize+10);

    /*for(auto sensor : m_sensorList)
    {
        if(sensor->getEnableRelativePosition())
            sensor->setPos(m_pos);
        if(sensor->getEnableRelativeRotation())
            sensor->setRotation(m_rotation);
        sensor->engineCalled_preTick();
    }*/

    this->preTick();
}
void GameObject::preTick()
{}
void GameObject::engineCalled_tick(const Vector2i &direction)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green300);

    this->tick(direction);
    LayerItem::swapPosToLastPos();
    if(m_hasMoveToMake)
    {
        if(direction.x > 0)
        {
            //m_collider->tick();
            //m_movementCoordinator.clearMovement();
            m_movingVector.x = 0;
            m_movingVector.y = 0;
            GAME_OBJECT_BLOCK("for(size_t i=0; i<m_controllerList.size(); i++)",profiler::colors::Green300);
            for(size_t i=0; i<m_controllerList.size(); i++)
            {
                if(m_controllerList[i]->getMovingMode() == Controller::MovingMode::override)
                {
                    //m_movementCoordinator.clearMovement();
                    m_movingVector.x = 0;
                    m_movingVector.y = 0;
                }
                //m_movementCoordinator.addMovement(m_controllerList[i]->getMovingVector());
                m_movingVector += m_controllerList[i]->getMovingVector();

                m_controllerList[i]->tick(); // Clears the movingVector
            }
            //m_movementCoordinator.calculateMovement();
            //LayerItem::move(Vector2f(m_movementCoordinator.getMovingVector_X(),0));
            LayerItem::moveX(m_movingVector.x);

            m_collider->setRotation(LayerItem::getRotation());
            GAME_OBJECT_END_BLOCK;
        }
        else
        {
            //LayerItem::move(Vector2f(0,m_movementCoordinator.getMovingVector_Y()));
            LayerItem::moveY(m_movingVector.y);

            //emit signal
            /*if(m_objSubscriberList.size() > 0)
                if(Vector::length(m_movementCoordinator.getMovingVector()) != 0)
                    m_objSubscriberList.moved(this,m_movementCoordinator.getMovingVector());

            m_movementCoordinator.tick();
            if(m_lastRotation != m_rotation)
            {
                if(m_objSubscriberList.size() > 0)
                    m_objSubscriberList.rotated(this,m_rotation-m_lastRotation);
                Submodule::swapRotationToLastRotation();
            }*/
            m_hasMoveToMake    = false;
        }
    }
    for(auto sensor : m_sensorList)
        sensor->engineCalled_tick(direction);
    Submodule::engineCalled_tick(direction);
    m_collider->setPos(m_pos);
    m_collider->setRotation(m_rotation);
    m_colliderSearchBox.setPos(m_pos+m_colliderSearchBoxRelativePos);
    for(auto sensor : m_sensorList)
    {
        if(sensor->getEnableRelativePosition())
            sensor->setPos(m_pos);
        if(sensor->getEnableRelativeRotation())
            sensor->setRotation(m_rotation);
        sensor->engineCalled_preTick();
    }
    //m_collider->setPos(m_pos);

}
void GameObject::tick(const Vector2i &direction)
{}
void GameObject::engineCalled_postTick()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green300);
    Submodule::engineCalled_postTick();
    m_collider->setPos(m_pos);
    m_collider->setRotation(m_rotation);
    m_colliderSearchBox.setPos(m_pos+m_colliderSearchBoxRelativePos);

    for(auto sensor : m_sensorList)
    {
        if(sensor->getEnableRelativePosition())
            sensor->setPos(m_pos);
        if(sensor->getEnableRelativeRotation())
            sensor->setRotation(m_rotation);
        sensor->engineCalled_preTick();
    }

    for(auto sensor : m_sensorList)
        sensor->engineCalled_postTick();

    postTick();
}

void GameObject::postTick()
{}
void GameObject::engineCalled_postNoThreadTick()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green300);
    Submodule::engineCalled_postNoThreadTick();
    if(m_objSubscriberList.size() > 0)
        if(Vector::length(/*m_movementCoordinator.getMovingVector()*/m_movingVector) != 0)
            m_objSubscriberList.moved(this,/*m_movementCoordinator.getMovingVector()*/m_movingVector);

    m_movementCoordinator.tick();
    if(m_lastRotation != m_rotation)
    {
        if(m_objSubscriberList.size() > 0)
            m_objSubscriberList.rotated(this,m_rotation-m_lastRotation);
        LayerItem::swapRotationToLastRotation();
    }
}
void GameObject::engineCalled_preDraw()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green300);
    if(!m_visibility)
        return;
    m_colliderPainter->update(m_collidedObjects);
    Submodule::engineCalled_preDraw();
    for(auto sensor : m_sensorList)
        sensor->engineCalled_preDraw();
    this->preDraw();
    m_utilityPainter->clear();
    if(m_visibility_colliderSearchBox)
        m_utilityPainter->addPath(m_colliderSearchBox.getDrawable(Color(255,255,0)));
  /*  if(m_painter != m_originalPainter && m_painter->isVisible())
    {
        m_painter->setPos(m_layerItem.getPos());
        m_painter->setRotation(m_layerItem.getRotation());
    }
    if(m_colliderPainter->isVisible())
        m_colliderPainter->update(m_collidedObjects);
    this->preDraw();*/

}
void GameObject::preDraw()
{}

unsigned int GameObject::checkCollision(const vector<GameObject*> &other)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green400);
    for(auto sensor : m_sensorList)
        sensor->detectObjects(other);

    vector<GameObject*> collided = GameObject::getCollidedObjects(this, m_collider, other);
    for(size_t i=0; i<collided.size(); i++)
        m_collidedObjects.push_back(collided[i]);
    if(m_collidedObjects.size() > 0)
    {
        event_hasCollision(m_collidedObjects);
    }
    return m_collidedObjects.size();
}
vector<GameObject*> GameObject::getCollidedObjects(GameObject *owner, Collider *collider,const vector<GameObject*> &other)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green600);
    vector<GameObject*> collided;
    for(size_t i=0; i<other.size(); i++)
    {
        if(owner == other[i])
            continue; // This is the same object like other[i]
        if(collider->intersectsBoundingBox(other[i]->m_collider))
        {
            if(collider->collides(other[i]->m_collider))
            {
                collided.push_back(other[i]);
            }
        }
    }
    return collided;
}

/*void GameObject::subscribeToDisplay(PixelDisplay &display)
{
    display.subscribePainter(m_painterList);
}
void GameObject::unsubscribeToDisplay(PixelDisplay &display)
{
    display.unsubscribePainter(m_painterList);
}*/

void GameObject::setDisplayInterface(DisplayInterface *display)
{
    if(m_display_interface && !display)
        m_display_interface->unsubscribePainter(m_painterList);

    m_display_interface = display;

    if(m_display_interface)
        m_display_interface->subscribePainter(m_painterList);
}


void GameObject::subscribe_ObjSignal(ObjSignal *subscriber)
{
    if(subscriber == nullptr)
        return;
    m_objSubscriberList.insert(subscriber);
}
void GameObject::unsubscribe_ObjSignal(ObjSignal *subscriber)
{
    m_objSubscriberList.erase(subscriber);
}
void GameObject::unsubscribeAll_ObjSignal()
{
    m_objSubscriberList.clear();
}

/*void GameObject::addController(CgetEngineInterfaceroller)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green800);
    if(controller == nullptr)
        return;

    for(size_t i=0; i<m_controllerList.size(); i++)
        if(m_controllerList[i] == controller)
            return;

    m_controllerList.push_back(controller);
    if(controller->hasEventsToCheck())
        m_hasEventsToCheck = true;
    controller->subscribe_UserEventSignal(this);
    controller->subscribe_ControllerSignal(this);
}
void GameObject::clearController()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green900);
    size_t size = m_controllerList.size();
    for(size_t i=1; i<size; i++)
    {
        m_controllerList[1]->unsubscribe_UserEventSignal(this);
        m_controllerList[1]->unsubscribe_ControllerSignal(this);
        delete m_controllerList[1];
        m_controllerList.erase(m_controllerList.begin()+1);
    }
}
*/
void GameObject::setCollider(Collider *collider)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA100);
    if(m_collider == collider || collider == nullptr)
        return;
    if(m_collider)
        m_collider->unsubscribe_ColliderSignal(this);
    m_collider = collider;
    m_collider->setPos(m_pos);
    m_colliderPainter->setCollider(m_collider);
    m_collider->subscribe_ColliderSignal(this);
    m_colliderSearchBox = m_collider->getBoundingBox();
    m_colliderSearchBoxRelativePos = m_colliderSearchBox.getPos() - m_pos;
    boundingBoxChanged(m_collider);
}
Collider *GameObject::getCollider() const
{
    return m_collider;
}
void GameObject::setCollisionSeachRadius(float radius)
{
    m_colliderSearchBoxRadius = radius;
    m_colliderSearchBoxRelativePos = Vector2f(-radius,-radius);
    m_colliderSearchBox.setPos(m_pos + m_colliderSearchBoxRelativePos);
    m_colliderSearchBox.setSize(m_colliderSearchBoxRelativePos * -2.f);

}
float GameObject::getCollisionSeachRadius() const
{
    return m_colliderSearchBoxRadius;
}
const RectF &GameObject::getCollisionSeachRect() const
{
    return m_colliderSearchBox;
}
void GameObject::addController(Controller *controller)
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
void GameObject::removeController(Controller *controller)
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
const vector<Controller* > &GameObject::getControllerList() const
{
    return m_controllerList;
}

void GameObject::addSensor(Sensor *sensor)
{
    if(!sensor)
        return;
    for(auto listed : m_sensorList)
        if(listed == sensor)
            return;
    sensor->setOwner(this);
    m_sensorList.push_back(sensor);

    vector<Event*> eList = sensor->getEventList();
    vector<Painter*> pList = sensor->getPainterList();

    for(auto e : eList)
        this->addEvent(e);

    for(auto p : pList)
        this->addPainter(p);

}
void GameObject::removeSensor(Sensor *sensor)
{
    for(size_t i=0; i<m_sensorList.size(); i++)
    {
        if(m_sensorList[i] == sensor)
        {
            m_sensorList.erase(m_sensorList.begin() + i);

            vector<Event*> eList = sensor->getEventList();
            vector<Painter*> pList = sensor->getPainterList();

            for(auto e : eList)
                this->removeEvent(e);

            for(auto p : pList)
                this->removePainter(p);
            sensor->setOwner(nullptr);
            return;
        }
    }
}
const vector<Sensor*> &GameObject::getSensorList() const
{
    return m_sensorList;
}
/*
const Collider &GameObject::getCollider() const
{
    return *m_collider;
}
void GameObject::setPainter(Painter *painter)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA200);
    if(m_painter == painter || painter == nullptr)
        return;
    if(m_painter != nullptr)
        display_unsubscribePainter(m_painter);
    m_painter = painter;
    display_subscribePainter(m_painter);
}
const Painter &GameObject::getPainter() const
{
    return *m_painter;
}*/

void GameObject::setPosInitial(const Vector2f &pos)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    Submodule::setPosInitial(pos);
    m_collider->setPosInitial(pos);
    m_colliderSearchBox.setPos(m_pos+m_colliderSearchBoxRelativePos);
    if(m_property.getBody().material    == Property::Material::Grass)
    {
    //   qDebug()<<"grass initialPosSet";
    }
}
/*
void GameObject::setPos(int x,int y)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(x,y);
}
void GameObject::setPos(const Vector2i &pos)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(pos);
}
void GameObject::setPos(float x, float y)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(x,y);
}
void GameObject::setPos(const Vector2f &pos)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(pos);
}
void GameObject::setX(int x)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(float(x),m_layerItem.getY());
}
void GameObject::setY(int y)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(m_layerItem.getX(),float(y));
}
void GameObject::setX(float x)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(x,m_layerItem.getY());
}
void GameObject::setY(float y)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(m_layerItem.getX(),y);
}*/

/*void GameObject::moveToPos(const Vector2i&destination,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_controller->moveToPos(m_pos,destination,mode);
}
void GameObject::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->moveToPos(m_layerItem.getXI(),m_layerItem.getYI(),x,y,mode);
}
void GameObject::move(const Vector2i&vec,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->move(vec,mode);
}*/
void GameObject::move(const Vector2f &vec,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_controller->move(vec,mode);
    if(m_property.getBody().material    == Property::Material::Grass)
    {
        qDebug()<<"grass moved";
    }
}
void GameObject::move(float deltaX, float deltaY,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_controller->move(deltaX,deltaY,mode);
    if(m_property.getBody().material    == Property::Material::Grass)
    {
        qDebug()<<"grass moved";
    }
}
void GameObject::moveX(float delta,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_controller->moveX(delta,mode);
    if(m_property.getBody().material    == Property::Material::Grass)
    {
        qDebug()<<"grass moved";
    }
}
void GameObject::moveY(float delta,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    m_controller->moveY(delta,mode);
    if(m_property.getBody().material    == Property::Material::Grass)
    {
        qDebug()<<"grass moved";
    }
}
void GameObject::rotate(float deg)
{
    if((int)(deg*1000) % 360000 == 0)
        return;

    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate(deg);
    Submodule::rotate(deg);
}
void GameObject::setRotation(float deg)
{
    if(m_rotation == deg)
        return;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(deg);
    Submodule::setRotation(deg);
}

void GameObject::setRotation(const Vector2f &rotationPoint,float deg)
{
    Submodule::setRotation(rotationPoint,deg);
}

/*
const Vector2f &GameObject::getPos() const
{
    return m_layerItem.getPos();
}*/
/*const Vector2f &GameObject::getMovingVector() const
{
    return m_movementCoordinator.getMovingVector();
}*/
/*
void GameObject::rotate(const float &deg)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    if((int)(deg*1000) % 360000 == 0)
        return;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate(deg);
    m_layerItem.rotate(deg);
    if(m_objSubscriberList.size() > 0)
        m_objSubscriberList.rotated(this,deg);
}

float GameObject::getRotation() const
{
    return m_layerItem.getRotation();
}
void GameObject::setRotation(const float &deg)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    if(m_layerItem.getRotation() == deg)
        return;
    float deltaAngle = deg - m_layerItem.getRotation();
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(deg);
    m_layerItem.setRotation(deg);

    if(m_objSubscriberList.size() > 0)
        m_objSubscriberList.rotated(this,deltaAngle);
}
void GameObject::rotate_90()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    rotate(90);
}
void GameObject::rotate_180()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    rotate(180);
}
void GameObject::rotate_270()
{
    rotate(270);
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
}
void GameObject::setRotation(const Vector2f &rotationPoint,const float &deg)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,deg);
    this->setPos(newPos);
    rotate(deg);
}
void GameObject::rotate_90(const Vector2f &rotationPoint)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,90);
    this->setPos(newPos);
    rotate(90);
}
void GameObject::rotate_180(const Vector2f &rotationPoint)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,180);
    this->setPos(newPos);
    rotate(180);
}
void GameObject::rotate_270(const Vector2f &rotationPoint)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,270);
    this->setPos(newPos);
    rotate(270);
}*/
/*void GameObject::addHitbox(const RectI &box)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green100);
    m_collider->addHitbox(box);
}
void GameObject::addHitbox(const vector<RectI> &boxList)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green100);
    m_collider->addHitbox(boxList);
}
void GameObject::eraseHitbox(const size_t &index)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green200);
    m_collider->erase(index);
}
void GameObject::clearCollider()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green300);
    m_collider->clear();
}
const bool &GameObject::isBoundingBoxUpdated() const
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green400);
    return m_collider->isBoundingBoxUpdated();
}
void GameObject::updateBoundingBox()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green500);
    m_collider->updateBoundingBox();
}

void GameObject::setHitboxFromTexture(const Texture &texture)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green600);
    m_collider->setHitboxFromTexture(&texture);
}
const RectF &GameObject::getBoundingBox() const
{
    return m_collider->getBoundingBox();
}*/


/*
void GameObject::setRenderLayer(size_t layer)
{
    m_painter->setRenderLayer(layer);
}
size_t GameObject::getRenderLayer() const
{
    m_painter->getRenderLayer();
}*/
bool GameObject::addPainter(Painter *painter)
{
    if(Submodule::addPainter(painter))
    {
        if(m_display_interface)
            m_display_interface->subscribePainter(painter);
        return true;
    }
    return false;
}
bool GameObject::removePainter(Painter *painter)
{
    if(Submodule::removePainter(painter))
    {
        if(m_display_interface)
            m_display_interface->unsubscribePainter(painter);
        return true;
    }
    return false;
}
ColliderPainter *GameObject::getColliderPainter() const
{
    return m_colliderPainter;
}
void GameObject::setVisibility(bool isVisible)
{
    m_visibility = isVisible;
    Submodule::setVisibility(isVisible);
}
void GameObject::setVisibility_objectTree(bool isVisible)
{
    if(m_thisInteractiveObject != nullptr)
        m_thisInteractiveObject->setVisibility_objectTree(isVisible);
}
void GameObject::setVisibility_colliderSearchRect(bool isVisible)
{
    m_visibility_colliderSearchBox = isVisible;
    checkIfUtilityPainterIsUsed();
}
void GameObject::checkIfUtilityPainterIsUsed()
{
    m_utilityPainter->setVisibility(m_visibility_colliderSearchBox);
}

/*
void GameObject::setVisibility_collider_hitbox(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green700);
    m_colliderPainter->setVisibility_hitBox(isVisible);
}
void GameObject::setVisibility_collider_boundingBox(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green700);
    m_colliderPainter->setVisibility_boundingBox(isVisible);
}
void GameObject::setVisibility_collider_collisionData(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green700);
    m_colliderPainter->setVisibility_collisionData(isVisible);

}
void GameObject::setVisibility_collider_isCollidingWith_boundingBox(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green700);
    m_colliderPainter->setVisibility_collidedObjects_boundingBox(isVisible);
}
void GameObject::setVisibility_collider_isCollidingWith_hitBox(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green700);
    m_colliderPainter->setVisibility_collidedObjects_hitBox(isVisible);
}*/

bool GameObject::isVisible() const
{
    return m_visibility;
}
bool GameObject::isVisible_objectTree() const
{
    if(m_thisInteractiveObject != nullptr)
        return m_thisInteractiveObject->isVisible_objectTree();
    return false;
}
bool GameObject::isVisible_colliderSearchRect() const
{
    return m_visibility_colliderSearchBox;
}
/*
bool GameObject::isVisible_collider_hitbox() const
{
    return m_colliderPainter->isVisible_hitBox();
}
bool GameObject::isVisible_collider_boundingBox() const
{
    return m_colliderPainter->isVisible_boundingBox();
}
bool GameObject::isVisible_collider_collisionData() const
{
    return m_colliderPainter->isVisible_collisionData();
}
bool GameObject::isVisible_collider_isCollidingWith() const
{
    return m_colliderPainter->isVisible_collidedObjects();
}*/


void GameObject::setProperty(const Property::Property &property)
{
    m_property = property;
}
const Property::Property &GameObject::getProperty() const
{
    return m_property;
}
/*
void GameObject::addPainter(Painter *painter)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA400);
    if(painter == nullptr)
        return;

    m_painterList.insert({painter,painter});
    if(m_engine_interface != nullptr)
        m_engine_interface->addPainterToDisplay(painter);
}
void GameObject::removePainter(Painter *painter)
{
    GAME_OBJECT_FUNCTION(profiler::colors::GreenA700);
    if(painter == nullptr)
        return;
    if(m_engine_interface != nullptr)
        m_engine_interface->removePainterFromDisplay(painter);
    m_painterList.erase(painter);
}
void GameObject::removePainter()
{
    m_painterList.clear();
}


vector<Painter*> GameObject::getPainterList()
{
    vector<Painter* > pList;
    pList.reserve(m_painterList.size());
    for(auto p : m_painterList)
        pList.push_back(p.second);
    return pList;
}*/

void GameObject::markAsTrash(bool isTrash)
{
    m_isTrash = isTrash;
    if(!m_isTrash)
        return;
}
bool GameObject::isTrash() const
{
    return m_isTrash;
}
void GameObject::setThisInteractiveGameObject(InteractiveGameObject *parent)
{
    if(m_thisInteractiveObject != nullptr && parent != nullptr)
    {
        qDebug() << "WARNING: GameObject::setThisInteractiveGameObject(InteractiveGameObject *parent): InteractiveGameObject was already set";
        qDebug() << "  Last InteractiveGameObject: "<<m_thisInteractiveObject;
        qDebug() << "  New InteractiveGameObject:  "<<parent;
        qDebug() << "  This shuld be used only once!";
    }
    m_thisInteractiveObject = parent;
}
InteractiveGameObject* GameObject::getThisInteractiveGameObject()
{
    return m_thisInteractiveObject;
}
void GameObject::display_setPixel(const Vector2u &pos, const Color &color)
{
    if(m_display_interface)
        m_display_interface->setPixel(pos,color);
}
void GameObject::display_setPixel(const Pixel &pixel)
{
    if(m_display_interface)
        m_display_interface->setPixel(pixel);
}
void GameObject::display_setPixel(const vector<Pixel> &pixelList)
{
    if(m_display_interface)
        m_display_interface->setPixel(pixelList);
}
void GameObject::display_zoomViewAt(sf::Vector2i pixel, float zoom)
{
    if(m_display_interface)
        m_display_interface->zoomViewAt(pixel,zoom);
}
void GameObject::display_setView(const RectF &frame)
{
    if(m_display_interface)
        m_display_interface->setView(frame);
}
void GameObject::display_setCameraZoom(float zoom)
{
    if(m_display_interface)
        m_display_interface->setCameraZoom(zoom);
}
void GameObject::display_setCameraPos(const Vector2f &pos)
{
    if(m_display_interface)
        m_display_interface->setCameraPos(pos);
}
const Vector2u &GameObject::display_getWindowSize() const
{
    if(m_display_interface)
        return m_display_interface->getWindowSize();
    return m_dummiVecU;
}
const Vector2u &GameObject::display_getMapSize() const
{
    if(m_display_interface)
        return m_display_interface->getMapSize();
    return m_dummiVecU;
}
void GameObject::display_subscribePainter(Painter *painter)
{
    if(m_display_interface)
        m_display_interface->subscribePainter(painter);
}
void GameObject::display_unsubscribePainter(Painter *painter)
{
    if(m_display_interface)
        m_display_interface->unsubscribePainter(painter);
}

void GameObject::event_hasCollision(vector<GameObject *> other)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Green100);
    if(m_engine_interface != nullptr)
        m_engine_interface->collisionOccured(this,other);
    Submodule::setToLastPos();
    LayerItem::setToLastRotation();

   /* m_collider->setPos(m_layerItem.getPos());
    m_painter->setPos(m_layerItem.getPos());
    m_collider->setRotation(m_layerItem.getRotation());
    m_painter->setRotation(m_layerItem.getRotation());

    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(m_layerItem.getRotation());*/
}

void GameObject::eventAdded(UserEventHandler *sender,  Event *e)
{
    m_hasEventsToCheck = true;
}
void GameObject::eventRemoved(UserEventHandler *sender,  Event *e)
{
    m_hasEventsToCheck = false;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_hasEventsToCheck |= m_controllerList[i]->hasEventsToCheck();
}
void GameObject::moveAvailable(Controller *sender)
{
    m_hasMoveToMake = true;
}
void GameObject::boundingBoxChanged(Collider* sender)
{
    if(RectF::intersects_inverseOf_fast(sender->getBoundingBox(),m_colliderSearchBox))
    {
        // BoundingBox of Collider is outside or at the edge of the m_colliderSearchBox
        Vector2f min;
        min.x = RectF::getMinX({sender->getBoundingBox(),m_colliderSearchBox});
        min.y = RectF::getMinY({sender->getBoundingBox(),m_colliderSearchBox});

        Vector2f max;
        max.x = RectF::getMaxX({sender->getBoundingBox(),m_colliderSearchBox});
        max.y = RectF::getMaxY({sender->getBoundingBox(),m_colliderSearchBox});

        Vector2f relativeMin = m_pos - min;
        Vector2f relativeMax = m_pos - max;

        float radius = abs(relativeMin.x);
        if(radius<abs(relativeMin.y))
            radius = abs(relativeMin.y);
        if(radius<abs(relativeMax.x))
            radius = abs(relativeMax.x);
        if(radius<abs(relativeMax.y))
            radius = abs(relativeMax.y);



        setCollisionSeachRadius(radius);
    }
}


