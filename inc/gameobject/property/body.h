#ifndef BODY_H
#define BODY_H

#include <string>

using std::string;

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
        Sand,
        Metal,
        Flesh
    };

    struct Body
    {
        float fat;
        float nutritionalValue;

        float stamina;
        float health;
        float strength;


        float weight;
        float density;
        Material material;
    };
    inline string material_toString(const Material &mat)
    {
         switch(mat)
         {
             case Material::Water:
                 return "Water";
             case Material::Air:
                 return "Air";
             case Material::Dirt:
                 return "Dirt";
             case Material::Grass:
                 return "Grass";
             case Material::Wood:
                 return "Wood";
             case Material::Stone:
                 return "Stone";
             case Material::Sand:
                 return "Sand";
             case Material::Metal:
                 return "Metal";
             case Material::Flesh:
                 return "Flesh";
             default:
                 return "notDefined";
         }
    }
}

#endif // BODY_H
