#include "vertexPathPainter.h"
/*
VertexPath::VertexPath()
{

}

VertexPath::~VertexPath()
{
    delete this->line;
}
const VertexPath &VertexPath::operator=(const VertexPath &other)
{
    this->length = other.length;
    this->type   = other.type;
    this->line   = new sf::Vertex[this->length];
    for(size_t i=0; i<this->length; i++)
    {
        this->line[i] = other.line[i];
    }
    return *this;
}

void VertexPath::move(sf::Vector2f vec)
{
    for(size_t i=0; i<length; i++)
    {
        line[i].position += vec;
    }
}
void VertexPath::setColor(const Color &color)
{
    for(size_t i=0; i<length; i++)
    {
        line[i].color   = color;
    }
}*/

VertexPathPainter::VertexPathPainter()
    :   Painter()
{
    setRenderLayer(RenderLayerIndex::vertexPaths);
    m_origin = Vector2f(0,0);
    m_rotation = 0;
}
VertexPathPainter::~VertexPathPainter()
{
    clear();
}

void VertexPathPainter::render(sf::RenderWindow *window,
                               float viewPortZoom,
                               DisplayStats &stats)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
  //  if(!m_isVisible || !m_frame.intersects_fast(renderFrame))
  //      return;
    for(auto pair   :   m_pathList)
    {
        window->draw(pair.second->line, pair.second->length, pair.second->type);
        stats.renderVertexPaths ++;
    }
}

void VertexPathPainter::addPath(VertexPath *path)
{
    internal_addPath(path);
}
void VertexPathPainter::addPath(const vector<VertexPath*> &path)
{
    for(size_t i=0; i<path.size(); i++)
        addPath(path[i]);
}
void VertexPathPainter::addPath(const vector<Vector2f> &points)
{
    VertexPath *path = intern_pointsToPath(points);
    path->setColor(m_standardColor);
    internal_addPath(path);
}
void VertexPathPainter::addPath(VertexPath *path, const Color &color)
{
    internal_addPath(path,color);
}
void VertexPathPainter::addPath(const vector<VertexPath*> &path,const Color &color)
{
    for(size_t i=0; i<path.size(); i++)
        addPath(path[i],color);
}
void VertexPathPainter::addPath(const vector<Vector2f> &points, const Color &color)
{
    VertexPath *path = intern_pointsToPath(points);
    path->setColor(color);
    internal_addPath(path);
}
void VertexPathPainter::internal_addPath(VertexPath *path)
{
    m_pathList.insert({path,path});
    m_points.reserve(m_points.size() + path->length);
    for(size_t i=0; i<path->length; i++)
    {
        m_points.push_back(path->line[i].position);
    }
    internal_CalculateFrame();
}
void VertexPathPainter::internal_addPath(VertexPath *path, const Color &color)
{
    path->setColor(color);
    internal_addPath(path);
}
VertexPath *VertexPathPainter::intern_pointsToPath(const vector<Vector2f> &points)
{
    VertexPath *path = new VertexPath;
    path->length = points.size();
    path->type   = sf::LineStrip;
    path->line = new sf::Vertex[path->length];
    for(size_t i=0; i<points.size(); i++)
    {
        path->line[i] = sf::Vertex(points[i]);
    }

    return path;
}

void VertexPathPainter::setStandardColor(const Color &color)
{
    m_standardColor = color;
}
const Color &VertexPathPainter::getStandardColor()
{
    return m_standardColor;
}

void VertexPathPainter::clear()
{
    for(auto pair   :   m_pathList)
        delete pair.second;
    m_pathList.clear();
    m_points.clear();
}
/*void VertexPathPainter::erase(VertexPath *path)
{
    m_pathList.erase(path);

    delete path;
}*/
void VertexPathPainter::internal_setPos(const Vector2f &pos)
{
    Vector2f deltaPos = pos - m_pos;
    for(auto pair   :   m_pathList)
    {
        for(size_t i=0; i<pair.second->length; i++)
            pair.second->line[i].position += deltaPos;
    }
    internal_CalculateFrame();
}
float VertexPathPainter::internal_getRotation() const
{
    return m_rotation;
}
void VertexPathPainter::internal_setRotation(const Vector2f &rotPoint,float deg)
{
    float deltaRot = deg - m_rotation;
    Vector::rotate(m_points,rotPoint,deltaRot);
    m_rotation = deg;
    size_t it = 0;
    for(auto pair   :   m_pathList)
    {
        for(size_t i=0; i<pair.second->length; i++)
        {
            pair.second->line[i].position = m_points[it];
            it++;
        }
    }
}
void VertexPathPainter::internal_setRotation(const float &deg)
{
    internal_setRotation(m_origin,deg);
}
void VertexPathPainter::internal_UpdateOrigin()
{
    switch(m_originType)
    {
        case Origin::topLeft:
            internal_SetOrigin(Vector2f(0,0)+m_frame.getPos());
        break;
        case Origin::topRight:
            internal_SetOrigin(Vector2f(m_frame.getSize().x,0)+m_frame.getPos());
        break;
        case Origin::bottomLeft:
            internal_SetOrigin(Vector2f(0,m_frame.getSize().y)+m_frame.getPos());
        break;
        case Origin::bottomRight:
            internal_SetOrigin(Vector2f(m_frame.getSize().x,m_frame.getSize().y)+m_frame.getPos());
        break;
        case Origin::middle:
            internal_SetOrigin(Vector2f(m_frame.getSize().x/2,m_frame.getSize().y/2)+m_frame.getPos());
        break;
        default:

        break;
    }
}
void VertexPathPainter::internal_SetOrigin(const Vector2f &origin)
{
    m_origin = origin;
}
const Vector2f &VertexPathPainter::internal_getOrigin() const
{
    return m_origin;
}
void VertexPathPainter::internal_CalculateFrame()
{
    Vector2f TL(Vector::getMinX(m_points),Vector::getMinY(m_points));
    Vector2f BR(Vector::getMaxX(m_points),Vector::getMaxY(m_points));

    m_frame.set(TL,BR-TL);
}
