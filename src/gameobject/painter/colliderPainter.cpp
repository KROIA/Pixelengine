#include "colliderPainter.h"

ColliderPainter::ColliderPainter()
    :   VertexPathPainter()
{
    m_collider = nullptr;
    VertexPathPainter::setVisibility(false);
    setVisibility_boundingBox(false);
    setVisibility_collidedObjects(false);
    setVisibility_hitBox(false);
    setVisibility_collisionData(false);
    m_dummyColor = Color(0,0,0);
    m_collidedObjectsColor = Color(255,50,0);
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
    EASY_FUNCTION(profiler::colors::Cyan200);
    if(!m_isVisible)
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
    if(m_visibility_collidedObjects)
        for(size_t i=0; i<collided.size(); i++)
            VertexPathPainter::addPath(collided[i]->getCollider().getBoundingBox().getDrawable(m_collidedObjectsColor));

}
void ColliderPainter::setVisibility_boundingBox(bool isVisible)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    m_visibility_boundingBox = isVisible;
    checkIfPainterIsVisible();
}
void ColliderPainter::setVisibility_hitBox(bool isVisible)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    m_visibility_hitbox = isVisible;
    checkIfPainterIsVisible();
}
void ColliderPainter::setVisibility_collisionData(bool isVisible)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    m_visibility_collisionData = isVisible;
    if(m_collider != nullptr)
        m_collider->generateCollisionData(isVisible);
    checkIfPainterIsVisible();
}
void ColliderPainter::setVisibility_collidedObjects(bool isVisible)
{
    EASY_FUNCTION(profiler::colors::Cyan300);
    m_visibility_collidedObjects= isVisible;
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
bool ColliderPainter::isVisible_collidedObjects()
{
    return m_visibility_collidedObjects;
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
void ColliderPainter::setColor_collidedObjects(const Color &color)
{
    m_collidedObjectsColor = color;
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
const Color &ColliderPainter::getColor_collidedObjects() const
{
    return m_collidedObjectsColor;
}

void ColliderPainter::checkIfPainterIsVisible()
{
    bool v = m_visibility_boundingBox + m_visibility_hitbox + m_visibility_collisionData + m_visibility_collidedObjects;
    if(v != m_isVisible)
        VertexPathPainter::setVisibility(v);
}
