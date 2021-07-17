#include "InteractiveGameObjectGroup.h"

InteractiveGameObjectGroup::InteractiveGameObjectGroup()
{
    m_settings  = InteractiveGameObject::__defaultSettings;
}
InteractiveGameObjectGroup::InteractiveGameObjectGroup(const InteractiveGameObject::Settings &settings)
{
    m_settings  = settings;
}
InteractiveGameObjectGroup::InteractiveGameObjectGroup(const InteractiveGameObjectGroup &other)
{
    this->operator=(other);
}
InteractiveGameObjectGroup::~InteractiveGameObjectGroup()
{
    for(InteractiveGameObject* &o : m_interactiveObjectsList)
        delete o;
    m_interactiveObjectsList.clear();
}

InteractiveGameObject* InteractiveGameObjectGroup::operator[](size_t index)
{
    if(m_interactiveObjectsList.size() <= index)
        return nullptr;
    return m_interactiveObjectsList[index];
}
const InteractiveGameObjectGroup &InteractiveGameObjectGroup::operator=(const InteractiveGameObjectGroup &other)
{
    m_settings                      = other.m_settings;
    m_cacheObjectsList              = other.m_cacheObjectsList;
    m_cacheInteractiveObjectsList   = other.m_cacheInteractiveObjectsList;
    m_interactiveObjectsList        = other.m_interactiveObjectsList;
    return *this;
}
void InteractiveGameObjectGroup::reserve(size_t size)
{
    m_interactiveObjectsList.reserve(m_interactiveObjectsList.size()+size);
    m_cacheObjectsList.reserve(m_cacheObjectsList.size()+size);
    m_cacheInteractiveObjectsList.reserve(m_cacheInteractiveObjectsList.size()+size);
}
void InteractiveGameObjectGroup::add(InteractiveGameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple50);
    m_interactiveObjectsList.push_back(obj);
}
void InteractiveGameObjectGroup::add(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple50);
    if(obj == nullptr)
        return;
    if(m_objectsList[obj] != nullptr) // GameObject is already added to the Group
        return;

    InteractiveGameObject *j = new InteractiveGameObject();
    j->setGameObject(obj);
    m_objectsList.insert({obj,obj});
    this->add(j);
}
void InteractiveGameObjectGroup::addToCache(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple50);
    if(obj == nullptr)
        return;
   /* GameObject *alreadyInListChecker = m_cacheObjectsList[obj];
    if(alreadyInListChecker != nullptr) // GameObject is already added to the Group
        return;*/
    m_cacheObjectsList.insert({obj,obj});
    m_objectsList.insert({obj,obj});
    /*.push_back(nullptr);
    if(m_cacheInteractiveObjectsList.size() == 9682 ||
       m_cacheInteractiveObjectsList.size() == 5932 ||
            m_cacheInteractiveObjectsList.size() == 6250)
    {
        qDebug() << "";
    }*/
}
void InteractiveGameObjectGroup::buildCache()
{
    EASY_FUNCTION(profiler::colors::Purple100);
    m_cacheObjectsList_vector.clear();
    for(auto element    :   m_cacheObjectsList)
    {
        m_cacheObjectsList_vector.push_back(element.second);
        m_cacheInteractiveObjectsList.push_back(nullptr);
    }

    m_interactiveObjectsList.reserve(m_interactiveObjectsList.size()+m_cacheInteractiveObjectsList.size());
    generateInteractiveObjects(m_cacheInteractiveObjectsList,m_cacheObjectsList_vector);

    for(size_t i=0; i<m_cacheInteractiveObjectsList.size(); i++)
        m_interactiveObjectsList.push_back(m_cacheInteractiveObjectsList[i]);

    m_cacheInteractiveObjectsList.clear();
    m_cacheObjectsList.clear();
}

