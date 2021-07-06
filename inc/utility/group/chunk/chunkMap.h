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

        virtual vector<Vector2<size_t> > findChunk(GameObject *obj,bool &outOfMap);
        virtual bool intersects(GameObject *obj);
        virtual bool intersectsInverse(GameObject *obj);


        virtual const vector<GameObject*> &getGameObjectGroup(const ChunkID &id) const;
        virtual const vector<GameObject*> getGameObjectGroup(const vector<ChunkID> &idList) const;

        virtual void draw_chunks(PixelDisplay &display);
        virtual void setVisibility_chunk(const ChunkID &id,bool isVisible);
        virtual void setVisibility_chunk(const vector<ChunkID> &idList,bool isVisible);
        virtual void setVisibility_chunks(bool isVisible);
        virtual bool isVisible_chunk(const ChunkID &id) const;
        virtual bool isVisible_chunks() const;

    protected:
        virtual void internalAddOutside(GameObject *obj);
        virtual void internalRemoveOutside(GameObject *obj);
        // Signals from the chunks
        virtual void objectIsNowInChunk(Chunk *sender,GameObject* obj,const Vector2<size_t> &newChunkIndex);
        virtual void objectIsNowOutOfBoundry(Chunk *sender,GameObject *obj);
        virtual void objectIsNowIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk);
        virtual void objectIsNoLongerIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk);
        virtual void updateChunkPos(Chunk *sender, GameObject* obj);


        // GameObject singals:
        virtual void moved(GameObject* sender,const Vector2f &move);
    private:

        Vector2<size_t>  calculateMapSize(const Vector2u &chunkSize,
                                          const Vector2i &area);
        void generateMap();

        vector<vector<Chunk*>  >  m_chunkMap;
        Vector2u                  m_chunkSize;
        Vector2i                  m_mapPos;
        Vector2<size_t>           m_mapSize;
        vector<GameObject*>       m_dummyGroup;

        bool                      m_isVisible_chunks;
        ChunkID                   m_chunkID;
};
#endif // CHUNKMAP_H
