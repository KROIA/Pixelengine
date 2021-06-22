#include "texture.h"

Texture::Texture()
{
    m_textureFileName = "";
    m_changesAvailable = false;
    m_alphaThreshold = 150;
    m_frame.setPos(0,0);
    m_frame.setSize(0,0);
    setOriginType(Origin::middle);
}
Texture::Texture(const Texture &other)
{
    this->m_textureFileName = other.m_textureFileName;
    this->m_image           = other.m_image;
    this->m_alphaThreshold  = other.m_alphaThreshold;
    this->m_pixelList       = other.m_pixelList;
    this->m_pixelRectList   = other.m_pixelRectList;
    this->m_changesAvailable= other.m_changesAvailable;
    this->m_origin          = other.m_origin;
    this->m_originType      = other.m_originType;
    this->m_frame           = other.m_frame;
}
Texture::~Texture()
{

}
Texture &Texture::operator=(const Texture &other)
{
    this->m_textureFileName = other.m_textureFileName;
    this->m_image           = other.m_image;
    this->m_alphaThreshold  = other.m_alphaThreshold;
    this->m_pixelList       = other.m_pixelList;
    this->m_pixelRectList   = other.m_pixelRectList;
    this->m_changesAvailable= other.m_changesAvailable;
    this->m_origin          = other.m_origin;
    this->m_originType      = other.m_originType;
    this->m_frame           = other.m_frame;
    return *this;
}

void Texture::setFilePath(const string &filePath)
{
    m_textureFileName = filePath;
}
const string &Texture::getFilePath() const
{
    return m_textureFileName;
}

void Texture::setAlphaThreshold(uint8_t alphaThreshold)
{
    m_alphaThreshold = alphaThreshold;
}
uint8_t Texture::getAlphaThreshold() const
{
    return m_alphaThreshold;
}

bool Texture::loadTexture()
{
    EASY_FUNCTION(profiler::colors::Brown);
    if(m_textureFileName == "")
        return false;
    if(!m_image.loadFromFile(m_textureFileName))
    {
        qDebug() << "ERROR: Texture::loadTexture(): Can't load file "<<m_textureFileName.c_str();
        return false;
    }
    m_texture.loadFromFile(m_textureFileName);


    fillPixelList(m_image);
    calculateBoxes(m_pixelList);
    m_changesAvailable = true;

    return true;
}
bool Texture::loadTexture(const string &filePath)
{
    EASY_FUNCTION(profiler::colors::Brown);
    setFilePath(filePath);
    return loadTexture();
}
void Texture::setOriginType(Origin origin)
{
    EASY_FUNCTION(profiler::colors::Brown100);
    if(origin == Origin::costumPos)
        return;
    m_originType = origin;
}
Texture::Origin Texture::getOriginType() const
{
    return m_originType;
}
void Texture::setOrigin(const Point &origin)
{
    EASY_FUNCTION(profiler::colors::Brown200);
    setOriginType(Origin::costumPos);
    internalSetOrigin(origin);
}
void Texture::internalSetOrigin(const Point &origin)
{
    EASY_FUNCTION(profiler::colors::Brown200);
    if(m_origin == origin)
        return;
    Point lastOrigin = m_origin;
    m_origin = origin;

    Point deltaOrigin = Vector(lastOrigin) - Vector(m_origin);
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        m_pixelList[i].setPos(Vector(m_pixelList[i].getPos()) + Vector(deltaOrigin));
    }
}
const Point &Texture::getOrigin() const
{
    return m_origin;
}
PointU Texture::getSize() const
{
    return PointU(m_image.getSize().x, m_image.getSize().y);
}
Color Texture::getColor(const Point &pos) const
{
    if(pos.getX() >= signed(m_image.getSize().x) ||
       pos.getY() >= signed(m_image.getSize().y))
        return Color();
    for(size_t i=0; i<m_pixelList.size(); i++)
    {
        if(m_pixelList[i].getPos() == pos)
        {
            return m_pixelList[i];
        }
    }
    return Color();
}

const vector<Pixel> &Texture::getPixels() const
{
    return m_pixelList;
}
const vector<Rect>  &Texture::getRects() const
{
    return m_pixelRectList;
}
const Rect          &Texture::getFrame() const
{
    return m_frame;
}
bool Texture::changesAvailable()
{
    return m_changesAvailable;
}
void Texture::changesApplied()
{
    m_changesAvailable = false;
}
const sf::Texture &Texture::getTexture() const
{
    return m_texture;
}

