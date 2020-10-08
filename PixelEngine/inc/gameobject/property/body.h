#ifndef BODY_H
#define BODY_H

namespace Property
{
    enum Material
    {
        Water,
        Air,
        Dirt,
        Grass,
        Wood,
        Stone,
        Metal,
        Flesh
    };

    struct Body
    {
        double fat;
        double nutritionalValue;

        double stamina;
        double health;
        double strength;


        double weight;
        double density;
        Material material;
    };
}

#endif // BODY_H
