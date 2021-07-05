#include "chunkMap.h"

ChunkMap::ChunkMap(Vector2u chunkSize,
                   RectI area)
{
    if(chunkSize.x == 0)
        chunkSize.x =128;
    if(chunkSize.y == 0)
        chunkSize.y =128;

    if(area.getSize().x == 0)
        area.setWidth(1);
    if(area.getSize().y == 0)
        area.setHeight(1);

    m_isVisible_chunks = false;
    m_mapPos    = area.getPos();
    m_chunkSize = chunkSize;
    m_mapSize   = calculateMapSize(chunkSize, area.getSize());
    generateMap();
}
ChunkMap::ChunkMap(const ChunkMap &other)
{

}
ChunkMap::~ChunkMap()
{
    for(size_t x=0; x<m_mapSize.x; x++)
    {
        for(size_t y=0; y<m_mapSize.y; y++)
        {
            m_chunkMap[x][y]->unsubscribeAllChunks();
            delete m_chunkMap[x][y];
        }
        m_chunkMap[x].clear();
    }
    m_chunkMap.clear();
}

void ChunkMap::add(const vector<GameObject*> &list)
{
    for(GameObject* obj : list)
        this->add(obj);
}
void ChunkMap::add(GameObject *object)
{
    //qDebug() << "trying to add: "<<object;
    bool outOfMap;
    Vector2<size_t> chunkPos = findChunk(object,outOfMap);
    if(!outOfMap)
        m_chunkMap[chunkPos.x][chunkPos.y]->add(object);
    else
        GameObjectGroup::add(object);
}
void ChunkMap::add(GameObjectGroup *other)
{
    this->add(other->getVector());
}
void ChunkMap::remove(const vector<GameObject*> &list)
{
    for(size_t x=0; x<m_chunkSize.x; x++)
    {
        for(size_t y=0; y<m_chunkSize.y; y++)
        {
            m_chunkMap[x][y]->remove(list);
        }
    }
}
void ChunkMap::remove(GameObject *object)
{
    for(size_t x=0; x<m_chunkSize.x; x++)
    {
        for(size_t y=0; y<m_chunkSize.y; y++)
        {
            m_chunkMap[x][y]->remove(object);
        }
    }
}
void ChunkMap::remove(GameObjectGroup *other)
{
    for(size_t x=0; x<m_chunkSize.x; x++)
    {
        for(size_t y=0; y<m_chunkSize.y; y++)
        {
            m_chunkMap[x][y]->remove(other);
        }
    }
}
Vector2<size_t> ChunkMap::findChunk(GameObject *obj,bool &outOfMap)
{
    Vector2i chunkOfObj(0,0);
    Vector2f posOfObj = obj->getCollider().getBoundingBox().getPos();

    Vector2f relativeToChunkMapPos = posOfObj - Vector2f(m_mapPos);

    float xScalar = relativeToChunkMapPos.x / float(m_chunkSize.x);
    float yScalar = relativeToChunkMapPos.y / float(m_chunkSize.y);


    chunkOfObj = Vector2i(floor(xScalar),floor(yScalar));
    /*chunkOfObj.x = relativeToChunkMapPos.x / m_chunkSize.x ;
    chunkOfObj.y = relativeToChunkMapPos.y / m_chunkSize.y ;

    chunkOfObj.x   += (int(relativeToChunkMapPos.x) % m_chunkSize.x) != 0 ? 0 : -1;
    chunkOfObj.y   += (int(relativeToChunkMapPos.y) % m_chunkSize.y) != 0 ? 0 : -1;
    */


    /*float floatingX = relativeToChunkMapPos.x - int(relativeToChunkMapPos.x);
    float floatingY = relativeToChunkMapPos.x - int(relativeToChunkMapPos.x);
    if(floatingX > 0)
    {

    }*/

    if(chunkOfObj.x < 0 || chunkOfObj.x >= signed(m_mapSize.x) ||
       chunkOfObj.y < 0 || chunkOfObj.y >= signed(m_mapSize.y))
    {
        //qDebug() << "out of map";
        outOfMap = true;
        return Vector2<size_t>(0,0);
    }
    outOfMap = false;
    //qDebug() << "chunk Found: "<<Vector::toString(chunkOfObj).c_str();
    return Vector2<size_t>(chunkOfObj);
}

