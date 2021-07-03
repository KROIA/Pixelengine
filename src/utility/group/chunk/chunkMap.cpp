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
}
void ChunkMap::add(GameObjectGroup *other)
{
    this->add(other->getVector());
}
Vector2<size_t> ChunkMap::findChunk(GameObject *obj,bool &outOfMap)
{
    Vector2i chunkOfObj(0,0);
    Vector2f posOfObj = obj->getCollider().getBoundingBox().getPos();

    Vector2i relativeToChunkMapPos = Vector2i(posOfObj) - m_mapPos;
    chunkOfObj.x = relativeToChunkMapPos.x / m_chunkSize.x ;
    chunkOfObj.y = relativeToChunkMapPos.y / m_chunkSize.y ;

    chunkOfObj.x   += (relativeToChunkMapPos.x % m_chunkSize.x) != 0 ? 0 : -1;
    chunkOfObj.y   += (relativeToChunkMapPos.y % m_chunkSize.y) != 0 ? 0 : -1;

    if(chunkOfObj.x < 0 || chunkOfObj.x >= signed(m_mapSize.x) ||
       chunkOfObj.y < 0 || chunkOfObj.y >= signed(m_mapSize.y))
    {
        qDebug() << "out of map";
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
    qDebug() << "chunkSize:    "<<chunkSize.x<<" "<<chunkSize.y;
    qDebug() << "area:         "<<area.x<<" "<<area.y;
    qDebug() << "mapSize:      "<<size.x<<" "<<size.y;
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
            Chunk* chunk = new Chunk(m_chunkSize,Vector2f(movingPos));
            chunk->subscribeChunk(this);
            m_chunkMap[x].push_back(chunk);
            movingPos += Vector2i(0,int(m_chunkSize.y));
        }
    }
}

void ChunkMap::draw(PixelDisplay &display)
{
    for(size_t x=0; x<m_mapSize.x; x++)
    {
        for(size_t y=0; y<m_mapSize.y; y++)
        {
            m_chunkMap[x][y]->draw(display);
        }
    }
}


void ChunkMap::movingToUpperChunk(GameObject* sender)
{
    qDebug() << "Obj: "<<sender<<" moving to upper chunk";
}
void ChunkMap::movingToLowerChunk(GameObject* sender)
{
    qDebug() << "Obj: "<<sender<<" moving to lower chunk";
}
void ChunkMap::movingToLeftChunk(GameObject* sender)
{
    qDebug() << "Obj: "<<sender<<" moving to left chunk";
}
void ChunkMap::movingToRightChunk(GameObject* sender)
{
    qDebug() << "Obj: "<<sender<<" moving to right chunk";
}
