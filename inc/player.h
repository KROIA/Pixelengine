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


        virtual void setColor(const Color &color);
        virtual void setStartPos(const Point &point);
        virtual void setKeyBinding(const int &UP_KEY,
                                   const int &LEFT_KEY,
                                   const int &DOWN_KEY,
                                   const int &RIGHT_KEY);

        virtual void buildPlayer(); // Generates The PlayerObject
        virtual Collider *getCollider(){return collider;};
        virtual Painter *getPainter(){return painter;}


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
        Collider *collider;
        Painter *painter;
};
#endif
