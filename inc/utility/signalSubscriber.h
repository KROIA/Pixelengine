#ifndef OBJSIGNAL_H
#define OBJSIGNAL_H
#include "base.h"

// Signals for GameObjects
class ObjSignal
{
    public:
        ObjSignal(){}

        virtual void moved(GameObject* sender,const Vector2f &move) = 0;
        virtual void rotated(GameObject* sender,const float deltaAngle) = 0;
    protected:

};
// Vector of Signals
class ObjSubscriberList    : public vector<ObjSignal*>
{
    public:
        ObjSubscriberList();
        virtual void moved(GameObject* sender,const Vector2f &move);
        virtual void rotated(GameObject* sender,const float deltaAngle);
    protected:

};


// Signals for GameObjectGroups
class GroupSignal
{
    public:
        virtual void adding(GameObjectGroup* sender,GameObject* obj) = 0;
        virtual void adding(GameObjectGroup* sender,GameObjectGroup* group) = 0;
        virtual void removing(GameObjectGroup* sender,GameObject* obj) = 0;
        virtual void removing(GameObjectGroup* sender,GameObjectGroup* group) = 0;
        virtual void willBeCleared(GameObjectGroup* sender) = 0;
        virtual void cleared(GameObjectGroup* sender) = 0;
};

// Vector of Signals
class GroupSubscriberList    : public vector<GroupSignal*>
{
    public:
        GroupSubscriberList();
        virtual void adding(GameObjectGroup* sender,GameObject* obj);
        virtual void adding(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void removing(GameObjectGroup* sender,GameObject* obj);
        virtual void removing(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void willBeCleared(GameObjectGroup* sender);
        virtual void cleared(GameObjectGroup* sender);
    protected:

};


// Signals for Chunks
class ChunkSignal
{
    public:
        ChunkSignal(){}

        /*virtual void movingToUpperChunk(GameObject* sender) = 0;
        virtual void movingToLowerChunk(GameObject* sender) = 0;
        virtual void movingToLeftChunk(GameObject* sender)  = 0;
        virtual void movingToRightChunk(GameObject* sender) = 0;*/
        virtual void objectIsNowInChunk(Chunk *sender,GameObject* obj,const Vector2<size_t> &newChunkIndex) = 0;
        virtual void objectIsNowOutOfBoundry(Chunk *sender,GameObject *obj) = 0;
        virtual void objectIsNowIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk) = 0;
        virtual void objectIsNoLongerIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk) = 0;
        virtual void updateChunkPos(Chunk *sender, GameObject* obj) = 0;
    protected:

};
// Vector of Signals
class ChunkSubscriberList    : public vector<ChunkSignal*>
{
    public:
        ChunkSubscriberList();
       /* virtual void movingToUpperChunk(GameObject* sender);
        virtual void movingToLowerChunk(GameObject* sender);
        virtual void movingToLeftChunk(GameObject* sender);
        virtual void movingToRightChunk(GameObject* sender);*/
        virtual void objectIsNowInChunk(Chunk *sender,GameObject* obj,const Vector2<size_t> &newChunkIndex);
        virtual void objectIsNowOutOfBoundry(Chunk *sender,GameObject *obj);
        virtual void objectIsNowIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk);
        virtual void objectIsNoLongerIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk);
        virtual void updateChunkPos(Chunk *sender, GameObject* obj);
    protected:

};


// Signals for GameObjects
class UserEventSignal
{
    public:
        UserEventSignal(){}

        virtual void eventAdded(UserEventHandler *sender,  Event *e) = 0;
        virtual void eventRemoved(UserEventHandler *sender,  Event *e) = 0;
    protected:

};
// Vector of Signals
class UserEventSubscriberList    : public vector<UserEventSignal*>
{
    public:
        UserEventSubscriberList();
        virtual void eventAdded(UserEventHandler *sender,  Event *e);
        virtual void eventRemoved(UserEventHandler *sender,  Event *e);
    protected:

};
#endif // SIGNAL_H
