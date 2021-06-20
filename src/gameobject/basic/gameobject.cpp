#include "gameobject.h"
#include "gameObjectEventHandler.h"

GameObject::GameObject()
{
    this->addController(new Controller());
    m_collider      = new Collider();
    m_painter       = new Painter();
    m_hitboxPainter = new Painter();
    m_texture       = new Texture();
   // m_texture->setAlphaColor(Color(255,255,255,255));
    m_objEventHandler = nullptr;
    m_textureIsActiveForPainter         = false;
    m_painterNeedsUpdateFromTexture     = false;
    m_textureIsActiveForCollider        = false;
    m_colliderNeedsUpdateFromTexture    = false;
    m_rotationDeg      = 90; // 90 deg
    setHitboxVisibility(false);
}
GameObject::GameObject(const GameObject &other)
{
    this->addController(new Controller());
    m_collider      = new Collider();
    m_painter       = new Painter();
    m_hitboxPainter = new Painter();
    m_texture       = new Texture();
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
    m_texture         = new Texture();
    m_objEventHandler = nullptr;
    m_textureIsActiveForPainter         = false;
    m_painterNeedsUpdateFromTexture     = false;
    m_textureIsActiveForCollider        = false;
    m_colliderNeedsUpdateFromTexture    = false;
    m_rotationDeg      = 90; // 90 deg
    setHitboxVisibility(false);
}

GameObject::~GameObject()
{
    removeText();
    clearController();
    delete m_collider;
    delete m_painter;
    delete m_hitboxPainter;
    delete m_texture;
}
const GameObject &GameObject::operator=(const GameObject &other)
{
    this->m_controllerList      = other.m_controllerList;
    *this->m_collider           = *other.m_collider;
    *this->m_painter            = *other.m_painter;
    *this->m_hitboxPainter      = *other.m_hitboxPainter;
    *this->m_texture            = *other.m_texture;
    this->m_property            = other.m_property;
    this->m_objEventHandler     = other.m_objEventHandler;
    this->m_rotationDeg         = other.m_rotationDeg;
    this->m_textureIsActiveForPainter       = other.m_textureIsActiveForPainter;
    this->m_painterNeedsUpdateFromTexture   = other.m_painterNeedsUpdateFromTexture;
    this->m_textureIsActiveForCollider      = other.m_textureIsActiveForCollider;
    this->m_colliderNeedsUpdateFromTexture  = other.m_colliderNeedsUpdateFromTexture;

    return *this;
}
void GameObject::checkEvent()
{
    this->checkTextureUpdateForCollider();
    this->checkTextureUpdateForPainter();
    m_texture->changesApplied();

    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->checkEvent();
}
void GameObject::killMe()
{
    if(m_objEventHandler != nullptr)
        m_objEventHandler->kill(this);
}
void GameObject::removeMeFromEngine()
{
    if(m_objEventHandler != nullptr)
        m_objEventHandler->removeFromEngine(this);
}
void GameObject::deleteMeFromEngine()
{
    if(m_objEventHandler != nullptr)
        m_objEventHandler->deleteObject(this);
}

void GameObject::tick(const Point &direction)
{
    if(m_colliderNeedsUpdateFromTexture)
        this->setHitboxFromTexture();
    m_layerItem.swapPosToLastPos();
    if(direction.getX() > 0)
    {
        for(size_t i=0; i<m_controllerList.size(); i++)
        {
            if(m_controllerList[i]->getMovingMode() == Controller::MovingMode::override)
                m_movementCoordinator.clearMovement();
            m_movementCoordinator.addMovement(m_controllerList[i]->getMovingVector());
            m_controllerList[i]->tick(); // Clears the movingVector
        }
        m_movementCoordinator.calculateMovement();
        m_layerItem.moveX_F(m_movementCoordinator.getMovingVector_X());
    }
    else
    {
        m_layerItem.moveY_F(m_movementCoordinator.getMovingVector_Y());
        m_movementCoordinator.tick();
    }
    m_collider->setPos(m_layerItem.getPos());
    //m_painter->setPos(m_layerItem.getPos());
}


unsigned int GameObject::checkCollision(const vector<GameObject*> &other)
{
    vector<GameObject*> collided = GameObject::getCollidedObjects(this, m_collider, other);
    if(collided.size() > 0)
    {
        event_hasCollision(collided);
    }
    return collided.size();
}
unsigned int GameObject::checkCollision(const vector<vector<GameObject*> >&other)
{
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
    if(m_painterNeedsUpdateFromTexture)
        this->setTextureOnPainter();
    m_painter->setPos(m_layerItem.getPos());
    m_hitboxPainter->setPos(m_layerItem.getPos());
    int outOfFrameBoundry = 16;
    if(m_layerItem.getX() > signed(display.getMapSize().getX()) + outOfFrameBoundry)
        return;
    if(m_layerItem.getY() > signed(display.getMapSize().getY()) + outOfFrameBoundry)
        return;
    if(m_layerItem.getX() < -outOfFrameBoundry)
        return;
    if(m_layerItem.getY() < -outOfFrameBoundry)
        return;


    /*if(!this->m_painter->getFrame().intersects(Rect(10,10,display.getMapSize().getX()-20,display.getMapSize().getY()-20)))
    {
        return;
    }*/
    m_painter->draw(display);
    m_hitboxPainter->draw(display);
}

