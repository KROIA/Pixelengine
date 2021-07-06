#include "chunkMap.h"

ChunkMap::ChunkMap(Vector2u chunkSize,
                   RectI area)
{
    EASY_BLOCK("new ChunkMap()",profiler::colors::Blue);
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
    m_chunkID = ChunkID(false,Vector2<size_t>(0,0));
    generateMap();
}
ChunkMap::ChunkMap(const ChunkMap &other)
{

}
ChunkMap::~ChunkMap()
{
    EASY_FUNCTION(profiler::colors::Blue);
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
    EASY_FUNCTION(profiler::colors::Blue100);
    for(GameObject* obj : list)
        this->add(obj);
}
void ChunkMap::add(GameObject *object)
{
    EASY_FUNCTION(profiler::colors::Blue100);
    //qDebug() << "trying to add: "<<object;
    bool outOfMap;
    vector<Vector2<size_t> > chunkPosList = findChunk(object,outOfMap);
    if(!outOfMap)
        for(const Vector2<size_t> &chunk : chunkPosList)
            m_chunkMap[chunk.x][chunk.y]->add(object);

    if(intersectsInverse(object))
        internalAddOutside(object);
}
void ChunkMap::add(GameObjectGroup *other)
{
    EASY_FUNCTION(profiler::colors::Blue100);
    this->add(other->getVector());
}
void ChunkMap::remove(const vector<GameObject*> &list)
{
    EASY_FUNCTION(profiler::colors::Blue200);
    for(size_t x=0; x<m_mapSize.x; x++)
    {
        for(size_t y=0; y<m_mapSize.y; y++)
        {
            m_chunkMap[x][y]->remove(list);
        }
    }
    for(size_t i=0; i<list.size(); i++)
        internalRemoveOutside(list[i]);
}
void ChunkMap::remove(GameObject *object)
{
    EASY_FUNCTION(profiler::colors::Blue200);
    for(size_t x=0; x<m_mapSize.x; x++)
    {
        for(size_t y=0; y<m_mapSize.y; y++)
        {
            m_chunkMap[x][y]->remove(object);
        }
    }
    internalRemoveOutside(object);
}
void ChunkMap::remove(GameObjectGroup *other)
{
    EASY_FUNCTION(profiler::colors::Blue200);
    for(size_t x=0; x<m_mapSize.x; x++)
    {
        for(size_t y=0; y<m_mapSize.y; y++)
        {
            m_chunkMap[x][y]->remove(other);
        }
    }
    for(size_t i=0; i<other->size(); i++)
        internalRemoveOutside((*other)[i]);
}
vector<Vector2<size_t> > ChunkMap::findChunk(GameObject *obj,bool &outOfMap)
{
    EASY_FUNCTION(profiler::colors::Blue400);
    vector<Vector2<size_t> > chunks;
    outOfMap = true;
    if(!intersects(obj))
    {
        return chunks;
    }
    chunks.reserve(9);
    RectF objBoundingBox = obj->getCollider().getBoundingBox();

    for(size_t x=0; x<m_mapSize.x; x++)
    {
        for(size_t y=0; y<m_mapSize.y; y++)
        {
            RectF chunkRect = m_chunkMap[x][y]->getRect();
            if(chunkRect.intersects_fast(objBoundingBox))
            {
                outOfMap = false;
                chunks.push_back(Vector2<size_t>(x,y));
            }
        }
    }
   /* Vector2i chunkOfObj(0,0);
    Vector2f posOfObj = obj->getCollider().getBoundingBox().getPos();

    Vector2f relativeToChunkMapPos = posOfObj - Vector2f(m_mapPos);

    float xScalar = relativeToChunkMapPos.x / float(m_chunkSize.x);
    float yScalar = relativeToChunkMapPos.y / float(m_chunkSize.y);


    chunkOfObj = Vector2i(floor(xScalar),floor(yScalar));

    if(chunkOfObj.x < 0 || chunkOfObj.x >= signed(m_mapSize.x) ||
       chunkOfObj.y < 0 || chunkOfObj.y >= signed(m_mapSize.y))
    {
        //qDebug() << "out of map";
        outOfMap = true;
        return chunks;
    }*/

    //qDebug() << "chunk Found: "<<Vector::toString(chunkOfObj).c_str();
    //return Vector2<size_t>(chunkOfObj);
    return chunks;
}
bool ChunkMap::intersects(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Blue500);
    Vector2f size = Vector2f(m_mapSize);
    size.x *= (float)m_chunkSize.x;
    size.y *= (float)m_chunkSize.y;
    RectF allChunksRect(Vector2f(m_mapPos),size);
    return allChunksRect.intersects_fast(obj->getCollider().getBoundingBox());
}
bool ChunkMap::intersectsInverse(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Blue500);
    Vector2f size = Vector2f(m_mapSize);
    size.x *= (float)m_chunkSize.x;
    size.y *= (float)m_chunkSize.y;
    RectF allChunksRect(Vector2f(m_mapPos),size);
    RectF objBox = obj->getCollider().getBoundingBox();
    return objBox.intersects_inverse_fast(allChunksRect);
}

