#include "texture.h"

Texture::Texture()
{
    m_textureFileName       = "";
    m_changesAvailable      = false;
    m_alphaThreshold        = 150;
    m_origin                = Vector2f(0,0);
    m_originType            = Origin::middle;
    m_rotation              = 0;

}
Texture::Texture(const Texture &other)
{
    this->m_textureFileName = other.m_textureFileName;
    this->m_image           = other.m_image;
    this->m_alphaThreshold  = other.m_alphaThreshold;
    this->m_pixelRectList   = other.m_pixelRectList;
    this->m_changesAvailable= other.m_changesAvailable;
    this->m_origin          = other.m_origin;
    this->m_originType      = other.m_originType;
    this->m_texture         = other.m_texture;
    this->m_rotation        = other.m_rotation;
}
Texture::~Texture()
{

}
Texture &Texture::operator=(const Texture &other)
{
    this->m_textureFileName = other.m_textureFileName;
    this->m_image           = other.m_image;
    this->m_alphaThreshold  = other.m_alphaThreshold;
    this->m_pixelRectList   = other.m_pixelRectList;
    this->m_changesAvailable= other.m_changesAvailable;
    this->m_origin          = other.m_origin;
    this->m_originType      = other.m_originType;
    this->m_texture         = other.m_texture;
    this->m_rotation        = other.m_rotation;
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
    if(!m_image.loadFromFile(m_textureFileName) || !m_texture.loadFromImage(m_image))
    {

        qDebug() << "ERROR: Texture::loadTexture(): Can't load file "<<m_textureFileName.c_str();
        return false;
    }

    internalUpdateOrigin();
    calculateBoxes();
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
    internalUpdateOrigin();
}
void Texture::internalUpdateOrigin()
{
    EASY_FUNCTION(profiler::colors::Cyan700);
    switch(m_originType)
    {
        case Origin::topLeft:
            internalSetOrigin(Vector2f(0,0));
        break;
        case Origin::topRight:
            internalSetOrigin(Vector2f(m_image.getSize().x,0));
        break;
        case Origin::bottomLeft:
            internalSetOrigin(Vector2f(0,m_image.getSize().y));
        break;
        case Origin::bottomRight:
            internalSetOrigin(Vector2f(m_image.getSize().x,m_image.getSize().y));
        break;
        case Origin::middle:
            internalSetOrigin(Vector2f(m_image.getSize().x/2,m_image.getSize().y/2));
        break;
        default:

        break;
    }
}
Origin Texture::getOriginType() const
{
    return m_originType;
}
void Texture::setOrigin(const Vector2f &origin)
{
    EASY_FUNCTION(profiler::colors::Brown200);
    m_originType = Origin::costumPos;
    internalSetOrigin(origin);
}
void Texture::internalSetOrigin(const Vector2f &origin)
{
    EASY_FUNCTION(profiler::colors::Brown200);
    if(m_origin == origin)
        return;
    m_origin = origin;
}
const Vector2f &Texture::getOrigin() const
{
    return m_origin;
}
Vector2u  Texture::getSize() const
{
    return m_image.getSize();
}
Color Texture::getColor(const Vector2i&pos) const
{
    if(pos.x >= signed(m_image.getSize().x) ||
       pos.y >= signed(m_image.getSize().y))
        return Color();
    return m_image.getPixel(pos.x,pos.y);
}

const vector<RectI>  &Texture::getRects() const
{
    return m_pixelRectList;
}

bool Texture::changesAvailable()
{
    return m_changesAvailable;
}
void Texture::changesApplied()
{
    m_changesAvailable = false;
}
sf::Texture &Texture::getTexture()
{
    return m_texture;
}
sf::Image   &Texture::getImage()
{
    return m_image;
}
void Texture::rotate(float deg)
{
    m_rotation += deg;
    m_rotation = float(((long long)m_rotation * 10000) % 3600000) / 10000;
    m_changesAvailable = true;
}
const float &Texture::getRotation() const
{
    return m_rotation;
}

