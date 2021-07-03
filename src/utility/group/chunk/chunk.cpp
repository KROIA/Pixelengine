#include "chunk.h"


Chunk::Chunk(const Vector2u &size,
             const Vector2f &pos)
    :   GameObjectGroup()
{
    if(size.x != 0 && size.y != 0)
        m_chunkRect.setSize(Vector2f(size));
    else
        m_chunkRect.setSize(Vector2f(128,128));
    m_chunkRect.setPos(pos);

}
Chunk::Chunk(const Chunk &other)
{
    this->m_chunkRect = other.m_chunkRect;
    GameObjectGroup::operator=(other);
}
Chunk::~Chunk()
{

}

vector<GameObject*> Chunk::getFilteredList(const vector<GameObject*> &list)
{
    vector<GameObject*> resultList;
    resultList.reserve(list.size());
    for(GameObject* obj : list)
    {
        if(isInChunk(obj))
            resultList.push_back(obj);
    }
    return resultList;
}
void Chunk::add(const vector<GameObject*> &list)
{
    for(GameObject* obj : list)
        this->add(obj);
}
void Chunk::add(GameObject *object)
{
    EASY_FUNCTION(profiler::colors::Purple50);
    if(!isInChunk(object))
    {
        qDebug() << "obj: "<<object<< " is not in this chunk: "<<m_chunkRect.getPos().x<<"\t"<<m_chunkRect.getPos().y;
        return; // Not in this area
    }
    //qDebug() << "adding: "<<object<< " to chunk: \t"<<m_chunkRect.getPos().x<<"\t"<<m_chunkRect.getPos().y;
    GameObjectGroup::addInternal(object);
    m_groupSubscriberList.adding(this,object);//emit signal
}
void Chunk::add(GameObjectGroup *other)
{
    this->add(other->getVector());
}
const RectF &Chunk::getRect() const
{
    return m_chunkRect;
}

// Signals
void Chunk::subscribeChunk(ChunkSignal *subscriber)
{
    if(subscriber == nullptr)
        return;
    for(size_t i=0; i<m_chunkSubscriberList.size(); i++)
    {
        if(m_chunkSubscriberList[i] == subscriber)
        {
            return;
        }
    }
    m_chunkSubscriberList.push_back(subscriber);
}
void Chunk::unsubscribeChunk(ChunkSignal *subscriber)
{
    for(size_t i=0; i<m_chunkSubscriberList.size(); i++)
    {
        if(m_chunkSubscriberList[i] == subscriber)
        {
            m_chunkSubscriberList.erase(m_chunkSubscriberList.begin()+i);
            return;
        }
    }
}
void Chunk::unsubscribeAllChunks()
{
    m_chunkSubscriberList.clear();
}

void Chunk::draw(PixelDisplay &display)
{
    display.addVertexLine(m_chunkRect.getDrawable());
}
inline bool Chunk::isInChunk(GameObject *obj)
{
    if(m_chunkRect.intersects_fast(obj->getCollider().getBoundingBox()))
        return true; // in this area
    return false;
}



// GameObject singals:
void Chunk::moved(GameObject* sender,const Vector2f &move)
{
    if(!isInChunk(sender))
    {
        qDebug() << " OBJ: "<< sender << " is out of this chunk";
        //GameObjectGroup::remove(sender);
    }
}
