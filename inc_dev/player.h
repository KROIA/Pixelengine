#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"
#include "keyController.h"
#include "sensor.h"
#include <QDebug>
#include "timer.h"

class Player    :   public GameObject
{
    public:
        Player();
        Player(const Player &other);

        virtual ~Player();

        virtual void tick(const Vector2i &direction);
        virtual unsigned int checkCollision(const vector<GameObject*> &other);
        virtual void draw(PixelDisplay &display);

        virtual void setColor(const Color &color);
        virtual void setStartPos(const Vector2f &point);
        virtual void setKeyBinding(const int &UP_KEY,
                                   const int &LEFT_KEY,
                                   const int &DOWN_KEY,
                                   const int &RIGHT_KEY);

        virtual void setStepSize(const int size);
        virtual const int &getStepSize() const;

        virtual void buildPlayer(); // Generates The PlayerObject

        virtual void setRotation(const float &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const Vector2f &rotationPoint,const float &deg);
        virtual void rotate_90(const Vector2f &rotationPoint);
        virtual void rotate_180(const Vector2f &rotationPoint);
        virtual void rotate_270(const Vector2f &rotationPoint);

        virtual void event_hasCollision(vector<GameObject*> other);


    protected:
        virtual void setupPLayerBody(PixelPainter *p,Collider *c);

        Color m_playerColor;
        Vector2f m_initalPos;

        int m_keyUP;
        int m_keyLEFT;
        int m_keyDOWN;
        int m_keyRIGHT;

    private:
        bool m_onceBuild;
        Collider *m_collider;
        Collider *sensorCollider;
        PixelPainter  *m_painter;
        KeyController *m_controller;

        Sensor m_sensor;
        Timer m_sensorDebugTimer;
};
#endif
