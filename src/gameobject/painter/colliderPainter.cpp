#include "colliderPainter.h"

ColliderPainter::ColliderPainter()
    :   VertexPathPainter()
{
    m_collider = nullptr;
    VertexPathPainter::setVisibility(false);
    setVisibility_boundingBox(false);
    setVisibility_collidedObjects_boundingBox(false);
    setVisibility_collidedObjects_hitBox(false);
    setVisibility_hitBox(false);
    setVisibility_collisionData(false);
    m_dummyColor = Color(0,0,0);
    m_collidedObjectsColor_boundingBox = Color(255,50,0);
    m_collidedObjectsColor_hitBox      = Color(255,0,0);
    setEnableRelativePosition(true);
}
ColliderPainter::ColliderPainter(Collider *collider)
    :   VertexPathPainter()
{
    setCollider(collider);
}

void ColliderPainter::setCollider(Collider *collider)
{
    m_collider = collider;
    if(m_visibility_collisionData)
        m_collider->generateCollisionData(m_visibility_collisionData);
}
void ColliderPainter::update(const vector<GameObject* > &collided)
{
    PAINTER_FUNCTION(profiler::colors::Cyan200);
    if(!m_isVisible || !m_collider)
        return;

    size_t hashedList = Hash::getHashOfList(collided);
    if(m_hashed_colliderObjectsList == hashedList && !m_collider->stateChanged())
        return; // There are no new objects colliding and the collider hasn't changed
    else
        m_hashed_colliderObjectsList = hashedList;

    VertexPathPainter::clear();

    if(m_collider  != nullptr)
    {
        if(m_visibility_boundingBox)
            VertexPathPainter::addPath(m_collider->getDrawableBoundingBox());
        if(m_visibility_hitbox)
            VertexPathPainter::addPath(m_collider->getDrawableHitBox());
        if(m_visibility_collisionData)
            VertexPathPainter::addPath(m_collider->getDrawableColliderVector());
    }
    if(m_visibility_collidedObjects_boundingBox)
        for(size_t i=0; i<collided.size(); i++)
            VertexPathPainter::addPath(collided[i]->getCollider()->getBoundingBox().getDrawable(m_collidedObjectsColor_boundingBox));
    if(m_visibility_collidedObjects_hitBox)
        for(size_t i=0; i<collided.size(); i++)
            for(size_t j=0; j<collided[i]->getCollider()->getHitboxAmount(); j++)
                VertexPathPainter::addPath(collided[i]->getCollider()->getHitbox(j).getDrawable(m_collidedObjectsColor_hitBox));

}
void ColliderPainter::setVisibility_boundingBox(bool isVisible)
{
    PAINTER_FUNCTION(profiler::colors::Cyan300);
    m_visibility_boundingBox = isVisible;
    checkIfPainterIsVisible();
}
void ColliderPainter::setVisibility_hitBox(bool isVisible)
{
    PAINTER_FUNCTION(profiler::colors::Cyan300);
    m_visibility_hitbox = isVisible;
    checkIfPainterIsVisible();
}
void ColliderPainter::setVisibility_collisionData(bool isVisible)
{
    PAINTER_FUNCTION(profiler::colors::Cyan300);
    m_visibility_collisionData = isVisible;
    if(m_collider != nullptr)
        m_collider->generateCollisionData(isVisible);
    checkIfPainterIsVisible();
}
void ColliderPainter::setVisibility_collidedObjects_boundingBox(bool isVisible)
{
    PAINTER_FUNCTION(profiler::colors::Cyan300);
    m_visibility_collidedObjects_boundingBox= isVisible;
    checkIfPainterIsVisible();
}
void ColliderPainter::setVisibility_collidedObjects_hitBox(bool isVisible)
{
    PAINTER_FUNCTION(profiler::colors::Cyan300);
    m_visibility_collidedObjects_hitBox = isVisible;
    checkIfPainterIsVisible();
}
bool ColliderPainter::isVisible_boundingBox()
{
    return m_visibility_boundingBox;
}
bool ColliderPainter::isVisible_hitBox()
{
    return m_visibility_hitbox;
}
bool ColliderPainter::isVisible_collisionData()
{
    return m_visibility_collisionData;
}
bool ColliderPainter::isVisible_collidedObjects_boundingBox()
{
    return m_visibility_collidedObjects_boundingBox;
}
bool ColliderPainter::isVisible_collidedObjects_hitBox()
{
    return m_visibility_collidedObjects_boundingBox;
}


void ColliderPainter::setColor_boundingBox_noIntersection(const Color &color)
{
    if(m_collider != nullptr)
        m_collider->setColor_boundingBox_noIntersection(color);
}
void ColliderPainter::setColor_boundingBox_intersecting(const Color &color)
{
    if(m_collider != nullptr)
        m_collider->setColor_boundingBox_intersecting(color);
}
void ColliderPainter::setColor_hitBox_noCollision(const Color &color)
{
    if(m_collider != nullptr)
        m_collider->setColor_hitBox_noCollision(color);
}
void ColliderPainter::setColor_hitBox_colliding(const Color &color)
{
    if(m_collider != nullptr)
        m_collider->setColor_hitBox_colliding(color);
}
void ColliderPainter::setColor_collidedObjects_boundingBox(const Color &color)
{
    m_collidedObjectsColor_boundingBox = color;
}
void ColliderPainter::setColor_collidedObjects_hitBox(const Color &color)
{
    m_collidedObjectsColor_hitBox = color;
}

const Color &ColliderPainter::getColor_boundingBox_noIntersection() const
{
    if(m_collider != nullptr)
        return m_collider->getColor_boundingBox_noIntersection();
    return m_dummyColor;
}
const Color &ColliderPainter::getColor_boundingBox_intersecting() const
{
    if(m_collider != nullptr)
        return m_collider->getColor_boundingBox_intersecting();
    return m_dummyColor;
}
const Color &ColliderPainter::getColor_hitBox_noCollision() const
{
    if(m_collider != nullptr)
        return m_collider->getColor_hitBox_noCollision();
    return m_dummyColor;
}
const Color &ColliderPainter::getColor_hitBox_colliding() const
{
    if(m_collider != nullptr)
        return m_collider->getColor_hitBox_colliding();
    return m_dummyColor;
}
const Color &ColliderPainter::getColor_collidedObjects_boundingBox() const
{
    return m_collidedObjectsColor_boundingBox;
}
const Color &ColliderPainter::getColor_collidedObjects_hitBox() const
{
    return m_collidedObjectsColor_hitBox;
}

void ColliderPainter::checkIfPainterIsVisible()
{
    bool v = m_visibility_boundingBox +
            m_visibility_hitbox +
            m_visibility_collisionData +
            m_visibility_collidedObjects_boundingBox +
            m_visibility_collidedObjects_hitBox;
    if(v != m_isVisible)
        VertexPathPainter::setVisibility(v);
}

void ColliderPainter::setRotation(float deg)
{}
void ColliderPainter::rotate(float deg)
{}
void ColliderPainter::rotate_90()
{}
void ColliderPainter::rotate_180()
{}
void ColliderPainter::rotate_270()
{}
void ColliderPainter::setRotation(const Vector2f &rotPoint,float deg)
{}
void ColliderPainter::rotate(const Vector2f &rotPoint,float deg)
{}
void ColliderPainter::rotate_90(const Vector2f &rotPoint)
{}
void ColliderPainter::rotate_180(const Vector2f &rotPoint)
{}
void ColliderPainter::rotate_270(const Vector2f &rotPoint)
{}
