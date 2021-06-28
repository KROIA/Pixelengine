#include "gameobject.h"
#include "gameObjectEventHandler.h"

GameObject::GameObject()
{
    this->addController(new Controller());
    m_collider      = new Collider();
    m_painter       = nullptr;
    //m_painter       = new Painter();
    m_hitboxPainter = new PixelPainter();
    //m_texture       = new Texture();
   // m_texture->setAlphaColor(Color(255,255,255,255));
    m_objEventHandler = nullptr;
    //m_textureIsActiveForPainter         = false;
    //m_painterNeedsUpdateFromTexture     = false;
    //m_textureIsActiveForCollider        = false;
    //m_colliderNeedsUpdateFromTexture    = false;
    m_rotationDeg      = 90; // 90 deg
    setHitboxVisibility(false);
}
GameObject::GameObject(const GameObject &other)
{
    this->addController(new Controller());
    m_collider      = new Collider();
    //m_painter       = new Painter();
    m_painter       = nullptr;
    m_hitboxPainter = new PixelPainter();
    //m_texture       = new Texture();
    m_objEventHandler = nullptr;

    *this = other;
    setHitboxVisibility(false);
}
GameObject::GameObject(Controller *controller,
                       Collider   *collider,
                       Painter    *painter)
{
    this->addController(controller);
    this->setCollider(collider);
    this->setPainter(painter);
  //  m_texture         = new Texture();
    m_objEventHandler = nullptr;
  //  m_textureIsActiveForPainter         = false;
  //  m_painterNeedsUpdateFromTexture     = false;
  //  m_textureIsActiveForCollider        = false;
  //  m_colliderNeedsUpdateFromTexture    = false;
    m_rotationDeg      = 90; // 90 deg
    setHitboxVisibility(false);
}

GameObject::~GameObject()
{
    removeText();
    clearController();
    delete m_collider;
    if(m_painter != nullptr)
        delete m_painter;
    delete m_hitboxPainter;
  //  delete m_texture;
}
const GameObject &GameObject::operator=(const GameObject &other)
{
    this->m_controllerList      = other.m_controllerList;
    *this->m_collider           = *other.m_collider;
    *this->m_painter            = *other.m_painter;
    *this->m_hitboxPainter      = *other.m_hitboxPainter;
 //   *this->m_texture            = *other.m_texture;
    this->m_property            = other.m_property;
    this->m_objEventHandler     = other.m_objEventHandler;
    this->m_rotationDeg         = other.m_rotationDeg;
  //  this->m_textureIsActiveForPainter       = other.m_textureIsActiveForPainter;
 //   this->m_painterNeedsUpdateFromTexture   = other.m_painterNeedsUpdateFromTexture;
 //   this->m_textureIsActiveForCollider      = other.m_textureIsActiveForCollider;
   // this->m_colliderNeedsUpdateFromTexture  = other.m_colliderNeedsUpdateFromTexture;

    return *this;
}
void GameObject::checkEvent()
{
    EASY_FUNCTION(profiler::colors::Green);
    //this->checkTextureUpdateForCollider();
   // this->checkTextureUpdateForPainter();
//    m_texture->changesApplied();

    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->checkEvent();
}
void GameObject::killMe()
{
    EASY_FUNCTION(profiler::colors::Green50);
    if(m_objEventHandler != nullptr)
        m_objEventHandler->kill(this);
}
void GameObject::removeMeFromEngine()
{
    EASY_FUNCTION(profiler::colors::Green100);
    if(m_objEventHandler != nullptr)
        m_objEventHandler->removeFromEngine(this);
}
void GameObject::deleteMeFromEngine()
{
    EASY_FUNCTION(profiler::colors::Green200);
    if(m_objEventHandler != nullptr)
        m_objEventHandler->deleteObject(this);
}

