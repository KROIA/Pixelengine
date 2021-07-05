#include "chunk.h"


Chunk::Chunk(const Vector2u &size,
             const Vector2f &pos,
             const ChunkID  &chunkID)
    :   GameObjectGroup()
{
    if(size.x != 0 && size.y != 0)
        m_chunkRect.setSize(Vector2f(size));
    else
        m_chunkRect.setSize(Vector2f(128,128));
    m_chunkRect.setPos(pos);
    m_chunkID = chunkID;
    m_chunkID.isInChunkMap = true;
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
    object->setChunkID(m_chunkID);
    GameObjectGroup::addInternal(object);
    m_groupSubscriberList.adding(this,object);//emit signal
}
void Chunk::add(GameObjectGroup *other)
{
    this->add(other->getVector());
}
void Chunk::remove(const vector<GameObject*> &list)
{
    for(size_t i=0; i<list.size(); i++)
    {
        this->remove(list[i]);
    }
}
void Chunk::remove(GameObject *object)
{
    ChunkID id = object->getChunkID();
    id.isInChunkMap = false;
    object->setChunkID(id);
    GameObjectGroup::remove(object);
}
void Chunk::remove(GameObjectGroup *other)
{
    for(size_t i=0; i<other->size(); i++)
    {
        ChunkID id = (*other)[i]->getChunkID();
        id.isInChunkMap = false;
        (*other)[i]->setChunkID(id);
    }
    GameObjectGroup::remove(other);
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
inline ChunkID Chunk::getNewChunkPos(GameObject *obj)
{
    ChunkID newChunk = m_chunkID;
    RectF objBox = obj->getCollider().getBoundingBox();
    if(objBox.isBeneathOf(m_chunkRect))
        newChunk.chunk.y++;
    else if(objBox.isOnTopOf(m_chunkRect))
    {
        if(newChunk.chunk.y == 0)
            newChunk.isInChunkMap = false;
        else
            newChunk.chunk.y--;
    }
    if(objBox.isRightOf(m_chunkRect))
        newChunk.chunk.x++;
    else if(objBox.isLeftOf(m_chunkRect))
    {
        if(newChunk.chunk.x == 0)
            newChunk.isInChunkMap = false;
        else
            newChunk.chunk.x--;
    }

    if(newChunk == m_chunkID)
        qDebug() << "same chunk";
    return newChunk;
}



// GameObject singals:
void Chunk::moved(GameObject* sender,const Vector2f &move)
{
    if(!isInChunk(sender))
    {
        //qDebug() << " OBJ: "<< sender << " is out of this chunk";
       ChunkID newChunkID = getNewChunkPos(sender);

        if(!newChunkID.isInChunkMap)
        {
            //qDebug() << "OBJ is now out of bourdy";
            ChunkID id = sender->getChunkID();
            id.isInChunkMap = false;
            sender->setChunkID(id);
            m_chunkSubscriberList.objectIsNowOutOfBoundry(this,sender);
        }
        else
            m_chunkSubscriberList.objectIsNowInChunk(this,sender,newChunkID.chunk);
    }
}
