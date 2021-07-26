#include "shape.h"


Shape::Shape()
{
    m_rotation      =   0;
    m_pos           =   {0,0};
    m_dummyVertex   =   {0,0};
    m_static        =   false;
    m_mass          =   1;
    m_pos           =   {0,0};
    m_origin        =   {0,0};
}
Shape::Shape(const Shape &other)
{
    this->m_pos         =   other.m_pos;
    this->m_origin      =   other.m_origin;
    this->m_center      =   other.m_center;
    this->m_rotation    =   other.m_rotation;
    this->m_vertexList  =   other.m_vertexList;
    this->m_collisionResolveVec = other.m_collisionResolveVec;
    this->m_static      =   other.m_static;
    this->m_mass        =   other.m_mass;
}
Shape::Shape(const vector<Vector2f> &Vertexs)
{
    m_vertexList    =   Vertexs;
    m_rotation      =   0;
    m_dummyVertex   =   {0,0};
    m_static        =   false;
    m_mass          =   1;
    m_pos           =   {0,0};
    m_origin        =   {0,0};
    calculateCenter();
}
Shape::~Shape()
{
    m_vertexList.clear();
}
const Shape &Shape::operator=(const Shape &other)
{
    this->m_pos         =   other.m_pos;
    this->m_origin      =   other.m_origin;
    this->m_center      =   other.m_center;
    this->m_rotation    =   other.m_rotation;
    this->m_vertexList  =   other.m_vertexList;
    this->m_collisionResolveVec = other.m_collisionResolveVec;
    this->m_static      =   other.m_static;
    this->m_mass        =   other.m_mass;
    return *this;
}

void Shape::setSize(size_t size)
{
    m_vertexList.resize(size);
}
void Shape::reserve(size_t size)
{
    m_vertexList.reserve(size);
}
size_t Shape::getSize() const
{
    return m_vertexList.size();
}

void Shape::setVertex(size_t index, const Vector2f &pos)
{
    if(indexInvalid(index))
        return;
    recalculateCenter(m_vertexList[index],pos);
    m_vertexList[index] = pos;
}
void Shape::addVertex(const Vector2f &pos)
{
    m_vertexList.push_back(pos);
    recalculateCenterAddedVertex(pos);
}
void Shape::removeVertex(size_t index)
{
    if(indexInvalid(index))
        return;
    Vector2f oldV = m_vertexList[index];
    m_vertexList.erase(m_vertexList.begin() + index);
    recalculateCenterRemovedVertex(oldV);
}
void Shape::clear()
{
    m_vertexList.clear();
    m_center = {0,0};
}
void Shape::setPos(const Vector2f &pos)
{
    move(pos - (m_pos-m_origin));
}
void Shape::setOrigin(const Vector2f &pos)
{
    m_origin = pos;
    setPos(m_pos);
}
void Shape::move(const Vector2f delta)
{
    for(auto &vertex : m_vertexList)
        vertex  += delta;
    m_pos       += delta;
    m_center    += delta;
}

void Shape::setRotation(float angle)
{
    rotate(angle - m_rotation);
}
void Shape::setRotation(Vector2f rotVertex, float angle)
{
    rotate(rotVertex, angle - m_rotation);
}
void Shape::rotate(float angle)
{
    rotate(m_origin, angle);
}
void Shape::rotate(Vector2f rotVertex, float angle)
{
    sf::Transform transform;
    transform.rotate(angle, rotVertex);
    for(auto &vertex :   m_vertexList)
        vertex = transform.transformPoint(vertex);

    m_pos = transform.transformPoint(m_pos);
    m_center = transform.transformPoint(m_center);
    m_rotation += angle;
}


const Vector2f &Shape::getVertex(size_t index) const
{
    if(indexInvalid(index))
        return m_dummyVertex;
    return m_vertexList[index];
}
const vector<Vector2f> &Shape::getVertexs() const
{
    return m_vertexList;
}
const Vector2f &Shape::getPos() const
{
    return m_pos;
}
const Vector2f &Shape::getOrigin() const
{
    return m_origin;
}
const Vector2f &Shape::getCenter() const
{
    return m_center;
}
float Shape::getRotation()
{
    return m_rotation;
}

VertexPath* Shape::getDrawable(const Color &color) const
{
    VertexPath *path = new VertexPath;

    if(m_vertexList.size() == 0)
    {
        path->length = 0;
        return path;
    }
    path->length = m_vertexList.size()+1;
    path->type = sf::LineStrip;
    path->line = new sf::Vertex[path->length];

    for(size_t i = 0; i < m_vertexList.size(); i++)
    {
        path->line[i] = sf::Vertex(m_vertexList[i]);
        path->line[i].color = color;
    }
    path->line[m_vertexList.size()] = sf::Vertex(m_vertexList[0]);
    path->line[m_vertexList.size()].color = color;
    return path;
}
void Shape::setCollisionResolveVec(const Vector2f &vec)
{
    m_collisionResolveVec = vec;
}
const Vector2f &Shape::getCollisionResolveVec() const
{
    return m_collisionResolveVec;
}
void Shape::resolveCollision(Shape &s)
{
    if(s.m_static)
        return;
    s.move(s.m_collisionResolveVec);
    s.m_collisionResolveVec = {0,0};
}
void Shape::resolveCollision(Shape &s1, Shape &s2)
{
    float massSum = s1.m_mass + s2.m_mass;

    if(!s1.m_static && !s2.m_static)
    {
        s1.move(s1.m_collisionResolveVec *s2.m_mass/massSum);
        s2.move(s2.m_collisionResolveVec *s1.m_mass/massSum);
    }
    else if(s1.m_static && !s2.m_static)
    {
        s2.move(s2.m_collisionResolveVec);
    }else if(!s1.m_static && s2.m_static)
    {
        s1.move(s1.m_collisionResolveVec);
    }

    s1.m_collisionResolveVec = {0,0};
    s2.m_collisionResolveVec = {0,0};
}