void InteractiveGameObjectGroup::remove(InteractiveGameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple100);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i] == obj)
        {
            m_interactiveObjectsList.erase(m_interactiveObjectsList.begin()+i);
            i--;
        }
    }
}
void InteractiveGameObjectGroup::remove(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple100);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->getGameObject() == obj)
        {
            m_interactiveObjectsList.erase(m_interactiveObjectsList.begin()+i);
            i--;
        }
    }
}
void InteractiveGameObjectGroup::deleteObj(InteractiveGameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i] == obj)
        {
            delete m_interactiveObjectsList[i];
            m_interactiveObjectsList.erase(m_interactiveObjectsList.begin()+i);
            i--;
        }
    }
}
void InteractiveGameObjectGroup::deleteObj(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple200);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->getGameObject() == obj)
        {
            delete m_interactiveObjectsList[i];
            m_interactiveObjectsList.erase(m_interactiveObjectsList.begin()+i);
            i--;
        }
    }
}
void InteractiveGameObjectGroup::clear()
{
    EASY_FUNCTION(profiler::colors::Purple300);
    m_interactiveObjectsList.clear();
}

InteractiveGameObject *InteractiveGameObjectGroup::getInteractiveObject(const GameObject *obj) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->getGameObject() == obj)
            return m_interactiveObjectsList[i];
    }
    return nullptr;
}

InteractiveGameObject *InteractiveGameObjectGroup::getInteractiveObject(unsigned int index) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
    if(m_interactiveObjectsList.size() >= index)
        return nullptr;
    return m_interactiveObjectsList[index];
}

const vector<InteractiveGameObject*> &InteractiveGameObjectGroup::getInteractiveObjectList() const
{
    return m_interactiveObjectsList;
}


const vector<GameObjectGroup*> &InteractiveGameObjectGroup::getInteractiveObjectsList(const GameObject *obj) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->getGameObject() == obj)
            return getInteractiveObjectsList(1);
    }
    return m_const_dummy_list;
}
const vector<GameObjectGroup*> &InteractiveGameObjectGroup::getInteractiveObjectsList(size_t index) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
     return m_interactiveObjectsList[index]->getInteractiveObjectsList();
}

const vector<GameObject*> InteractiveGameObjectGroup::getInteractiveObjects(const GameObject *obj) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->getGameObject() == obj)
            return getInteractiveObjects(i);
    }
    return m_const_dummy_list_2;
}
const vector<GameObject*> InteractiveGameObjectGroup::getInteractiveObjects(size_t index) const
{
    EASY_FUNCTION(profiler::colors::Purple400);
    if(index<=m_interactiveObjectsList.size())
        return m_const_dummy_list_2;
    return m_interactiveObjectsList[index]->getInteractiveObjects();
}

void InteractiveGameObjectGroup::removeAllInteractionsWithObj(GameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple500);
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        m_interactiveObjectsList[i]->removeInteractionWith(obj);
    }
}
void InteractiveGameObjectGroup::removeAllInteractionsWithObj(InteractiveGameObject *obj)
{
    EASY_FUNCTION(profiler::colors::Purple500);
    removeAllInteractionsWithObj(obj->getGameObject());
}


size_t InteractiveGameObjectGroup::size() const
{
    return m_interactiveObjectsList.size();
}

/*void InteractiveGameObjectGroup::addInteractionWith(GameObject *obj)
{
    if(obj == nullptr)
        return;
#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i]->indexOf(obj) != -1)
            return;
    }
#endif
    m_interactiveObjectsList[0]->add(obj);

}
void InteractiveGameObjectGroup::addInteractionWith(GameObjectGroup *group)
{
    if(group == nullptr)
        return;
#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i] == group)
            return;
    }
#endif
    m_interactiveObjectsList.push_back(group);
}
void InteractiveGameObjectGroup::addInteractionWith(vector<GameObjectGroup*> *groupList)
{
    for(size_t i=0; i<groupList->size(); i++)
    {
        addInteractionWith((*groupList)[i]);
    }
}

void InteractiveGameObjectGroup::removeInteractionWith(GameObject *obj)
{
    if(obj == nullptr)
        return;

    m_interactiveObjectsList[0]->remove(obj);
#ifdef CHECK_FOR_DOUBLE_OBJ
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        m_interactiveObjectsList[i]->remove(obj);
    }
#endif
}
void InteractiveGameObjectGroup::removeInteractionWith(GameObjectGroup *group)
{
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        if(m_interactiveObjectsList[i] == group)
            m_interactiveObjectsList.erase(m_interactiveObjectsList.begin()+i);
    }
}
void InteractiveGameObjectGroup::removeInteractionWith(vector<GameObjectGroup*> *groupList)
{
    for(size_t i=0; i<groupList->size(); i++)
    {
        removeInteractionWith((*groupList)[i]);
    }
}

const vector<GameObjectGroup*> &InteractiveGameObjectGroup::getInteractiveObjectsList() const
{
    return m_interactiveObjectsList;
}
const GameObjectGroup InteractiveGameObjectGroup::getInteractiveObjects() const
{
    GameObjectGroup list;
    for(size_t i=0; i<m_interactiveObjectsList.size(); i++)
    {
        list.add(m_interactiveObjectsList[i]);
    }
    return list;
}*/