void GameObject::tick(const Vector2i&direction)
{
    EASY_FUNCTION(profiler::colors::Green300);
//    if(m_colliderNeedsUpdateFromTexture)
  //      this->setHitboxFromTexture();
    m_layerItem.swapPosToLastPos();
    if(direction.x > 0)
    {
        EASY_BLOCK("for(size_t i=0; i<m_controllerList.size(); i++)",profiler::colors::Green300);
        for(size_t i=0; i<m_controllerList.size(); i++)
        {
            if(m_controllerList[i]->getMovingMode() == Controller::MovingMode::override)
                m_movementCoordinator.clearMovement();
            m_movementCoordinator.addMovement(m_controllerList[i]->getMovingVector());
            m_controllerList[i]->tick(); // Clears the movingVector
        }
        m_movementCoordinator.calculateMovement();
        m_layerItem.move(Vector2i(round(m_movementCoordinator.getMovingVector_X()),0));
       // qDebug() << round(m_movementCoordinator.getMovingVector().x) << " "<<round(m_movementCoordinator.getMovingVector().y);
        //m_layerItem.move(Vector2f(m_movementCoordinator.getMovingVector_X(),0));
        //qDebug() << m_movementCoordinator.getMovingVector().x << " "<<m_movementCoordinator.getMovingVector().y << "\t"<<m_layerItem.getX()<<"\t"<<m_layerItem.getY();

        EASY_END_BLOCK;
    }
    else
    {
        m_layerItem.move(Vector2i(0,round(m_movementCoordinator.getMovingVector_Y())));
        //m_layerItem.move(Vector2f(0,m_movementCoordinator.getMovingVector_Y()));
        m_movementCoordinator.tick();
    }
    m_collider->setPos(m_layerItem.getPos());
    //m_painter->setPos(m_layerItem.getPos());
}


unsigned int GameObject::checkCollision(const vector<GameObject*> &other)
{
    EASY_FUNCTION(profiler::colors::Green400);
    vector<GameObject*> collided = GameObject::getCollidedObjects(this, m_collider, other);
    if(collided.size() > 0)
    {
        event_hasCollision(collided);
    }
    return collided.size();
}
unsigned int GameObject::checkCollision(const vector<vector<GameObject*> >&other)
{
    EASY_FUNCTION(profiler::colors::Green500);
    vector<GameObject*> collided;
    for(size_t i=0; i<other.size(); i++)
    {
        vector<GameObject*> coll = GameObject::getCollidedObjects(this, m_collider, other[i]);
        collided.reserve(collided.size() + coll.size());
        for(size_t j=0; j<coll.size(); j++)
        {
            collided.push_back(coll[i]);
        }

    }
    if(collided.size() > 0)
    {
        event_hasCollision(collided);
    }
    return collided.size();
}
vector<GameObject*> GameObject::getCollidedObjects(GameObject *owner, Collider *collider,const vector<GameObject*> &other)
{
    EASY_FUNCTION(profiler::colors::Green600);
    vector<GameObject*> collided;
    collided.reserve(10);
    for(size_t i=0; i<other.size(); i++)
    {
        if(owner == other[i])
            continue; // This is the same object like other[i]
        if(collider->intersectsBoundingBox(*other[i]->m_collider))
        {
            if(collider->collides(*other[i]->m_collider))
            {
                collided.push_back(other[i]);
            }
        }
    }
    return collided;
}

