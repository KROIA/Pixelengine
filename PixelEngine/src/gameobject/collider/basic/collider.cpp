#include "collider.h"


Collider::Collider()
    :   LayerItem()
{
    this->setPos(0,0);
    m_dummy.setPos(0,0);
    m_dummy.setSize(0,0);
    m_boundingBoxUpdated = false;
    m_rotationRad = 0;
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
    this->m_rotationRad     = other.m_rotationRad;
    return *this;
}

void Collider::setPos(const int &x,const int &y)
{
    if(LayerItem::getX() == x && LayerItem::getY() == y)
        return;
    this->setPos(Point(x,y));
}
void Collider::setPos(const Point &pos)
{
    if(LayerItem::getPos() == pos)
        return;
    Point deltaPos(pos.getX() - LayerItem::getX(),
                   pos.getY() - LayerItem::getY());
    m_boundingBox.setPos(m_boundingBox.getX() + deltaPos.getX(),
                         m_boundingBox.getY() + deltaPos.getY());
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setPos(m_hitboxList[i].getX() + deltaPos.getX(),
                               m_hitboxList[i].getY() + deltaPos.getY());
    }
    LayerItem::setPos(pos);
}
void Collider::setX(const int &x)
{
    if(LayerItem::getX() == x)
        return;
    int deltaX = x - LayerItem::getX();
    m_boundingBox.setX(m_boundingBox.getPos().getX() + deltaX);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setX(m_hitboxList[i].getX() + deltaX);
    }
    LayerItem::setX(x);
}
void Collider::setY(const int &y)
{
    if(LayerItem::getX() == y)
        return;
    int deltaY = y - LayerItem::getY();
    m_boundingBox.setY(m_boundingBox.getPos().getY() + deltaY);
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        m_hitboxList[i].setY(m_hitboxList[i].getY() + deltaY);
    }
    LayerItem::setY(y);
}


const Rect &Collider::getBoundingBox() const
{
    return m_boundingBox;
}

void Collider::reserve(const size_t &amount)
{
    m_hitboxList.reserve(amount);
}

void Collider::addHitbox(const Rect &box)
{
    m_boundingBoxUpdated = false;
    m_hitboxList.push_back(box);
    m_hitboxList[m_hitboxList.size()-1].setPos(box.getPos().getX()+LayerItem::getX(),
                                               box.getPos().getY()+LayerItem::getY());
}

void Collider::addHitbox(const vector<Rect> &boxList)
{
    m_boundingBoxUpdated = false;
    m_hitboxList.reserve(m_hitboxList.size()+boxList.size());
    for(size_t i=0; i<boxList.size(); i++)
    {
        this->addHitbox(boxList[i]);
    }
}


const Rect &Collider::getHitbox(const unsigned int &index) const
{
    if(index < m_hitboxList.size())
        return m_hitboxList[index];
    return m_dummy;
}

const vector<Rect> &Collider::getHitbox() const
{
    return m_hitboxList;
}


bool Collider::intersectsBoundingBox(const Collider &other) const
{
    if(LayerItem::getLastPos() == LayerItem::getPos() && other.LayerItem::getLastPos() == other.LayerItem::getPos())
        return false; // Beide Objekete haben sicht nicht bewegt -> sollte keine Kollision geben

    return this->m_boundingBox.intersects(other.m_boundingBox);
}

bool Collider::collides(const Collider &other) const
{
    if(LayerItem::getLastPos() == LayerItem::getPos() && other.LayerItem::getLastPos() == other.LayerItem::getPos())
        return false; // Beide Objekete haben sicht nicht bewegt -> sollte keine Kollision geben

    for(size_t x=0; x<this->m_hitboxList.size(); x++)
    {
        for(size_t y=0; y<other.m_hitboxList.size(); y++)
        {
            if(this->m_hitboxList[x].intersects(other.m_hitboxList[y]))
            {
                //qDebug() << "this->Hitbox: "<<x<<"\tother.Hitbox: "<<y;
                return true;
            }
        }
    }
    return false;
}
void Collider::erase(const size_t &index)
{
    m_hitboxList.erase(m_hitboxList.begin()+index);
    this->setBoundingBox();
}
void Collider::clear()
{
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
    this->setBoundingBox();
}
void Collider::setBoundingBox()
{
    int minX = this->getMinX();
    int minY = this->getMinY();
    int maxX = this->getMaxX();
    int maxY = this->getMaxY();
    setBoundingBox(minX,minY,maxX-minX+1,maxY-minY+1);
    m_boundingBoxUpdated = true;
}
void Collider::setBoundingBox(const Rect &box)
{
    m_boundingBox = box;
    m_boundingBoxUpdated = true;
}

