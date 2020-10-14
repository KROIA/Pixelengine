#include "gameobject.h"
#include "gameObjectEventHandler.h"

GameObject::GameObject()
{
    this->addController(new Controller());
    m_collider      = new Collider();
    m_painter       = new Painter();
    m_hitboxPainter = new Painter();
    m_objEventHandler = nullptr;
    m_rotationDeg      = 90; // 90 deg
}
GameObject::GameObject(const GameObject &other)
{
    this->addController(new Controller());
    m_collider      = new Collider();
    m_painter       = new Painter();
    m_hitboxPainter = new Painter();
    m_objEventHandler = nullptr;
    *this = other;
}
GameObject::GameObject(Controller *controller,
                       Collider   *collider,
                       Painter    *painter)
{
    this->addController(controller);
    this->setCollider(collider);
    this->setPainter(painter);
}

GameObject::~GameObject()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        delete m_controllerList[i];
    m_controllerList.clear();
    delete m_collider;
    delete m_painter;
    delete m_hitboxPainter;
}
const GameObject &GameObject::operator=(const GameObject &other)
{
    this->m_controllerList    = other.m_controllerList;
    *this->m_collider      = *other.m_collider;
    *this->m_painter       = *other.m_painter;
    *this->m_hitboxPainter = *other.m_hitboxPainter;
    this->m_property       = other.m_property;
    this->m_objEventHandler = other.m_objEventHandler;
    this->m_rotationDeg       = other.m_rotationDeg;
    return *this;
}
void GameObject::checkEvent()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->checkEvent();
}
void GameObject::tick(const Point &direction)
{
    m_layerItem.swapPosToLastPos();
    if(direction.getX() > 0)
    {

        for(size_t i=0; i<m_controllerList.size(); i++)
        {
            if(m_controllerList[i]->getMovingMode() == Controller::MovingMode::override)
                m_movementCoordinator.clearMovement();
            m_movementCoordinator.addMovement(m_controllerList[i]->getMovingVector());
            m_controllerList[i]->tick(); // Clears the movingVector
        }
        m_movementCoordinator.calculateMovement();
        //m_controller->tick();
        //m_layerItem.moveX(int(round(m_controller->getMovingVector().getX())));

        m_layerItem.moveX_F(m_movementCoordinator.getMovingVector_X());
        //m_layerItem.moveX(round(m_movementCoordinator.getMovingVector_X()));
        //if(m_movementCoordinator.getMovingVector().getX() != 0 || m_movementCoordinator.getMovingVector().getY() != 0)
        //   qDebug() << "vec: "<<m_movementCoordinator.getMovingVector_X()<<"\t"<<m_movementCoordinator.getMovingVector_Y();
    }
    else
    {
        //m_layerItem.moveY(int(round(m_controller->getMovingVector().getY())));

        m_layerItem.moveY_F(m_movementCoordinator.getMovingVector_Y());
        //m_layerItem.moveY(round(m_movementCoordinator.getMovingVector_Y()));
        m_movementCoordinator.tick();
    }
    m_collider->setPos(m_layerItem.getPos());


}


void GameObject::checkCollision(const vector<GameObject*> &other)
{
    vector<GameObject*> collided = GameObject::getCollidedObjects(this, m_collider, other);
    if(collided.size() > 0)
    {
        event_hasCollision(collided[0]);
    }
}
vector<GameObject*> GameObject::getCollidedObjects(GameObject *owner, Collider *collider,const vector<GameObject*> &other)
{
    vector<GameObject*> collided;
    collided.reserve(10);
    for(size_t i=0; i<other.size(); i++)
    {
        if(owner == other[i])
            continue; // This is the same object like other[i]
        if(collider->intersectsBoundingBox(*other[i]->m_collider))
        {
            if(collider->collides(*other[i]->m_collider))
            {
                collided.push_back(other[i]);
            }
        }
    }
    return collided;
}
/*void GameObject::checkCollision(GameObject *owner,collisionSlot slot,Collider *collider,const vector<GameObject*> &other)
{
    for(size_t i=0; i<other.size(); i++)
    {
        if(owner == other[i])
            continue; // This is the same object like other[i]
        if(collider->intersectsBoundingBox(*other[i]->m_collider))
        {
            if(collider->collides(*other[i]->m_collider))
            {
                (owner->*slot)(other[i]);
                return;
            }
        }
    }
}*/

void GameObject::draw(PixelDisplay &display)
{
    m_painter->setPos(m_layerItem.getPos());
    m_hitboxPainter->setPos(m_layerItem.getPos());
    m_painter->draw(display);
    m_hitboxPainter->draw(display);
}