void GameObject::draw(PixelDisplay &display)
{
    EASY_FUNCTION(profiler::colors::Green700);
 //   if(m_painterNeedsUpdateFromTexture)
 //       this->setTextureOnPainter();
    m_painter->setPos(m_layerItem.getPos());
    m_hitboxPainter->setPos(m_layerItem.getPos());
    int outOfFrameBoundry = 16;
    if(m_layerItem.getX() > signed(display.getMapSize().x) + outOfFrameBoundry)
        return;
    if(m_layerItem.getY() > signed(display.getMapSize().x) + outOfFrameBoundry)
        return;
    if(m_layerItem.getX() < -outOfFrameBoundry)
        return;
    if(m_layerItem.getY() < -outOfFrameBoundry)
        return;


    /*if(!this->m_painter->getFrame().intersects(RectI(10,10,display.getMapSize().getX()-20,display.getMapSize().getY()-20)))
    {
        return;
    }*/
    m_painter->draw(display);
    if(m_hitboxPainter->isVisible())
    {

        m_hitboxPainter->draw(display);

        // ----------------- TEST ---------------
       // Vector2f renderScale = display.getRenderScale();
       // vector<sf::Vertex>  line {
      /*  sf::Vertex line[] ={
            sf::Vertex(sf::Vector2f(m_collider->getBoundingBox().getCornerPoint_TL().getX()*renderScale.getX(), m_collider->getBoundingBox().getCornerPoint_TL().getY()*renderScale.getY())),
            sf::Vertex(sf::Vector2f(m_collider->getBoundingBox().getCornerPoint_BR().getX()*renderScale.getX(), m_collider->getBoundingBox().getCornerPoint_BR().getY()*renderScale.getY()))
        };*/
        VertexPath line_;
        line_.line = new sf::Vertex [2]{
            sf::Vertex(sf::Vector2f(m_collider->getBoundingBox().getCornerPoint_TL().x, m_collider->getBoundingBox().getCornerPoint_TL().y)),
            sf::Vertex(sf::Vector2f(m_collider->getBoundingBox().getCornerPoint_BR().x, m_collider->getBoundingBox().getCornerPoint_BR().y))
        };
        line_.length = 2;
        line_.type = sf::Lines;

        display.addVertexLine(line_);

        //display.getRenderWindow()->draw(line_.line, line_.length, line_.type);
    }

}

void GameObject::addController(Controller *controller)
{
    EASY_FUNCTION(profiler::colors::Green800);
    if(controller == nullptr)
        return;

    for(size_t i=0; i<m_controllerList.size(); i++)
        if(m_controllerList[i] == controller)
            return;

    m_controllerList.push_back(controller);
}
void GameObject::clearController()
{
    EASY_FUNCTION(profiler::colors::Green900);
    for(size_t i=0; i<m_controllerList.size(); i++)
        delete m_controllerList[i];
    m_controllerList.clear();
}

void GameObject::setCollider(Collider *collider)
{
    EASY_FUNCTION(profiler::colors::GreenA100);
    if(m_collider == collider || collider == nullptr)
        return;
    if(m_collider != nullptr)
        delete m_collider;
    m_collider = collider;
}
const Collider &GameObject::getCollider() const
{
    return *m_collider;
}
void GameObject::setPainter(Painter *painter)
{
    EASY_FUNCTION(profiler::colors::GreenA200);
    if(m_painter == painter || painter == nullptr)
        return;
    if(m_painter != nullptr)
        delete m_painter;
    m_painter = painter;
}
const Painter &GameObject::getPainter() const
{
    return *m_painter;
}
void GameObject::setEventHandler(GameObjectEventHandler *handler)
{
    EASY_FUNCTION(profiler::colors::GreenA400);
    m_objEventHandler = handler;

    if(m_objEventHandler == nullptr)
        return;
    if(m_displayTextList.size() != 0)
        for(DisplayText* &text : m_displayTextList)
            m_objEventHandler->addDisplayText(text);

}

void GameObject::setPos(int x,int y)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(x,y);
    //m_collider->setPos(x,y);
   // m_painter->setPos(x,y);
}
void GameObject::setPos(const Vector2i &pos)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(pos);
}
void GameObject::setPos(float x, float y)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(x,y);
    //m_collider->setPos(x,y);
   // m_painter->setPos(x,y);
}
void GameObject::setPos(const Vector2f &pos)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(pos);
}
void GameObject::setX(int x)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(float(x),m_layerItem.getY());
}
void GameObject::setY(int y)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(m_layerItem.getX(),float(y));
}
void GameObject::setX(float x)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(x,m_layerItem.getY());
}
void GameObject::setY(float y)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(m_layerItem.getX(),y);
}

