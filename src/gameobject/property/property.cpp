#include "property.h"

namespace Property {
Property::Property()
{
    m_type.description      = Description::staticObstacle;

    m_body.fat              = 0;
    m_body.health           = 0;
    m_body.density          = 0;
    m_body.stamina          = 0;
    m_body.strength         = 0;
    m_body.nutritionalValue = 0;
    m_body.material         = Material::Dirt;

    m_food.isEatable        = false;
    m_food.foodAmount       = 0;
    m_food.healthyLevel     = 0;

    m_mood.angrylevel       = 0;
    m_mood.stresslevel      = 0;
    m_mood.inLove           = 0;
    m_mood.druglevel        = 0;
}
Property::Property(const Property &other)
{
    *this = other;
}
Property::~Property()
{

}
const Property &Property::operator=(const Property &other)
{
    this->m_type = other.m_type;
    this->m_body = other.m_body;
    this->m_food = other.m_food;
    this->m_mood = other.m_mood;
    return *this;
}
string Property::toString(const string &newLine) const
{
    string str = "Property:"+newLine;
    str+=getType_toString(newLine);
    str+=getBody_toString(newLine);
    str+=getFood_toString(newLine);
    str+=getMood_toString(newLine);
    return str;
}
// Type
void Property::setType(const Type &type)
{
    m_type = type;
}
void Property::setType_description(const Description &description)
{
    m_type.description = description;
}
const Type Property::getType() const
{
    return m_type;
}
string Property::getType_toString(const string &newLine) const
{
    string str = "Type:"+newLine;
    str += "   Description  :  "+description_toString(m_type.description)+newLine;

    return str;
}

// Body
void Property::setBody(const Body &body)
{
    m_body = body;
}
void Property::setBody_fat(const float &fat)
{
    m_body.fat = fat;
}
void Property::setBody_nutritionalValue(const float &value)
{
    m_body.nutritionalValue = value;
}
void Property::setBody_stamina(const float &stamina)
{
    m_body.stamina = stamina;
}
void Property::setBody_health(const float &health)
{
    m_body.health = health;
}
void Property::setBody_strength(const float &strength)
{
    m_body.strength = strength;
}
void Property::setBody_weight(const float &weight)
{
    m_body.weight = weight;
}
void Property::setBody_density(const float &density)
{
    m_body.density = density;
}
void Property::setBody_material(const Material &material)
{
    m_body.material = material;
}
const Body &Property::getBody() const
{
    return m_body;
}
string Property::getBody_toString(const string &newLine) const
{
    string str = "Body:"+newLine;
    str += "   Fat               : "+to_string(m_body.fat)+newLine;
    str += "   NutritionalValue  : "+to_string(m_body.nutritionalValue)+newLine;
    str += "   Stamina           : "+to_string(m_body.stamina)+newLine;
    str += "   Health            : "+to_string(m_body.health)+newLine;
    str += "   Strength          : "+to_string(m_body.strength)+newLine;
    str += "   Weight            : "+to_string(m_body.weight)+newLine;
    str += "   Density           : "+to_string(m_body.density)+newLine;
    str += "   Material          : "+material_toString(m_body.material)+newLine;

    return str;
}

// Food
void Property::setFood(const Food &food)
{
    m_food = food;
}
void Property::setFood_isEatable(const bool &isEatable)
{
    m_food.isEatable = isEatable;
}
void Property::setFood_foodAmout(const float &amount)
{
    m_food.foodAmount = amount;
}
void Property::setFood_taste(const std::vector<Food::Taste> &list)
{
    m_food.taste = list;
}
void Property::addFood_taste(const Food::Taste &taste)
{
    for(size_t i=0; i<m_food.taste.size(); i++)
        if(m_food.taste[i] == taste)
            return;
    m_food.taste.push_back(taste);
}
void Property::removeFood_taste(const Food::Taste &taste)
{
    for(size_t i=0; i<m_food.taste.size(); i++)
        if(m_food.taste[i] == taste)
        {
            m_food.taste.erase(m_food.taste.begin()+i);
            if(i>0)
                i--;
        }
}
void Property::setFood_healthyLevel(const float &level)
{
    m_food.healthyLevel = level;
}
const Food &Property::getFood() const
{
    return m_food;
}
string Property::getFood_toString(const string &newLine) const
{
    string str = "Food"+newLine;
    str += "   IsEatable     : "+string(m_food.isEatable?"true":"false")+newLine;
    str += "   FoodAmount    : "+to_string(m_food.foodAmount)+newLine;
    str += "   Taste:"+newLine;
    for(size_t i=0; i<m_food.taste.size(); i++)
        str += "      "+taste_toString(m_food.taste[i])+newLine;
    str += "   HealthyLevel  : "+to_string(m_food.healthyLevel)+newLine;
    return str;
}

// Mood
void Property::setMood(const Mood &mood)
{
    m_mood = mood;
}
void Property::setMood_stresslevel(const float &level)
{
    m_mood.stresslevel = level;
}
void Property::setMood_angrylevel(const float &level)
{
    m_mood.angrylevel = level;
}
void Property::setMood_inLove(const float &inLove)
{
    m_mood.inLove = inLove;
}
void Property::setMood_druglevel(const float &druglevel)
{
    m_mood.druglevel = druglevel;
}
const Mood &Property::getMood() const
{
    return m_mood;
}
string Property::getMood_toString(const string &newLine) const
{
    string str = "Mood:"+newLine;
    str += "   Stresslevel  : "+to_string(m_mood.stresslevel)+newLine;
    str += "   Angrylevel   : "+to_string(m_mood.angrylevel)+newLine;
    str += "   InLove       : "+to_string(m_mood.inLove)+newLine;
    str += "   Druglevel    : "+to_string(m_mood.druglevel)+newLine;

    return str;
}
}