Vector2<size_t> ChunkMap::calculateMapSize(const Vector2u &chunkSize,
                                           const Vector2i &area)
{
    Vector2<size_t> size;

    size.x = area.x / chunkSize.x;
    size.y = area.y / chunkSize.y;

    if(area.x % chunkSize.x != 0)
        size.x += 1;
    if(area.y % chunkSize.y != 0)
        size.y += 1;
   // qDebug() << "chunkSize:    "<<chunkSize.x<<" "<<chunkSize.y;
   // qDebug() << "area:         "<<area.x<<" "<<area.y;
   // qDebug() << "mapSize:      "<<size.x<<" "<<size.y;
    return size;
}
void ChunkMap::generateMap()
{
    Vector2i movingPos;
    m_chunkMap.reserve(m_mapSize.x);
    for(size_t x=0; x<m_mapSize.x; x++)
    {
        m_chunkMap.push_back(vector<Chunk*>());
        m_chunkMap[x].reserve(m_mapSize.y);
        movingPos = m_mapPos  + Vector2i(int(m_chunkSize.x)*int(x),0);
        for(size_t y=0; y<m_mapSize.y; y++)
        {
            Chunk* chunk = new Chunk(m_chunkSize,Vector2f(movingPos),ChunkID(true,Vector2<size_t>(x,y)));
            chunk->subscribeChunk(this);
            m_chunkMap[x].push_back(chunk);
            movingPos += Vector2i(0,int(m_chunkSize.y));
        }
    }
}
const vector<GameObject*> &ChunkMap::getGameObjectGroup(const ChunkID &id) const
{
    if(!id.isInChunkMap)
        return this->getVector(); // Get the objects which are outside of any chunk
    if(m_chunkMap.size() <= id.chunk.x)
        return m_dummyGroup;
    if(m_chunkMap[id.chunk.x].size() <= id.chunk.y)
        return m_dummyGroup;
    return m_chunkMap[id.chunk.x][id.chunk.y]->getVector();
}
void ChunkMap::draw_chunks(PixelDisplay &display)
{
    for(size_t x=0; x<m_mapSize.x; x++)
    {
        for(size_t y=0; y<m_mapSize.y; y++)
        {
            m_chunkMap[x][y]->draw_chunk(display);
        }
    }
}
void ChunkMap::setVisibility_chunk(const ChunkID &id,bool isVisible)
{
    if(m_chunkMap.size() <= id.chunk.x)
        return;
    if(m_chunkMap[id.chunk.x].size() <= id.chunk.y)
        return;
    m_chunkMap[id.chunk.x][id.chunk.y]->setVisibility_chunk(isVisible);
}
void ChunkMap::setVisibility_chunks(bool isVisible)
{
    m_isVisible_chunks = isVisible;
    for(size_t x=0; x<m_mapSize.x; x++)
    {
        for(size_t y=0; y<m_mapSize.y; y++)
        {
            m_chunkMap[x][y]->setVisibility_chunk(m_isVisible_chunks);
        }
    }
}
bool ChunkMap::isVisible_chunk(const ChunkID &id) const
{
    if(m_chunkMap.size() <= id.chunk.x)
        return false;
    if(m_chunkMap[id.chunk.x].size() <= id.chunk.y)
        return false;
    return m_chunkMap[id.chunk.x][id.chunk.y]->isVisible_chunk();
}
bool ChunkMap::isVisible_chunks() const
{
    return m_isVisible_chunks;
}


void ChunkMap::objectIsNowInChunk(Chunk *sender,GameObject* obj,const Vector2<size_t> &newChunkIndex)
{
    if(newChunkIndex.x < m_chunkSize.x &&
       newChunkIndex.y < m_chunkSize.y)
    {
        sender->remove(obj);
        m_chunkMap[newChunkIndex.x][newChunkIndex.y]->add(obj);

        qDebug()<<"OBJ: "<<obj<<" is now in chunk: "<<newChunkIndex.x<<" "<<newChunkIndex.y;
    }
}
void ChunkMap::objectIsNowOutOfBoundry(Chunk *sender,GameObject *obj)
{
    qDebug()<<"OBJ: "<<obj<<" is out of boundry";
    sender->remove(obj);
    GameObjectGroup::add(obj);

}

void ChunkMap::moved(GameObject* sender,const Vector2f &move)
{
    bool outOfMap;
    Vector2<size_t> chunkPos = findChunk(sender,outOfMap);
    if(!outOfMap)
    {
        GameObjectGroup::remove(sender);
        m_chunkMap[chunkPos.x][chunkPos.y]->add(sender);
        qDebug()<<"OBJ: "<<sender<<" is now in chunk: "<<chunkPos.x<<" "<<chunkPos.y;


    }
}
