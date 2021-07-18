#include "gameObjectGroup.h"

GameObjectGroup::GameObjectGroup()
    :   ObjSignal()
{
    this->m_visibility       = true;
    this->m_visibility_collider_hitbox = false;
}
GameObjectGroup::GameObjectGroup(const GameObjectGroup &other)
    :   ObjSignal()
{
    *this = other;
}

GameObjectGroup::~GameObjectGroup()
{
    for(GameObject* &obj : m_isInList)
        obj->unsubscribe_ObjSignal(this);
}
GameObjectGroup &GameObjectGroup::operator=(const GameObjectGroup &other)
{
    for(GameObject* &obj : m_isInList)
        obj->unsubscribe_ObjSignal(this);
    this->m_visibility        = other.m_visibility;
    this->m_visibility_collider_hitbox  = other.m_visibility_collider_hitbox;
    this->m_isInList         = other.m_isInList;
    for(GameObject* &obj : m_isInList)
        obj->subscribe_ObjSignal(this);
    //this->m_groupSubscriberList = other.m_groupSubscriberList;
    return *this;
}
/*void GameObjectGroup::draw(PixelDisplay &display)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple);
    size_t size = m_isInList.size();
    for(size_t i=0; i<size; i++)
        m_isInList[i]->draw(display);
}*/
bool GameObjectGroup::add(GameObject *object)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple50);
    addInternal(object);
    m_groupSubscriberList.adding(this,object);//emit signal
    return true;
}
bool GameObjectGroup::add(GameObjectGroup *other)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple50);
    m_isInList.reserve(m_isInList.size()   + other->size());
    for(size_t i=0; i<other->size(); i++)
        this->addInternal((*other)[i]);
    m_groupSubscriberList.adding(this,other);//emit signal
    return true;
}
bool GameObjectGroup::addInternal(GameObject *object)
{
    m_isInList.push_back(object);
    object->subscribe_ObjSignal(this);
    return true;
}

bool GameObjectGroup::remove(GameObject *toRemove)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple100);
    bool ret = false;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        if(m_isInList[i] == toRemove)
        {
            m_groupSubscriberList.removing(this,m_isInList[i]);//emit signal
            ret |= this->removeInternal(i);
        }
    }
    return ret;
}
bool GameObjectGroup::remove(GameObjectGroup *other)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple100);
    //other->unsubscribe(this);
    if(m_isInList.size() == 0 || other->size() == 0)
        return false;
    m_groupSubscriberList.removing(this,other);//emit signal
    bool ret = true;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        ret &= this->removeInternal((*other)[i]);
    }
    return ret;
}
bool GameObjectGroup::remove(const size_t index)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple100);
    if(index >= m_isInList.size())
        return false;
    m_groupSubscriberList.removing(this,m_isInList[index]);//emit signal
    return removeInternal(index);
}
bool GameObjectGroup::removeInternal(GameObject *object)
{
    bool ret = false;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        if(m_isInList[i] == object)
        {
            ret |= removeInternal(i);
        }
    }
    return ret;
}
bool GameObjectGroup::removeInternal(size_t index)
{
    m_isInList[index]->unsubscribe_ObjSignal(this);
    m_isInList.erase(m_isInList.begin()+index);
    return true;
}
void GameObjectGroup::clear()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple200);
    m_groupSubscriberList.willBeCleared(this);
    for(GameObject* &obj : m_isInList)
        obj->unsubscribe_ObjSignal(this);
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
void GameObjectGroup::setPosInital(const Vector2f &pos)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPosInital(pos);
}
void GameObjectGroup::setPos(int x,int y)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(x,y);
}
void GameObjectGroup::setPos(const Vector2i &pos)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(pos);
}
void GameObjectGroup::setPos(float x, float y)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(x,y);
}
void GameObjectGroup::setPos(const Vector2f &pos)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setPos(pos);
}
void GameObjectGroup::setX(int x)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setX(x);
}
void GameObjectGroup::setY(int y)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setY(y);
}
void GameObjectGroup::setX(float x)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setX(x);
}
void GameObjectGroup::setY(float y)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setY(y);
}
void GameObjectGroup::moveToPos(const Vector2i&destination,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveToPos(destination,mode);
}
void GameObjectGroup::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveToPos(x,y,mode);
}
void GameObjectGroup::move(const Vector2i&vec,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(vec,mode);
}
void GameObjectGroup::move(const Vector2f &vec,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(vec,mode);
}
void GameObjectGroup::move(const float &deltaX, const float &deltaY, Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->move(deltaX,deltaY,mode);
}
void GameObjectGroup::moveX(const float &delta,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveX(delta,mode);
}
void GameObjectGroup::moveY(const float &delta,Controller::MovingMode mode)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple300);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->moveY(delta,mode);
}

