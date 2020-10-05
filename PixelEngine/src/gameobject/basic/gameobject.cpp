#include "gameobject.h"

GameObject::GameObject()
{
    m_controller = new Controller();
    m_collider   = new Collider();
    m_painter    = new Painter;
}
GameObject::GameObject(const GameObject &other)
{
    *this->m_controller = *other.m_controller;
    *this->m_collider   = *other.m_collider;
    *this->m_painter    = *other.m_painter;
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
}

void GameObject::tick(const Point &direction)
{
    m_controller->tick(direction);
    //m_collider->setPos(m_controller->getNextPos());
    m_collider->setPos(m_controller->getPos());
}
void GameObject::checkCollision()
{
    this->checkCollision(m_collisionInteractionGroup);
}

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
    m_painter->draw(display);
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
void GameObject::addInteraction_collision_with(GameObject *other)
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

void GameObject::setVisibility(const bool &isVisible)
{
    m_painter->setVisibility(isVisible);
}
const bool &GameObject::isVisible() const
{
    return m_painter->isVisible();
}

void GameObject::event_hasCollision(GameObject *other)
{
    m_controller->setToLastPos();
    m_collider->setPos(m_controller->getPos());
}