void GameObject::addController(Controller *controller)
{
    if(controller == nullptr)
        return;

    for(size_t i=0; i<m_controllerList.size(); i++)
        if(m_controllerList[i] == controller)
            return;

    m_controllerList.push_back(controller);
}
void GameObject::clearController()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        delete m_controllerList[i];
    m_controllerList.clear();
}

void GameObject::setCollider(Collider *collider)
{
    if(m_collider == collider || collider == nullptr)
        return;
    delete m_collider;
    m_collider = collider;
}
const Collider &GameObject::getCollider() const
{
    return *m_collider;
}
void GameObject::setPainter(Painter *painter)
{
    if(m_painter == painter || painter == nullptr)
        return;
    delete m_painter;
    m_painter = painter;
}
const Painter &GameObject::getPainter() const
{
    return *m_painter;
}
void GameObject::setEventHandler(GameObjectEventHandler *handler)
{
    m_objEventHandler = handler;

    if(m_objEventHandler == nullptr)
        return;
    if(m_displayTextList.size() != 0)
        for(DisplayText* &text : m_displayTextList)
            m_objEventHandler->addDisplayText(text);

}

void GameObject::setPos(const int &x,const int &y)
{
    m_layerItem.setPosInitial(x,y);
    //m_collider->setPos(x,y);
   // m_painter->setPos(x,y);
}
void GameObject::setPos(const Point &pos)
{
    m_layerItem.setPosInitial(pos);
}

void GameObject::setX(const int &x)
{
    m_layerItem.setPosInitial(x,m_layerItem.getY());
}
void GameObject::setY(const int &y)
{
    m_layerItem.setPosInitial(m_layerItem.getX(),y);
}

void GameObject::moveToPos(const Point &destination,Controller::MovingMode mode)
{
    m_controllerList[0]->moveToPos(m_layerItem.getPos(),destination,mode);
}
void GameObject::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    m_controllerList[0]->moveToPos(m_layerItem.getPos().getX(),m_layerItem.getPos().getY(),x,y,mode);
}
void GameObject::move(const Vector &vec,Controller::MovingMode mode)
{
    m_controllerList[0]->move(vec,mode);
}
void GameObject::move(const VectorF &vec,Controller::MovingMode mode)
{
    m_controllerList[0]->move(vec,mode);
}
void GameObject::move(const double &deltaX, const double &deltaY,Controller::MovingMode mode)
{
    m_controllerList[0]->move(deltaX,deltaY,mode);
}
void GameObject::moveX(const double &delta,Controller::MovingMode mode)
{
    m_controllerList[0]->moveX(delta,mode);
}
void GameObject::moveY(const double &delta,Controller::MovingMode mode)
{
    m_controllerList[0]->moveY(delta,mode);
}

const Point GameObject::getPos() const
{
    return m_layerItem.getPos();
}
const VectorF &GameObject::getMovingVector() const
{
    return m_movementCoordinator.getMovingVector();
}

void GameObject::rotate(const double &rad)
{
    if(m_hitboxPainter->isVisible())
    {
        this->setHitboxVisibility(false);
        this->setHitboxVisibility(true);
    }
    m_rotationDeg+=rad*180/M_PI;
    if(m_rotationDeg >= 360)
        m_rotationDeg = m_rotationDeg%360;

    m_painter->setPos(m_layerItem.getPos());
    m_collider->setPos(m_layerItem.getPos());
}

