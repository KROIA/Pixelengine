#include "collider.h"

ColliderSubscriberList::ColliderSubscriberList()
    :   SubscriberList<ColliderSignal>()
{
    m_emiterCallActive = false;
}


void ColliderSubscriberList::boundingBoxChanged(Collider* sender)
{
    EMIT_SIGNAL(boundingBoxChanged,sender);
}

unsigned long long Collider::stats_checkIntersectCounter = 0;
unsigned long long Collider::stats_doesIntersectCounter  = 0;
unsigned long long Collider::stats_checkCollisionCounter = 0;
unsigned long long Collider::stats_doesCollideCounter    = 0;
Collider::Collider()
    :   LayerItem()
{
    this->setPosInitial(0,0);
    m_dummy.setPos(0,0);
    m_dummy.setSize(0,0);
    m_boundingBoxUpdated = false;
    m_generate_collisionData = false;
    m_stateChanged      = false;

    m_boundingBox_standardColor = Color(255,255,255,255);
    m_boundingBox_intersectingColor = Color(255,100,0,255);
    m_boundingBox_color = &m_boundingBox_standardColor;


    m_hitbox_standardColor = Color(100,100,255,255);
    m_hitbox_intersectingColor = Color(200,200,0,255);
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
    this->m_hitboxList      = other.m_hitboxList;
    this->m_hitBoxListDoesIntersect = other.m_hitBoxListDoesIntersect;
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
    LayerItem::setPosInitial(pos);
    m_stateChanged = true;
}
void Collider::setPosInitial(const Vector2i &pos)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == pos.x && LayerItem::getY() == pos.y)
        return;
    LayerItem::setPosInitial(pos);
    m_stateChanged = true;
}
void Collider::setPosInitial(int x, int y)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == x && LayerItem::getY() == y)
        return;
    LayerItem::setPosInitial(x,y);
    m_stateChanged = true;
}
void Collider::setPosInitial(float x, float y)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == x && LayerItem::getY() == y)
        return;
    LayerItem::setPosInitial(x,y);
    m_stateChanged = true;
}
void Collider::setPos(const Vector2f &pos)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    if(LayerItem::getPos() == pos)
        return;
    Vector2f deltaPos = pos - LayerItem::getPos();
    m_boundingBox.setPos(m_boundingBox.getPos() + deltaPos);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setPos(m_hitboxList[i].getPos() + deltaPos);
    }
    LayerItem::setPos(pos);
    m_stateChanged = true;
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
    if(LayerItem::getX() == x)
        return;
    float deltaX = x - LayerItem::getX();
    m_boundingBox.setX(m_boundingBox.getPos().x + deltaX);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setX(m_hitboxList[i].getPos().x + deltaX);
    }
    LayerItem::setX(x);
    m_stateChanged = true;
}
void Collider::setY(float y)
{
    COLLIDER_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == y)
        return;
    float deltaY = y - LayerItem::getY();
    m_boundingBox.setY(m_boundingBox.getPos().y + deltaY);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setY(m_hitboxList[i].getPos().y + deltaY);
    }
    LayerItem::setY(y);
    m_stateChanged = true;
}


const RectF &Collider::getBoundingBox() const
{
    return m_boundingBox;
}


void Collider::reserve(const size_t &amount)
{
    m_hitboxList.reserve(amount);
    m_hitBoxListDoesIntersect.reserve(amount);
}

void Collider::addHitbox(const RectF &box)
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
}


bool Collider::intersectsBoundingBox(const Collider *other)
{
    COLLIDER_FUNCTION(profiler::colors::Red200);
    /*if(LayerItem::getLastPos()       == LayerItem::getPos()      && other.LayerItem::getLastPos()      == other.LayerItem::getPos() &&
       LayerItem::getLastRotation()  == LayerItem::getRotation() && other.LayerItem::getLastRotation() == other.LayerItem::getRotation())
        return false; // Beide Objekete haben sicht nicht bewegt -> sollte keine Kollision geben*/

    bool intersects = this->m_boundingBox.intersects_fast(other->m_boundingBox);
    stats_checkIntersectCounter += this->m_boundingBox.stats_intersectionCheckCounter;
    if(intersects)
    {
        m_boundingBox_color = &m_boundingBox_intersectingColor;
        stats_doesIntersectCounter++;
    }
    return intersects;
}