void Texture::fillPixelList(const Image &image)
{
    EASY_FUNCTION(profiler::colors::Brown300);
    m_pixelList.clear();
    PointU texture_size(m_image.getSize().x,m_image.getSize().y);
    switch(m_originType)
    {
        case Origin::topLeft:
            internalSetOrigin(Point(0,0));
        break;
        case Origin::topRight:
            internalSetOrigin(Point(m_image.getSize().x,0));
        break;
        case Origin::bottomLeft:
            internalSetOrigin(Point(0,m_image.getSize().y));
        break;
        case Origin::bottomRight:
            internalSetOrigin(Point(m_image.getSize().x,m_image.getSize().y));
        break;
        case Origin::middle:
            internalSetOrigin(Point(m_image.getSize().x/2,m_image.getSize().y/2));
        break;
        default:

        break;
    }
    EASY_BLOCK("fillPixel x loop",profiler::colors::Brown400);
    for(unsigned int x=0; x<texture_size.getX(); x++)
    {
        EASY_BLOCK("fillPixel y loop",profiler::colors::Brown500);
        for(unsigned int y=0; y<texture_size.getY(); y++)
        {
            uint8_t pixelAlpha = m_image.getPixel(x,y).a;
            if(pixelAlpha > m_alphaThreshold)
            {
                Pixel p(m_image.getPixel(x,y));
                p.setPos(x - m_origin.getX() , y - m_origin.getY());
                m_pixelList.push_back(p);
            }
        }
        EASY_END_BLOCK;
    }
    EASY_END_BLOCK;
}
void Texture::calculateBoxes(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Brown50);
    vector<Rect> rawRectList;
    rawRectList.reserve(pixelList.size());

    EASY_BLOCK("Fill rawRectList",profiler::colors::Brown100);
    for(const Pixel &pixel : pixelList)
    {
        rawRectList.push_back(Rect(Vector(pixel.getPos())+Vector(m_origin),Point(1,1)));
    }
    EASY_END_BLOCK;
    //----------- OPTIMIZE ---------------------
    size_t width = 0;
    size_t height = 0;

    vector<vector<Rect*>    > map;

    // Lese Maximale Grösse der Textur
    EASY_BLOCK("Read max texture size",profiler::colors::Brown200);
    for(Rect &rect : rawRectList)
    {
        if(width < static_cast<size_t>(rect.getX()))
            width = static_cast<size_t>(rect.getX());
        if(height < static_cast<size_t>(rect.getY()))
            height = static_cast<size_t>(rect.getY());
    }
    width++;
    height++;
    EASY_END_BLOCK;


    EASY_BLOCK("Fill map with nullptr type: Rect*",profiler::colors::Brown300);
    // Fülle die ganze Fläche mit nullptr vom type Rect
    map.reserve(width);
    for(size_t x=0; x<width; x++)
    {
        map.push_back(vector<Rect*>());
        map[x].reserve(height);

        for(size_t y=0; y<height; y++)
        {
            map[x].push_back(nullptr);
        }
    }
    EASY_END_BLOCK;

    EASY_BLOCK("Fill map with new Rect*",profiler::colors::Brown400);
    // Fülle die Fläche mit Rects
    for(Rect &rect : rawRectList)
    {
        if(rect.getX() < 0 ||
           rect.getY() < 0 ||
           rect.getX() >= map.size())
        {
            qDebug() <<   "ERROR: void Texture::calculateBoxes(const vector<Pixel> &pixelList): POINT 1";
            return;
        }else if(rect.getY() >= map[rect.getX()].size())
        {
            qDebug() <<   "ERROR: void Texture::calculateBoxes(const vector<Pixel> &pixelList): POINT 2";
            return;
        }
         map[rect.getX()][rect.getY()] = new Rect();
        *map[rect.getX()][rect.getY()] = rect;
    }
    EASY_END_BLOCK;

    // Verkleinere die Rects und lösche die unnötigen Rects
    optimize_HitboxMap(map,m_pixelRectList);

    EASY_BLOCK("Move m_pixelRectList",profiler::colors::Brown500);
    // Verschiebe alle Rects, abhängig vom m_origin Punkt
    for(size_t i=0; i<m_pixelRectList.size(); i++)
    {
        m_pixelRectList[i].setPos(m_pixelRectList[i].getX()-m_origin.getX(),
                                  m_pixelRectList[i].getY()-m_origin.getY());
    }
    EASY_END_BLOCK;

    EASY_BLOCK("Delete map",profiler::colors::Brown600);
    for(size_t x=0; x<width; x++)
    {
        for(size_t y=0; y<height; y++)
        {
            delete map[x][y];
        }
    }
    EASY_END_BLOCK;
    m_frame = Rect::getFrame(m_pixelRectList);
}
void Texture::optimize_HitboxMap(vector<vector<Rect*>  > &map,vector<Rect> &outputColliderList)
{
    EASY_FUNCTION(profiler::colors::Brown50);
    if(map.size() == 0)
        return;
    if(map[0].size() == 0)
        return;
    outputColliderList.clear();
    size_t width    = map.size();
    size_t height   = map[0].size();

    EASY_BLOCK("Optimizer y loop",profiler::colors::Brown100);
    for(size_t y=0; y<height; y++)
    {
        EASY_BLOCK("Optimizer x loop",profiler::colors::Brown200);
        for(size_t x=0; x<width; x++)
        {
            if(map[x][y] == nullptr)
                continue;
            bool endXloop = false;
            size_t xIterator = 1;
            unsigned int colliderWidth = map[x][y]->getSize().getX();
            vector<Rect**> toDeleteList;

            EASY_BLOCK("while(!endXloop)",profiler::colors::Brown300);
            while(!endXloop)
            {
                if(x+xIterator >= width)
                {
                    endXloop = true;
                    continue;
                }
                if(map[x+xIterator][y] == nullptr)
                {
                    endXloop = true;
                    continue;
                }
                colliderWidth += map[x+xIterator][y]->getSize().getX();
                toDeleteList.push_back(&map[x+xIterator][y]);
                xIterator++;
            }
            EASY_END_BLOCK;
            EASY_BLOCK("Delete unused Rects",profiler::colors::Brown300);
            for(size_t i=0; i<toDeleteList.size(); i++)
            {
                delete *toDeleteList[i];
                *toDeleteList[i] = nullptr;
            }
            EASY_END_BLOCK;
            map[x][y]->setSize(colliderWidth,map[x][y]->getSize().getY());
            outputColliderList.push_back(Rect(*map[x][y]));
            x+=xIterator-1;
        }
        EASY_END_BLOCK;
    }
    EASY_END_BLOCK;
}
