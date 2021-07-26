#ifndef INTERACTIVEGAMEOBJECTGROUP_H
#define INTERACTIVEGAMEOBJECTGROUP_H

#include "InteractiveGameObject.h"

#define CHECK_FOR_DOUBLE_OBJ

class InteractiveGameObjectGroup
{
    public:
        InteractiveGameObjectGroup();
        InteractiveGameObjectGroup(const InteractiveGameObject::Settings &settings);
        InteractiveGameObjectGroup(const InteractiveGameObjectGroup &other);
        virtual ~InteractiveGameObjectGroup();

        InteractiveGameObject* operator[](size_t index);
        const InteractiveGameObjectGroup &operator=(const InteractiveGameObjectGroup &other);

        virtual void reserve(size_t size);
        virtual bool add(InteractiveGameObject *obj);
        virtual bool add(GameObject *obj);        // returns true if added
        virtual void addToCache(GameObject *obj); //will not generate a new InteractiveGameObject.
        virtual void buildCache();                //Will generate the InteractiveGameObject with threads

        virtual void remove(InteractiveGameObject *obj);
        virtual void remove(GameObject *obj);
        virtual void deleteObj(InteractiveGameObject *obj);
        virtual void deleteObj(GameObject *obj);

        virtual void clear();

        virtual InteractiveGameObject *getInteractiveObject(const GameObject *obj) const;
        virtual InteractiveGameObject *getInteractiveObject(unsigned int index) const;
        virtual const vector<InteractiveGameObject*> &getInteractiveObjectList() const;

        virtual const vector<GameObjectGroup*> &getInteractiveObjectsList(const GameObject *obj,Interaction type) const;
        virtual const vector<GameObjectGroup*> &getInteractiveObjectsList(size_t index,Interaction type) const;
        virtual const vector<GameObject*> getInteractiveObjects(const GameObject *obj,Interaction type) const;
        virtual const vector<GameObject*> getInteractiveObjects(size_t index,Interaction type) const;

        virtual void removeAllInteractionsWithObj(GameObject *obj);
        virtual void removeAllInteractionsWithObj(InteractiveGameObject *obj);


        virtual size_t size() const;


        static void generateInteractiveObjects(vector<InteractiveGameObject*>   &list,
                                               vector<GameObject*> &objList);


    protected:

        HashTable<GameObject*> m_cacheObjectsList;
        HashTable<GameObject*> m_objectsList;
        vector<GameObject*>            m_cacheObjectsList_vector;
        vector<InteractiveGameObject*> m_cacheInteractiveObjectsList;
        vector<InteractiveGameObject*> m_interactiveObjectsList;
        vector<GameObjectGroup*>       m_const_dummy_list;
        vector<GameObject*>            m_const_dummy_list_2;
        InteractiveGameObject::Settings m_settings;

    private:
        struct InteractiveGameObject_ThreadParam
        {
            vector<InteractiveGameObject*>   *list;
            vector<GameObject*>              *objList;
            size_t begin;
            size_t end;
        };
        static vector<InteractiveGameObject_ThreadParam*> m_threadParamList;
        static vector<pthread_t*> m_threadList;
        static void *thread_generateInteractiveObject(void *p);
};

#endif // INTERACTIVEGAMEOBJECTGROUP_H
