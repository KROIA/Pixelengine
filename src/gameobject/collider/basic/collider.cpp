#include "collider.h"

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
    m_rotationDeg = 0;

    m_boundingBox_standardColor = Color(255,255,255,255);
    m_boundingBox_intersectingColor = Color(255,100,0,255);
    m_boundingBox_color = m_boundingBox_standardColor;
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
    this->m_boundingBox     = other.m_boundingBox;

    this->m_boundingBoxUpdated = other.m_boundingBoxUpdated;
    this->m_rotationDeg     = other.m_rotationDeg;
    return *this;
}
void Collider::setPosInitial(const Vector2f &pos)
{
    EASY_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == pos.x && LayerItem::getY() == pos.y)
        return;
    LayerItem::setPosInitial(pos);
}
void Collider::setPosInitial(const Vector2i &pos)
{
    EASY_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == pos.x && LayerItem::getY() == pos.y)
        return;
    LayerItem::setPosInitial(pos);
}
void Collider::setPosInitial(int x, int y)
{
    EASY_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == x && LayerItem::getY() == y)
        return;
    LayerItem::setPosInitial(x,y);
}
void Collider::setPosInitial(float x, float y)
{
    EASY_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == x && LayerItem::getY() == y)
        return;
    LayerItem::setPosInitial(x,y);
}
void Collider::setPos(const Vector2f &pos)
{
    EASY_FUNCTION(profiler::colors::Red);
    if(LayerItem::getPos() == pos)
        return;
    Vector2f deltaPos = pos - LayerItem::getPos();
    m_boundingBox.setPos(m_boundingBox.getPos() + deltaPos);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setPos(m_hitboxList[i].getPos() + deltaPos);
    }
    LayerItem::setPos(pos);
}
void Collider::setPos(const Vector2i &pos)
{
    EASY_FUNCTION(profiler::colors::Red);
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
    EASY_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == x)
        return;
    float deltaX = x - LayerItem::getX();
    m_boundingBox.setX(m_boundingBox.getPos().x + deltaX);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setX(m_hitboxList[i].getPos().x + deltaX);
    }
    LayerItem::setX(x);
}
void Collider::setY(float y)
{
    EASY_FUNCTION(profiler::colors::Red);
    if(LayerItem::getX() == y)
        return;
    float deltaY = y - LayerItem::getY();
    m_boundingBox.setY(m_boundingBox.getPos().y + deltaY);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setY(m_hitboxList[i].getPos().y + deltaY);
    }
    LayerItem::setY(y);
}


const RectF &Collider::getBoundingBox() const
{
    return m_boundingBox;
}


void Collider::reserve(const size_t &amount)
{
    m_hitboxList.reserve(amount);
}

void Collider::addHitbox(const RectF &box)
{
    EASY_FUNCTION(profiler::colors::Red100);
    m_boundingBoxUpdated = false;
    m_hitboxList.push_back(box);
    m_hitboxList[m_hitboxList.size()-1].setPos(box.getPos() + LayerItem::getPos());
    updateBoundingBox();
}

