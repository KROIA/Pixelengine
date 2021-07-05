#ifndef CHUNK_H
#define CHUNK_H
#include "base.h"
#include "gameObjectGroup.h"
#include "rect.h"
#include "signalSubscriber.h"
#include "chunkID.h"



class Chunk :   public GameObjectGroup
{
    public:
        Chunk(const Vector2u &size,
              const Vector2f &pos,
              const ChunkID  &chunkID);
        Chunk(const Chunk &other);
        ~Chunk();

        vector<GameObject*> getFilteredList(const vector<GameObject*> &list);
        virtual void add(const vector<GameObject*> &list);
        virtual void add(GameObject *object);
        virtual void add(GameObjectGroup *other);

        virtual void remove(const vector<GameObject*> &list);
        virtual void remove(GameObject *object);
        virtual void remove(GameObjectGroup *other);


        virtual const RectF &getRect() const;

        // Signals
        virtual void subscribeChunk(ChunkSignal *subscriber);
        virtual void unsubscribeChunk(ChunkSignal *subscriber);
        virtual void unsubscribeAllChunks();

        virtual void draw(PixelDisplay &display);

    protected:
        inline bool isInChunk(GameObject *obj);
        inline ChunkID getNewChunkPos(GameObject *obj);

        // GameObject singals:
        virtual void moved(GameObject* sender,const Vector2f &move);

    private:
        ChunkSubscriberList m_chunkSubscriberList;
        RectF       m_chunkRect;
        ChunkID     m_chunkID;
};
#endif // CHUNK_H
