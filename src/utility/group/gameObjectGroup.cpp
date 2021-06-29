#include "gameObjectGroup.h"

GameObjectGroup::GameObjectGroup()
{
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
    this->m_isInList             = other.m_isInList;
    return *this;
}
void GameObjectGroup::draw(PixelDisplay &display)
{
    EASY_FUNCTION(profiler::colors::Purple);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->draw(display);
}
void GameObjectGroup::add(GameObject *object)
{
    EASY_FUNCTION(profiler::colors::Purple50);
    m_isInList.push_back(object);
}
void GameObjectGroup::add(GameObjectGroup *other)
{
    EASY_FUNCTION(profiler::colors::Purple50);
    m_isInList.reserve(m_isInList.size()   + other->size());
    for(size_t i=0; i<other->size(); i++)
        this->add((*other)[i]);
}
void GameObjectGroup::remove(GameObject *toRemove)
{
    EASY_FUNCTION(profiler::colors::Purple100);
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        if(m_isInList[i] == toRemove)
        {
            this->remove(i);
        }
    }
}
void GameObjectGroup::remove(GameObjectGroup *other)
{
    EASY_FUNCTION(profiler::colors::Purple100);
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        this->remove((*other)[i]);
    }
}
void GameObjectGroup::remove(const size_t index)
{
    EASY_FUNCTION(profiler::colors::Purple100);
    if(index >= m_isInList.size())
        return;
    m_isInList.erase(m_isInList.begin()+index);
}
void GameObjectGroup::clear()
{
    EASY_FUNCTION(profiler::colors::Purple200);
    m_isInList.clear();
}
void GameObjectGroup::reserve(size_t size)
{
    m_isInList.reserve(size);
}
size_t GameObjectGroup::size() const
{
    return m_isInList.size();
}
GameObject *GameObjectGroup::operator[](const size_t &index) const
{
    return m_isInList[index];
}
const vector<GameObject*> &GameObjectGroup::getVector() const
{
    return m_isInList;
}
// GameObject stuff
void GameObjectGroup::setPos(const int &x,const int &y)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(x,y);
}
void GameObjectGroup::setPos(const Vector2i&pos)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(pos);
}
void GameObjectGroup::setX(const int &x)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setX(x);
}
void GameObjectGroup::setY(const int &y)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setY(y);
}

void GameObjectGroup::moveToPos(const Vector2i&destination,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveToPos(destination,mode);
}
void GameObjectGroup::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveToPos(x,y,mode);
}
void GameObjectGroup::move(const Vector2i&vec,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(vec,mode);
}
void GameObjectGroup::move(const Vector2f &vec,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(vec,mode);
}
void GameObjectGroup::move(const float &deltaX, const float &deltaY, Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(deltaX,deltaY,mode);
}
void GameObjectGroup::moveX(const float &delta,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveX(delta,mode);
}
void GameObjectGroup::moveY(const float &delta,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveY(delta,mode);
}
void GameObjectGroup::setRotation(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setRotation(deg);
}
void GameObjectGroup::rotate_90()
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_90();
}
void GameObjectGroup::rotate_180()
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_180();
}
void GameObjectGroup::rotate_270()
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_270();
}
void GameObjectGroup::setRotation(const Vector2f &rotationPoint,const float &deg)
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setRotation(rotationPoint,deg);
}
void GameObjectGroup::rotate_90(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_90(rotationPoint);
}
void GameObjectGroup::rotate_180(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_180(rotationPoint);
}
void GameObjectGroup::rotate_270(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_270(rotationPoint);
}
void GameObjectGroup::setVisibility(const bool &isVisible)
{
    EASY_FUNCTION(profiler::colors::Purple500);
    m_isVisible = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility(m_isVisible);
    }
}
const bool &GameObjectGroup::isVisible() const
{
    return m_isVisible;
}
void GameObjectGroup::setHitboxVisibility(const bool &isVisible)
{
    EASY_FUNCTION(profiler::colors::Purple600);
    m_hitboxIsVisible = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        try {
            m_isInList[i]->setHitboxVisibility(m_hitboxIsVisible);
        }  catch (...) {
            qDebug() << "error on pointer";
        }

    }
}
const bool &GameObjectGroup::isHitboxVisible() const
{
    return m_hitboxIsVisible;
}
long long GameObjectGroup::indexOf(const GameObject* obj)
{
    return GameObjectGroup::indexOf(m_isInList,obj);
}
long long GameObjectGroup::indexOf(const vector<GameObject *> list,const GameObject* obj)
{
    EASY_FUNCTION(profiler::colors::Purple600);
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i] == obj)
            return i;
    }
    return -1;
}

void GameObjectGroup::removeDuplicates(vector<GameObject *> *list)
{
    EASY_FUNCTION(profiler::colors::Purple700);
    vector<GameObject *> copyList;
    copyList.reserve(list->size());

    EASY_BLOCK("Compare list 1 loop",profiler::colors::Purple800);
    for(size_t i=0; i<list->size(); i++)
    {
        bool hasCopy = false;
        EASY_BLOCK("Compare list 2 loop",profiler::colors::Purple900);
        for(size_t j=0; j<copyList.size(); j++)
        {
            if((*list)[i] == copyList[j])
            {
                hasCopy = true;
                break; // Jumps to the end of this for loop
            }
        }
        EASY_END_BLOCK;
        // break jumpt to this Point
        if(!hasCopy)
            copyList.push_back((*list)[i]);

    }
    EASY_END_BLOCK;
    *list = copyList;
}
void GameObjectGroup::removeDuplicates(GameObjectGroup *list)
{
    EASY_FUNCTION(profiler::colors::Purple700);
    removeDuplicates(&list->m_isInList);
}