double GameObject::getRotation() const
{
    return m_rotationDeg;
}
//this->rotate(PointF(this->getX(),this->getY()),(deg*M_PI/180.f) - m_rotationRad);
void GameObject::setRotation(const double &deg)
{
    double rot = m_rotationDeg - deg;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(deg);
    m_collider->setRotation(deg);
    m_painter->setRotation(deg);
    rotate(rot/180.f*M_PI);
}
void GameObject::rotate_90()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_90();
    m_collider->rotate_90();
    m_painter->setPos(m_layerItem.getPos());
    m_painter->rotate_90();
    rotate(M_PI_2);
}
void GameObject::rotate_180()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_180();
    m_collider->rotate_180();
    m_painter->rotate_180();
    rotate(M_PI);
}
void GameObject::rotate_270()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_270();
    m_collider->rotate_270();
    m_painter->rotate_270();
    rotate(M_PI_2*3);
}
void GameObject::setRotation(const PointF &rotationPoint,const double &deg)
{
    PointF newPos = VectorF::rotate(VectorF(this->getPos().getX(), this->getPos().getY()),rotationPoint,deg*M_PI/180).toPoint();
    this->setPos(round(newPos.getX()),round(newPos.getY()));
    double rot = m_rotationDeg - deg;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(deg);
    m_collider->setRotation(deg);
    m_painter->setRotation(deg);
    rotate(rot/180.f*M_PI);
}
void GameObject::rotate_90(const PointF &rotationPoint)
{
    PointF newPos = VectorF::rotate(VectorF(this->getPos().getX(), this->getPos().getY()),rotationPoint,M_PI_2).toPoint();
    this->setPos(round(newPos.getX()),round(newPos.getY()));
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_90();
    m_collider->rotate_90();
    m_painter->rotate_90();
    rotate(M_PI_2);
}
void GameObject::rotate_180(const PointF &rotationPoint)
{
    PointF newPos = VectorF::rotate(VectorF(this->getPos().getX(), this->getPos().getY()),rotationPoint,M_PI).toPoint();
    this->setPos(round(newPos.getX()),round(newPos.getY()));
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_180();
    m_collider->rotate_180();
    m_painter->rotate_180();
    rotate(M_PI);
}
void GameObject::rotate_270(const PointF &rotationPoint)
{
    PointF newPos = VectorF::rotate(VectorF(this->getPos().getX(), this->getPos().getY()),rotationPoint,M_PI_2*3).toPoint();
    this->setPos(round(newPos.getX()),round(newPos.getY()));
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate_270();
    m_collider->rotate_270();
    m_painter->rotate_270();
    rotate(M_PI_2*3);
}
void GameObject::addHitbox(const Rect &box)
{
    m_collider->addHitbox(box);
}
void GameObject::addHitbox(const vector<Rect> &boxList)
{
    m_collider->addHitbox(boxList);
}
void GameObject::eraseHitbox(const size_t &index)
{
    m_collider->erase(index);
}
void GameObject::clearCollider()
{
    m_collider->clear();
}
const bool &GameObject::isBoundingBoxUpdated() const
{
    return m_collider->isBoundingBoxUpdated();
}
void GameObject::updateBoundingBox()
{
    m_collider->updateBoundingBox();
}
void GameObject::setHitboxFromTexture()
{
    m_textureIsActiveForCollider = true;
    m_collider->setHitboxFromTexture(m_texture);
    this->updateHitboxPainter();
    m_colliderNeedsUpdateFromTexture = false;
}
void GameObject::setHitboxFromTexture(const Texture &texture)
{
    //m_textureIsActiveForCollider = true;
    m_collider->setHitboxFromTexture(&texture);
    //m_colliderNeedsUpdateFromTexture = false;
}
void GameObject::setHitboxVisibility(const bool &isVisible)
{
    if(isVisible)
    {
        HitboxPainter::makeVisibleCollider(m_collider,m_hitboxPainter);
    }
    m_hitboxPainter->setVisibility(isVisible);
}
void GameObject::updateHitboxPainter()
{
    if(m_hitboxPainter->isVisible())
    {
        HitboxPainter::makeVisibleCollider(m_collider,m_hitboxPainter);
    }
}
const bool &GameObject::isHitboxVisible() const
{
    return m_hitboxPainter->isVisible();
}
bool GameObject::checkTextureUpdateForCollider()
{
    if(m_textureIsActiveForCollider && m_texture->changesAvailable())
    {
        m_colliderNeedsUpdateFromTexture = true;
        return true;
    }
    return false;
}

void GameObject::reservePixelAmount(const size_t amount)
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
const Pixel &GameObject::getPixel(const Point &pixelPos) const
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
void GameObject::setPixelColor(const Point &pixelPos, const Color &color)
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
void GameObject::erasePixel(const Point &pixelPos)
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
}
void GameObject::setVisibility(const bool &isVisible)
{
    m_painter->setVisibility(isVisible);
}
const bool &GameObject::isVisible() const
{
    return m_painter->isVisible();
}

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
    m_texture->setFilePath(path);
}
void GameObject::loadTexture()
{
    m_texture->loadTexture();
}
const Texture &GameObject::getTexture() const
{
    return *m_texture;
}
void GameObject::setTextureOnPainter()
{
    m_textureIsActiveForPainter = true;
    m_painter->setTexture(m_texture);
    m_painterNeedsUpdateFromTexture = false;
}
void GameObject::setTextureOnPainter(const Texture &texture)
{
    //m_textureIsActiveForPainter = true;
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
}


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
    if(m_objEventHandler != nullptr)
        m_objEventHandler->collisionOccured(this,other);
    m_layerItem.setToLastPos();
    m_collider->setPos(m_layerItem.getPos());
    m_painter->setPos(m_layerItem.getPos());
}
