#include "gameobject.h"
#include "gameObjectEventHandler.h"
#include "InteractiveGameObject.h"

GameObject::GameObject()
{
    this->addController(new Controller());
    m_collider              = new Collider();
    m_originalCollider      = m_collider;

    m_originalPainter       = new PixelPainter();
    m_painter               = m_originalPainter;
    m_objEventHandler       = nullptr;
    m_thisInteractiveObject = nullptr;
    this->m_visibility                          = true;
    this->m_visibility_collider_hitbox          = false;
    this->m_visibility_collider_boundingBox     = false;
    this->m_visibility_collider_collisionData   = false;
    this->m_visibility_collider_collidingWith   = false;

    m_hasEventsToCheck = false;
    m_isTrash = false;
    m_textureIsActiveForCollider = false;
    //this->m_visibility_chunkMap                 = false;
    //m_rotationDeg           = 90; // 90 deg
    m_layerItem.setRotationInitial(0);
}
GameObject::GameObject(const GameObject &other)
{
    this->addController(new Controller());
    m_collider              = new Collider();
    m_originalCollider      = m_collider;
    m_originalPainter       = new PixelPainter();
    m_painter               = m_originalPainter;
    m_objEventHandler       = nullptr;
    this->m_visibility                          = true;
    this->m_visibility_collider_hitbox          = false;
    this->m_visibility_collider_boundingBox     = false;
    this->m_visibility_collider_collisionData   = false;
    this->m_visibility_collider_collidingWith   = false;
    m_hasEventsToCheck = false;
    m_isTrash = false;
    m_textureIsActiveForCollider = false;
    //this->m_visibility_chunkMap                 = false;
    m_thisInteractiveObject = other.m_thisInteractiveObject;

    *this = other;
}
GameObject::GameObject(Controller *controller,
                       Collider   *collider,
                       Painter    *painter)
{
    this->addController(controller);
    this->setCollider(collider);
    this->setPainter(painter);
    m_objEventHandler                           = nullptr;
    m_thisInteractiveObject                     = nullptr;
    this->m_visibility                          = true;
    this->m_visibility_collider_hitbox          = false;
    this->m_visibility_collider_boundingBox     = false;
    this->m_visibility_collider_collisionData   = false;
    this->m_visibility_collider_collidingWith   = false;
    m_hasEventsToCheck = false;
    m_isTrash = false;
    m_textureIsActiveForCollider = false;
    //this->m_visibility_chunkMap                 = false;
    //m_rotationDeg       = 90; // 90 deg
    m_layerItem.setRotationInitial(0);
}

GameObject::~GameObject()
{
    removeText();
    clearController();
    delete m_originalCollider;
    delete m_originalPainter;
   // if(m_painter != nullptr)
   //     delete m_painter;
}
const GameObject &GameObject::operator=(const GameObject &other)
{
    this->m_controllerList      = other.m_controllerList;
    *this->m_collider           = *other.m_collider;
    this->m_painter             = other.m_painter;
    this->m_property            = other.m_property;
    this->m_objEventHandler     = other.m_objEventHandler;
    this->m_thisInteractiveObject = other.m_thisInteractiveObject;
    this->m_visibility          = other.m_visibility;
    this->m_visibility_collider_hitbox         = other.m_visibility_collider_hitbox;
    this->m_visibility_collider_boundingBox    = other.m_visibility_collider_boundingBox;
    this->m_visibility_collider_collisionData  = other.m_visibility_collider_collisionData;
    this->m_visibility_collider_collidingWith  = other.m_visibility_collider_collidingWith;
    this->m_isTrash = other.m_isTrash;
    this->m_textureIsActiveForCollider = other.m_textureIsActiveForCollider;
    //this->m_visibility_chunkMap                = other.m_visibility_chunkMap;
    //this->m_rotationDeg         = other.m_rotationDeg;

    return *this;
}
void GameObject::checkEvent()
{
    EASY_FUNCTION(profiler::colors::Green);
    for(size_t i=0; i<m_controllerList.size(); i++)
        if(m_controllerList[i]->hasEventsToCheck())
            m_controllerList[i]->checkEvent();
}
bool GameObject::hasEventsToCheck() const
{
    return m_hasEventsToCheck;
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
    this->setPosInital(m_layerItem.getPos());
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
        if(m_objSubscriberList.size() > 0)
            if(Vector::length(m_movementCoordinator.getMovingVector()) != 0)
                m_objSubscriberList.moved(this,m_movementCoordinator.getMovingVector());

        m_movementCoordinator.tick();
        m_layerItem.swapRotationToLastRotation();
        m_painter->setPos(m_layerItem.getPos());
        m_painter->setRotation(m_layerItem.getRotation());
    }

    m_collider->setPos(m_layerItem.getPos());


}


