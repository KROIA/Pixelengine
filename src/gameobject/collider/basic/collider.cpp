#include "collider.h"
/*
ColliderSubscriberList::ColliderSubscriberList()
    :   SubscriberList<ColliderSignal>()
{
    m_emiterCallActive = false;
}


void ColliderSubscriberList::boundingBoxChanged(Collider* sender)
{
    SIGNAL_EMIT_INTERN(boundingBoxChanged,sender);
}*/

unsigned long long Collider::stats_checkIntersectCounter = 0;
unsigned long long Collider::stats_doesIntersectCounter  = 0;
unsigned long long Collider::stats_checkCollisionCounter = 0;
unsigned long long Collider::stats_doesCollideCounter    = 0;
Collider::Collider()
    :   LayerItem()
{
    this->setPosInitial(0,0);
    //m_dummy.setPos(0,0);
    //m_dummy.setSize(0,0);
    m_boundingBoxUpdated = false;
    m_generate_collisionData = false;
    m_stateChanged      = false;

    m_boundingBox_standardColor = Color(255,255,255,255);
    m_boundingBox_intersectingColor = Color(255,100,0,255);
    m_boundingBox_color = &m_boundingBox_standardColor;


    m_hitbox_standardColor = Color(100,100,255,255);
    m_hitbox_intersectingColor = Color(200,200,0,255);

    m_boundingBox.setPos({0,0});
    m_boundingBox.setSize({0,0});
}

Collider::Collider(const Collider &other)
    :   LayerItem()
{
    *this = other;
}

Collider::~Collider()
{

}
const Collider &Collider::operator=(const Collider &other)
{
    LayerItem::operator=(other);
    //this->m_hitboxList      = other.m_hitboxList;
    this->m_shape           = other.m_shape;
  //  this->m_hitBoxListDoesIntersect = other.m_hitBoxListDoesIntersect;
    this->m_hitShapeDoesIntersect = other.m_hitShapeDoesIntersect;
    this->m_boundingBox     = other.m_boundingBox;

    this->m_boundingBoxUpdated = other.m_boundingBoxUpdated;
    this->m_generate_collisionData = other.m_generate_collisionData;
    return *this;
}
void Collider::setPosInitial(const Vector2f &pos)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == pos.x && LayerItem::getY() == pos.y)
        return;
    m_shape.setPos(pos);
    LayerItem::setPosInitial(pos);
    m_stateChanged = true;
    updateBoundingBox();
}
void Collider::setPosInitial(const Vector2i &pos)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == pos.x && LayerItem::getY() == pos.y)
        return;

    m_shape.setPos(Vector2f(pos));
    LayerItem::setPosInitial(pos);
    m_stateChanged = true;
    updateBoundingBox();
}
void Collider::setPosInitial(int x, int y)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == x && LayerItem::getY() == y)
        return;
    m_shape.setPos(Vector2f(x,y));
    LayerItem::setPosInitial(x,y);
    m_stateChanged = true;
    updateBoundingBox();
}
void Collider::setPosInitial(float x, float y)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == x && LayerItem::getY() == y)
        return;
    LayerItem::setPosInitial(x,y);
    m_shape.setPos(Vector2f(x,y));
    m_stateChanged = true;
    updateBoundingBox();
}
void Collider::setPos(const Vector2f &pos)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    if(LayerItem::getPos() == pos)
        return;
  /*  Vector2f deltaPos = pos - LayerItem::getPos();
    m_boundingBox.move(deltaPos);
    m_shape.move(deltaPos);*/
    m_shape.setPos(pos);

   /* Vector2f deltaPos = pos - LayerItem::getPos();
    m_boundingBox.setPos(m_boundingBox.getPos() + deltaPos);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setPos(m_hitboxList[i].getPos() + deltaPos);
    }*/
    LayerItem::setPos(pos);
    m_stateChanged = true;
    updateBoundingBox();
}
void Collider::setPos(const Vector2i &pos)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    setPos(Vector2f(pos));
}
void Collider::setX(int x)
{
    this->setX(float(x));
}
void Collider::setY(int y)
{
    this->setY(float(y));
}
void Collider::setX(float x)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    Vector2f deltaPos(x - LayerItem::getX(),0);
    m_boundingBox.move(deltaPos);
    m_shape.move(deltaPos);
  /*  if(LayerItem::getX() == x)
        return;


    float deltaX = x - LayerItem::getX();
    m_boundingBox.setX(m_boundingBox.getPos().x + deltaX);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setX(m_hitboxList[i].getPos().x + deltaX);
    }
    LayerItem::setX(x);
    m_stateChanged = true;*/
}
void Collider::setY(float y)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    Vector2f deltaPos(0,y - LayerItem::getY());
    m_boundingBox.move(deltaPos);
    m_shape.move(deltaPos);
   /* if(LayerItem::getX() == y)
        return;
    float deltaY = y - LayerItem::getY();
    m_boundingBox.setY(m_boundingBox.getPos().y + deltaY);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setY(m_hitboxList[i].getPos().y + deltaY);
    }
    LayerItem::setY(y);
    m_stateChanged = true;*/
}


