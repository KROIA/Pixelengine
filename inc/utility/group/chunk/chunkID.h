#ifndef CHUNKID_H
#define CHUNKID_H
#include "base.h"
struct ChunkID
{
    bool isInChunkMap;
    Vector2<size_t> chunk;
    ChunkID()
    {
        isInChunkMap = false;
        chunk.x = 0;
        chunk.y = 0;
    }
    ChunkID(bool _isInChunkMap, Vector2<size_t> _chunk)
    {
        isInChunkMap = _isInChunkMap;
        chunk = _chunk;
    }
    bool operator==(const ChunkID &other)
    {
        if(this->isInChunkMap == other.isInChunkMap &&
           this->chunk        == other.chunk)
            return true;
        return false;
    }
    bool operator!=(const ChunkID &other)
    {
        if(this->chunk        != other.chunk)
            return true;
        if(this->isInChunkMap != other.isInChunkMap)
            return true;
        return false;
    }
    const ChunkID &operator=(const ChunkID &other)
    {
        this->isInChunkMap = other.isInChunkMap;
        this->chunk        = other.chunk;
        return *this;
    }
};
#endif // CHUNKID_H