void Collider::addHitbox(const vector<RectF> &boxList)
{
    EASY_FUNCTION(profiler::colors::Red100);
    m_boundingBoxUpdated = false;
    m_hitboxList.reserve(m_hitboxList.size()+boxList.size());
    for(size_t i=0; i<boxList.size(); i++)
    {
        this->addHitbox(boxList[i]);
    }
    updateBoundingBox();
}
void Collider::addHitbox(const RectI &box)
{
    EASY_FUNCTION(profiler::colors::Red100);
    m_boundingBoxUpdated = false;
    m_hitboxList.push_back(RectF(box.getPos().x,box.getPos().y,box.getSize().x,box.getSize().y));
    m_hitboxList[m_hitboxList.size()-1].setPos(Vector2f(box.getPos()) + LayerItem::getPos());
    updateBoundingBox();
}
void Collider::addHitbox(const vector<RectI> &boxList)
{
    EASY_FUNCTION(profiler::colors::Red100);
    m_boundingBoxUpdated = false;
    m_hitboxList.reserve(m_hitboxList.size()+boxList.size());
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


bool Collider::intersectsBoundingBox(const Collider &other)
{
    EASY_FUNCTION(profiler::colors::Red200);
    if(LayerItem::getLastPos() == LayerItem::getPos() && other.LayerItem::getLastPos() == other.LayerItem::getPos())
        return false; // Beide Objekete haben sicht nicht bewegt -> sollte keine Kollision geben

    bool intersects = this->m_boundingBox.intersects(other.m_boundingBox);
    stats_checkIntersectCounter++;
    if(intersects)
    {
        m_boundingBox_color = m_boundingBox_intersectingColor;
        stats_doesIntersectCounter++;
    }
    return intersects;
}

bool Collider::collides(const Collider &other) const
{
    EASY_FUNCTION(profiler::colors::Red300);
    if(LayerItem::getLastPos() == LayerItem::getPos() && other.LayerItem::getLastPos() == other.LayerItem::getPos())
        return false; // Beide Objekete haben sicht nicht bewegt -> sollte keine Kollision geben

    EASY_BLOCK("for(size_t x=0; x<this->m_hitboxList.size(); x++)",profiler::colors::Red400);
    for(size_t x=0; x<this->m_hitboxList.size(); x++)
    {
        EASY_BLOCK("for(size_t y=0; y<other.m_hitboxList.size(); y++)",profiler::colors::Red500);
        for(size_t y=0; y<other.m_hitboxList.size(); y++)
        {
            EASY_BLOCK("this->m_hitboxList[x].intersects(other.m_hitboxList[y])",profiler::colors::Red600);
            if(this->m_hitboxList[x].intersects(other.m_hitboxList[y]))
            {
                stats_checkCollisionCounter++;
                stats_doesCollideCounter++;
                return true;
            }
            stats_checkCollisionCounter++;
            EASY_END_BLOCK;
        }
        EASY_END_BLOCK;
    }
    EASY_END_BLOCK;
    return false;
}
void Collider::tick()
{
    m_boundingBox_color = m_boundingBox_standardColor;
}
void Collider::erase(const size_t &index)
{
    EASY_FUNCTION(profiler::colors::Red700);
    m_hitboxList.erase(m_hitboxList.begin()+index);
    this->setBoundingBox();
}
void Collider::clear()
{
    EASY_FUNCTION(profiler::colors::Red800);
    m_boundingBoxUpdated = false;
    m_hitboxList.clear();
    this->setBoundingBox();
}
const bool &Collider::isBoundingBoxUpdated() const
{
    return m_boundingBoxUpdated;
}
void Collider::updateBoundingBox()
{
    EASY_FUNCTION(profiler::colors::Red900);
    this->setBoundingBox();
}
void Collider::setBoundingBox()
{
    EASY_FUNCTION(profiler::colors::Red900);
    setBoundingBox(RectF::getFrame(m_hitboxList));
}
void Collider::setBoundingBox(const RectF &box)
{
    EASY_FUNCTION(profiler::colors::RedA100);
    m_boundingBox = box;
    m_boundingBoxUpdated = true;
}

void Collider::setBoundingBox(const int &x,const int &y,
                              const int &width,const int &height)
{
    EASY_FUNCTION(profiler::colors::RedA100);
    m_boundingBox.setPos(x,y);
    m_boundingBox.setSize(width,height);
    m_boundingBoxUpdated = true;
}


size_t Collider::getHitboxAmount() const
{
    return m_hitboxList.size();
}
float Collider::getRotation() const
{
    return m_rotationDeg*180.f/M_PI;
}
void Collider::setRotation(const float &deg)
{
    EASY_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(Vector2f(LayerItem::getPos()),deg - m_rotationDeg);
}
void Collider::rotate_90()
{
    EASY_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(Vector2f(LayerItem::getPos()),90);
}
void Collider::rotate_180()
{
    EASY_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(Vector2f(LayerItem::getPos()),180);
}
void Collider::rotate_270()
{
    EASY_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(Vector2f(LayerItem::getPos()),-90);
}
void Collider::setRotation(const Vector2f &rotationPoint,const float &deg)
{
    EASY_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(rotationPoint,deg - m_rotationDeg);
}
void Collider::rotate_90(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(rotationPoint,90);
}
void Collider::rotate_180(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(rotationPoint,180);
}
void Collider::rotate_270(const Vector2f &rotationPoint)
{
    EASY_FUNCTION(profiler::colors::RedA200);
    this->internalRotate(rotationPoint,-90);
}

void Collider::setHitboxFromTexture(const Texture *texture)
{
    EASY_FUNCTION(profiler::colors::RedA400);
    this->clear();
    this->addHitbox(texture->getRects());
}
VertexPath Collider::getDrawableBoundingBox()
{
    return m_boundingBox.getDrawable(m_boundingBox_color);
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
    EASY_FUNCTION(profiler::colors::RedA200);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        Vector2f vec(m_hitboxList[i].getPos().x,m_hitboxList[i].getPos().y);
        Vector2f newPos = Vector::rotate(vec,rotPoint,deg);


        m_hitboxList[i].setPos(round(newPos.x),round(newPos.y));

        RectF newRect = RectF::rotate(RectF(m_hitboxList[i].getPos().x,m_hitboxList[i].getPos().y,m_hitboxList[i].getSize().x,m_hitboxList[i].getSize().y),deg);

        m_hitboxList[i].setPos(round(newRect.getX()),round(newRect.getY()));
        m_hitboxList[i].setSize(round(newRect.getSize().x),round(newRect.getSize().y));
    }
    m_rotationDeg += deg;
    m_rotationDeg = float(int(m_rotationDeg*1000) % int(360 *1000))/1000.f;
    this->updateBoundingBox();
}