const AABB &Collider::getBoundingBox() const
{
    return m_boundingBox;
}


void Collider::reserve(const size_t &amount)
{
    m_shape.reserve(amount);
    //m_hitBoxListDoesIntersect.reserve(amount);
}
void Collider::addVertex(Vector2f vertex)
{
    m_shape.addVertex(vertex);
    updateBoundingBox();
}
void Collider::setShape(const Shape &shape)
{
    m_shape = shape;
    updateBoundingBox();
}
const Shape &Collider::getShape() const
{
    return m_shape;
}

/*void Collider::addHitbox(const RectF &box)
{
    COLLIDER_FUNCTION(profiler::colors::Red100);
    m_boundingBoxUpdated = false;
    m_hitboxList.push_back(box);
    m_hitboxList[m_hitboxList.size()-1].setPos(box.getPos() + LayerItem::getPos());
    m_hitBoxListDoesIntersect.push_back(false);
    updateBoundingBox();
}

void Collider::addHitbox(const vector<RectF> &boxList)
{
    COLLIDER_FUNCTION(profiler::colors::Red100);
    m_boundingBoxUpdated = false;
    m_hitboxList.reserve(m_hitboxList.size()+boxList.size());
    m_hitBoxListDoesIntersect.reserve(m_hitBoxListDoesIntersect.size()+boxList.size());
    for(size_t i=0; i<boxList.size(); i++)
    {
        this->addHitbox(boxList[i]);
    }
    updateBoundingBox();
}
void Collider::addHitbox(const RectI &box)
{
    COLLIDER_FUNCTION(profiler::colors::Red100);
    m_boundingBoxUpdated = false;
    m_hitboxList.push_back(RectF(box.getPos().x,box.getPos().y,box.getSize().x,box.getSize().y));
    m_hitboxList[m_hitboxList.size()-1].setPos(Vector2f(box.getPos()) + LayerItem::getPos());
    m_hitBoxListDoesIntersect.push_back(false);
    updateBoundingBox();
}
void Collider::addHitbox(const vector<RectI> &boxList)
{
    COLLIDER_FUNCTION(profiler::colors::Red100);
    m_boundingBoxUpdated = false;
    m_hitboxList.reserve(m_hitboxList.size()+boxList.size());
    m_hitBoxListDoesIntersect.reserve(m_hitBoxListDoesIntersect.size()+boxList.size());
    for(size_t i=0; i<boxList.size(); i++)
    {
        this->addHitbox(boxList[i]);
    }
    updateBoundingBox();
}

const RectF &Collider::getHitbox(const unsigned int &index) const
{
    if(index < m_hitboxList.size())
        return m_hitboxList[index];
    return m_dummy;
}

const vector<RectF> &Collider::getHitbox() const
{
    return m_hitboxList;
}*/