void Texture::calculateBoxes()
{
    EASY_FUNCTION(profiler::colors::Brown50);
    vector<Vector2i> pixelPosList;
    Vector2u  texture_size(m_image.getSize().x,m_image.getSize().y);

    pixelPosList.reserve(texture_size.x * texture_size.y);

    EASY_BLOCK("fillPixelPos x loop",profiler::colors::Brown400);
    for(unsigned int x=0; x<texture_size.x; x++)
    {
        EASY_BLOCK("fillPixelPos y loop",profiler::colors::Brown500);
        for(unsigned int y=0; y<texture_size.y; y++)
        {
            uint8_t pixelAlpha = m_image.getPixel(x,y).a;
            if(pixelAlpha > m_alphaThreshold)
            {
                pixelPosList.push_back(Vector2i(x,y));
            }
        }
        EASY_END_BLOCK;
    }
    EASY_END_BLOCK;
    //------------------------------
    vector<RectI> rawRectList;
    rawRectList.reserve(pixelPosList.size());

    EASY_BLOCK("Fill rawRectList",profiler::colors::Brown100);
    for(const Vector2i &pixel : pixelPosList)
    {
        rawRectList.push_back(RectI(pixel,Vector2i(1,1)));
    }
    EASY_END_BLOCK;
    //----------- OPTIMIZE ---------------------
    size_t width = 0;
    size_t height = 0;

    vector<vector<RectI*>    > map;

    // Lese Maximale Grösse der Textur
    EASY_BLOCK("Read max texture size",profiler::colors::Brown200);
    for(RectI &rect : rawRectList)
    {
        if(width < static_cast<size_t>(rect.getX()))
            width = static_cast<size_t>(rect.getX());
        if(height < static_cast<size_t>(rect.getY()))
            height = static_cast<size_t>(rect.getY());
    }
    width++;
    height++;
    EASY_END_BLOCK;


    EASY_BLOCK("Fill map with nullptr type: RectI*",profiler::colors::Brown300);
    // Fülle die ganze Fläche mit nullptr vom type RectI
    map.reserve(width);
    for(size_t x=0; x<width; x++)
    {
        map.push_back(vector<RectI*>());
        map[x].reserve(height);

        for(size_t y=0; y<height; y++)
        {
            map[x].push_back(nullptr);
        }
    }
    EASY_END_BLOCK;

    EASY_BLOCK("Fill map with new RectI*",profiler::colors::Brown400);
    // Fülle die Fläche mit Rects
    for(RectI &rect : rawRectList)
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
         map[rect.getX()][rect.getY()] = new RectI();
        *map[rect.getX()][rect.getY()] = rect;
    }
    EASY_END_BLOCK;

    // Verkleinere die Rects und lösche die unnötigen Rects
    optimize_HitboxMap(map,m_pixelRectList);

    EASY_BLOCK("Move m_pixelRectList",profiler::colors::Brown500);
    // Verschiebe alle Rects, abhängig vom m_origin Punkt
    for(size_t i=0; i<m_pixelRectList.size(); i++)
    {
        m_pixelRectList[i].setPos(m_pixelRectList[i].getPos() - Vector2i(m_origin));
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
    //m_frame = RectI::getFrame(m_pixelRectList);
}
void Texture::optimize_HitboxMap(vector<vector<RectI*>  > &map,vector<RectI> &outputColliderList)
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
            unsigned int colliderWidth = map[x][y]->getSize().x;
            vector<RectI**> toDeleteList;

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
                colliderWidth += map[x+xIterator][y]->getSize().x;
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
            map[x][y]->setSize(colliderWidth,map[x][y]->getSize().y);
            outputColliderList.push_back(RectI(*map[x][y]));
            x+=xIterator-1;
        }
        EASY_END_BLOCK;
    }
    EASY_END_BLOCK;
}
