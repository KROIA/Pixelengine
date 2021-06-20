#include "gameObjectGroup.h"

GameObjectGroup::GameObjectGroup()
{
    //this->setVisibility(true);
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

    this->m_isInList             = other.m_isInList;
    return *this;
}
void GameObjectGroup::draw(PixelDisplay &display)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->draw(display);
}
void GameObjectGroup::add(GameObject *object)
{
    m_isInList.push_back(object);
}
void GameObjectGroup::add(GameObjectGroup *other)
{
    m_isInList.reserve(m_isInList.size()   + other->size());
    for(size_t i=0; i<other->size(); i++)
        this->add((*other)[i]);
}
void GameObjectGroup::remove(GameObject *toRemove)
{
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
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        this->remove((*other)[i]);
    }
}
void GameObjectGroup::remove(const size_t index)
{
    if(index >= m_isInList.size())
        return;
    m_isInList.erase(m_isInList.begin()+index);
}
void GameObjectGroup::clear()
{
    m_isInList.clear();
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
/*void GameObjectGroup::setPosInitial(const Point &pos)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(pos);
}
void GameObjectGroup::setPosInitial(const int &x, const int &y)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(x,y);
}*/
void GameObjectGroup::setPos(const int &x,const int &y)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(x,y);
}
void GameObjectGroup::setPos(const Point &pos)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(pos);
}
void GameObjectGroup::setX(const int &x)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setX(x);
}
void GameObjectGroup::setY(const int &y)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setY(y);
}

void GameObjectGroup::moveToPos(const Point &destination,Controller::MovingMode mode)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveToPos(destination,mode);
}
void GameObjectGroup::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveToPos(x,y,mode);
}
void GameObjectGroup::move(const Vector &vec,Controller::MovingMode mode)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(vec,mode);
}
void GameObjectGroup::move(const VectorF &vec,Controller::MovingMode mode)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(vec,mode);
}
void GameObjectGroup::move(const double &deltaX, const double &deltaY, Controller::MovingMode mode)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(deltaX,deltaY,mode);
}
void GameObjectGroup::moveX(const double &delta,Controller::MovingMode mode)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveX(delta,mode);
}
void GameObjectGroup::moveY(const double &delta,Controller::MovingMode mode)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveY(delta,mode);
}
void GameObjectGroup::setRotation(const double &deg)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setRotation(deg);
}
void GameObjectGroup::rotate_90()
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_90();
}
void GameObjectGroup::rotate_180()
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_180();
}
void GameObjectGroup::rotate_270()
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_270();
}
void GameObjectGroup::setRotation(const PointF &rotationPoint,const double &deg)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setRotation(rotationPoint,deg);
}
void GameObjectGroup::rotate_90(const PointF &rotationPoint)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_90(rotationPoint);
}
void GameObjectGroup::rotate_180(const PointF &rotationPoint)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_180(rotationPoint);
}
void GameObjectGroup::rotate_270(const PointF &rotationPoint)
{
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_270(rotationPoint);
}
void GameObjectGroup::setVisibility(const bool &isVisible)
{
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
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i] == obj)
            return i;
    }
    return -1;
}

void GameObjectGroup::removeDuplicates(vector<GameObject *> *list)
{
    vector<GameObject *> copyList;
    copyList.reserve(list->size());

    for(size_t i=0; i<list->size(); i++)
    {
        bool hasCopy = false;
        for(size_t j=0; j<copyList.size(); j++)
        {
            if((*list)[i] == copyList[j])
            {
                hasCopy = true;
                break; // Jumps to the end of this for loop
            }
        }
        // break jumpt to this Point
        if(!hasCopy)
            copyList.push_back((*list)[i]);
    }
    *list = copyList;
}
void GameObjectGroup::removeDuplicates(GameObjectGroup *list)
{
    removeDuplicates(&list->m_isInList);
}