const Shape &Collider::getHitboxShape() const
{
    return m_shape;
}
bool Collider::intersectsBoundingBox(const Collider *other)
{
    COLLIDER_FUNCTION(profiler::colors::Red200);
    /*if(LayerItem::getLastPos()       == LayerItem::getPos()      && other.LayerItem::getLastPos()      == other.LayerItem::getPos() &&
       LayerItem::getLastRotation()  == LayerItem::getRotation() && other.LayerItem::getLastRotation() == other.LayerItem::getRotation())
        return false; // Beide Objekete haben sicht nicht bewegt -> sollte keine Kollision geben*/

    bool intersects = AABB::intersects(this->m_boundingBox,other->m_boundingBox);
    stats_checkIntersectCounter += 1;
    if(intersects)
    {
        m_boundingBox_color = &m_boundingBox_intersectingColor;
        stats_doesIntersectCounter++;
    }
    return intersects;
}

bool Collider::collides(Collider *other)
{
    COLLIDER_FUNCTION(profiler::colors::Red300);
    /*if(LayerItem::getLastPos()       == LayerItem::getPos()      && other.LayerItem::getLastPos()      == other.LayerItem::getPos() &&
       LayerItem::getLastRotation()  == LayerItem::getRotation() && other.LayerItem::getLastRotation() == other.LayerItem::getRotation())
        return false; // Beide Objekete haben sicht nicht bewegt -> sollte keine Kollision geben*/

    /*COLLIDER_BLOCK("for(size_t x=0; x<this->m_hitboxList.size(); x++)",profiler::colors::Red400);
    for(size_t x=0; x<this->m_hitboxList.size(); x++)
    {
        COLLIDER_BLOCK("for(size_t y=0; y<other.m_hitboxList.size(); y++)",profiler::colors::Red500);
        for(size_t y=0; y<other->m_hitboxList.size(); y++)
        {
            COLLIDER_BLOCK("this->m_hitboxList[x].intersects(other.m_hitboxList[y])",profiler::colors::Red600);
            //Vector::Func2f colliderFunc;
            if(this->m_hitboxList[x].intersects(other->m_hitboxList[y]))
            {
                stats_checkCollisionCounter += this->m_hitboxList[x].stats_intersectionCheckCounter;
                stats_doesCollideCounter++;
                m_hitBoxListDoesIntersect[x] = true;
                if(m_generate_collisionData)
                    m_collisionData = this->m_hitboxList[x].getColliderData();
                //m_colliderVector.push_back(colliderFunc);
                return true;
            }
            stats_checkCollisionCounter++;
            COLLIDER_END_BLOCK;
        }
        COLLIDER_END_BLOCK;
    }
    COLLIDER_END_BLOCK;*/
    COLLIDER_BLOCK("check collision with shapes",profiler::colors::Red400);
    if(this->m_shape.checkForCollision(other->m_shape))
    {

        Vector2f deltaPos = other->m_shape.getPos() - other->LayerItem::getPos();
        //qDebug()<<deltaPos.x<<" "<<deltaPos.y;
        Shape::resolveCollision(this->m_shape,other->m_shape);
        //this->setPos(m_shape.getPos());
        //other->setPos(other->m_shape.getPos());


        deltaPos = m_shape.getPos() - LayerItem::getPos();
        m_boundingBox.move(deltaPos);
        //m_shape.move(deltaPos);
        LayerItem::setPos(m_shape.getPos());
        m_stateChanged = true;

        deltaPos = other->m_shape.getPos() - other->LayerItem::getPos();
        other->m_boundingBox.move(deltaPos);
        //other->m_shape.move(deltaPos);
        other->LayerItem::setPos(other->m_shape.getPos());
        other->m_stateChanged = true;
        //qDebug()<<deltaPos.x<<" "<<deltaPos.y;

        return true;
    }
    return false;
   // COLLIDER_END_BLOCK;
   // return false;
}
void Collider::tick()
{
    m_boundingBox_color = &m_boundingBox_standardColor;
    m_hitShapeDoesIntersect = false;
   /* for(size_t i=0; i<m_hitBoxListDoesIntersect.size(); i++)
    {
        m_hitBoxListDoesIntersect[i] = false;
        if(m_generate_collisionData)
        {
            m_hitboxList[i].clearColliderData();
        }
    }
    m_collisionData.clear();*/
    //m_collisionData.clear();
    //m_colliderVector.clear();
    //m_colliderVector.reserve(10);
}
void Collider::erase(size_t index)
{
    COLLIDER_FUNCTION(profiler::colors::Red700);
    m_shape.removeVertex(index);
  //  m_hitboxList.erase(m_hitboxList.begin()+index);
  //  m_hitBoxListDoesIntersect.erase(m_hitBoxListDoesIntersect.begin()+index);
    this->setBoundingBox();
}
void Collider::clear()
{
    COLLIDER_FUNCTION(profiler::colors::Red800);
    m_boundingBoxUpdated = false;
    m_shape.clear();
   // m_hitboxList.clear();
   // m_hitBoxListDoesIntersect.clear();
    this->setBoundingBox();
}
const bool &Collider::isBoundingBoxUpdated() const
{
    return m_boundingBoxUpdated;
}
void Collider::updateBoundingBox()
{
    COLLIDER_FUNCTION(profiler::colors::Red900);
    this->setBoundingBox();
}
void Collider::setBoundingBox()
{
    COLLIDER_FUNCTION(profiler::colors::Red900);
    setBoundingBox(m_shape.getFrame());
}
void Collider::setBoundingBox(const AABB &box)
{
    COLLIDER_FUNCTION(profiler::colors::RedA100);
    m_boundingBox = box;
    m_boundingBoxUpdated = true;
    m_stateChanged = true;
   // m_colliderSubscriber.boundingBoxChanged(this);
    SIGNAL_EMIT(Collider,boundingBoxChanged)
}

