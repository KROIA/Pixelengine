#include "gameObjectGroup.h"

GameObjectGroup::GameObjectGroup()
{
    this->setVisibility(true);
    this->setHitboxVisibility(false);
}
GameObjectGroup::GameObjectGroup(const GameObjectGroup &other)
{
    this->m_isVisible        = other.m_isVisible;
    this->m_hitBoxIsVisible  = other.m_hitBoxIsVisible;

    this->m_list             = other.m_list;
}

GameObjectGroup::~GameObjectGroup()
{

}
void GameObjectGroup::draw(PixelDisplay &display)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->draw(display);
}
void GameObjectGroup::add(GameObject *object)
{
  /*  for(size_t i=0; i<m_list.size(); i++)
        if(m_list[i] == object)
            return; // GameObject already added to list*/
    m_list.push_back(object);
}
void GameObjectGroup::add(GameObjectGroup *other)
{
    m_list.reserve(m_list.size() + other->size());
    for(size_t i=0; i<other->size(); i++)
        this->add((*other)[i]);
}
void GameObjectGroup::remove(GameObject *toRemove)
{
    for(size_t i=0; i<m_list.size(); i++)
    {
        if(m_list[i] == toRemove)
        {
            this->remove(i);
        }
    }
}
void GameObjectGroup::remove(GameObjectGroup *other)
{
    for(size_t i=0; i<m_list.size(); i++)
    {
        this->remove((*other)[i]);
    }
}
void GameObjectGroup::remove(const size_t index)
{
    m_list.erase(m_list.begin()+index);
}
void GameObjectGroup::clear()
{
    m_list.clear();
}
/*void GameObjectGroup::push_back(GameObject* obj)
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
}*/
/*void GameObjectGroup::append(const vector<GameObject*> &other)
{
    for(size_t i=0; i<other.size(); i++)
    {
        if(other[i]->isRemoved())
        {
            other[i]->reActivate();
        }
    }
    this->insert(this->end(),other.begin(),other.end());
}*/

void GameObjectGroup::setVisibility(const bool &isVisible)
{
    m_isVisible = isVisible;
    for(size_t i=0; i<this->size(); i++)
    {
        m_list[i]->setVisibility(m_isVisible);
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
        m_list[i]->setHitboxVisibility(m_hitBoxIsVisible);
    }
}
const bool &GameObjectGroup::isHitboxVisible() const
{
    return m_hitBoxIsVisible;
}

size_t GameObjectGroup::size() const
{
    return m_list.size();
}
GameObject *GameObjectGroup::operator[](const size_t &index) const
{
    return m_list[index];
}
const vector<GameObject*> &GameObjectGroup::getVector() const
{
    return m_list;
}
