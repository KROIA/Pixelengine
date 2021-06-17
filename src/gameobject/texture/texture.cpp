#include "texture.h"

Texture::Texture()
{
    m_textureFileName = "";
    setAlphaColor(Color(0,0,0,0));
}
Texture::Texture(const Texture &other)
{
    this->m_textureFileName = other.m_textureFileName;
    this->m_image           = other.m_image;
    this->m_alpha           = other.m_alpha;
    this->m_pixelList       = other.m_pixelList;
    this->m_pixelRectList   = other.m_pixelRectList;
}
Texture::~Texture()
{

}

void Texture::setFilePath(const string &filePath)
{
    m_textureFileName = filePath;
}
const string &Texture::getFileName() const
{
    return m_textureFileName;
}

void Texture::setAlphaColor(const Color &alphaColor)
{
    m_alpha = alphaColor;
}
const Color &Texture::getAlphaColor() const
{
    return m_alpha;
}

bool Texture::loadTexture()
{
    if(m_textureFileName == "")
        return false;
    if(!m_image.loadFromFile(m_textureFileName))
    {
        qDebug() << "ERROR: Texture::loadTexture(): Can't load file "<<m_textureFileName.c_str();
        return false;
    }

    fillPixelList(m_image);
    calculateBoxes(m_pixelList);

    return true;
}
bool Texture::loadTexture(const string &filePath)
{
    setFilePath(filePath);
    return loadTexture();
}
const vector<Pixel> &Texture::getPixels() const
{
    return m_pixelList;
}
const vector<Rect>  &Texture::getRects() const
{
    return m_pixelRectList;
}


void Texture::fillPixelList(const Image &image)
{
    m_pixelList.clear();
    PointU texture_size(m_image.getSize().x,m_image.getSize().y);
    for(unsigned int x=0; x<texture_size.getX(); x++)
    {
        for(unsigned int y=0; y<texture_size.getY(); y++)
        {
            Color pixelCol = m_image.getPixel(x,y);
            if(pixelCol != m_alpha)
            {
                Pixel p(pixelCol);
                p.setPos(x,y);
                m_pixelList.push_back(p);
            }
        }
    }
}
void Texture::calculateBoxes(const vector<Pixel> &pixelList)
{
    vector<Rect> rawRectList;
    rawRectList.reserve(pixelList.size());

    for(const Pixel &pixel : pixelList)
    {
        rawRectList.push_back(Rect(pixel.getPos(),Point(1,1)));
    }
    //----------- OPTIMIZE ---------------------
    Point origin(0,0);
    size_t width = 0;
    size_t height = 0;

    vector<vector<Rect*>    > map;

    // Lese Maximale Grösse der Textur
    for(Rect &rect : rawRectList)
    {
        if(width < static_cast<size_t>(rect.getX()+origin.getX()))
            width = static_cast<size_t>(rect.getX()+origin.getX());
        if(height < static_cast<size_t>(rect.getY()+origin.getY()))
            height = static_cast<size_t>(rect.getY()+origin.getY());
    }
    width++;
    height++;

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

    // Verkleinere die Rects und lösche die unnötigen Rects
    optimize_HitboxMap(map,m_pixelRectList);

    // Verschiebe alle Rects, abhängig vom origin Punkt
    for(size_t i=0; i<m_pixelRectList.size(); i++)
    {
        m_pixelRectList[i].setPos(m_pixelRectList[i].getX()-origin.getX(),
                                  m_pixelRectList[i].getY()-origin.getY());
    }
    for(size_t x=0; x<width; x++)
    {
        for(size_t y=0; y<height; y++)
        {
            delete map[x][y];
        }
    }
}
void Texture::optimize_HitboxMap(vector<vector<Rect*>  > &map,vector<Rect> &outputColliderList)
{
    if(map.size() == 0)
        return;
    if(map[0].size() == 0)
        return;
    outputColliderList.clear();
    size_t width    = map.size();
    size_t height   = map[0].size();

    for(size_t y=0; y<height; y++)
    {
        for(size_t x=0; x<width; x++)
        {
            if(map[x][y] == nullptr)
                continue;
            bool endXloop = false;
            size_t xIterator = 1;
            unsigned int colliderWidth = map[x][y]->getSize().getX();
            vector<Rect**> toDeleteList;
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
            for(size_t i=0; i<toDeleteList.size(); i++)
            {
                delete *toDeleteList[i];
                *toDeleteList[i] = nullptr;
            }
            map[x][y]->setSize(colliderWidth,map[x][y]->getSize().getY());
            outputColliderList.push_back(Rect(*map[x][y]));
            x+=xIterator-1;
        }
    }
}
