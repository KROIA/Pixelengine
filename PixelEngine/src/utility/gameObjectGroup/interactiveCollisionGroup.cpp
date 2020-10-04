#include "interactiveCollisionGroup.h"

InteractiveCollisionGroup::InteractiveCollisionGroup()
    :   InteractiveGroup<GameObject*>()
{

}
InteractiveCollisionGroup::InteractiveCollisionGroup(const InteractiveCollisionGroup &other)
    :   InteractiveGroup<GameObject*>(other)
{

}

InteractiveCollisionGroup::~InteractiveCollisionGroup()
{

}
