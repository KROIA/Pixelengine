#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

#include <string>

using std::string;

namespace Property {
    enum Description
    {
        staticObstacle,
        dynamicObstacle,
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
            case Description::staticObstacle:
                return "staticObject";
            case Description::dynamicObstacle:
                return "dynamicObstacle";
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
