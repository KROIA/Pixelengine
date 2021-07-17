#include "signalSubscriber.h"

ObjSubscriberList::ObjSubscriberList()
    :   HashTable<ObjSignal *>()
{}

void ObjSubscriberList::insert(ObjSignal* signal)
{
    HashTable<ObjSignal *>::insert({signal,signal});
}

void ObjSubscriberList::moved(GameObject* sender,const Vector2f &move)
{
    for(auto pair : *this)
    {
        pair.second->moved(sender,move);
    }
}
void ObjSubscriberList::rotated(GameObject* sender,const float deltaAngle)
{
    for(auto pair : *this)
    {
        pair.second->rotated(sender,deltaAngle);
    }
}


GroupSubscriberList::GroupSubscriberList()
    :   HashTable<GroupSignal *>()
{

}
void GroupSubscriberList::insert(GroupSignal* signal)
{
    HashTable<GroupSignal *>::insert({signal,signal});
}
void GroupSubscriberList::adding(GameObjectGroup *sender,GameObject* obj)
{
    for(auto pair : *this)
    {
        pair.second->adding(sender,obj);
    }
}
void GroupSubscriberList::adding(GameObjectGroup *sender,GameObjectGroup* group)
{
    for(auto pair : *this)
    {
        pair.second->adding(sender,group);
    }
}
void GroupSubscriberList::removing(GameObjectGroup *sender,GameObject* obj)
{
    for(auto pair : *this)
    {
        pair.second->removing(sender,obj);
    }
}
void GroupSubscriberList::removing(GameObjectGroup *sender,GameObjectGroup* group)
{
    for(auto pair : *this)
    {
        pair.second->removing(sender,group);
    }
}
void GroupSubscriberList::willBeCleared(GameObjectGroup* sender)
{
    for(auto pair : *this)
    {
        pair.second->willBeCleared(sender);
    }
}
void GroupSubscriberList::cleared(GameObjectGroup* sender)
{
    for(auto pair : *this)
    {
        pair.second->cleared(sender);
    }
}
/*
ChunkSubscriberList::ChunkSubscriberList()
    :   vector<ChunkSignal *>()
{

}
void ChunkSubscriberList::objectIsNowInChunk(Chunk *sender,GameObject* obj,const Vector2<size_t> &newChunkIndex)
{
    for(ChunkSignal* &pair.second : *this)
    {
        pair.second->objectIsNowInChunk(sender,obj,newChunkIndex);
    }
}
void ChunkSubscriberList::objectIsNowOutOfBoundry(Chunk *sender,GameObject *obj)
{
    for(ChunkSignal* &pair.second : *this)
    {
        pair.second->objectIsNowOutOfBoundry(sender,obj);
    }
}
void ChunkSubscriberList::objectIsNowIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk)
{
    for(ChunkSignal* &pair.second : *this)
    {
        pair.second->objectIsNowIntersecting(sender,obj,intersectingChunk);
    }
}
void ChunkSubscriberList::objectIsNoLongerIntersecting(Chunk *sender,GameObject *obj, const Vector2<size_t> &intersectingChunk)
{
    for(ChunkSignal* &pair.second : *this)
    {
        pair.second->objectIsNoLongerIntersecting(sender,obj,intersectingChunk);
    }
}
void ChunkSubscriberList::updateChunkPos(Chunk *sender, GameObject* obj)
{
    for(ChunkSignal* &pair.second : *this)
    {
        pair.second->updateChunkPos(sender,obj);
    }
}*/
ControllerSubscriberList::ControllerSubscriberList()
    :   HashTable<ControllerSignal *>()
{}
void ControllerSubscriberList::insert(ControllerSignal* signal)
{
    HashTable<ControllerSignal *>::insert({signal,signal});
}

void ControllerSubscriberList::moveAvailable(Controller *sender)
{
    for(auto pair : *this)
    {
        pair.second->moveAvailable(sender);
    }
}

UserEventSubscriberList::UserEventSubscriberList()
    :   HashTable<UserEventSignal *>()
{

}
void UserEventSubscriberList::insert(UserEventSignal* signal)
{
    HashTable<UserEventSignal *>::insert({signal,signal});
}
void UserEventSubscriberList::eventAdded(UserEventHandler *sender,  Event *e)
{
    for(auto pair : *this)
    {
        pair.second->eventAdded(sender,e);
    }
}
void UserEventSubscriberList::eventRemoved(UserEventHandler *sender,  Event *e)
{
    for(auto pair : *this)
    {
        pair.second->eventRemoved(sender,e);
    }
}
PainterSubscriberList::PainterSubscriberList()
    :   HashTable<PainterSignal *>()
{}
void PainterSubscriberList::insert(PainterSignal* signal)
{
    HashTable<PainterSignal *>::insert({signal,signal});
}
void PainterSubscriberList::renderLayerChanged(Painter *sender, size_t lastLayer, size_t &newLayer)
{
    for(auto pair : *this)
    {
        pair.second->renderLayerChanged(sender,lastLayer,newLayer);
    }
}
void PainterSubscriberList::isInvisible(Painter *sender)
{
    for(auto pair : *this)
    {
        pair.second->isInvisible(sender);
    }
}
void PainterSubscriberList::isVisible(Painter *sender)
{
    for(auto pair : *this)
    {
        pair.second->isVisible(sender);
    }
}
