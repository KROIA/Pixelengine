#ifndef OBJSIGNAL_H
#define OBJSIGNAL_H
#include "base.h"


// Signals for GameObjects
class SubmoduleSignal
{
    public:
        SubmoduleSignal(){}

        virtual void moved(Submodule* sender,const Vector2f &move) = 0;
        virtual void rotated(Submodule* sender,const float deltaAngle) = 0;
    protected:

};
// Vector of Signals
class SubmoduleSubscriberList    : public HashTable<SubmoduleSignal*>
{
    public:
        SubmoduleSubscriberList();
        virtual void insert(SubmoduleSignal* signal);
        virtual void erase(SubmoduleSignal* signal);

        virtual void moved(Submodule* sender,const Vector2f &move);
        virtual void rotated(Submodule* sender,const float deltaAngle);
    protected:
        void updateList();
        bool m_emiterCallActive;
        HashTable<SubmoduleSignal*> toRemove;
        HashTable<SubmoduleSignal*> toInsert;
};
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
class ObjSubscriberList    : public HashTable<ObjSignal*>
{
    public:
        ObjSubscriberList();
        virtual void insert(ObjSignal* signal);
        virtual void erase(ObjSignal* signal);

        virtual void moved(GameObject* sender,const Vector2f &move);
        virtual void rotated(GameObject* sender,const float deltaAngle);
    protected:
        void updateList();
        bool m_emiterCallActive;
        HashTable<ObjSignal*> toRemove;
        HashTable<ObjSignal*> toInsert;
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
class GroupSubscriberList    : public HashTable<GroupSignal*>
{
    public:
        GroupSubscriberList();
        virtual void insert(GroupSignal* signal);

        virtual void adding(GameObjectGroup* sender,GameObject* obj);
        virtual void adding(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void removing(GameObjectGroup* sender,GameObject* obj);
        virtual void removing(GameObjectGroup* sender,GameObjectGroup* group);
        virtual void willBeCleared(GameObjectGroup* sender);
        virtual void cleared(GameObjectGroup* sender);
    protected:

};


// Signals for Chunks
/*class ChunkSignal
{
    public:
        ChunkSignal(){}
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
        virtual void objectIsNowInChunk(Chunk *sender,GameObject* obj,const Vector2<size_t> &newChunkIndex);
        virtual void objectIsNowOutOfBoundry(Chunk *sender,GameObject *obj);
        virtual void objectIsNowIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk);
        virtual void objectIsNoLongerIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk);
        virtual void updateChunkPos(Chunk *sender, GameObject* obj);
    protected:

};*/


// Signals for Controller
class ControllerSignal
{
    public:
        ControllerSignal(){}

        virtual void moveAvailable(Controller *sender) = 0;
};
// Vector of Signals
class ControllerSubscriberList: public HashTable<ControllerSignal*>
{
    public:
        ControllerSubscriberList();
        virtual void insert(ControllerSignal* signal);

        virtual void moveAvailable(Controller *sender);
};

// Signals for User Events
class UserEventSignal
{
    public:
        UserEventSignal(){}

        virtual void eventAdded(UserEventHandler *sender,  Event *e) = 0;
        virtual void eventRemoved(UserEventHandler *sender,  Event *e) = 0;
    protected:

};
// Vector of Signals
class UserEventSubscriberList    : public HashTable<UserEventSignal*>
{
    public:
        UserEventSubscriberList();
        virtual void insert(UserEventSignal* signal);

        virtual void eventAdded(UserEventHandler *sender,  Event *e);
        virtual void eventRemoved(UserEventHandler *sender,  Event *e);
    protected:

};

// Signals from Painter
class PainterSignal
{
    public:
        PainterSignal(){}

        virtual void renderLayerChanged(Painter *sender, size_t lastLayer, size_t &newLayer) = 0;
        virtual void isInvisible(Painter *sender) = 0;
        virtual void isVisible(Painter *sender) = 0;
};

// Vector of Signals
class PainterSubscriberList    : public HashTable<PainterSignal*>
{
    public:
        PainterSubscriberList();
        virtual void insert(PainterSignal* signal);

        virtual void renderLayerChanged(Painter *sender, size_t lastLayer, size_t &newLayer);
        virtual void isInvisible(Painter *sender);
        virtual void isVisible(Painter *sender);
    protected:

};
#endif // SIGNAL_H
