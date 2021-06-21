#ifndef DYNAMICCOORDINATOR_H
#define DYNAMICCOORDINATOR_H

#include "vector.h"
#include "vector"

#include "profiler.h"

using std::vector;

class DynamicCoordinator
{
    public:
        DynamicCoordinator();
        DynamicCoordinator(const DynamicCoordinator &other);
        virtual ~DynamicCoordinator();
        const DynamicCoordinator &operator=(const DynamicCoordinator &other);

        virtual void tick();

        virtual void addMovement(const VectorF &vec);
        virtual void addMovement(const Vector &vec);

        virtual void calculateMovement();

        virtual const unsigned int &getNeededSteps() const;
        virtual const VectorF      &getMovingVector() const;
        virtual const double       &getMovingVector_X() const;
        virtual const double       &getMovingVector_Y() const;

        virtual Vector        getRoundedVector() const;
        virtual int           getRoundedVector_X() const;
        virtual int           getRoundedVector_Y() const;

        virtual void clearMovement();

    protected:
        vector<VectorF> m_vecList;
        VectorF m_movingVector;
        unsigned int m_neededSteps;

        unsigned int m_xStepInterval;
        unsigned int m_xStepCounter;
        unsigned int m_yStepInterval;
        unsigned int m_yStepCounter;
    private:
};
#endif // DYNAMICCOORDINATOR_H
