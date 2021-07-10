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
        struct Settings{
                Vector2u size;
                Vector2f position;
                ChunkID  chunkID;
                bool isVisible;
        };
        static Settings __defaultSettings;

        Chunk(const Settings &settings);
        Chunk(const Vector2u &size,
              const Vector2f &pos,
              const ChunkID  &chunkID);
        Chunk(const Chunk &other);
        ~Chunk();

        virtual const Chunk &operator=(const Chunk &other);
        virtual Settings getSettings() const;

        vector<GameObject*> getFilteredList(const vector<GameObject*> &list);
        virtual void add(const vector<GameObject*> &list);
        virtual void add(GameObject *object);
        virtual void add(GameObjectGroup *other);

        virtual void remove(const vector<GameObject*> &list);
        virtual void remove(GameObject *object);
        virtual void remove(GameObjectGroup *other);

        virtual bool intersects(GameObject *object);


        virtual const RectF &getRect() const;
        virtual const ChunkID &getChunkID() const;

        // Signals
        virtual void subscribeChunk(ChunkSignal *subscriber);
        virtual void unsubscribeChunk(ChunkSignal *subscriber);
        virtual void unsubscribeAllChunks();

        virtual void draw_chunk(PixelDisplay &display);
        virtual void setVisibility_chunk(bool isVisible);
        virtual bool isVisible_chunk() const;

    protected:
        //inline bool isInChunk(GameObject *obj);
        inline ChunkID getNewChunkPos(GameObject *obj);

        // GameObject singals:
        virtual void moved(GameObject* sender,const Vector2f &move);
        virtual void rotated(GameObject* sender,const float deltaAngle);

    private:
        void constructor(const Settings &settings);
        ChunkSubscriberList m_chunkSubscriberList;
        RectF       m_chunkRect;
        ChunkID     m_chunkID;

        bool        m_visibility_chunk;
};
#endif // CHUNK_H
