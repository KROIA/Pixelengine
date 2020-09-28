#include "collider.h"


Collider::Collider()
{
    this->setPos(0,0);
    m_dummy.setPos(0,0);
    m_dummy.setSize(0,0);
}

Collider::Collider(const Collider &other)
{
    this->m_bodyPos         = other.m_bodyPos;
    this->m_hitBoxList      = other.m_hitBoxList;
    this->m_boundingBox     = other.m_boundingBox;
}

Collider::~Collider()
{

}

void Collider::setPos(const int &x,const int &y)
{
    this->setPos(Point(x,y));
}
void Collider::setPos(const Point &pos)
{
    Point deltaPos(pos.getX() - m_bodyPos.getX(),
                   pos.getY() - m_bodyPos.getY());
    m_boundingBox.setPos(m_boundingBox.getPos().getX() + deltaPos.getX(),
                         m_boundingBox.getPos().getY() + deltaPos.getY());
    for(size_t i=0; i<m_hitBoxList.size(); i++)
    {
        m_hitBoxList[i].setPos(m_hitBoxList[i].getPos().getX() + deltaPos.getX(),
                               m_hitBoxList[i].getPos().getY() + deltaPos.getY());
    }
    m_bodyPos = pos;
}
const Point &Collider::getPos() const
{
    return m_bodyPos;
}


const Rect &Collider::getBoundingBox() const
{
    return m_boundingBox;
}


void Collider::addHitBox(Rect box)
{
    for(size_t i=0; i<m_hitBoxList.size(); i++)
    {
        if(m_hitBoxList[i] == box)
            return;
    }
    box.setPos(box.getPos().getX()+m_bodyPos.getX(),
               box.getPos().getY()+m_bodyPos.getY());
    m_hitBoxList.push_back(box);
    int minX = this->getMinX();
    int minY = this->getMinY();
    int maxX = this->getMaxX();
    int maxY = this->getMaxY();
    m_boundingBox.setSize(maxX-minX,maxY-minY);
    m_boundingBox.setPos(minX,minY);
}

void Collider::addHitBox(const vector<Rect> &boxList)
{
    for(size_t i=0; i<boxList.size(); i++)
    {
        this->addHitBox(boxList[i]);
    }
}


const Rect &Collider::getHitBox(const unsigned int &index) const
{
    if(index < m_hitBoxList.size())
        return m_hitBoxList[index];
    return m_dummy;
}

const vector<Rect> &Collider::getHitBox() const
{
    return m_hitBoxList;
}


bool Collider::intersectsBoundingBox(const Collider &other) const
{
    return this->m_boundingBox.intersects(other.m_boundingBox);
}

bool Collider::collides(const Collider &other) const
{
    for(size_t x=0; x<this->m_hitBoxList.size(); x++)
    {
        for(size_t y=0; y<other.m_hitBoxList.size(); y++)
        {
            if(this->m_hitBoxList[x].intersects(other.m_hitBoxList[y]))
                return true;
        }
    }
    return false;
}

void Collider::setBoundingBox(const Rect &box)
{
    m_boundingBox = box;
}

void Collider::setBoundingBox(const int &x,const int &y,
                              const int &width,const int &height)
{
    m_boundingBox.setPos(x,y);
    m_boundingBox.setSize(width,height);
}

int Collider::getMinX()
{
    if(m_hitBoxList.size() == 0)
        return 0;
    int minX = m_hitBoxList[0].getCornerPoint_TL().getX();
    for(size_t i=1; i<m_hitBoxList.size(); i++)
    {
        if(m_hitBoxList[i].getCornerPoint_TL().getX() < minX)
            minX = m_hitBoxList[i].getCornerPoint_TL().getX();
    }
    return minX;
}
int Collider::getMaxX()
{
    if(m_hitBoxList.size() == 0)
        return 0;
    int maxX = m_hitBoxList[0].getCornerPoint_BL().getX();
    for(size_t i=1; i<m_hitBoxList.size(); i++)
    {
        if(m_hitBoxList[i].getCornerPoint_BL().getX() > maxX)
            maxX = m_hitBoxList[i].getCornerPoint_BL().getX();
    }
    return maxX;
}
int Collider::getMinY()
{
    if(m_hitBoxList.size() == 0)
        return 0;
    int minY = m_hitBoxList[0].getCornerPoint_TL().getY();
    for(size_t i=0; i<m_hitBoxList.size(); i++)
    {
        if(m_hitBoxList[i].getCornerPoint_TL().getY() < minY)
            minY = m_hitBoxList[i].getCornerPoint_TL().getY();
    }
    return minY;
}
int Collider::getMaxY()
{
    if(m_hitBoxList.size() == 0)
        return 0;
    int maxY = m_hitBoxList[0].getCornerPoint_TR().getY();
    for(size_t i=0; i<m_hitBoxList.size(); i++)
    {
        if(m_hitBoxList[i].getCornerPoint_TR().getY() > maxY)
            maxY = m_hitBoxList[i].getCornerPoint_TR().getY();
    }
    return maxY;
}