Vector2<size_t> ChunkMap::calculateMapSize(const Vector2u &chunkSize,
                                           const Vector2i &area)
{
    EASY_FUNCTION(profiler::colors::Blue50);
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
    EASY_FUNCTION(profiler::colors::Blue100);
    Vector2i movingPos;
    m_chunkMap.reserve(m_mapSize.x);
    for(size_t x=0; x<m_mapSize.x; x++)
    {
        EASY_BLOCK("for(size_t x=0; x<m_mapSize.x; x++)",profiler::colors::Blue200);
        m_chunkMap.push_back(vector<Chunk*>());
        m_chunkMap[x].reserve(m_mapSize.y);
        movingPos = m_mapPos  + Vector2i(int(m_chunkSize.x)*int(x),0);
        for(size_t y=0; y<m_mapSize.y; y++)
        {
            EASY_BLOCK("for(size_t y=0; y<m_mapSize.y; y++)",profiler::colors::Blue300);
            Chunk* chunk = new Chunk(m_chunkSize,Vector2f(movingPos),ChunkID(true,Vector2<size_t>(x,y)));
            chunk->subscribeChunk(this);
            m_chunkMap[x].push_back(chunk);
            movingPos += Vector2i(0,int(m_chunkSize.y));
        }
    }
}
const vector<GameObject*> &ChunkMap::getGameObjectGroup(const ChunkID &id) const
{
    EASY_FUNCTION(profiler::colors::Blue700);
    if(!id.isInChunkMap)
        return this->getVector(); // Get the objects which are outside of any chunk
    if(m_chunkMap.size() <= id.chunk.x)
        return m_dummyGroup;
    if(m_chunkMap[id.chunk.x].size() <= id.chunk.y)
        return m_dummyGroup;
    return m_chunkMap[id.chunk.x][id.chunk.y]->getVector();
}
const vector<GameObject*> ChunkMap::getGameObjectGroup(const vector<ChunkID> &idList) const
{
    EASY_FUNCTION(profiler::colors::Blue700);
    vector<GameObject*> list;
    for(size_t i=0; i<idList.size(); i++)
    {
        vector<GameObject*> tmpList = getGameObjectGroup(idList[i]);
        list.reserve(list.size() + tmpList.size());
        for(size_t j=0; j<tmpList.size(); j++)
        {
            for(size_t k=0; k<list.size(); k++)
            {
                if(list[k] == tmpList[j])
                    goto overJump;
            }

            list.push_back(tmpList[j]);
            overJump:
            continue;
        }
    }
    return list;
}
void ChunkMap::draw_chunks(PixelDisplay &display)
{
    EASY_FUNCTION(profiler::colors::Blue);
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
    EASY_FUNCTION(profiler::colors::Blue800);
    if(!id.isInChunkMap)
        return;
    if(m_chunkMap.size() <= id.chunk.x)
        return;
    if(m_chunkMap[id.chunk.x].size() <= id.chunk.y)
        return;
    m_chunkMap[id.chunk.x][id.chunk.y]->setVisibility_chunk(isVisible);
}
void ChunkMap::setVisibility_chunk(const vector<ChunkID> &idList,bool isVisible)
{
    EASY_FUNCTION(profiler::colors::Blue800);
    for(const ChunkID &id : idList)
        setVisibility_chunk(id,isVisible);
}
void ChunkMap::setVisibility_chunks(bool isVisible)
{
    EASY_FUNCTION(profiler::colors::Blue800);
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

void ChunkMap::internalAddOutside(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Blue100);
    obj->addChunkID(m_chunkID);
    GameObjectGroup::add(obj);
}
void ChunkMap::internalRemoveOutside(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Blue300);
    obj->removeChunkID(m_chunkID);
    GameObjectGroup::remove(obj);
}


