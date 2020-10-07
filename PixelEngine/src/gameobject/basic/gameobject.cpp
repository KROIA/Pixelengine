#include "gameobject.h"

GameObject::GameObject()
{
    m_controller    = new Controller();
    m_collider      = new Collider();
    m_painter       = new Painter();
    m_hitboxPainter = new Painter();
    //m_isRemoved     = false;
}
GameObject::GameObject(const GameObject &other)
{
    *this->m_controller    = *other.m_controller;
    *this->m_collider      = *other.m_collider;
    *this->m_painter       = *other.m_painter;
    *this->m_hitboxPainter = *other.m_hitboxPainter;
    //this->m_isRemoved      = other.m_isRemoved;
}
GameObject::GameObject(Controller *controller,
                       Collider   *collider,
                       Painter    *painter)
{
    this->setController(controller);
    this->setCollider(collider);
    this->setPainter(painter);
   // m_isRemoved = false;
}

GameObject::~GameObject()
{
    delete m_controller;
    delete m_collider;
    delete m_painter;
    delete m_hitboxPainter;
}
void GameObject::checkEvent()
{
    m_controller->checkEvent();
}
void GameObject::tick(const Point &direction)
{
    m_controller->tick(direction);
    //m_collider->setPos(m_controller->getNextPos());
    m_collider->setPos(m_controller->getPos());
}
/*void GameObject::checkCollision()
{
    for(size_t i=0; i<m_collisionInteractionGroup.size(); i++)
    {
        if(m_collisionInteractionGroup[i]->isRemoved())
            m_collisionInteractionGroup.erase(m_collisionInteractionGroup.begin()+i);
    }
    this->checkCollision(m_collisionInteractionGroup);
}*/

void GameObject::checkCollision(const vector<GameObject*> &other)
{
    for(size_t i=0; i<other.size(); i++)
    {
        if(this == other[i])
            continue; // This is the same object like other[i]
        if(m_collider->intersectsBoundingBox(*other[i]->m_collider))
        {
            if(m_collider->collides(*other[i]->m_collider))
            {
                this->event_hasCollision(other[i]);
                return;
            }
        }
    }
}
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
void GameObject::setCollider(Collider *collider)
{
    if(m_collider == collider || collider == nullptr)
        return;
    delete m_collider;
    m_collider = collider;
}
void GameObject::setPainter(Painter *painter)
{
    if(m_painter == painter || painter == nullptr)
        return;
    delete m_painter;
    m_painter = painter;
}
/*void GameObject::addInteraction_collision_with(GameObject *other)
{
    if(other == nullptr)
        throw std::runtime_error(std::string("GameObject::addCollisionWith(GameObject *[nullptr])): ")+
                                 "Can't add not existing object to the group");
    for(size_t i=0; i<m_collisionInteractionGroup.size(); i++)
    {
        if(m_collisionInteractionGroup[i] == other)
            return; // obj already exists in the list, so don't add it.
    }
    m_collisionInteractionGroup.push_back(other);
}
void GameObject::addInteraction_collision_with(const vector<GameObject *> otherList)
{
    for(size_t i=0; i<otherList.size(); i++)
    {
        this->addInteraction_collision_with(otherList[i]);
    }
}*/
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
/*void GameObject::remove()
{
    m_isRemoved = true;
}
void GameObject::reActivate()
{
    m_isRemoved = false;
}
const bool &GameObject::isRemoved() const
{
    return m_isRemoved;
}*/
void GameObject::event_hasCollision(GameObject *other)
{
    m_controller->setToLastPos();
    m_collider->setPos(m_controller->getPos());
}
