#ifndef PROPERTY_H
#define PROPERTY_H


class Property
{
    public:
        enum Type
        {
            staticObsticle=0,
            dynamicObsticle=1,
            player=2,
            bot=3,
            AI=4
        };



        Property();
        Property(const Property &other);
        virtual ~Property();
        virtual const Property &operator=(const Property &other);

    protected:

    private:

};
#endif // PROPERTY_H
