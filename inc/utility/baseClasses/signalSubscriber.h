#ifndef OBJSIGNAL_H
#define OBJSIGNAL_H
#include "base.h"

#define EMIT_SIGNAL(func,sender,...)\
emitStart();\
for(auto pair : *this)\
{\
    pair.second->func(sender, ##__VA_ARGS__);\
}\
emitEnd();

template<class T>
class SubscriberList    : public HashTable<T*>
{
    public:
        SubscriberList();
        virtual void insert(T* signal);
        virtual void erase(T* signal);
    protected:
        void emitStart();
        void emitEnd();
        void updateList();
        bool m_emiterCallActive;
        HashTable<T*> toRemove;
        HashTable<T*> toInsert;
};

template<class T>
SubscriberList<T>::SubscriberList()
    :   HashTable<T*>()
{
    m_emiterCallActive = false;
}

template<class T>
void SubscriberList<T>::insert(T* signal)
{

    if(m_emiterCallActive)
        toInsert.insert({signal,signal});
    else
        HashTable<T*>::insert({signal,signal});
}
template<class T>
void SubscriberList<T>::erase(T* signal)
{
    if(m_emiterCallActive)
        toRemove.insert({signal,signal});
    else
        HashTable<T*>::erase(signal);
}
template<class T>
void SubscriberList<T>::emitStart()
{
    m_emiterCallActive = true;
}
template<class T>
void SubscriberList<T>::emitEnd()
{
    m_emiterCallActive = false;
    updateList();
}
template<class T>
void SubscriberList<T>::updateList()
{
    for(auto pair : toRemove)
        HashTable<T*>::erase(pair.second);
    toRemove.clear();
    for(auto pair : toInsert)
        HashTable<T*>::insert(pair);
    toInsert.clear();
}
#endif // SIGNAL_H
