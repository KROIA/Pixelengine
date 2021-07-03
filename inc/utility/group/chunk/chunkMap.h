#ifndef CHUNKMAP_H
#define CHUNKMAP_H
#include "base.h"
#include "chunk.h"

class ChunkMap  :   private ChunkSignal
{
    public:
        ChunkMap(Vector2u chunkSize,
                 RectI area);
        ChunkMap(const ChunkMap &other);
        ~ChunkMap();

        virtual void add(const vector<GameObject*> &list);
        virtual void add(GameObject *object);
        virtual void add(GameObjectGroup *other);

        virtual Vector2<size_t> findChunk(GameObject *obj,bool &outOfMap);

        virtual void draw(PixelDisplay &display);
    protected:
        // Signals from the chunks
        virtual void movingToUpperChunk(GameObject* sender);
        virtual void movingToLowerChunk(GameObject* sender);
        virtual void movingToLeftChunk(GameObject* sender);
        virtual void movingToRightChunk(GameObject* sender);

    private:

        Vector2<size_t>  calculateMapSize(const Vector2u &chunkSize,
                                          const Vector2i &area);
        void generateMap();

        vector<vector<Chunk*>    > m_chunkMap;
        Vector2u                  m_chunkSize;
        Vector2i                  m_mapPos;
        Vector2<size_t>           m_mapSize;

};
#endif // CHUNKMAP_H
