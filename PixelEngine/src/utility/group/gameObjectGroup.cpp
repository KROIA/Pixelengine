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
// GameObject stuff
/*void GameObjectGroup::setPosInitial(const Point &pos)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->setPos(pos);
}
void GameObjectGroup::setPosInitial(const int &x, const int &y)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->setPos(x,y);
}*/
void GameObjectGroup::setPos(const int &x,const int &y)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->setPos(x,y);
}
void GameObjectGroup::setPos(const Point &pos)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->setPos(pos);
}
void GameObjectGroup::setX(const int &x)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->setX(x);
}
void GameObjectGroup::setY(const int &y)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->setY(y);
}
void GameObjectGroup::moveToPos(const Point &destination)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->moveToPos(destination);
}
void GameObjectGroup::moveToPos(const int &x,const int &y)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->moveToPos(x,y);
}
void GameObjectGroup::move(const Point &directionVector)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->move(directionVector);
}
void GameObjectGroup::move(int x,int y)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->move(x,y);
}
void GameObjectGroup::setRotation(const double &deg)
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->setRotation(deg);
}
void GameObjectGroup::rotate_90()
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->rotate_90();
}
void GameObjectGroup::rotate_180()
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->rotate_180();
}
void GameObjectGroup::rotate_270()
{
    for(size_t i=0; i<m_list.size(); i++)
        m_list[i]->rotate_270();
}
void GameObjectGroup::setVisibility(const bool &isVisible)
{
    m_isVisible = isVisible;
    for(size_t i=0; i<m_list.size(); i++)
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
    for(size_t i=0; i<m_list.size(); i++)
    {
        m_list[i]->setHitboxVisibility(m_hitboxIsVisible);
    }
}
const bool &GameObjectGroup::isHitboxVisible() const
{
    return m_hitboxIsVisible;
}

