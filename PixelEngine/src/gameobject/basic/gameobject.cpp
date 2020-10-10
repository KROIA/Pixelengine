#include "gameobject.h"
#include "gameObjectEventHandler.h"

GameObject::GameObject()
{
    m_controller    = new Controller();
    m_collider      = new Collider();
    m_painter       = new Painter();
    m_hitboxPainter = new Painter();
    m_objEventHandler = nullptr;
}
GameObject::GameObject(const GameObject &other)
{
    m_controller    = new Controller();
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
    this->setController(controller);
    this->setCollider(collider);
    this->setPainter(painter);
}

GameObject::~GameObject()
{
    delete m_controller;
    delete m_collider;
    delete m_painter;
    delete m_hitboxPainter;
}
const GameObject &GameObject::operator=(const GameObject &other)
{
    *this->m_controller    = *other.m_controller;
    *this->m_collider      = *other.m_collider;
    *this->m_painter       = *other.m_painter;
    *this->m_hitboxPainter = *other.m_hitboxPainter;
    this->m_property       = other.m_property;
    this->m_objEventHandler = other.m_objEventHandler;
    return *this;
}
void GameObject::checkEvent()
{
    m_controller->checkEvent();
}
void GameObject::tick(const Point &direction)
{
    m_controller->tick(direction);
    m_collider->setPos(m_controller->getPos());
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
    m_painter->setPos(m_controller->getPos());
    m_hitboxPainter->setPos(m_controller->getPos());
    m_painter->draw(display);
    m_hitboxPainter->draw(display);
}

void GameObject::setController(Controller *controller)
{
    if(m_controller == controller || controller == nullptr)
        return;
    delete m_controller;
    m_controller = controller;
}
const Controller &GameObject::getController() const
{
    return *m_controller;
}
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
void GameObject::setPosInitial(const Point &pos)
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
}

void GameObject::moveToPos(const Point &destination)
{
    m_controller->moveToPos(destination);
}
void GameObject::moveToPos(const int &x,const int &y)
{
    m_controller->moveToPos(x,y);
}
void GameObject::move(const Point &directionVector)
{
    m_controller->move(directionVector);
}
void GameObject::move(int x,int y)
{
    m_controller->move(x,y);
}
const Point &GameObject::getPos()
{
    return m_controller->getPos();
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
        m_hitboxPainter->setPos(m_controller->getPos());
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
    m_controller->setToLastPos();
    m_collider->setPos(m_controller->getPos());
}
