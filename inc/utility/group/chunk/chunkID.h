#ifndef CHUNKID_H
#define CHUNKID_H
#include "base.h"
struct ChunkID
{
    bool isInChunkMap;
    Vector2<size_t> chunk;
    bool operator==(const ChunkID &other)
    {
        if(this->isInChunkMap == other.isInChunkMap &&
           this->chunk        == other.chunk)
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
