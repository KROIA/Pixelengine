#include "signalSubscriber.h"

ObjSubscriberList::ObjSubscriberList()
    :   vector<ObjSignal *>()
{

}

void ObjSubscriberList::moved(GameObject* sender,const Vector2f &move)
{
    for(size_t i=0; i<this->size(); i++)
    //for(ObjSignal* &sub : *this)
    {
        (*this)[i]->moved(sender,move);
    }
}



GroupSubscriberList::GroupSubscriberList()
    :   vector<GroupSignal *>()
{

}
void GroupSubscriberList::adding(GameObjectGroup *sender,GameObject* obj)
{
    for(GroupSignal* &sub : *this)
    {
        sub->adding(sender,obj);
    }
}
void GroupSubscriberList::adding(GameObjectGroup *sender,GameObjectGroup* group)
{
    for(GroupSignal* &sub : *this)
    {
        sub->adding(sender,group);
    }
}
void GroupSubscriberList::removing(GameObjectGroup *sender,GameObject* obj)
{
    for(GroupSignal* &sub : *this)
    {
        sub->removing(sender,obj);
    }
}
void GroupSubscriberList::removing(GameObjectGroup *sender,GameObjectGroup* group)
{
    for(GroupSignal* &sub : *this)
    {
        sub->removing(sender,group);
    }
}
void GroupSubscriberList::willBeCleared(GameObjectGroup* sender)
{
    for(GroupSignal* &sub : *this)
    {
        sub->willBeCleared(sender);
    }
}
void GroupSubscriberList::cleared(GameObjectGroup* sender)
{
    for(GroupSignal* &sub : *this)
    {
        sub->cleared(sender);
    }
}

ChunkSubscriberList::ChunkSubscriberList()
    :   vector<ChunkSignal *>()
{

}/*
void ChunkSubscriberList::movingToUpperChunk(GameObject* sender)
{
    for(ChunkSignal* &sub : *this)
    {
        sub->movingToUpperChunk(sender);
    }
}
void ChunkSubscriberList::movingToLowerChunk(GameObject* sender)
{
    for(ChunkSignal* &sub : *this)
    {
        sub->movingToLowerChunk(sender);
    }
}
void ChunkSubscriberList::movingToLeftChunk(GameObject* sender)
{
    for(ChunkSignal* &sub : *this)
    {
        sub->movingToLeftChunk(sender);
    }
}
void ChunkSubscriberList::movingToRightChunk(GameObject* sender)
{
    for(ChunkSignal* &sub : *this)
    {
        sub->movingToRightChunk(sender);
    }
}
*/
void ChunkSubscriberList::objectIsNowInChunk(Chunk *sender,GameObject* obj,const Vector2<size_t> &newChunkIndex)
{
    for(ChunkSignal* &sub : *this)
    {
        sub->objectIsNowInChunk(sender,obj,newChunkIndex);
    }
}
void ChunkSubscriberList::objectIsNowOutOfBoundry(Chunk *sender,GameObject *obj)
{
    for(ChunkSignal* &sub : *this)
    {
        sub->objectIsNowOutOfBoundry(sender,obj);
    }
}
void ChunkSubscriberList::objectIsNowIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk)
{
    for(ChunkSignal* &sub : *this)
    {
        sub->objectIsNowIntersecting(sender,obj,intersectingChunk);
    }
}
void ChunkSubscriberList::objectIsNoLongerIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk)
{
    for(ChunkSignal* &sub : *this)
    {
        sub->objectIsNoLongerIntersecting(sender,obj,intersectingChunk);
    }
}
void ChunkSubscriberList::updateChunkPos(Chunk *sender, GameObject* obj)
{
    for(ChunkSignal* &sub : *this)
    {
        sub->updateChunkPos(sender,obj);
    }
}
