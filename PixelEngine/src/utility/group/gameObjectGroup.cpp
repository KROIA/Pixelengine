#include "gameObjectGroup.h"

GameObjectGroup::GameObjectGroup()
    :   vector<GameObject *>()
{
    this->setVisibility(true);
    this->setHitboxVisibility(false);
}
GameObjectGroup::GameObjectGroup(const GameObjectGroup &other)
    :   vector<GameObject *>(other)
{
    this->m_isVisible        = other.m_isVisible;
    this->m_hitBoxIsVisible  = other.m_hitBoxIsVisible;
}

GameObjectGroup::~GameObjectGroup()
{

}
void GameObjectGroup::push_back(GameObject* obj)
{
    for(size_t i=0; i<this->size(); i++)
    {
        if((*this)[i] == obj)
        {
            return; // Obj already exists in list
        }
    }
    if(obj->isRemoved())
        obj->reActivate();
    vector::push_back(obj);
}
void GameObjectGroup::append(const vector<GameObject*> &other)
{
    for(size_t i=0; i<other.size(); i++)
    {
        if(other[i]->isRemoved())
        {
            other[i]->reActivate();
        }
    }
    this->insert(this->end(),other.begin(),other.end());
}
void GameObjectGroup::remove(GameObject *toRemove)
{
    for(size_t i=0; i<this->size(); i++)
    {
        if((*this)[i] == toRemove)
        {
            toRemove->remove();
            this->erase(this->begin()+i);
            if(i>0)
                i--;
        }
    }
}
void GameObjectGroup::remove(const vector<GameObject*> &other)
{
    for(size_t i=0; i<this->size(); i++)
    {
        this->remove(other[i]);
    }
}
void GameObjectGroup::setVisibility(const bool &isVisible)
{
    m_isVisible = isVisible;
    for(size_t i=0; i<this->size(); i++)
    {
        if((*this)[i]->isRemoved())
        {
            this->remove((*this)[i]);
            continue;
        }
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
        if((*this)[i]->isRemoved())
        {
            this->remove((*this)[i]);
            continue;
        }
        (*this)[i]->setHitboxVisibility(m_hitBoxIsVisible);
    }
}
const bool &GameObjectGroup::isHitboxVisible() const
{
    return m_hitBoxIsVisible;
}
