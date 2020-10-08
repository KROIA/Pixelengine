#include "property.h"

namespace Property {
Property::Property()
{
    m_type.description      = Description::staticObsticle;

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

// Body
void Property::setBody(const Body &body)
{
    m_body = body;
}
void Property::setBody_fat(const double &fat)
{
    m_body.fat = fat;
}
void Property::setBody_nutritionalValue(const double &value)
{
    m_body.nutritionalValue = value;
}
void Property::setBody_stamina(const double &stamina)
{
    m_body.stamina = stamina;
}
void Property::setBody_health(const double &health)
{
    m_body.health = health;
}
void Property::setBody_strength(const double &strength)
{
    m_body.strength = strength;
}
void Property::setBody_weight(const double &weight)
{
    m_body.weight = weight;
}
void Property::setBody_density(const double &density)
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

// Food
void Property::setFood(const Food &food)
{
    m_food = food;
}
void Property::setFood_isEatable(const bool &isEatable)
{
    m_food.isEatable = isEatable;
}
void Property::setFood_foodAmout(const double &amount)
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
void Property::setFood_healthyLevel(const double &level)
{
    m_food.healthyLevel = level;
}
const Food &Property::getFood() const
{
    return m_food;
}

// Mood
void Property::setMood(const Mood &mood)
{
    m_mood = mood;
}
void Property::setMood_stresslevel(const double &level)
{
    m_mood.stresslevel = level;
}
void Property::setMood_angrylevel(const double &level)
{
    m_mood.angrylevel = level;
}
void Property::setMood_inLove(const double &inLove)
{
    m_mood.inLove = inLove;
}
void Property::setMood_druglevel(const double &druglevel)
{
    m_mood.druglevel = druglevel;
}
const Mood &Property::getMood() const
{
    return m_mood;
}
}
