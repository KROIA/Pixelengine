#ifndef PROPERTY_H
#define PROPERTY_H

#include "body.h"
#include "food.h"
#include "objectType.h"
#include "mood.h"
#include <string>

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
        virtual void setBody_fat(const double &fat);
        virtual void setBody_nutritionalValue(const double &value);
        virtual void setBody_stamina(const double &stamina);
        virtual void setBody_health(const double &health);
        virtual void setBody_strength(const double &strength);
        virtual void setBody_weight(const double &weight);
        virtual void setBody_density(const double &density);
        virtual void setBody_material(const Material &material);
        virtual const Body &getBody() const;
        virtual string getBody_toString(const string &newLine = "\n") const;

        // Food
        virtual void setFood(const Food &food);
        virtual void setFood_isEatable(const bool &isEatable);
        virtual void setFood_foodAmout(const double &amount);
        virtual void setFood_taste(const std::vector<Food::Taste> &list);
        virtual void addFood_taste(const Food::Taste &taste);
        virtual void removeFood_taste(const Food::Taste &taste);
        virtual void setFood_healthyLevel(const double &level);
        virtual const Food &getFood() const;
        virtual string getFood_toString(const string &newLine = "\n") const;

        // Mood
        virtual void setMood(const Mood &mood);
        virtual void setMood_stresslevel(const double &level);
        virtual void setMood_angrylevel(const double &level);
        virtual void setMood_inLove(const double &inLove);
        virtual void setMood_druglevel(const double &druglevel);
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
