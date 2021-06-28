#ifndef DYNAMICCOORDINATOR_H
#define DYNAMICCOORDINATOR_H

#include "SFML/System/Vector2.hpp"
#include "mathFunctions.h"
//#include "vector"

#include "qdebug.h"
#include "profiler.h"

using std::vector;
using sf::Vector2f;
using sf::Vector2i;

class DynamicCoordinator
{
    public:
        DynamicCoordinator();
        DynamicCoordinator(const DynamicCoordinator &other);
        virtual ~DynamicCoordinator();
        const DynamicCoordinator &operator=(const DynamicCoordinator &other);

        virtual void tick();

        virtual void addMovement(const Vector2f &vec);
        //virtual void addMovement(const Vector2i&vec);

        virtual void calculateMovement();

        virtual const unsigned int &getNeededSteps() const;
        virtual const Vector2f      &getMovingVector() const;
        virtual const float       &getMovingVector_X() const;
        virtual const float       &getMovingVector_Y() const;

        //virtual Vector2i       getRoundedVector() const;
        //virtual int           getRoundedVector_X() const;
        //virtual int           getRoundedVector_Y() const;

        virtual void clearMovement();

    protected:
        vector<Vector2f> m_vecList;
        Vector2f m_movingVector;
        unsigned int m_neededSteps;

        unsigned int m_xStepInterval;
        unsigned int m_xStepCounter;
        unsigned int m_yStepInterval;
        unsigned int m_yStepCounter;
    private:
};
#endif // DYNAMICCOORDINATOR_H
