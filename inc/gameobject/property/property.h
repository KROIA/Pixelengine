#ifndef PROPERTY_H
#define PROPERTY_H

#include "body.h"
#include "food.h"
#include "objectType.h"
#include "mood.h"
#include <string>

#include "profiler.h"

using std::string;
using std::to_string;


namespace Property {


class Property
{
    public:
        Property();
        Property(const Property &other);
        virtual ~Property();
        virtual const Property &operator=(const Property &other);
        virtual string toString(const string &newLine = "\n") const;

        // Type
        virtual void setType(const Type &type);
        virtual void setType_description(const Description &description);
        virtual const Type getType() const;
        virtual string getType_toString(const string &newLine = "\n") const;

        // Body
        virtual void setBody(const Body &body);
        virtual void setBody_fat(const float &fat);
        virtual void setBody_nutritionalValue(const float &value);
        virtual void setBody_stamina(const float &stamina);
        virtual void setBody_health(const float &health);
        virtual void setBody_strength(const float &strength);
        virtual void setBody_weight(const float &weight);
        virtual void setBody_density(const float &density);
        virtual void setBody_material(const Material &material);
        virtual const Body &getBody() const;
        virtual string getBody_toString(const string &newLine = "\n") const;

        // Food
        virtual void setFood(const Food &food);
        virtual void setFood_isEatable(const bool &isEatable);
        virtual void setFood_foodAmout(const float &amount);
        virtual void setFood_taste(const std::vector<Food::Taste> &list);
        virtual void addFood_taste(const Food::Taste &taste);
        virtual void removeFood_taste(const Food::Taste &taste);
        virtual void setFood_healthyLevel(const float &level);
        virtual const Food &getFood() const;
        virtual string getFood_toString(const string &newLine = "\n") const;

        // Mood
        virtual void setMood(const Mood &mood);
        virtual void setMood_stresslevel(const float &level);
        virtual void setMood_angrylevel(const float &level);
        virtual void setMood_inLove(const float &inLove);
        virtual void setMood_druglevel(const float &druglevel);
        virtual const Mood &getMood() const;
        virtual string getMood_toString(const string &newLine = "\n") const;

    protected:
        Type m_type;
        Body m_body;
        Food m_food;
        Mood m_mood;


    private:

};
}
#endif // PROPERTY_H
