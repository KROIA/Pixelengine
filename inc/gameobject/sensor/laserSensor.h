#ifndef LASERSENSOR_H
#define LASERSENSOR_H

#include "sensor.h"
#include "vertexPathPainter.h"

class Laser
{
    public:
        Laser();
        Laser(const Vector2f &begin, float length, float angle);

        void set(const Vector2f &begin, float length, float angle);
        void setReference(Vector2f pos, float angle);

        const Vector2f &getBegin() const;
        const Vector2f &getDirection() const;
        const Vector2f &getEnd() const;
        float getLength() const;
        float getAngle() const;

        const Vector2f &getGlobalBegin() const;
        const Vector2f &getGlobalDirection() const;
        const Vector2f &getGlobalEnd() const;
        float getGlobalAngle() const;
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
};



class LaserSensor   :   public Sensor
{
    public:
        LaserSensor();
        ~LaserSensor();

        void setBeam(const Vector2f &begin, float length, float angle);

        void engineCalled_preTick();
        void detectObjects(const vector<GameObject*> &other);

        void engineCalled_preDraw();

        void setBeamRotation(float deg);
        void rotateBeam(float deg);

        void setDetectedColor(const Color &color);
        void setSensorColor(const Color &color);


    protected:
        VertexPathPainter *m_sensorPainter;

        Color m_detectedColor;
        Color m_sensorColor;


        Laser m_laser;
    private:

};
#endif // LASERSENSOR_H
