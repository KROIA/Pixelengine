#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

namespace Property {
    enum Description
    {
        staticObsticle,
        dynamicObsticle,
        player,
        bot,
        AI
    };
    struct Type
    {
        Description description;

    };
}

#endif // OBJECTTYPE_H