bool Collider::collides(const Collider *other)
{
    COLLIDER_FUNCTION(profiler::colors::Red300);
    /*if(LayerItem::getLastPos()       == LayerItem::getPos()      && other.LayerItem::getLastPos()      == other.LayerItem::getPos() &&
       LayerItem::getLastRotation()  == LayerItem::getRotation() && other.LayerItem::getLastRotation() == other.LayerItem::getRotation())
        return false; // Beide Objekete haben sicht nicht bewegt -> sollte keine Kollision geben*/

    COLLIDER_BLOCK("for(size_t x=0; x<this->m_hitboxList.size(); x++)",profiler::colors::Red400);
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
    COLLIDER_END_BLOCK;
    return false;
}
void Collider::tick()
{
    m_boundingBox_color = &m_boundingBox_standardColor;
    for(size_t i=0; i<m_hitBoxListDoesIntersect.size(); i++)
    {
        m_hitBoxListDoesIntersect[i] = false;
        if(m_generate_collisionData)
        {
            m_hitboxList[i].clearColliderData();
        }
    }
    m_collisionData.clear();
    //m_collisionData.clear();
    //m_colliderVector.clear();
    //m_colliderVector.reserve(10);
}
void Collider::erase(const size_t &index)
{
    COLLIDER_FUNCTION(profiler::colors::Red700);
    m_hitboxList.erase(m_hitboxList.begin()+index);
    m_hitBoxListDoesIntersect.erase(m_hitBoxListDoesIntersect.begin()+index);
    this->setBoundingBox();
}
void Collider::clear()
{
    COLLIDER_FUNCTION(profiler::colors::Red800);
    m_boundingBoxUpdated = false;
    m_hitboxList.clear();
    m_hitBoxListDoesIntersect.clear();
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
    setBoundingBox(RectF::getFrame(m_hitboxList));
}
void Collider::setBoundingBox(const RectF &box)
{
    COLLIDER_FUNCTION(profiler::colors::RedA100);
    m_boundingBox = box;
    m_boundingBoxUpdated = true;
    m_stateChanged = true;
    m_colliderSubscriber.boundingBoxChanged(this);
}

void Collider::setBoundingBox(const int &x,const int &y,
                              const int &width,const int &height)
{
    COLLIDER_FUNCTION(profiler::colors::RedA100);
    m_boundingBox.setPos(x,y);
    m_boundingBox.setSize(width,height);
    m_boundingBoxUpdated = true;
    m_stateChanged = true;
    m_colliderSubscriber.boundingBoxChanged(this);
}


size_t Collider::getHitboxAmount() const
{
    return m_hitboxList.size();
}
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
    this->addHitbox(texture->getRects());
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
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].generateColliderData(enable);
    }
}
vector<VertexPath*> Collider::getDrawableHitBox()
{
    vector<VertexPath*> list;
    list.reserve(m_hitboxList.size());
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        list.push_back(m_hitboxList[i].getDrawable(m_hitBoxListDoesIntersect[i] ? m_hitbox_intersectingColor : m_hitbox_standardColor));
    }
    return list;
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
void Collider::subscribe_ColliderSignal(ColliderSignal *subscriber)
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
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        COLLIDER_BLOCK("internalRotate Obj",profiler::colors::RedA200);

       /* Vector2f vec(m_hitboxList[i].getPos().x,m_hitboxList[i].getPos().y);
        Vector2f newPos = Vector::getRotated(vec,rotPoint,deg);


        m_hitboxList[i].setPos(round(newPos.x),round(newPos.y));

        RectF newRect = RectF::rotate(RectF(m_hitboxList[i].getPos().x,m_hitboxList[i].getPos().y,m_hitboxList[i].getSize().x,m_hitboxList[i].getSize().y),deg);

        m_hitboxList[i].setPos(round(newRect.getX()),round(newRect.getY()));
        m_hitboxList[i].setSize(round(newRect.getSize().x),round(newRect.getSize().y));

*/
        /*RectF newRect = RectF::rotate(m_hitboxList[i],rotPoint,deg);

        m_hitboxList[i].setPos(newRect.getPos());
        m_hitboxList[i].setSize(newRect.getSize());*/
        m_hitboxList[i].rotate(rotPoint,deg);
    }
    m_rotation += deg;
    m_rotation = float(int(m_rotation*1000) % int(360 *1000))/1000.f;
    this->updateBoundingBox();
}
