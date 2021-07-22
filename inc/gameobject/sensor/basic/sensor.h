#ifndef SENSOR_H
#define SENSOR_H

#include "base.h"

#include "gameobject.h"
#include "submodule.h"

class Sensor    :   public Submodule
{
    public:
        Sensor();
        Sensor(const Sensor &other);

        virtual ~Sensor();
        virtual const Sensor &operator=(const Sensor &other);

        virtual void setOwner(GameObject *owner);

        virtual void engineCalled_preTick();
        virtual void engineCalled_tick(const Vector2i &direction);
        virtual void engineCalled_postTick();
        virtual void engineCalled_preDraw();

        virtual void detectObjects(const vector<GameObject*> &other) = 0;
        virtual const vector<GameObject*> &getDetectedObjects() const;

        void setEnableRelativeRotation(bool enable);
        void setEnableRelativePosition(bool enable);
        bool getEnableRelativeRotation() const;
        bool getEnableRelativePosition() const;

    protected:
        vector<GameObject*> m_detected;
        GameObject *m_owner;

        bool        m_enableRelativeRotation;
        bool        m_enableRelativePosition;
    private:
};

#endif