void Collider::setBoundingBox(const int &x,const int &y,
                              const int &width,const int &height)
{
    m_boundingBox.setPos(x,y);
    m_boundingBox.setSize(width,height);
    m_boundingBoxUpdated = true;
}

int Collider::getMinX()
{
    if(m_hitboxList.size() == 0)
        return 0;
    int minX = m_hitboxList[0].getCornerPoint_TL().getX();
    for(size_t i=1; i<m_hitboxList.size(); i++)
    {
        if(m_hitboxList[i].getCornerPoint_TL().getX() < minX)
            minX = m_hitboxList[i].getCornerPoint_TL().getX();
    }
    return minX;
}
int Collider::getMaxX()
{
    if(m_hitboxList.size() == 0)
        return 0;
    int maxX = m_hitboxList[0].getCornerPoint_BR().getX();
    for(size_t i=1; i<m_hitboxList.size(); i++)
    {
        if(m_hitboxList[i].getCornerPoint_BR().getX() > maxX)
            maxX = m_hitboxList[i].getCornerPoint_BR().getX();
    }
    return maxX;
}
int Collider::getMinY()
{
    if(m_hitboxList.size() == 0)
        return 0;
    int minY = m_hitboxList[0].getCornerPoint_TL().getY();
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        if(m_hitboxList[i].getCornerPoint_TL().getY() < minY)
            minY = m_hitboxList[i].getCornerPoint_TL().getY();
    }
    return minY;
}
int Collider::getMaxY()
{
    if(m_hitboxList.size() == 0)
        return 0;
    int maxY = m_hitboxList[0].getCornerPoint_BL().getY();
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        if(m_hitboxList[i].getCornerPoint_BL().getY() > maxY)
            maxY = m_hitboxList[i].getCornerPoint_BL().getY();
    }
    return maxY;
}
size_t Collider::getHitboxAmount() const
{
    return m_hitboxList.size();
}
double Collider::getRotation() const
{
    return m_rotationRad*180.f/M_PI;
}
void Collider::setRotation(const double &deg)
{
    this->rotate(PointF(this->getX(),this->getY()),(deg*M_PI/180.f) - m_rotationRad);
}
void Collider::rotate_90()
{
    this->rotate(PointF(this->getX(),this->getY()),M_PI_2);
}
void Collider::rotate_180()
{
    this->rotate(PointF(this->getX(),this->getY()),M_PI);
}
void Collider::rotate_270()
{
    this->rotate(PointF(this->getX(),this->getY()),-M_PI_2);
}
void Collider::setRotation(const PointF &rotationPoint,const double &deg)
{
    this->rotate(rotationPoint,(deg*M_PI/180.f) - m_rotationRad);
}
void Collider::rotate_90(const PointF &rotationPoint)
{
    this->rotate(rotationPoint,M_PI_2);
}
void Collider::rotate_180(const PointF &rotationPoint)
{
    this->rotate(rotationPoint,M_PI);
}
void Collider::rotate_270(const PointF &rotationPoint)
{
    this->rotate(rotationPoint,-M_PI_2);
}


void Collider::rotate(const PointF &rotPoint,const double &rad)
{
    for(size_t i=0; i<m_hitboxList.size(); i++)
    {
        GeneralVector<double> vec(m_hitboxList[i].getPos().getX(),m_hitboxList[i].getPos().getY());
        //GeneralVector<double> offset(this->getPos().getX(),this->getPos().getY());
        //offset.moveX(-0.5);
        //offset.moveY(-0.5);
        //vec -= offset;
        PointF newPos = GeneralVector<double>::rotate(vec,rotPoint,rad).toPoint();
        m_hitboxList[i].setPos(round(newPos.getX()),round(newPos.getY()));

        RectF newRect = RectF::rotate(RectF(m_hitboxList[i].getX(),m_hitboxList[i].getY(),m_hitboxList[i].getSize().getX(),m_hitboxList[i].getSize().getY()),rad);

        m_hitboxList[i].setPos(round(newRect.getX()),round(newRect.getY()));
        m_hitboxList[i].setSize(round(newRect.getSize().getX()),round(newRect.getSize().getY()));
    }
    this->updateBoundingBox();
}
