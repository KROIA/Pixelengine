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

}

GameObject::~GameObject()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        delete m_controllerList[i];
    m_controllerList.clear();
    delete m_collider;
    delete m_painter;
    delete m_hitboxPainter;
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
    return *this;
}
void GameObject::checkEvent()
{
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->checkEvent();
}
void GameObject::tick(const Point &direction)
{
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
        event_hasCollision(collided[0]);
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
    m_painter->setPos(m_layerItem.getPos());
    m_hitboxPainter->setPos(m_layerItem.getPos());
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
    m_collider->setHitboxFromTexture(m_texture);
}
void GameObject::setHitboxFromTexture(const Texture &texture)
{
    m_collider->setHitboxFromTexture(&texture);
}
void GameObject::setHitboxVisibility(const bool &isVisible)
{
    if(isVisible)
    {
        HitboxPainter::makeVisibleCollider(m_collider,m_hitboxPainter);
    }
    m_hitboxPainter->setVisibility(isVisible);
}
const bool &GameObject::isHitboxVisible() const
{
    return m_hitboxPainter->isVisible();
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
    m_painter->setTexture(m_texture);
}
void GameObject::setTextureOnPainter(const Texture &texture)
{
    m_painter->setTexture(&texture);
}


void GameObject::setProperty(const Property::Property &property)
{
    m_property = property;
}
const Property::Property &GameObject::getProperty() const
{
    return m_property;
}
void GameObject::event_hasCollision(GameObject *other)
{
    if(m_objEventHandler != nullptr)
        m_objEventHandler->collisionOccured(this,other);
    m_layerItem.setToLastPos();
    m_collider->setPos(m_layerItem.getPos());
    m_painter->setPos(m_layerItem.getPos());
}