/*void Collider::setBoundingBox(const int &x,const int &y,
                              const int &width,const int &height)
{
    COLLIDER_FUNCTION(profiler::colors::RedA100);
    m_boundingBox.setPos({float(x),float(y)});
    m_boundingBox.setSize({float(width),float(height)});
    m_boundingBoxUpdated = true;
    m_stateChanged = true;
  //  m_colliderSubscriber.boundingBoxChanged(this);
    SIGNAL_EMIT(Collider,boundingBoxChanged)
}
*/

/*size_t Collider::getHitboxAmount() const
{
    return m_hitboxList.size();
}*/
float Collider::getRotation() const
{
    return m_rotation;
}
void Collider::setRotation(float deg)
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    if(m_rotation != deg)
        this->internalRotate(Vector2f(LayerItem::getPos()),deg - m_rotation);
    m_rotation = deg;
}
void Collider::rotate(float deg)
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(LayerItem::getPos(),deg);
}
void Collider::rotate_90()
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(Vector2f(LayerItem::getPos()),90);
}
void Collider::rotate_180()
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(Vector2f(LayerItem::getPos()),180);
}
void Collider::rotate_270()
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(Vector2f(LayerItem::getPos()),-90);
}
void Collider::rotate(const Vector2f &rotationPoint,float deg)
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(rotationPoint,deg);
}
void Collider::setRotation(const Vector2f &rotationPoint,float deg)
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    if(m_rotation != deg)
        this->internalRotate(rotationPoint,deg - m_rotation);
    m_rotation = deg;
}
void Collider::rotate_90(const Vector2f &rotationPoint)
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(rotationPoint,90);
}
void Collider::rotate_180(const Vector2f &rotationPoint)
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(rotationPoint,180);
}
void Collider::rotate_270(const Vector2f &rotationPoint)
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(rotationPoint,-90);
}