void GameObject::moveToPos(const Vector2i&destination,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->moveToPos(m_layerItem.getPosI(),destination,mode);
}
void GameObject::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->moveToPos(m_layerItem.getXI(),m_layerItem.getYI(),x,y,mode);
}
void GameObject::move(const Vector2i&vec,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->move(vec,mode);
}
void GameObject::move(const Vector2f &vec,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->move(vec,mode);
}
void GameObject::move(const float &deltaX, const float &deltaY,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->move(deltaX,deltaY,mode);
}
void GameObject::moveX(const float &delta,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->moveX(delta,mode);
}
void GameObject::moveY(const float &delta,Controller::MovingMode mode)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_controllerList[0]->moveY(delta,mode);
}

const Vector2f &GameObject::getPos() const
{
    return m_layerItem.getPos();
}
const Vector2f &GameObject::getMovingVector() const
{
    return m_movementCoordinator.getMovingVector();
}

void GameObject::rotate(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Green);
    if(m_hitboxPainter->isVisible())
    {
        this->setHitboxVisibility(false);
        this->setHitboxVisibility(true);
    }
    m_rotationDeg+=deg;
    if(m_rotationDeg >= 360)
        m_rotationDeg = m_rotationDeg%360;

    m_painter->setPos(m_layerItem.getPos());
    m_collider->setPos(m_layerItem.getPos());
}

float GameObject::getRotation() const
{
    return m_rotationDeg;
}
//this->rotate(Vector2f(this->getX(),this->getY()),(deg*M_PI/180.f) - m_rotationRad);
void GameObject::setRotation(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Green);
    float rot = m_rotationDeg - deg;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(deg);
    m_collider->setRotation(deg);
    m_painter->setRotation(deg);
    rotate(rot/180.f*M_PI);
}
void GameObject::rotate_90()
{
    EASY_FUNCTION(profiler::colors::Green);
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_90();
    m_collider->rotate_90();
    m_painter->setPos(m_layerItem.getPos());
    m_painter->rotate_90();
    rotate(M_PI_2);
}
void GameObject::rotate_180()
{
    EASY_FUNCTION(profiler::colors::Green);
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_180();
    m_collider->rotate_180();
    m_painter->rotate_180();
    rotate(M_PI);
}
void GameObject::rotate_270()
{
    EASY_FUNCTION(profiler::colors::Green);
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_270();
    m_collider->rotate_270();
    m_painter->rotate_270();
    rotate(M_PI_2*3);
}
void GameObject::setRotation(const Vector2f &rotationPoint,const float &deg)
{
    EASY_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::rotate(Vector2f(this->getPos()),rotationPoint,deg);
    this->setPos(round(newPos.x),round(newPos.y));
    float rot = m_rotationDeg - deg;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(deg);
    m_collider->setRotation(deg);
    m_painter->setRotation(deg);
    rotate(rot/180.f*M_PI);
}
void GameObject::rotate_90(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::rotate(Vector2f(this->getPos()),rotationPoint,90);
    this->setPos(round(newPos.x),round(newPos.y));
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_90();
    m_collider->rotate_90();
    m_painter->rotate_90();
    rotate(M_PI_2);
}
void GameObject::rotate_180(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::rotate(Vector2f(this->getPos()),rotationPoint,180);
    this->setPos(round(newPos.x),round(newPos.y));
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_180();
    m_collider->rotate_180();
    m_painter->rotate_180();
    rotate(M_PI);
}
void GameObject::rotate_270(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::rotate(Vector2f(this->getPos()),rotationPoint,270);
    this->setPos(round(newPos.x),round(newPos.y));
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_270();
    m_collider->rotate_270();
    m_painter->rotate_270();
    rotate(M_PI_2*3);
}
void GameObject::addHitbox(const RectI &box)
{
    EASY_FUNCTION(profiler::colors::Green100);
    m_collider->addHitbox(box);
}
void GameObject::addHitbox(const vector<RectI> &boxList)
{
    EASY_FUNCTION(profiler::colors::Green100);
    m_collider->addHitbox(boxList);
}
void GameObject::eraseHitbox(const size_t &index)
{
    EASY_FUNCTION(profiler::colors::Green200);
    m_collider->erase(index);
}
void GameObject::clearCollider()
{
    EASY_FUNCTION(profiler::colors::Green300);
    m_collider->clear();
}
const bool &GameObject::isBoundingBoxUpdated() const
{
    EASY_FUNCTION(profiler::colors::Green400);
    return m_collider->isBoundingBoxUpdated();
}
void GameObject::updateBoundingBox()
{
    EASY_FUNCTION(profiler::colors::Green500);
    m_collider->updateBoundingBox();
}
/*void GameObject::setHitboxFromTexture()
{
    EASY_FUNCTION(profiler::colors::Green600);
    m_textureIsActiveForCollider = true;
    m_collider->setHitboxFromTexture(m_texture);
 //   this->updateHitboxPainter();
    m_colliderNeedsUpdateFromTexture = false;
}*/
void GameObject::setHitboxFromTexture(const Texture &texture)
{
    EASY_FUNCTION(profiler::colors::Green600);
    m_textureIsActiveForCollider = true;
    m_collider->setHitboxFromTexture(&texture);
    updateHitboxPainter();
   // m_colliderNeedsUpdateFromTexture = false;
}
void GameObject::setHitboxVisibility(const bool &isVisible)
{
    EASY_FUNCTION(profiler::colors::Green700);
    m_hitboxPainter->setVisibility(isVisible);
    if(isVisible)
    {
        //EASY_BLOCK("makeVisibleCollider");
        updateHitboxPainter();
        //EASY_END_BLOCK;
        //getchar();
        //getchar();
    }

}
void GameObject::updateHitboxPainter()
{
    EASY_FUNCTION(profiler::colors::Green800);
    if(m_hitboxPainter->isVisible())
    {
        HitboxPainter::makeVisibleCollider(m_collider,m_hitboxPainter);
       // Point offset = Vector(m_collider->getPos())-Vector(m_collider->getBoundingBox().getCornerPoint_TL());
       // m_hitboxPainter->setOrigin(Vector2f(offset.getX(),offset.getY()));
    }
}
const bool &GameObject::isHitboxVisible() const
{
    return m_hitboxPainter->isVisible();
}
/*bool GameObject::checkTextureUpdateForCollider()
{
    if(m_textureIsActiveForCollider && m_texture->changesAvailable())
    {
        m_colliderNeedsUpdateFromTexture = true;
        return true;
    }
    return false;
}*/

