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
void ObjSubscriberList::rotated(GameObject* sender,const float deltaAngle)
{
    for(size_t i=0; i<this->size(); i++)
    //for(ObjSignal* &sub : *this)
    {
        (*this)[i]->rotated(sender,deltaAngle);
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

}
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


UserEventSubscriberList::UserEventSubscriberList()
    :   vector<UserEventSignal *>()
{

}
void UserEventSubscriberList::eventAdded(UserEventHandler *sender,  Event *e)
{
    for(UserEventSignal* &sub : *this)
    {
        sub->eventAdded(sender,e);
    }
}
void UserEventSubscriberList::eventRemoved(UserEventHandler *sender,  Event *e)
{
    for(UserEventSignal* &sub : *this)
    {
        sub->eventRemoved(sender,e);
    }
}
