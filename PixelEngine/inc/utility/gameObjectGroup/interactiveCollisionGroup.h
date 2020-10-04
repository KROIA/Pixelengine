#ifndef INTERACTIVECOLLISIONGROUP_H
#define INTERACTIVECOLLISIONGROUP_H

#include "gameobject.h"
#include "interactiveGroup.h"


class InteractiveCollisionGroup     :   public InteractiveGroup<GameObject*>
{
    public:
        InteractiveCollisionGroup();
        InteractiveCollisionGroup(const InteractiveCollisionGroup &other);

        virtual ~InteractiveCollisionGroup();


    protected:

    private:

};
#endif // INTERACTIVECOLLISIONGROUP_H