void GameObject::addController(Controller *controller)
{
    if(controller == nullptr)
        return;

    for(size_t i=0; i<m_controllerList.size(); i++)
        if(m_controllerList[i] == controller)
            return;

    m_controllerList.push_back(controller);
}
/*const Controller &GameObject::getController() const
{
    return *m_controller;
}*/
void GameObject::setCollider(Collider *collider)
{
    if(m_collider == collider || collider == nullptr)
        return;
    delete m_collider;
    m_collider = collider;
}
const Collider &GameObject::getCollider() const
{
    return *m_collider;
}
void GameObject::setPainter(Painter *painter)
{
    if(m_painter == painter || painter == nullptr)
        return;
    delete m_painter;
    m_painter = painter;
}
const Painter &GameObject::getPainter() const
{
    return *m_painter;
}
void GameObject::setEventHandler(GameObjectEventHandler *handler)
{
    m_objEventHandler = handler;
}
/*void GameObject::setPosInitial(const Point &pos)
{
    m_controller->setPosInitial(pos);
}
void GameObject::setPosInitial(const int &x, const int &y)
{
    m_controller->setPosInitial(x,y);
}
void GameObject::setPos(const int &x,const int &y)
{
    m_controller->setPos(x,y);
}
void GameObject::setPos(const Point &pos)
{
    m_controller->setPos(pos);
}

void GameObject::setX(const int &x)
{
    m_controller->setX(x);
}
void GameObject::setY(const int &y)
{
    m_controller->setY(y);
}*/

void GameObject::setPos(const int &x,const int &y)
{
    m_layerItem.setPosInitial(x,y);
}
void GameObject::setPos(const Point &pos)
{
    m_layerItem.setPosInitial(pos);
}

void GameObject::setX(const int &x)
{
    m_layerItem.setPosInitial(x,m_layerItem.getY());
}
void GameObject::setY(const int &y)
{
    m_layerItem.setPosInitial(m_layerItem.getX(),y);
}

void GameObject::moveToPos(const Point &destination,Controller::MovingMode mode)
{
    m_controllerList[0]->moveToPos(m_layerItem.getPos(),destination,mode);
}
void GameObject::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    m_controllerList[0]->moveToPos(m_layerItem.getPos().getX(),m_layerItem.getPos().getY(),x,y,mode);
}
void GameObject::move(const Vector &vec,Controller::MovingMode mode)
{
    m_controllerList[0]->move(vec,mode);
}
void GameObject::move(const VectorF &vec,Controller::MovingMode mode)
{
    m_controllerList[0]->move(vec,mode);
}
void GameObject::move(const double &deltaX, const double &deltaY,Controller::MovingMode mode)
{
    m_controllerList[0]->move(deltaX,deltaY,mode);
}
void GameObject::moveX(const double &delta,Controller::MovingMode mode)
{
    m_controllerList[0]->moveX(delta,mode);
}
void GameObject::moveY(const double &delta,Controller::MovingMode mode)
{
    m_controllerList[0]->moveY(delta,mode);
}

const Point GameObject::getPos() const
{
    return m_layerItem.getPos();
}

void GameObject::rotate(const double &rad)
{
    if(m_hitboxPainter->isVisible())
    {
        this->setHitboxVisibility(false);
        this->setHitboxVisibility(true);
    }
    m_rotationDeg+=rad*180/M_PI;
    if(m_rotationDeg >= 360)
        m_rotationDeg = m_rotationDeg%360;
}
void GameObject::setRotation(const double &deg)
{
    double rot = m_rotationDeg - deg;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(deg);
    m_collider->setRotation(deg);
    m_painter->setRotation(deg);
    rotate(rot*180.f/M_PI);
}
double GameObject::getRotation() const
{
    return m_rotationDeg;
}
void GameObject::rotate_90()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_90();
    m_collider->rotate_90();
    m_painter->rotate_90();
    rotate(M_PI_2);
}
void GameObject::rotate_180()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_180();
    m_collider->rotate_180();
    m_painter->rotate_180();
    rotate(M_PI);
}
void GameObject::rotate_270()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_270();
    m_collider->rotate_270();
    m_painter->rotate_270();
    rotate(M_PI_2*3);
}

const bool &GameObject::isBoundingBoxUpdated() const
{
    return m_collider->isBoundingBoxUpdated();
}
void GameObject::updateBoundingBox()
{
    m_collider->updateBoundingBox();
}
void GameObject::setVisibility(const bool &isVisible)
{
    m_painter->setVisibility(isVisible);
}
const bool &GameObject::isVisible() const
{
    return m_painter->isVisible();
}
void GameObject::setHitboxVisibility(const bool &isVisible)
{
    if(isVisible)
    {
        m_hitboxPainter->setPos(m_layerItem.getPos());
        HitboxPainter::makeVisibleCollider(m_collider,m_hitboxPainter);
    }
    m_hitboxPainter->setVisibility(isVisible);
}
const bool &GameObject::isHitboxVisible() const
{
    return m_hitboxPainter->isVisible();
}
void GameObject::setProperty(const Property::Property &property)
{
    m_property = property;
}
const Property::Property &GameObject::getProperty() const
{
    return m_property;
}
void GameObject::event_hasCollision(GameObject *other)
{
    if(m_objEventHandler != nullptr)
        m_objEventHandler->collisionOccured(this,other);
    /*if(m_objEventHandler != nullptr)
        m_objEventHandler->removeFromEngine(this);*/
    m_layerItem.setToLastPos();
    m_collider->setPos(m_layerItem.getPos());
}
