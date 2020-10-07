#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"
#include "keyController.h"
#include <QDebug>

class Player    :   public GameObject
{
    public:
        Player();
        Player(const Player &other);

        virtual ~Player();

        virtual void tick(const Point &direction);

        virtual void setColor(const Color &color);
        virtual void setStartPos(const Point &point);
        virtual void setKeyBinding(const int &UP_KEY,
                                   const int &LEFT_KEY,
                                   const int &DOWN_KEY,
                                   const int &RIGHT_KEY);

        virtual void setStepSize(const unsigned int size);
        virtual const unsigned int &getStepSize() const;

        virtual void buildPlayer(); // Generates The PlayerObject



    protected:
        virtual void setupPLayerBody(Painter *p,Collider *c);

        Color m_playerColor;
        Point m_initalPos;

        int m_keyUP;
        int m_keyLEFT;
        int m_keyDOWN;
        int m_keyRIGHT;

    private:
        bool m_onceBuild;
        Collider *m_collider;
        Painter  *m_painter;
        KeyController *m_controller;
};
#endif