void Collider::setHitboxFromTexture(const Texture *texture)
{
    COLLIDER_FUNCTION(profiler::colors::RedA400);
    this->clear();
    qDebug()<< "setHitboxFromTexture(): not implemented with Shapecollider";
    //this->addHitbox(texture->getRects());
}
VertexPath* Collider::getDrawableBoundingBox()
{
    return m_boundingBox.getDrawable(*m_boundingBox_color);
}
void Collider::setColor_boundingBox_noIntersection(const Color &color)
{
    m_boundingBox_standardColor = color;
}
void Collider::setColor_boundingBox_intersecting(const Color &color)
{
    m_boundingBox_intersectingColor = color;
}
void Collider::setColor_hitBox_noCollision(const Color &color)
{
    m_hitbox_standardColor = color;
}
void Collider::setColor_hitBox_colliding(const Color &color)
{
    m_hitbox_intersectingColor = color;
}
const Color &Collider::getColor_boundingBox_noIntersection() const
{
    return m_boundingBox_standardColor;
}
const Color &Collider::getColor_boundingBox_intersecting() const
{
    return m_boundingBox_intersectingColor;
}
const Color &Collider::getColor_hitBox_noCollision() const
{
    return m_hitbox_standardColor;
}
const Color &Collider::getColor_hitBox_colliding() const
{
    return m_hitbox_intersectingColor;
}
void Collider::generateCollisionData(bool enable)
{
    m_generate_collisionData = enable;
    qDebug()<< "generateCollisionData(): not implemented with Shapecollider";
    /*for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].generateColliderData(enable);
    }*/
}
/*vector<VertexPath*> Collider::getDrawableHitBox()
{
    vector<VertexPath*> list;
    list.reserve(m_hitboxList.size());
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        list.push_back(m_hitboxList[i].getDrawable(m_hitBoxListDoesIntersect[i] ? m_hitbox_intersectingColor : m_hitbox_standardColor));
    }
    return list;
}*/
VertexPath* Collider::getDrawableHitBox()
{
    return m_shape.getDrawable(m_hitShapeDoesIntersect ? m_hitbox_intersectingColor : m_hitbox_standardColor);
}
vector<VertexPath*> Collider::getDrawableColliderVector()
{
    /*vector<VertexPath> list;
    list.reserve(m_colliderVector.size());
    for(size_t i=0; i<m_colliderVector.size(); i++)
    {
        list.push_back(Vector::getDrawableVector(this->getPos(),m_colliderVector[i].getPoint(),sf::Color(255,0,0)));
        //list.push_back(Vector::getDrawableVectorFunc(Vector2f(0,0),m_colliderVector[i],m_colliderVector[i].scalar));
    }*/
    return m_collisionData;
}
void Collider::resetStateChanged()
{
    m_stateChanged = false;
}
bool Collider::stateChanged() const
{
    return m_stateChanged;
}

/*void Collider::subscribe_ColliderSignal(ColliderSignal *subscriber)
{
    if(subscriber == nullptr)
        return;
    m_colliderSubscriber.insert(subscriber);
}
void Collider::unsubscribe_ColliderSignal(ColliderSignal *subscriber)
{
    m_colliderSubscriber.erase(subscriber);
}
void Collider::unsubscribeAll_ColliderSignal()
{
    m_colliderSubscriber.clear();
}
*/
void Collider::stats_reset()
{
    stats_checkIntersectCounter = 0;
    stats_doesIntersectCounter  = 0;
    stats_checkCollisionCounter = 0;
    stats_doesCollideCounter    = 0;
}

void Collider::internalRotate(const Vector2f &rotPoint,const float &deg)
{
    COLLIDER_FUNCTION(profiler::colors::RedA200);
    if(deg <= 0.00001 && deg >= -0.00001)
        return;
   /* for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        COLLIDER_BLOCK("internalRotate Obj",profiler::colors::RedA200);
        m_hitboxList[i].rotate(rotPoint,deg);
    }*/
    m_shape.rotate(rotPoint,deg);
    m_rotation += deg;
    m_rotation = float(int(m_rotation*1000) % int(360 *1000))/1000.f;
    this->updateBoundingBox();
}
