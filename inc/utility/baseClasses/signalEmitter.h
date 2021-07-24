#ifndef OBJSIGNAL_H
#define OBJSIGNAL_H
#include "base.h"


#define SIGNAL_EMIT_INTERN(func,sender,...)\
    emitStart();\
    for(auto pair : m_inList)\
    {\
        pair.second->func(sender, ##__VA_ARGS__);\
    }\
    emitEnd();

#define SIGNAL_DEF(baseClass)\
    class baseClass##Signal\
    {\
        typedef baseClass _SIGNAL_BASECLASS_; \
        public:\
    baseClass##Signal(){}

#define SIGNAL_DEF_END };

#define SIGNAL_FUNC(name,...) virtual void name(_SIGNAL_BASECLASS_ *sender PARAM_LIST(COUNT_ARGUMENTS(__VA_ARGS__),__VA_ARGS__)) = 0;


#define SIGNAL_EMITTER_DEF(baseClass)\
    class baseClass##SignalEmitter : public SignalEmitter<baseClass##Signal> \
    {\
    typedef baseClass _SIGNAL_BASECLASS_; \
    public:\
        baseClass##SignalEmitter() : SignalEmitter<baseClass##Signal>(){}

#define SIGNAL_EMITTER_DEF_END };

#define SIGNAL_EMITTER(baseClass)\
public:\
void subscribe_##baseClass##Signal(baseClass##Signal *subscriber) \
{	m_##baseClass##SignalEmitter.insert(subscriber);  } \
void unsubscribe_##baseClass##Signal(baseClass##Signal *subscriber) \
{	m_##baseClass##SignalEmitter.erase(subscriber);  } \
void unsubscribeAll_##baseClass##Signal() \
{	m_##baseClass##SignalEmitter.clear();  } \
private:\
baseClass##SignalEmitter m_##baseClass##SignalEmitter;


#define SIGNAL_EMIT(baseClass,signal,...) m_##baseClass##SignalEmitter.signal(this,##__VA_ARGS__);

#define SIGNAL_EMITTER_FUNC(name,...) \
    void name(_SIGNAL_BASECLASS_ *sender PARAM_LIST(COUNT_ARGUMENTS(__VA_ARGS__),__VA_ARGS__))\
    {\
        SIGNAL_EMIT_INTERN(name,sender VALUE_LIST(COUNT_ARGUMENTS(__VA_ARGS__),__VA_ARGS__))\
    }

// For inheritance
#define SIGNAL_RECEIVES(baseClass) private baseClass##Signal
#define SLOT_DECLARATION(signalBaseClass,name,...) void name(signalBaseClass *sender,##__VA_ARGS__);
#define SLOT_DEFINITION(thisClass,signalBaseClass,name,...) void thisClass::name(signalBaseClass *sender,##__VA_ARGS__)

#define SIGNAL_SUBSCRIBE(baseClass,sender) sender->subscribe_##baseClass##Signal(this);
#define SIGNAL_UNSUBSCRIBE(baseClass,sender) sender->unsubscribe_##baseClass##Signal(this);
#define SIGNAL_UNSUBSCRIBE_ALL(baseClass,sender) sender->unsubscribeAll_##baseClass##Signal();
//---------
#define TWENTIETH_ARGUMENT(x1,x2,a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12,a13,a14,a15,a16,a17,a18,a19,a20, ...) a20
#define COUNT_ARGUMENTS(...) TWENTIETH_ARGUMENT(dummy, ## __VA_ARGS__,20,19,18,17,16,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)


 #define TYPE_0(...)
 #define TYPE_1(type,...) type
 #define TYPE_2(t1,type,...) type
 #define TYPE_3(t1,t2,type,...) type
 #define TYPE_4(t1,t2,t3,type,...) type
 #define TYPE_5(t1,t2,t3,t4,type,...) type
 #define TYPE_6(t1,t2,t3,t4,t5,type,...) type
 #define TYPE_7(t1,t2,t3,t4,t5,t6,type,...) type
 #define TYPE_8(t1,t2,t3,t4,t5,t6,t7,type,...) type
 #define TYPE_9(t1,t2,t3,t4,t5,t6,t7,t8,type,...) type
#define TYPE_10(t1,t2,t3,t4,t5,t6,t7,t8,t9,type,...) type
/*
#define TYPE_8(t1,v1,t2,v2,t3,v3,type,...) type
#define TYPE_10(t1,v1,t2,v2,t3,v3,t4,v4,type,...) type
#define TYPE_12(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,type,...) type
#define TYPE_14(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,t6,v6,type,...) type
#define TYPE_16(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,t6,v6,t7,v7,type,...) type
#define TYPE_18(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,t6,v6,t7,v7,t8,v8,type,...) type
#define TYPE_20(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,t6,v6,t7,v7,t8,v8,t9,v9,type,...) type*/


#define TYPE__N_CONNECTOR(n) TYPE_##n
#define TYPE_N(n,...) TYPE__N_CONNECTOR(n)(__VA_ARGS__)


/*
#define VALUE_0(...)
#define VALUE_2(t,value,...) value
#define VALUE_4(t1,v1,t,value,...) value
#define VALUE_6(t1,v1,t2,v2,t,value,...) value
#define VALUE_8(t1,v1,t2,v2,t3,v3,t,value,...) value
#define VALUE_10(t1,v1,t2,v2,t3,v3,t4,v4,t,value,...) value
#define VALUE_12(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,t,value,...) value
#define VALUE_14(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,t6,v6,t,value,...) value
#define VALUE_16(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,t6,v6,t7,v7,t,value,...) value
#define VALUE_18(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,t6,v6,t7,v7,t8,v8,t,value,...) value
#define VALUE_20(t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,t6,v6,t7,v7,t8,v8,t9,v9,t,value,...) value
#define VALUE_N_CONNECTOR(n) VALUE_##n
#define VALUE_N(n,...) VALUE_N_CONNECTOR(n)(__VA_ARGS__)*/
#define VALUE_N(n,...) param##n

//#define DUMMY_VAR_NAME(type,n) type n
//#define PARAM_PAIR_N(n,...) TYPE_N(n,__VA_ARGS__) VALUE_N(n,__VA_ARGS__)
#define PARAM_PAIR_N(n,...) TYPE_N(n,__VA_ARGS__) param##n
 #define PARAM_PAIR_0(...)
 #define PARAM_PAIR_1(...), PARAM_PAIR_N(1,__VA_ARGS__)
 #define PARAM_PAIR_2(...)  PARAM_PAIR_1(__VA_ARGS__), PARAM_PAIR_N(2,__VA_ARGS__)
 #define PARAM_PAIR_3(...)  PARAM_PAIR_2(__VA_ARGS__), PARAM_PAIR_N(3,__VA_ARGS__)
 #define PARAM_PAIR_4(...)  PARAM_PAIR_3(__VA_ARGS__), PARAM_PAIR_N(4,__VA_ARGS__)
 #define PARAM_PAIR_5(...)  PARAM_PAIR_4(__VA_ARGS__), PARAM_PAIR_N(5,__VA_ARGS__)
 #define PARAM_PAIR_6(...)  PARAM_PAIR_5(__VA_ARGS__), PARAM_PAIR_N(6,__VA_ARGS__)
 #define PARAM_PAIR_7(...)  PARAM_PAIR_6(__VA_ARGS__), PARAM_PAIR_N(7,__VA_ARGS__)
 #define PARAM_PAIR_8(...)  PARAM_PAIR_7(__VA_ARGS__), PARAM_PAIR_N(8,__VA_ARGS__)
 #define PARAM_PAIR_9(...)  PARAM_PAIR_8(__VA_ARGS__), PARAM_PAIR_N(9,__VA_ARGS__)
#define PARAM_PAIR_10(...)  PARAM_PAIR_9(__VA_ARGS__), PARAM_PAIR_N(10,__VA_ARGS__)

#define PARAM_PAIR_CONNECTOR(n) PARAM_PAIR_##n
#define PARAM_LIST(n,...) PARAM_PAIR_CONNECTOR(n)(__VA_ARGS__)


#define VALUE_LIST_0(...)
 #define VALUE_LIST_1(...), VALUE_N(1,__VA_ARGS__)
 #define VALUE_LIST_2(...)  VALUE_LIST_1(__VA_ARGS__), VALUE_N(2,__VA_ARGS__)
 #define VALUE_LIST_3(...)  VALUE_LIST_2(__VA_ARGS__), VALUE_N(3,__VA_ARGS__)
 #define VALUE_LIST_4(...)  VALUE_LIST_3(__VA_ARGS__), VALUE_N(4,__VA_ARGS__)
 #define VALUE_LIST_5(...)  VALUE_LIST_4(__VA_ARGS__), VALUE_N(5,__VA_ARGS__)
 #define VALUE_LIST_6(...)  VALUE_LIST_5(__VA_ARGS__), VALUE_N(6,__VA_ARGS__)
 #define VALUE_LIST_7(...)  VALUE_LIST_6(__VA_ARGS__), VALUE_N(7,__VA_ARGS__)
 #define VALUE_LIST_8(...)  VALUE_LIST_7(__VA_ARGS__), VALUE_N(8,__VA_ARGS__)
 #define VALUE_LIST_9(...)  VALUE_LIST_8(__VA_ARGS__), VALUE_N(9,__VA_ARGS__)
#define VALUE_LIST_10(...)  VALUE_LIST_9(__VA_ARGS__), VALUE_N(10,__VA_ARGS__)


#define VALUE_LIST_CONNECTOR(n) VALUE_LIST_##n
#define VALUE_LIST(n,...) VALUE_LIST_CONNECTOR(n)(__VA_ARGS__)
template<class T>
class SignalEmitter
{
    public:

        SignalEmitter();
        void insert(T* signal);
        void erase(T* signal);
        size_t size() const;
        void clear();
    protected:
        void emitStart();
        void emitEnd();
        void updateList();
        bool m_emiterCallActive;
        HashTable<T*> m_toRemove;
        HashTable<T*> m_toInsert;
        HashTable<T*> m_inList;
};

template<class T>
SignalEmitter<T>::SignalEmitter()
{
    m_emiterCallActive = false;
}

template<class T>
void SignalEmitter<T>::insert(T* signal)
{
    if(!signal)
        return;
    if(m_emiterCallActive)
        m_toInsert.insert({signal,signal});
    else
        m_inList.insert({signal,signal});
}
template<class T>
void SignalEmitter<T>::erase(T* signal)
{
    if(m_emiterCallActive)
        m_toRemove.insert({signal,signal});
    else
        m_inList.erase(signal);
}
template<class T>
size_t SignalEmitter<T>::size() const
{
    return m_inList.size();
}
template<class T>
void SignalEmitter<T>::clear()
{
    m_inList.clear();
}
template<class T>
void SignalEmitter<T>::emitStart()
{
    m_emiterCallActive = true;
}
template<class T>
void SignalEmitter<T>::emitEnd()
{
    m_emiterCallActive = false;
    updateList();
}
template<class T>
void SignalEmitter<T>::updateList()
{
    for(auto pair : m_toRemove)
        m_inList.erase(pair.second);
    m_toRemove.clear();
    for(auto pair : m_toInsert)
        m_inList.insert(pair);
    m_toInsert.clear();
}
#endif // SIGNAL_H
