#ifndef FOOD_H
#define FOOD_H

#include <string>
#include <vector>

using std::string;

namespace Property
{
    struct Food
    {
        enum Taste
        {
            sweet,
            sour,
            salty,
            spicy,

        };
        bool isEatable;
        double foodAmount;
        std::vector<Taste> taste;   // List of tastes this food has
        double healthyLevel;        // how halthy this food is

    };
    inline string taste_toString(const Food::Taste &taste)
    {
        switch(taste)
        {
            case Food::Taste::sweet:
                return "sweet";
            case Food::Taste::sour:
                return "sour";
            case Food::Taste::salty:
                return "salty";
            case Food::Taste::spicy:
                return "spicy";
            default:
                return "notDefined";
        }
    }
}

#endif // FOOD_H
