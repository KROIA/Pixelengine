#include "player.h"
#include "gameObjectEventHandler.h"

Player::Player()
    :   GameObject()
{
    m_playerColor.r = 50;
    m_playerColor.g = 50;
    m_playerColor.b = 255;

    m_onceBuild  = false;

    m_painter      = new Painter();
    m_collider     = new Collider();
    m_controller   = new KeyController();

    this->setPainter(m_painter);
    this->setCollider(m_collider);
    this->setController(m_controller);

    Property::Property property;
    property.setBody_fat(5);
    property.setBody_health(100);
    property.setBody_stamina(100);
    property.setBody_weight(10);
    property.setBody_strength(10);
    property.setBody_material(Property::Material::Flesh);
    property.setType_description(Property::Description::player);
    this->setProperty(property);

    m_sensor.setOwner(this);
    sensorCollider = new Collider();
    sensorCollider->addHitbox(Rect(-10,-10,20,5));
    sensorCollider->updateBoundingBox();
    m_sensor.setSensorCollider(sensorCollider);
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

void Player::tick(const Point &direction)
{
    GameObject::tick(direction);
}
void Player::checkCollision(const vector<GameObject*> &other)
{
    GameObject::checkCollision(other);
    m_sensor.checkCollision(other);

    if(m_sensorDebugTimer.start(1))
    {
        this->rotate_90();
        if(m_sensor.getDetectedObjects().size()>0)
        {
            vector<GameObject*>list  = m_sensor.getDetectedObjects();
            qDebug()<<"sensor detects "<<m_sensor.getDetectedObjects().size()<<" objects";
            for(size_t i=0; i<list.size(); i++)
            {
                Property::Property p = list[i]->getProperty();
                qDebug() << p.toString().c_str();
                qDebug() << "";
                p.setMood_inLove(p.getMood().inLove+0.001);
                list[i]->setProperty(p);
            }
        }
    }
}
void Player::draw(PixelDisplay &display)
{
    GameObject::draw(display);
    m_sensor.draw(display);
}
void Player::setColor(const Color &color)
{
    m_playerColor = color;
    m_painter->setPixelColor(m_playerColor);
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
void Player::setStepSize(const unsigned int size)
{
    m_controller->setStepSize(size);
}
const unsigned int &Player::getStepSize() const
{
    return m_controller->getStepSize();
}

void Player::buildPlayer()
{
    if(m_onceBuild)
    {
        qDebug() << "Player already built";
        return;
    }
    m_onceBuild = true;

    m_controller->setKey_forMove_UP(m_keyUP);
    m_controller->setKey_forMove_LEFT(m_keyLEFT);
    m_controller->setKey_forMove_RIGHT(m_keyRIGHT);
    m_controller->setKey_forMove_DOWN(m_keyDOWN);
    m_controller->setPosInitial(m_initalPos);

    m_painter->clear();
    m_collider->clear();

    this->setupPLayerBody(m_painter,m_collider);


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

    c->addHitbox(Rect(-1,-2,3,1));
    c->addHitbox(Rect(0,-1,1,1));

    // Arms and shoulders
    for(int x=-4; x<=4; x++)
        p->addPixel(Pixel(Point(x,0),m_playerColor));
    c->addHitbox(Rect(-4,0,9,1));

    // Body
    for(int x=-1; x<=1; x++)
        for(int y=0; y<=3; y++)
            p->addPixel(Pixel(Point(x,y),m_playerColor));
    c->addHitbox(Rect(-1,1,3,3));

    // Legs
    p->addPixel(Pixel(Point(-1,4),m_playerColor));
    p->addPixel(Pixel(Point(-1,5),m_playerColor));
    p->addPixel(Pixel(Point( 1,4),m_playerColor));
    p->addPixel(Pixel(Point( 1,5),m_playerColor));
    c->addHitbox(Rect(-1,4,1,2));
    c->addHitbox(Rect( 1,4,1,2));
}
void Player::rotate_90()
{
    GameObject::rotate_90();
    m_sensor.rotate_90();
}
void Player::event_hasCollision(GameObject *other)
{
    if(this->m_objEventHandler != nullptr)
        m_objEventHandler->collisionOccured(this,other);
    Property::Property otherProperty = other->getProperty();

    if(otherProperty.getBody().material    == Property::Material::Grass &&
       otherProperty.getType().description != Property::Description::dynamicObsticle)
    {
        if(m_objEventHandler != nullptr)
           m_objEventHandler->removeFromEngine(other);
    }

    m_controller->setToLastPos();
    m_collider->setPos(m_controller->getPos());
}
