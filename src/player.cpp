#include "player.h"

Player::Player()
    :   GameObject()
{
    m_playerColor.r = 50;
    m_playerColor.g = 50;
    m_playerColor.b = 255;

    m_onceBuild = false;
}
Player::Player(const Player &other)
    :   GameObject(other)
{
    this->m_playerColor = other.m_playerColor;
    this->m_initalPos   = other.m_initalPos;
    this->m_onceBuild   = other.m_onceBuild;

    this->m_keyUP       = other.m_keyUP;
    this->m_keyLEFT     = other.m_keyLEFT;
    this->m_keyDOWN     = other.m_keyDOWN;
    this->m_keyRIGHT    = other.m_keyRIGHT;
}

Player::~Player()
{

}


void Player::setColor(const Color &color)
{
    m_playerColor = color;
}
void Player::setStartPos(const Point &point)
{
    m_initalPos = point;
}
void Player::setKeyBinding(const int &UP_KEY,
                           const int &LEFT_KEY,
                           const int &DOWN_KEY,
                           const int &RIGHT_KEY)
{
    m_keyUP     = UP_KEY;
    m_keyLEFT   = LEFT_KEY;
    m_keyDOWN   = DOWN_KEY;
    m_keyRIGHT  = RIGHT_KEY;

}

void Player::buildPlayer()
{
    if(m_onceBuild)
    {
        qDebug() << "Player already built";
        return;
    }
    m_onceBuild = true;
    KeyController *controller = new KeyController();
    controller->setKey_forMove_UP(m_keyUP);
    controller->setKey_forMove_LEFT(m_keyLEFT);
    controller->setKey_forMove_RIGHT(m_keyRIGHT);
    controller->setKey_forMove_DOWN(m_keyDOWN);
    controller->setPosInitial(m_initalPos);

    painter  = new Painter();
    collider = new Collider();
    this->setupPLayerBody(painter,collider);

    this->setPainter(painter);
    this->setCollider(collider);
    this->setController(controller);
}
void Player::setupPLayerBody(Painter *p,Collider *c)
{
    /**3**0**3*
     *   ###
     *    #
     0#########
     *   ###
     *   ###
     3   ###
     *   # #
     *   # #
     */

    // Head
    p->addPixel(Pixel(Point(-1,-2),m_playerColor));
    p->addPixel(Pixel(Point( 0,-2),m_playerColor));
    p->addPixel(Pixel(Point( 1,-2),m_playerColor));
    p->addPixel(Pixel(Point( 0,-1),m_playerColor));

    c->addHitBox(Rect(-1,-2,3,1));
    c->addHitBox(Rect(0,-1,1,1));

    // Arms and shoulders
    for(int x=-4; x<=4; x++)
        p->addPixel(Pixel(Point(x,0),m_playerColor));
    c->addHitBox(Rect(-4,0,9,1));

    // Body
    for(int x=-1; x<=1; x++)
        for(int y=0; y<=3; y++)
            p->addPixel(Pixel(Point(x,y),m_playerColor));
    c->addHitBox(Rect(-1,1,3,3));

    // Legs
    p->addPixel(Pixel(Point(-1,4),m_playerColor));
    p->addPixel(Pixel(Point(-1,5),m_playerColor));
    p->addPixel(Pixel(Point( 1,4),m_playerColor));
    p->addPixel(Pixel(Point( 1,5),m_playerColor));
    c->addHitBox(Rect(-1,4,1,2));
    c->addHitBox(Rect( 1,4,1,2));

}