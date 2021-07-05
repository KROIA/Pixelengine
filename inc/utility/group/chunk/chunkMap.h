#ifndef CHUNKMAP_H
#define CHUNKMAP_H
#include "base.h"
#include "chunk.h"

class ChunkMap  :   private ChunkSignal, GameObjectGroup
{
    public:
        ChunkMap(Vector2u chunkSize,
                 RectI area);
        ChunkMap(const ChunkMap &other);
        ~ChunkMap();


        virtual void add(const vector<GameObject*> &list);
        virtual void add(GameObject *object);
        virtual void add(GameObjectGroup *other);

        virtual void remove(const vector<GameObject*> &list);
        virtual void remove(GameObject *object);
        virtual void remove(GameObjectGroup *other);

        virtual Vector2<size_t> findChunk(GameObject *obj,bool &outOfMap);

        virtual const vector<GameObject*> &getGameObjectGroup(const ChunkID &id) const;

        virtual void draw_chunks(PixelDisplay &display);
        virtual void setVisibility_chunk(const ChunkID &id,bool isVisible);
        virtual void setVisibility_chunks(bool isVisible);
        virtual bool isVisible_chunk(const ChunkID &id) const;
        virtual bool isVisible_chunks() const;

    protected:
        // Signals from the chunks
        virtual void objectIsNowInChunk(Chunk *sender,GameObject* obj,const Vector2<size_t> &newChunkIndex);
        virtual void objectIsNowOutOfBoundry(Chunk *sender,GameObject *obj);

        // GameObject singals:
        virtual void moved(GameObject* sender,const Vector2f &move);
    private:

        Vector2<size_t>  calculateMapSize(const Vector2u &chunkSize,
                                          const Vector2i &area);
        void generateMap();

        vector<vector<Chunk*>    > m_chunkMap;
        Vector2u                  m_chunkSize;
        Vector2i                  m_mapPos;
        Vector2<size_t>           m_mapSize;
        vector<GameObject*>       m_dummyGroup;

        bool                      m_isVisible_chunks;
};
#endif // CHUNKMAP_H
