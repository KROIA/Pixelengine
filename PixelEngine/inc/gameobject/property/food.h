#ifndef FOOD_H
#define FOOD_H

#include <vector>


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
}

#endif // FOOD_H