/*void GameObject::reservePixelAmount(const size_t amount)
{
    m_painter->reserve(amount);
}
void GameObject::addPixel(const Pixel &pixel)
{
    m_painter->addPixel(pixel);
}
void GameObject::addPixel(const vector<Pixel> &pixelList)
{
    m_painter->addPixel(pixelList);
}
const Pixel &GameObject::getPixel(const size_t &index) const
{
    return m_painter->getPixel(index);
}
const Pixel &GameObject::getPixel(const Vector2i&pixelPos) const
{
    return m_painter->getPixel(pixelPos);
}
const Pixel &GameObject::getPixel(int x, int y) const
{
    return m_painter->getPixel(x,y);
}
size_t GameObject::getPixelAmount() const
{
    return m_painter->getPixelAmount();
}
void GameObject::setPixelColor(const size_t &index, const Color &color)
{
    m_painter->setPixelColor(index,color);
}
void GameObject::setPixelColor(const Vector2i&pixelPos, const Color &color)
{
    m_painter->setPixelColor(pixelPos,color);
}
void GameObject::setPixelColor(int x, int y, const Color &color)
{
    m_painter->setPixelColor(x,y,color);
}
void GameObject::setPixelColor(const Color &color)
{
    m_painter->setPixelColor(color);
}
void GameObject::erasePixel(const size_t &index)
{
    m_painter->erasePixel(index);
}
void GameObject::erasePixel(const Vector2i&pixelPos)
{
    m_painter->erasePixel(pixelPos);
}
void GameObject::erasePixel(int x, int y)
{
    m_painter->erasePixel(x,y);
}
void GameObject::clearPainter()
{
    m_painter->clear();
}*/
void GameObject::setVisibility(const bool &isVisible)
{
    m_painter->setVisibility(isVisible);
}
const bool &GameObject::isVisible() const
{
    return m_painter->isVisible();
}
/*
void GameObject::setTexture(Texture *texture)
{
    if(texture == nullptr)
        return;
    if(texture == m_texture)
        return;
    delete m_texture;
    m_texture = texture;
}
void GameObject::setTexturePath(const string &path)
{
    EASY_FUNCTION(profiler::colors::Green900);
    m_texture->setFilePath(path);
}
void GameObject::loadTexture()
{
    EASY_FUNCTION(profiler::colors::GreenA100);
    m_texture->loadTexture();
}
const Texture &GameObject::getTexture() const
{
    return *m_texture;
}
void GameObject::setTextureOnPainter()
{
    EASY_FUNCTION(profiler::colors::GreenA200);
    m_textureIsActiveForPainter = true;
    //m_painter->setTexture(m_texture);
    m_painter->setTexture(m_texture);
    m_painterNeedsUpdateFromTexture = false;
}
void GameObject::setTextureOnPainter(Texture &texture)
{
    EASY_FUNCTION(profiler::colors::GreenA200);
    m_painter->setTexture(&texture);
}
bool GameObject::checkTextureUpdateForPainter()
{
    if(m_textureIsActiveForPainter && m_texture->changesAvailable())
    {
        m_painterNeedsUpdateFromTexture = true;
        return true;
    }
    return false;
}*/


