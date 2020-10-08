#include "gameObjectGroup.h"

GameObjectGroup::GameObjectGroup()
{
    this->setVisibility(true);
    this->setHitboxVisibility(false);
}
GameObjectGroup::GameObjectGroup(const GameObjectGroup &other)
{
    *this = other;
}

GameObjectGroup::~GameObjectGroup()
{

}
GameObjectGroup &GameObjectGroup::operator=(const GameObjectGroup &other)
{
    this->m_isVisible        = other.m_isVisible;
    this->m_hitboxIsVisible  = other.m_hitboxIsVisible;

    this->m_list             = other.m_list;
    return *this;
}
void GameObjectGroup::draw(PixelDisplay &display)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->draw(display);
}
void GameObjectGroup::add(GameObject *object)
{
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
    m_hitboxIsVisible = isVisible;
    for(size_t i=0; i<this->size(); i++)
    {
        m_list[i]->setHitboxVisibility(m_hitboxIsVisible);
    }
}
const bool &GameObjectGroup::isHitboxVisible() const
{
    return m_hitboxIsVisible;
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
