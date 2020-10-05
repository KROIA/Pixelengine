#include "gameObjectGroup.h"

GameObjectGroup::GameObjectGroup()
    :   vector<GameObject *>()
{
    this->setVisibility(true);
}
GameObjectGroup::GameObjectGroup(const GameObjectGroup &other)
    :   vector<GameObject *>(other)
{
    this->m_isVisible = other.m_isVisible;
}

GameObjectGroup::~GameObjectGroup()
{

}

void GameObjectGroup::setVisibility(const bool &isVisible)
{
    m_isVisible = isVisible;
    for(size_t i=0; i<this->size(); i++)
    {
        (*this)[i]->setVisibility(m_isVisible);
    }
}
const bool &GameObjectGroup::isVisible() const
{
    return m_isVisible;
}
void GameObjectGroup::setHitboxVisibility(const bool &isVisible)
{
    m_hitBoxIsVisible = isVisible;
    for(size_t i=0; i<this->size(); i++)
    {
        (*this)[i]->setHitboxVisibility(m_hitBoxIsVisible);
    }
}
const bool &GameObjectGroup::isHitboxVisible() const
{
    return m_hitBoxIsVisible;
}