void ChunkMap::objectIsNowInChunk(Chunk *sender,GameObject* obj,const Vector2<size_t> &newChunkIndex)
{
    EASY_FUNCTION(profiler::colors::Blue800);
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
    //qDebug()<<"OBJ: "<<obj<<" is out of boundry";
    sender->remove(obj);
    //GameObjectGroup::add(obj);
    internalAddOutside(obj);
}
void ChunkMap::objectIsNowIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk)
{

}
void ChunkMap::objectIsNoLongerIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk)
{

}
void ChunkMap::updateChunkPos(Chunk *sender, GameObject* obj)
{
    EASY_FUNCTION(profiler::colors::Blue900);
    Vector2<size_t> senderPos = sender->getChunkID().chunk;
    RectF senderRect =  obj->getCollider().getBoundingBox();

    vector<ChunkID> oldIds = obj->getChunkIDList();
    for(size_t i=0; i<oldIds.size(); i++)
    {
        if(!m_chunkMap[oldIds[i].chunk.x][oldIds[i].chunk.y]->intersects(obj))
        {
            m_chunkMap[oldIds[i].chunk.x][oldIds[i].chunk.y]->remove(obj);
        }
    }

    for(long x=-2; x<=2; x++)
    {
        for(long y=-2; y<=2; y++)
        {
            long indexX = senderPos.x + x;
            long indexY = senderPos.y + y;
            if(indexX < 0 || indexY < 0)
                continue;
            if((size_t)indexX >= m_mapSize.x || (size_t)indexY >= m_mapSize.y)
                continue;

            if(senderRect.intersects_fast(m_chunkMap[indexX][indexY]->getRect()))
            {
                m_chunkMap[indexX][indexY]->add(obj);
            }
        }
    }
    if(intersectsInverse(obj))
    {
        bool add = true;
        for(size_t i=0; i<GameObjectGroup::size(); i++)
        {
            if(GameObjectGroup::operator[](i) == obj)
            {
                add = false; // Object already in this chunk
                break;
            }
        }
        if(add)
        {
            internalAddOutside(obj);
        }
    }
}


void ChunkMap::moved(GameObject* sender,const Vector2f &move)
{
    EASY_FUNCTION(profiler::colors::BlueA100);
    bool outOfMap;
    vector<Vector2<size_t> > chunkPosList = findChunk(sender,outOfMap);
    for(const Vector2<size_t> &chunk : chunkPosList)
        m_chunkMap[chunk.x][chunk.y]->add(sender);
    //qDebug() << intersectsInverse(sender);
    if(!intersectsInverse(sender))
    {
        internalRemoveOutside(sender);

        //qDebug()<<"OBJ: "<<sender<<" is now in chunk: "<<chunkPos.x<<" "<<chunkPos.y;


    }
}