unsigned int GameObject::checkCollision(const vector<GameObject*> &other)
{
    EASY_FUNCTION(profiler::colors::Green400);
    m_collidedObjects = GameObject::getCollidedObjects(this, m_collider, other);
    if(m_collidedObjects.size() > 0)
    {
        event_hasCollision(m_collidedObjects);
    }
    return m_collidedObjects.size();
}
unsigned int GameObject::checkCollision(const vector<vector<GameObject*> >&other)
{
    EASY_FUNCTION(profiler::colors::Green500);
    vector<GameObject*> collided;
    for(size_t i=0; i<other.size(); i++)
    {
        m_collidedObjects = GameObject::getCollidedObjects(this, m_collider, other[i]);
        collided.reserve(collided.size() + m_collidedObjects.size());
        for(size_t j=0; j<m_collidedObjects.size(); j++)
        {
            collided.push_back(m_collidedObjects[i]);
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
    //collided.reserve(10);
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
    if(!m_visibility)
        return;
    if(m_thisInteractiveObject != nullptr)
    {
        m_thisInteractiveObject->drawObjectTree(display);
    }

    if(m_painter != m_originalPainter)
    {
        m_painter->setPos(m_layerItem.getPos());
        m_painter->setRotation(m_layerItem.getRotation());
        RectF frame = display.getRenderFrame();
        if(!frame.intersects_fast(m_painter->getFrame()))
            return;
        m_painter->draw(display);
    }



    if(m_visibility_collider_boundingBox)
        display.addVertexLine(m_collider->getDrawableBoundingBox());
    if(m_visibility_collider_hitbox)
        display.addVertexLine(m_collider->getDrawableHitBox());    
    if(m_visibility_collider_collisionData)
        display.addVertexLine(m_collider->getDrawableColliderVector());
    if(m_visibility_collider_collidingWith)
        for(size_t i=0; i<m_collidedObjects.size(); i++)
            display.addVertexLine(m_collidedObjects[i]->getCollider().getBoundingBox().getDrawable(Color(255,100,0)));




}
void GameObject::subscribeToDisplay(PixelDisplay &display)
{
    m_painter->subscribeToDisplay(display);
}
void GameObject::unsubscribeToDisplay(PixelDisplay &display)
{
    m_painter->unsubscribeToDisplay(display);
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
void GameObject::setChunkID(const ChunkID &chunkID)
{
    clearChunkList();
    m_chunkIDList.push_back(chunkID);
}
void GameObject::setChunkID(const vector<ChunkID> &chunkIDList)
{
    m_chunkIDList = chunkIDList;
}
void GameObject::addChunkID(const ChunkID &chunkID)
{
    m_chunkIDList.push_back(chunkID);
}
void GameObject::removeChunkID(const ChunkID &chunkID)
{
    for(size_t i=0; i<m_chunkIDList.size(); i++)
    {
        if(m_chunkIDList[i] == chunkID)
        {
            m_chunkIDList.erase(m_chunkIDList.begin() + i);
            i--;
        }
    }
}
void GameObject::clearChunkList()
{
    m_chunkIDList.clear();
    m_chunkIDList.reserve(9);
}
const ChunkID &GameObject::getChunkID() const
{
    if(m_chunkIDList.size() > 0)
        return m_chunkIDList[0];
    else
        return m_constDummy_chunkID;
}
const vector<ChunkID> &GameObject::getChunkIDList() const
{
    return m_chunkIDList;
}
void GameObject::subscribe(ObjSignal *subscriber)
{
    if(subscriber == nullptr)
        return;
    for(size_t i=0; i<m_objSubscriberList.size(); i++)
    {
        if(m_objSubscriberList[i] == subscriber)
        {
            return;
        }
    }
    m_objSubscriberList.push_back(subscriber);
}
void GameObject::unsubscribe(ObjSignal *subscriber)
{
    for(size_t i=0; i<m_objSubscriberList.size(); i++)
    {
        if(m_objSubscriberList[i] == subscriber)
        {
            m_objSubscriberList.erase(m_objSubscriberList.begin()+i);
            return;
        }
    }
}
void GameObject::unsubscribeAll()
{
    m_objSubscriberList.clear();
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
    if(controller->hasEventsToCheck())
        m_hasEventsToCheck = true;
    controller->subscribe(this);
}
void GameObject::clearController()
{
    EASY_FUNCTION(profiler::colors::Green900);
    size_t size = m_controllerList.size();
    for(size_t i=1; i<size; i++)
    {
        m_controllerList[1]->unsubscribe(this);
        delete m_controllerList[1];
        m_controllerList.erase(m_controllerList.begin()+1);
    }
}

void GameObject::setCollider(Collider *collider)
{
    EASY_FUNCTION(profiler::colors::GreenA100);
    if(m_collider == collider || collider == nullptr)
        return;
    //if(m_collider != nullptr)
    //    delete m_collider;
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
   // if(m_painter != nullptr)
   //     delete m_painter;
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
    if((int)(deg*1000) % 360000 == 0)
        return;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->rotate(deg);
    m_layerItem.rotate(deg);
    if(m_objSubscriberList.size() > 0)
        m_objSubscriberList.rotated(this,deg);
}

float GameObject::getRotation() const
{
    return m_layerItem.getRotation();
}
void GameObject::setRotation(const float &deg)
{
    EASY_FUNCTION(profiler::colors::Green);
    if(m_layerItem.getRotation() == deg)
        return;
    float deltaAngle = deg - m_layerItem.getRotation();
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_controllerList[i]->setRotation(deg);
    m_layerItem.setRotation(deg);

    if(m_objSubscriberList.size() > 0)
        m_objSubscriberList.rotated(this,deltaAngle);
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
const RectF &GameObject::getBoundingBox() const
{
    return m_collider->getBoundingBox();
}




void GameObject::setVisibility(bool isVisible)
{
    m_visibility = isVisible;
    m_painter->setVisibility(isVisible);
}
void GameObject::setVisibility_objectTree(bool isVisible)
{
    if(m_thisInteractiveObject != nullptr)
        m_thisInteractiveObject->setVisibility_objectTree(isVisible);
}
/*void GameObject::setVisibility_chunks(bool isVisible)
{
    //m_visibility_chunkMap = isVisible;
    if(m_thisInteractiveObject != nullptr)
        m_thisInteractiveObject->setVisibility_chunks(isVisible);
}
void GameObject::setVisibility_chunk(const ChunkID &id, bool isVisible)
{
    if(m_thisInteractiveObject != nullptr)
        m_thisInteractiveObject->setVisibility_chunk(id,isVisible);
}*/

void GameObject::setVisibility_collider_hitbox(bool isVisible)
{
    m_visibility_collider_hitbox = isVisible;
}
void GameObject::setVisibility_collider_boundingBox(bool isVisible)
{
    m_visibility_collider_boundingBox = isVisible;
}
void GameObject::setVisibility_collider_collisionData(bool isVisible)
{
    m_visibility_collider_collisionData = isVisible;
    m_collider->generateCollisionData(isVisible);
}
void GameObject::setVisibility_collider_isCollidingWith(bool isVisible)
{
    m_visibility_collider_collidingWith = isVisible;
}

bool GameObject::isVisible() const
{
    return m_visibility;
}
bool GameObject::isVisible_objectTree() const
{
    if(m_thisInteractiveObject != nullptr)
        return m_thisInteractiveObject->isVisible_objectTree();
    return false;
}
/*bool GameObject::isVisible_chunks() const
{
   // return m_visibility_chunkMap;
    if(m_thisInteractiveObject != nullptr)
        return m_thisInteractiveObject->isVisible_chunks();
    return false;
}
bool GameObject::isVisible_chunk(const ChunkID &id) const
{
    if(m_thisInteractiveObject != nullptr)
        return m_thisInteractiveObject->isVisible_chunk(id);
    return false;
}*/
bool GameObject::isVisible_collider_hitbox() const
{
    return m_visibility_collider_hitbox;
}
bool GameObject::isVisible_collider_boundingBox() const
{
    return m_visibility_collider_boundingBox;
}
bool GameObject::isVisible_collider_collisionData() const
{
    return m_visibility_collider_collisionData;
}
bool GameObject::isVisible_collider_isCollidingWith() const
{
    return m_visibility_collider_collidingWith;
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
/*void GameObject::setTextSettings(const DisplayText::Settings &settings)
{
    m_textSettings = settings;
}
const DisplayText::Settings &GameObject::getTextSettings() const
{
    return m_textSettings;
}*/
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

void GameObject::markAsTrash(bool isTrash)
{
    m_isTrash = isTrash;
    if(!m_isTrash)
        return;
  /*  if(m_objSubscriberList.size() != 0)
    {
        qDebug() << "GameObject::markAsTrash(bool ["<<isTrash<<"]): Subscriberlist not empty!";
        qDebug() << m_objSubscriberList.size() << " subscriptions are active.";
        for(size_t i=0; i<m_objSubscriberList.size(); i++)
        {
            qDebug() << "Subscriber: ["<<i<<"] \t: "<<m_objSubscriberList[i];
        }
        qDebug() << "Property of this ("<<this<<") Objects is: ";
        qDebug() << this->getProperty().toString().c_str();
    }*/
}
bool GameObject::isTrash() const
{
    return m_isTrash;
}
void GameObject::setThisInteractiveGameObject(InteractiveGameObject *parent)
{
    m_thisInteractiveObject = parent;
}
InteractiveGameObject* GameObject::getThisInteractiveGameObject()
{
    return m_thisInteractiveObject;
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

void GameObject::eventAdded(UserEventHandler *sender,  Event *e)
{
    m_hasEventsToCheck = true;
}
void GameObject::eventRemoved(UserEventHandler *sender,  Event *e)
{
    m_hasEventsToCheck = false;
    for(size_t i=0; i<m_controllerList.size(); i++)
        m_hasEventsToCheck |= m_controllerList[i]->hasEventsToCheck();
}
