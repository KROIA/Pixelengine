#include "gameobject.h"
#include "gameObjectEventHandler.h"

GameObject::GameObject()
{
    this->addController(new Controller());
    m_collider              = new Collider();
    m_painter               = nullptr;
    m_objEventHandler       = nullptr;
    //m_rotationDeg           = 90; // 90 deg
    showHitbox(false);
    m_layerItem.setRotationInitial(0);
}
GameObject::GameObject(const GameObject &other)
{
    this->addController(new Controller());
    m_collider              = new Collider();
    m_painter               = nullptr;
    m_objEventHandler       = nullptr;

    *this = other;
    showHitbox(false);
}
GameObject::GameObject(Controller *controller,
                       Collider   *collider,
                       Painter    *painter)
{
    this->addController(controller);
    this->setCollider(collider);
    this->setPainter(painter);
    m_objEventHandler   = nullptr;
    //m_rotationDeg       = 90; // 90 deg
    showHitbox(false);
    m_layerItem.setRotationInitial(0);
}

GameObject::~GameObject()
{
    removeText();
    clearController();
    delete m_collider;
    if(m_painter != nullptr)
        delete m_painter;
}
const GameObject &GameObject::operator=(const GameObject &other)
{
    this->m_controllerList      = other.m_controllerList;
    *this->m_collider           = *other.m_collider;
    this->m_painter             = other.m_painter;
    this->m_property            = other.m_property;
    this->m_objEventHandler     = other.m_objEventHandler;
    //this->m_rotationDeg         = other.m_rotationDeg;

    return *this;
}
void GameObject::checkEvent()
{
    EASY_FUNCTION(profiler::colors::Green);
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
void GameObject::preRun()
{
    EASY_FUNCTION("GameObject::preRun()",profiler::colors::Green300);
}
void GameObject::tick(const Vector2i &direction)
{
    EASY_FUNCTION(profiler::colors::Green300);
    m_layerItem.swapPosToLastPos();

    if(direction.x > 0)
    {
        m_collider->tick();
        EASY_BLOCK("for(size_t i=0; i<m_controllerList.size(); i++)",profiler::colors::Green300);
        for(size_t i=0; i<m_controllerList.size(); i++)
        {
            if(m_controllerList[i]->getMovingMode() == Controller::MovingMode::override)
                m_movementCoordinator.clearMovement();
            m_movementCoordinator.addMovement(m_controllerList[i]->getMovingVector());
            m_controllerList[i]->tick(); // Clears the movingVector
        }
        m_movementCoordinator.calculateMovement();
        m_layerItem.move(Vector2f(m_movementCoordinator.getMovingVector_X(),0));
        m_collider->setRotation(m_layerItem.getRotation());
        EASY_END_BLOCK;
    }
    else
    {
        m_layerItem.move(Vector2f(0,m_movementCoordinator.getMovingVector_Y()));

        //emit signal
        if(m_ObjSubscriberList.size() > 0)
            if(Vector::length(m_movementCoordinator.getMovingVector()) != 0)
                m_ObjSubscriberList.moved(this,m_movementCoordinator.getMovingVector());

        m_movementCoordinator.tick();
        m_layerItem.swapRotationToLastRotation();
    }

    m_collider->setPos(m_layerItem.getPos());


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
    m_painter->setPos(m_layerItem.getPos());
    m_painter->setRotation(m_layerItem.getRotation());
    RectF frame = display.getRenderFrame();
    frame.setPos(-frame.getPos());

    if(!frame.intersects_fast(m_painter->getFrame()))
        return;


    m_painter->draw(display);
    if(m_hitboxIsVisible)
    {
        display.addVertexLine(m_collider->getDrawableHitBox());
        display.addVertexLine(m_collider->getDrawableColliderVector());
    }
    if(m_boundingBoxIsVisible)
        display.addVertexLine(m_collider->getDrawableBoundingBox());

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
const GameObjectEventHandler *GameObject::getEventHandler() const
{
    return m_objEventHandler;
}
void GameObject::subscribe(ObjSignal *subscriber)
{
    if(subscriber == nullptr)
        return;
    for(size_t i=0; i<m_ObjSubscriberList.size(); i++)
    {
        if(m_ObjSubscriberList[i] == subscriber)
        {
            return;
        }
    }
    m_ObjSubscriberList.push_back(subscriber);
}
void GameObject::unsubscribe(ObjSignal *subscriber)
{
    for(size_t i=0; i<m_ObjSubscriberList.size(); i++)
    {
        if(m_ObjSubscriberList[i] == subscriber)
        {
            m_ObjSubscriberList.erase(m_ObjSubscriberList.begin()+i);
            return;
        }
    }
}
void GameObject::unsubscribeAll()
{
    m_ObjSubscriberList.clear();
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

void GameObject::setPosInital(const Vector2f &pos)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(pos);
    m_collider->setPosInitial(pos);
    if(m_painter != nullptr)
        m_painter->setPosInitial(pos);
}
void GameObject::setPos(int x,int y)
{
    EASY_FUNCTION(profiler::colors::GreenA700);
    m_layerItem.setPosInitial(x,y);
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
    //m_rotationDeg+=deg;
   // if(m_rotationDeg >= 360)
   //     m_rotationDeg = (float)((int)(100*m_rotationDeg)%36000)/100;

    //m_painter->setPos(m_layerItem.getPos());
    //m_collider->setPos(m_layerItem.getPos());

    //m_painter->rotate(deg);
    //m_collider->rotate(deg);
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate(deg);
    m_layerItem.rotate(deg);
}

float GameObject::getRotation() const
{
    return m_layerItem.getRotation();
}
void GameObject::setRotation(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Green);
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(deg);
    m_layerItem.setRotation(deg);
}
void GameObject::rotate_90()
{
    EASY_FUNCTION(profiler::colors::Green);
    rotate(90);
}
void GameObject::rotate_180()
{
    EASY_FUNCTION(profiler::colors::Green);
    rotate(180);
}
void GameObject::rotate_270()
{
    rotate(270);
    EASY_FUNCTION(profiler::colors::Green);
}
void GameObject::setRotation(const Vector2f &rotationPoint,const float &deg)
{
    EASY_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,deg);
    this->setPos(newPos);
    rotate(deg);
}
void GameObject::rotate_90(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,90);
    this->setPos(newPos);
    rotate(90);
}
void GameObject::rotate_180(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,180);
    this->setPos(newPos);
    rotate(180);
}
void GameObject::rotate_270(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::Green);
    Vector2f newPos = Vector::getRotated(Vector2f(this->getPos()),rotationPoint,270);
    this->setPos(newPos);
    rotate(270);
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

