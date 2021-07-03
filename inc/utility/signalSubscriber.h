#ifndef OBJSIGNAL_H
#define OBJSIGNAL_H
#include "base.h"

// Signals for GameObjects
class ObjSignal
{
    public:
        ObjSignal(){}

        virtual void moved(GameObject* sender,const Vector2f &move) = 0;

    protected:

};
// Vector of Signals
class ObjSubscriberList    : public vector<ObjSignal*>
{
    public:
        ObjSubscriberList();
        virtual void moved(GameObject* sender,const Vector2f &move);
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

        virtual void movingToUpperChunk(GameObject* sender) = 0;
        virtual void movingToLowerChunk(GameObject* sender) = 0;
        virtual void movingToLeftChunk(GameObject* sender)  = 0;
        virtual void movingToRightChunk(GameObject* sender) = 0;

    protected:

};
// Vector of Signals
class ChunkSubscriberList    : public vector<ChunkSignal*>
{
    public:
        ChunkSubscriberList();
        virtual void movingToUpperChunk(GameObject* sender);
        virtual void movingToLowerChunk(GameObject* sender);
        virtual void movingToLeftChunk(GameObject* sender);
        virtual void movingToRightChunk(GameObject* sender);
    protected:

};


#endif // SIGNAL_H