void GameObject::setProperty(const Property::Property &property)
{
    m_property = property;
}
const Property::Property &GameObject::getProperty() const
{
    return m_property;
}


// Text visualisation
void GameObject::addText(DisplayText *text)
{
    EASY_FUNCTION(profiler::colors::GreenA400);
    if(text == nullptr)
        return;
    for(DisplayText* &t : m_displayTextList)
    {
        if(t == text)
            return;
    }
    m_displayTextList.push_back(text);
    if(m_objEventHandler != nullptr)
        m_objEventHandler->addDisplayText(text);
}
void GameObject::removeText(DisplayText *text)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    if(text == nullptr)
        return;
    for(size_t i=0; i<m_displayTextList.size(); i++)
    {
        if(m_displayTextList[i] == text)
        {
            if(m_objEventHandler != nullptr)
                m_objEventHandler->removeDisplayText(text);
            m_displayTextList.erase(m_displayTextList.begin() + i);
        }
    }
}
void GameObject::removeText()
{
    m_displayTextList.clear();
}
void GameObject::deleteText(DisplayText *text)
{
    EASY_FUNCTION(profiler::colors::Green);
    if(text == nullptr)
        return;
    for(size_t i=0; i<m_displayTextList.size(); i++)
    {
        if(m_displayTextList[i] == text)
        {
            if(m_objEventHandler != nullptr)
                m_objEventHandler->removeDisplayText(text);
            delete m_displayTextList[i];
            m_displayTextList.erase(m_displayTextList.begin() + i);
        }
    }
}
void GameObject::deleteText()
{
    EASY_FUNCTION(profiler::colors::Green);
    for(size_t i=0; i<m_displayTextList.size(); i++)
    {
        if(m_objEventHandler != nullptr)
            m_objEventHandler->removeDisplayText(m_displayTextList[i]);
        delete m_displayTextList[i];
    }
    m_displayTextList.clear();
}

const vector<DisplayText*> &GameObject::getTextList()
{
    return m_displayTextList;
}



void GameObject::event_hasCollision(vector<GameObject *> other)
{
    EASY_FUNCTION(profiler::colors::Green100);
    if(m_objEventHandler != nullptr)
        m_objEventHandler->collisionOccured(this,other);
    m_layerItem.setToLastPos();
    m_collider->setPos(m_layerItem.getPos());
    m_painter->setPos(m_layerItem.getPos());
}