void GameObject::setHitboxFromTexture(const Texture &texture)
{
    EASY_FUNCTION(profiler::colors::Green600);
    m_textureIsActiveForCollider = true;
    m_collider->setHitboxFromTexture(&texture);
}
void GameObject::showHitbox(const bool &isVisible)
{
    EASY_FUNCTION(profiler::colors::Green700);
    m_hitboxIsVisible = isVisible;
    m_collider->generateCollisionData(isVisible);
    showBoundingBox(isVisible);
}
void GameObject::showBoundingBox(bool enable)
{
    m_boundingBoxIsVisible = enable;
}
const bool &GameObject::isHitboxVisible() const
{
    return m_hitboxIsVisible;
}

void GameObject::setVisibility(const bool &isVisible)
{
    m_painter->setVisibility(isVisible);
}
const bool &GameObject::isVisible() const
{
    return m_painter->isVisible();
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
                m_objEventHandler->removingisplayText(text);
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
                m_objEventHandler->removingisplayText(text);
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
            m_objEventHandler->removingisplayText(m_displayTextList[i]);
        delete m_displayTextList[i];
    }
    m_displayTextList.clear();
}

const vector<DisplayText*> &GameObject::getTextList()
{
    return m_displayTextList;
}

void GameObject::markAsTrash(bool isTrash)
{
    m_isTrash = isTrash;
}
bool GameObject::isTrash() const
{
    return m_isTrash;
}


void GameObject::event_hasCollision(vector<GameObject *> other)
{
    EASY_FUNCTION(profiler::colors::Green100);
    if(m_objEventHandler != nullptr)
        m_objEventHandler->collisionOccured(this,other);
    m_layerItem.setToLastPos();
    m_layerItem.setToLastRotation();

    m_collider->setPos(m_layerItem.getPos());
    m_painter->setPos(m_layerItem.getPos());
    m_collider->setRotation(m_layerItem.getRotation());
    m_painter->setRotation(m_layerItem.getRotation());

    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(m_layerItem.getRotation());
}