void Shape::setStatic(bool enable)
{
    m_static = enable;
}
void Shape::setMass(float mass)
{
    if(mass <= 0)
        mass = 0.001;
    m_mass = mass;
}
bool Shape::getStatic()const
{
    return m_static;
}
float Shape::getMass()const
{
    return m_mass;
}
bool Shape::intersects(const Shape &other) const
{
    Vector2f normal;
    float depth;
    return shapeOverlap_SAX(*this,other,normal,depth);
}
bool Shape::checkForCollision(Shape &other)
{
    Vector2f normal;
    float depth;
    if(shapeOverlap_SAX(*this,other,normal,depth))
    {
        this->setCollisionResolveVec(-normal*depth);
        other.setCollisionResolveVec( normal*depth);
        return true;
    }
    return false;
}
AABB Shape::getFrame()
{
    Vector2f min, max;
    min.x = std::numeric_limits<float>::max();
    min.y = std::numeric_limits<float>::max();

    max.x = -std::numeric_limits<float>::max();
    max.y = -std::numeric_limits<float>::max();

    for(auto &vec : m_vertexList)
    {
        if(min.x > vec.x)
            min.x = vec.x;
        if(min.y > vec.y)
            min.y = vec.y;

        if(max.x < vec.x)
            max.x = vec.x;
        if(max.y < vec.y)
            max.y = vec.y;
    }
    return AABB(min,max-min);
}

Shape Shape::triangle(float width, float height, Vector2f pos)
{
    Shape s;
    s.reserve(3);
    s.addVertex({-width/2.f,height*1.f/3.f});
    s.addVertex({ width/2.f,height*1.f/3.f});
    s.addVertex({ 0,-height*2.f/3.f});
    return s;
}
Shape Shape::rect(float width, float height, Vector2f pos)
{
    Shape s;
    s.reserve(4);
    s.addVertex({-width/2.f,-height/2.f});
    s.addVertex({ width/2.f,-height/2.f});
    s.addVertex({ width/2.f, height/2.f});
    s.addVertex({-width/2.f, height/2.f});
    return s;
}
Shape Shape::pentagon(float sideLength, Vector2f pos)
{
    Shape s;
    s.reserve(5);
    Vector2f line(sideLength,0);
    float r = sideLength/(2*sqrt(5-sqrt(20)));
    Vector2f lastPoint(-sideLength/2,r);
    const float angle = 108;

    s.addVertex(lastPoint);
    for(size_t i=0; i<4; i++)
    {
        Vector::rotate(lastPoint,{0,0},-180+angle);
        s.addVertex(lastPoint);
    }
    return s;
}

void Shape::calculateCenter()
{
    if(m_vertexList.size() == 0)
        return;
    Vector2f origin{0,0};
    for(auto vertex :   m_vertexList)
        origin += vertex;

    m_center = origin /= (float)m_vertexList.size();
}
void Shape::recalculateCenterAddedVertex(const Vector2f &newVertex)
{
    if(m_vertexList.size() == 0)
        return;
    m_center = (m_center * (float)(m_vertexList.size()-1) + newVertex) / (float)m_vertexList.size();
}
void Shape::recalculateCenterRemovedVertex(const Vector2f &oldVertex)
{
    if(m_vertexList.size() == 0)
        return;
    m_center = (m_center * (float)(m_vertexList.size()+1) - oldVertex) / (float)m_vertexList.size();
}
void Shape::recalculateCenter(const Vector2f &oldVertex,const Vector2f &newVertex)
{
    if(m_vertexList.size() == 0)
        return;
    m_center = m_center - oldVertex / (float)m_vertexList.size() + newVertex / (float)m_vertexList.size();
}

bool Shape::indexInvalid(size_t index) const
{
    return m_vertexList.size() <= index;
}


bool Shape::shapeOverlap_SAX(const Shape &s1, const Shape &s2,Vector2f &normal,float &depth)
{
    depth = std::numeric_limits<float>::max();

    const Shape *shape1 = &s1;
    const Shape *shape2 = &s2;

    for(size_t s=0;s<2; s++)
    {
        if(s==1)
        {
            shape1 = &s2;
            shape2 = &s1;
        }
        for(size_t a=0;a<shape1->getSize(); a++)
        {
            Vector2f edge = shape1->getVertex((a+1)%shape1->getSize()) - shape1->getVertex(a);
            Vector2f axis = {edge.y,-edge.x};  // Perpendicular vector to edge
            Vector::normalize(axis);

            float minA, maxA, minB, maxB;


            projectVertecies(shape1->getVertexs(),axis,minA,maxA);
            projectVertecies(shape2->getVertexs(),axis,minB,maxB);

            if(minA >= maxB || minB >= maxA)
            {
                return false;
            }
            float axisDepth = std::min(maxB - minA, maxA - minB);
            if(axisDepth < depth)
            {
                depth  = axisDepth;
                normal = axis;
            }

        }
    }

    Vector2f distance = s2.m_center  - s1.m_center;
    if(Vector::getDotProduct(distance,normal) < 0.f)
    {
        normal = -normal;
    }



    return true;
}
void Shape::projectVertecies(const vector<Vector2f> &vertecies, Vector2f axis,float &min, float &max)
{
    min = std::numeric_limits<float>::max();
    max = -std::numeric_limits<float>::max();

    for(size_t i=0; i<vertecies.size(); i++)
    {
        float proj = Vector::getDotProduct(vertecies[i],axis);
        if(proj < min) { min = proj; }
        if(proj > max) { max = proj; }
    }
}
