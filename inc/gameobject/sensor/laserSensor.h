#ifndef LASERSENSOR_H
#define LASERSENSOR_H

#include "sensor.h"
#include "vertexPathPainter.h"

// Signals for Laser
/*class LaserSignal
{
    public:
        LaserSignal(){}

        virtual void changed(Laser *sender) = 0;
};
// Vector of Signals
class LaserSubscriberList: public SubscriberList<LaserSignal>
{
    public:
        LaserSubscriberList();

        virtual void changed(Laser *sender);
};*/
SIGNAL_DEF(Laser)
    SIGNAL_FUNC(changed)
SIGNAL_DEF_END

SIGNAL_EMITTER_DEF(Laser)
    SIGNAL_EMITTER_FUNC(changed)
SIGNAL_EMITTER_DEF_END

class Laser
{
    SIGNAL_EMITTER(Laser)
    public:
        Laser();
        Laser(const Vector2f &begin, float length, float angle);

        void set(const Vector2f &begin, float length, float angle);
        void setReference(Vector2f pos, float angle);

        void setBegin(const Vector2f &begin);
        void setLength(float length);
        void setRotation(float angle);
        void rotate(float angle);

        const Vector2f &getBegin() const;
        const Vector2f &getDirection() const;
        const Vector2f &getEnd() const;
        float getLength() const;
        float getRotation() const;

        const Vector2f &getGlobalBegin() const;
        const Vector2f &getGlobalDirection() const;
        const Vector2f &getGlobalEnd() const;
        float getGlobalAngle() const;

        /*void subscribe_laserSignal(LaserSignal *subscriber);
        void unsubscribe_laserSignal(LaserSignal *subscriber);
        void unsubscribeAll_laserSignal();*/

    private:
        void calculateLocal();
        void calculateGlobal();
        Vector2f m_localBegin;
        Vector2f m_localEnd;
        float    m_localRotation;
        float    m_length;
        Vector2f m_localDirectionVec;

        Vector2f m_origin;
        float    m_rotation;

        Vector2f m_globalBegin;
        Vector2f m_globalEnd;
        float    m_globalRotation;
        Vector2f m_globalDirectionVec;

        //LaserSubscriberList m_laserSubscriberList;
};



class LaserSensor   :   public Sensor,   SIGNAL_RECEIVES(Laser)
{
    public:
        LaserSensor();
        ~LaserSensor();

        bool addLaser(const Vector2f &begin, float length, float angle);
        bool addLaser(Laser *laser);
        bool removeLaser(Laser *laser);
        void clearLaser();

        void engineCalled_preTick();
        void detectObjects(const vector<GameObject*> &other);

        void engineCalled_preDraw();

        bool setBegin(size_t laserIndex, const Vector2f &begin);
        bool setLength(size_t laserIndex, float length);
        bool setLaserRotation(size_t laserIndex, float angle);
        bool rotateLaser(size_t laserIndex, float angle);

        void setDetectedColor(const Color &color);
        void setSensorColor(const Color &color);


    protected:

        // Signals from Laser
        //void changed(Laser *sender);
        SLOT_DECLARATION(Laser,changed)


        VertexPathPainter *m_sensorPainter;

        Color m_detectedColor;
        Color m_sensorColor;


        vector<Laser*>  m_laserList;
        vector<Laser*>  m_privateLaserPTR;
        bool            m_recalculateColliderSearchFrame;
    private:

};
#endif // LASERSENSOR_H