void GameObjectGroup::rotate(const float &deg)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate(deg);
}
void GameObjectGroup::setRotation(const float &deg)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setRotation(deg);
}
void GameObjectGroup::rotate_90()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_90();
}
void GameObjectGroup::rotate_180()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_180();
}
void GameObjectGroup::rotate_270()
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_270();
}
void GameObjectGroup::setRotation(const Vector2f &rotationPoint,const float &deg)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->setRotation(rotationPoint,deg);
}
void GameObjectGroup::rotate_90(const Vector2f &rotationPoint)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_90(rotationPoint);
}
void GameObjectGroup::rotate_180(const Vector2f &rotationPoint)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_180(rotationPoint);
}
void GameObjectGroup::rotate_270(const Vector2f &rotationPoint)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_isInList.size(); i++)
        m_isInList[i]->rotate_270(rotationPoint);
}/*
void GameObjectGroup::setVisibility(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple500);
    m_visibility = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility(m_visibility);
    }
}
bool GameObjectGroup::isVisible() const
{
    return m_visibility;
}
void GameObjectGroup::setVisibility_collider_hitbox(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple600);
    m_visibility_collider_hitbox = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        try {
            m_isInList[i]->setVisibility_collider_hitbox(m_visibility_collider_hitbox);
        }  catch (...) {
            qDebug() << "error on pointer";
        }

    }
}
bool GameObjectGroup::isVisible_collider_hitbox() const
{
    return m_visibility_collider_hitbox;
}*/
void GameObjectGroup::setVisibility(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple500);
    m_visibility = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility(m_visibility);
    }
}
void GameObjectGroup::setVisibility_objectTree(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple500);
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility_objectTree(isVisible);
    }
    m_visibility_objectTree = isVisible;
}
/*void GameObjectGroup::setVisibility_chunks(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple500);
    m_visibility_chunks = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility_chunks(m_visibility_chunks);
    }
}
void GameObjectGroup::setVisibility_chunk(const ChunkID &id, bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple500);
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility_chunk(id,isVisible);
    }
}*/
void GameObjectGroup::setVisibility_collider_hitbox(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple500);
    m_visibility_collider_hitbox = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility_collider_hitbox(m_visibility_collider_hitbox);
    }
}
void GameObjectGroup::setVisibility_collider_boundingBox(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple500);
    m_visibility_collider_boundingBox = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility_collider_boundingBox(m_visibility_collider_boundingBox);
    }
}
void GameObjectGroup::setVisibility_collider_collisionData(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple500);
    m_visibility_collider_collisionData = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility_collider_collisionData(m_visibility_collider_collisionData);
    }
}
void GameObjectGroup::setVisibility_collider_isCollidingWith(bool isVisible)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple500);
    m_visibility_collider_collidingWith = isVisible;
    for(size_t i=0; i<m_isInList.size(); i++)
    {
        m_isInList[i]->setVisibility_collider_isCollidingWith(m_visibility_collider_collidingWith);
    }
}
bool GameObjectGroup::isVisible() const
{
    return m_visibility;
}
bool GameObjectGroup::isVisible_objectTree() const
{
    return m_visibility_objectTree;
}
/*bool GameObjectGroup::isVisible_chunks() const
{
    return m_visibility_chunks;
}
bool GameObjectGroup::isVisible_collider_hitbox() const
{
    return m_visibility_collider_hitbox;
}*/
bool GameObjectGroup::isVisible_collider_boundingBox() const
{
    return m_visibility_collider_boundingBox;
}
bool GameObjectGroup::isVisible_collider_collisionData() const
{
    return m_visibility_collider_collisionData;
}
bool GameObjectGroup::isVisible_collider_isCollidingWith() const
{
    return m_visibility_collider_collidingWith;
}
long long GameObjectGroup::indexOf(const GameObject* obj)
{
    return GameObjectGroup::indexOf(m_isInList,obj);
}
long long GameObjectGroup::indexOf(const vector<GameObject *> list,const GameObject* obj)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple600);
    for(size_t i=0; i<list.size(); i++)
    {
        if(list[i] == obj)
            return i;
    }
    return -1;
}

void GameObjectGroup::removinguplicates(vector<GameObject *> *list)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple700);
    vector<GameObject *> copyList;
    copyList.reserve(list->size());

    GAME_OBJECT_BLOCK("Compare list 1 loop",profiler::colors::Purple800);
    for(size_t i=0; i<list->size(); i++)
    {
        bool hasCopy = false;
        GAME_OBJECT_BLOCK("Compare list 2 loop",profiler::colors::Purple900);
        for(size_t j=0; j<copyList.size(); j++)
        {
            if((*list)[i] == copyList[j])
            {
                hasCopy = true;
                break; // Jumps to the end of this for loop
            }
        }
        GAME_OBJECT_END_BLOCK;
        // break jumpt to this Point
        if(!hasCopy)
            copyList.push_back((*list)[i]);

    }
    GAME_OBJECT_END_BLOCK;
    *list = copyList;
}
void GameObjectGroup::removinguplicates(GameObjectGroup *list)
{
    GAME_OBJECT_FUNCTION(profiler::colors::Purple700);
    removinguplicates(&list->m_isInList);
}
void GameObjectGroup::subscribe_GroupSignal(GroupSignal *subscriber)
{
    if(subscriber == nullptr)
        return;
    m_groupSubscriberList.insert(subscriber);
}
void GameObjectGroup::unsubscribe_GroupSignal(GroupSignal *subscriber)
{
    m_groupSubscriberList.erase(subscriber);
}
void GameObjectGroup::unsubscribeAll_GroupSignal()
{
    m_groupSubscriberList.clear();
}
// GameObject singals:
void GameObjectGroup::moved(GameObject* sender,const Vector2f &move)
{
    //receive signal
    //qDebug() << "sender: "<<sender << " moved: "<<Vector::toString(move).c_str();
}
void GameObjectGroup::rotated(GameObject* sender,const float deltaAngle)
{

}

// GameObjectGroup signals:
/*void GameObjectGroup::adding(GameObjectGroup* group,GameObject* obj)
{

}*/


