#include "signalSubscriber.h"

ObjSubscriberList::ObjSubscriberList()
    :   vector<ObjSignal *>()
{

}

void ObjSubscriberList::moved(GameObject* sender,const Vector2f &move)
{
    for(ObjSignal* &sub : *this)
    {
        sub->moved(sender,move);
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