vector<InteractiveGameObjectGroup::InteractiveGameObject_ThreadParam*> InteractiveGameObjectGroup::m_threadParamList;
vector<pthread_t*> InteractiveGameObjectGroup::m_threadList;

void InteractiveGameObjectGroup::generateInteractiveObjects(vector<InteractiveGameObject*>   &list,
                                                            vector<GameObject*> &objList)
{
    //pthread_cond_t cv                   = PTHREAD_COND_INITIALIZER;
    //pthread_mutex_t m_threadGlobalMutex = PTHREAD_MUTEX_INITIALIZER;

    // Create Threads
    if(m_threadList.size() == 0)
    {
        size_t threadAmount = 20;
        if(list.size() < threadAmount)
            threadAmount = 1;
        m_threadList.reserve(threadAmount);
        m_threadParamList.reserve(threadAmount);
        for(size_t i=0; i<threadAmount; i++)
        {
            m_threadParamList.push_back(new InteractiveGameObject_ThreadParam());
            m_threadList.push_back(new pthread_t());
            //pthread_create(m_threadList[i], nullptr, &InteractiveGameObjectGroup::thread_generateInteractiveObject, static_cast<void *>(m_threadParamList[i]));
        }
    }

    // Set parameter
    size_t chunks = list.size()/m_threadList.size();
    size_t rest = list.size()%m_threadList.size();
    for(size_t i=0; i<m_threadList.size(); i++)
    {
        m_threadParamList[i]->list    = &list;
        m_threadParamList[i]->objList = &objList;
        m_threadParamList[i]->begin   = i*chunks;
        m_threadParamList[i]->end     = (i+1)*chunks-1;
        if(i==m_threadList.size()-1)
            m_threadParamList[i]->end+= rest;
        pthread_create(m_threadList[i], nullptr, &InteractiveGameObjectGroup::thread_generateInteractiveObject, static_cast<void *>(m_threadParamList[i]));
    }


    for(size_t i=0; i<m_threadList.size(); i++)
    {
        //thread_generateInteractiveObject(static_cast<void *>(m_threadParamList[i]));
        pthread_join(*m_threadList[i], (void **)&i);
    }

    for(size_t i=0; i<m_threadList.size(); i++)
    {
        delete m_threadParamList[i];
        delete m_threadList[i];
        m_threadParamList.clear();
        m_threadList.clear();

    }
}
void *InteractiveGameObjectGroup::thread_generateInteractiveObject(void *p)
{
    struct InteractiveGameObject_ThreadParam *param = static_cast<struct InteractiveGameObject_ThreadParam *>(p);
    //qDebug() << "Thread: "<<param->begin<< " - "<<param->end;

    for(size_t i=param->begin; i<=param->end; i++)
    {
        if((*param->list)[i] == nullptr)
        {
            (*param->list)[i] = new InteractiveGameObject();
            (*param->list)[i]->setGameObject((*param->objList)[i]);
        }
    }
    //qDebug() << "Thread: "<<param->begin<< " - "<<param->end << "  finished";
    pthread_exit(NULL);
}
