#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

#include <string>

using std::string;

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
    inline string description_toString(const Description &des)
    {
        switch(des)
        {
            case Description::staticObsticle:
                return "staticObject";
            case Description::dynamicObsticle:
                return "dynamicObsticle";
            case Description::player:
                return "player";
            case Description::bot:
                return "bot";
            case Description::AI:
                return "AI";
            default:
                return "notDefined";
        }
    }
}

#endif // OBJECTTYPE_H
