#ifndef MANAGEDGAMEOBJECTGROUP_H
#define MANAGEDGAMEOBJECTGROUP_H

#include "gameObjectGroup.h"
#include "groupManagerInterface.h"

using std::vector;

class ManagedGameObjectGroup    :   public GameObjectGroup,  GroupManagerInterface
{
    public:
        ManagedGameObjectGroup();
        ManagedGameObjectGroup(const ManagedGameObjectGroup &other);

        virtual GameObject *operator[](const size_t &index) const;
    //protected:
        virtual bool newObjectsAvailable();
        virtual bool deletableObjectsAvailable();

        virtual const vector<GameObject *> &getNewObjects();
        virtual const vector<GameObject *> &getDeletableObjects();

        virtual void newObjectsAddedToEngine();
        virtual void deletableObjectsRemovedFromEngine();

        virtual void removeObject_unmanaged(GameObject *obj);

        virtual void add(GameObject *object);
        virtual void add(GameObjectGroup *other);
        //virtual void remove(GameObject *toRemove);
        //virtual void remove(GameObjectGroup *other);
        virtual void remove(const size_t index);

        virtual const vector<GameObject*> &getVector() const;

       /* virtual ManagedGameObjectGroup &operator=(const ManagedGameObjectGroup &other);

        virtual ~ManagedGameObjectGroup();

        virtual void draw(PixelDisplay &display);

        virtual void add(GameObject *object);
        virtual void add(ManagedGameObjectGroup *other);
        virtual void remove(GameObject *toRemove);
        virtual void remove(ManagedGameObjectGroup *other);
        virtual void remove(const size_t index);
        virtual void clear();
        virtual size_t size() const;
        virtual GameObject *operator[](const size_t &index) const;
        virtual const vector<GameObject*> &getVector() const;

        // GameObject stuff
       // virtual void setPosInitial(const Point &pos);
       // virtual void setPosInitial(const int &x, const int &y);

        virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Point &pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual void moveToPos(const Point &destination);
        virtual void moveToPos(const int &x,const int &y);
        virtual void move(const Point &directionVector);
        virtual void move(int x,int y);

        virtual void setRotation(const double &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const PointF &rotationPoint,const double &deg);
        virtual void rotate_90(const PointF &rotationPoint);
        virtual void rotate_180(const PointF &rotationPoint);
        virtual void rotate_270(const PointF &rotationPoint);

        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;
        virtual void setHitboxVisibility(const bool &isVisible);
        virtual const bool &isHitboxVisible() const;*/


        /*virtual bool __engineUseOnly_newObjAvailable() const;
        virtual bool __engineUseOnly_deletableObjAvailable() const;
        virtual const vector<GameObject *> &__engineUseOnly_getAddList() const;
        virtual const vector<GameObject *> &__engineUseOnly_getRemoveList() const;
        virtual void __engineUseOnly_objsAddedToEngine();
        virtual void __engineUseOnly_objsRemovedFromEngine();*/

        /*static void removeDuplicates(vector<GameObject *> *list);
        static void removeDuplicates(ManagedGameObjectGroup *list);*/
    protected:
        bool m_isVisible;
        bool m_hitboxIsVisible;

        vector<GameObject *> m_toBeAdded; // To be added to the engine
        vector<GameObject *> m_toBeRemoved; // To be removed from the engine
        //vector<GameObject *> m_isInList;
    private:


};
#endif // ManagedGameObjectGroup_H
