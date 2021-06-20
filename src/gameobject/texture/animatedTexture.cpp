#include "animatedTexture.h"

AnimatedTexture::AnimatedTexture()
    :   Texture()
{
    m_selectedTexture = 0;
   // m_textureList.push_back(this);
    m_const_dummy_str = "";
}
AnimatedTexture::AnimatedTexture(const AnimatedTexture &other)
    :   Texture(other)
{
    m_selectedTexture = 0;
   // m_textureList.push_back(this);
    m_const_dummy_str = "";
    this->operator=(other);
}
AnimatedTexture::~AnimatedTexture()
{
    for(Texture* &texture : m_textureList)
    {
        delete texture;
    }
    m_textureList.clear();
}
AnimatedTexture &AnimatedTexture::operator=(const AnimatedTexture &other)
{
    Texture::operator=(other);

    clearTextureList();
    for(size_t i=0; i<other.m_textureList.size(); i++)
    {
        // Make copy by value
        m_textureList.push_back(new Texture(*other.m_textureList[i]));
    }
    return *this;
}

void AnimatedTexture::setFilePath(unsigned int textureIndex, const string &filePath)
{
    if(m_textureList.size() == 0)
    {
        qDebug() << "No textures added, first add by calling func: AnimatedTexture::addTexture(const string &filePath)";
        return;
    }
    if(m_textureList.size() < textureIndex)
    {
        qDebug() << "ERROR: AnimatedTexture::setFilePath(unsigned int ["<<textureIndex<<"], const string \""<<filePath.c_str()<<"\"): Param 1 is out of Range. Max is: "<<m_textureList.size()-1;
        return;
    }
    if(filePath == "")
    {
        qDebug() << "ERROR: AnimatedTexture::setFilePath(unsigned int ["<<textureIndex<<"], const string \""<<filePath.c_str()<<"\"): Param 2 is empty";
        return;
    }
    if(textureIndex == m_selectedTexture)
        Texture::setFilePath(filePath);

    m_textureList[textureIndex]->setFilePath(filePath);
}
const string &AnimatedTexture::getFilePath() const
{
    return Texture::getFilePath();
}
const string &AnimatedTexture::getFilePath(unsigned int textureIndex) const
{
    if(m_textureList.size() == 0)
    {
        qDebug() << "No textures added, first add by calling func: AnimatedTexture::addTexture(const string &filePath)";
        return m_const_dummy_str;
    }
    if(m_textureList.size() < textureIndex)
    {
        qDebug() << "ERROR: string &AnimatedTexture::getFilePath(unsigned int ["<<textureIndex<<"]): Param 1 is out of Range. Max is: "<<m_textureList.size()-1;
        return m_const_dummy_str;
    }
    /*if(textureIndex == m_selectedTexture)
        return Texture::getFilePath();
    else*/
    return m_textureList[textureIndex]->getFilePath();
}
vector<string> AnimatedTexture::getFilePathList() const
{
    vector<string>  fileList(m_textureList.size(),"");
    for(size_t i=0; i<m_textureList.size(); i++)
    {
        fileList[i] = m_textureList[i]->getFilePath();
    }
    return fileList;
}

bool AnimatedTexture::loadTexture()
{
    bool success = true;
    unsigned int index = 0;
    for(Texture* &texture : m_textureList)
    {
        if(index == m_selectedTexture)
        {
            success &= Texture::loadTexture();
            *texture = *this;
        }
        else
            success &= texture->loadTexture();

        index++;
    }
    return success;
}
bool AnimatedTexture::loadTexture(const string &filePath)
{
    bool success = Texture::loadTexture(filePath);
    *m_textureList[m_selectedTexture] = *this;
    return success;
}
bool AnimatedTexture::loadTexture(unsigned int textureIndex)
{
    if(m_textureList.size() == 0)
    {
        qDebug() << "No textures added, first add by calling func: AnimatedTexture::addTexture(const string &filePath)";
        return false;
    }
    if(m_textureList.size() < textureIndex)
    {
        qDebug() << "ERROR: bool AnimatedTexture::loadTexture(unsigned int ["<<textureIndex<<"]): Param 1 is out of Range. Max is: "<<m_textureList.size()-1;
        return false;
    }

    if(textureIndex == m_selectedTexture)
    {
        bool success = Texture::loadTexture();
        *m_textureList[m_selectedTexture] = *this;
        return success;
    }
    else
        return m_textureList[textureIndex]->loadTexture();
}
bool AnimatedTexture::loadTexture(unsigned int textureIndex, const string &filePath)
{
    if(m_textureList.size() == 0)
    {
        qDebug() << "No textures added, first add by calling func: AnimatedTexture::addTexture(const string &filePath)";
        return false;
    }
    if(m_textureList.size() < textureIndex)
    {
        qDebug() << "ERROR: bool AnimatedTexture::loadTexture(unsigned int ["<<textureIndex<<"], const string \""<<filePath.c_str()<<"\"): Param 1 is out of Range. Max is: "<<m_textureList.size()-1;
        return false;
    }
    if(filePath == "")
    {
        qDebug() << "ERROR: bool AnimatedTexture::loadTexture(unsigned int ["<<textureIndex<<"], const string \""<<filePath.c_str()<<"\"): Param 2 is empty";
        return false;
    }

    if(textureIndex == m_selectedTexture)
    {
        bool success = Texture::loadTexture(filePath);
        *m_textureList[m_selectedTexture] = *this;
        return success;
    }
    else
        return m_textureList[textureIndex]->loadTexture(filePath);
}

bool AnimatedTexture::addTexture(const string &filePath)
{
    Texture *texture = new Texture();
    texture->setOrigin(this->m_origin);
    bool success = texture->loadTexture(filePath);
    m_textureList.push_back(texture);

    if(m_textureList.size()-1 == m_selectedTexture)
        Texture::operator=(*m_textureList[m_textureList.size()-1]);
    return success;
}

void AnimatedTexture::setOriginType(Origin origin)
{
    Texture::setOriginType(origin);
    for(size_t i=0; i<m_textureList.size(); i++)
        m_textureList[i]->setOriginType(origin);
}
Texture::Origin AnimatedTexture::getOriginType() const
{
    Texture::getOriginType();
}
void AnimatedTexture::setOrigin(const Point &origin)
{
    Texture::setOrigin(origin);
    for(size_t i=0; i<m_textureList.size(); i++)
        m_textureList[i]->setOrigin(origin);
}
const Point &AnimatedTexture::getOrigin() const
{
    Texture::getOrigin();
}

vector< vector<Pixel>  > AnimatedTexture::getPixelsList() const
{
    vector< vector<Pixel>   > list;
    list.reserve(m_textureList.size());
    for(size_t i=0; i<m_textureList.size(); i++)
    {
        list.push_back(m_textureList[i]->getPixels());
    }
    return list;
}
const vector<Pixel> &AnimatedTexture::getPixels(unsigned int textureIndex) const
{
    if(m_textureList.size() == 0)
    {
        qDebug() << "No textures added, first add by calling func: AnimatedTexture::addTexture(const string &filePath)";
        return m_const_dummy_pixelList;
    }
    if(m_textureList.size() < textureIndex)
    {
        qDebug() << "ERROR: vector<Pixel> &AnimatedTexture::getPixels(unsigned int ["<<textureIndex<<"]): Param 1 is out of Range. Max is: "<<m_textureList.size()-1;
        return m_const_dummy_pixelList;
    }
    return m_textureList[textureIndex]->getPixels();
}
vector< vector<Rect>  > AnimatedTexture::getRectsList() const
{
    vector<vector<Rect>   > list;
    list.reserve(m_textureList.size());
    for(size_t i=0; i<m_textureList.size(); i++)
    {
        list.push_back(m_textureList[i]->getRects());
    }
    return list;
}
const vector<Rect>  &AnimatedTexture::getRects(unsigned int textureIndex) const
{
    if(m_textureList.size() == 0)
    {
        qDebug() << "No textures added, first add by calling func: AnimatedTexture::addTexture(const string &filePath)";
        return m_const_dummy_rectList;
    }
    if(m_textureList.size() < textureIndex)
    {
        qDebug() << "ERROR: vector<Rect>  &AnimatedTexture::getRects(unsigned int ["<<textureIndex<<"]): Param 1 is out of Range. Max is: "<<m_textureList.size()-1;
        return m_const_dummy_rectList;
    }
    return m_textureList[textureIndex]->getRects();
}

unsigned int AnimatedTexture::getTextureAmount() const
{
    return m_textureList.size();
}
void AnimatedTexture::select(unsigned int textureIndex)
{
    if(m_selectedTexture == textureIndex)
        return;
    if(m_textureList.size() == 0)
    {
        qDebug() << "No textures added, first add by calling func: AnimatedTexture::addTexture(const string &filePath)";
        return;
    }
    if(m_textureList.size() < textureIndex)
    {
        qDebug() << "ERROR: AnimatedTexture::select(unsigned int ["<<textureIndex<<"]): Param 1 is out of Range. Max is: "<<m_textureList.size()-1;
        return;
    }
    m_selectedTexture = textureIndex;
    Texture::operator=(*m_textureList[m_selectedTexture]);
    this->m_changesAvailable = true;

}
void AnimatedTexture::selectForward(bool goAround)
{
    if(m_textureList.size() == 0)
    {
        qDebug() << "No textures added, first add by calling func: AnimatedTexture::addTexture(const string &filePath)";
        return;
    }
    if(m_selectedTexture >= m_textureList.size()-1)
    {
        if(goAround)
        {
            this->select(0);
            return;
        }
        else
            return;
    }
    this->select(m_selectedTexture + 1);
}
void AnimatedTexture::selectBackward(bool goAround)
{
    if(m_textureList.size() == 0)
    {
        qDebug() << "No textures added, first add by calling func: AnimatedTexture::addTexture(const string &filePath)";
        return;
    }
    if(m_selectedTexture == 0)
    {
        if(goAround)
        {
            this->select(m_textureList.size()-1);
            return;
        }
        else
            return;
    }
    this->select(m_selectedTexture - 1);
}
unsigned int AnimatedTexture::getSelected() const
{
    return m_selectedTexture;
}

void AnimatedTexture::clearTextureList()
{
    for(size_t i=0; i<m_textureList.size(); i++)
    {
        delete m_textureList[i];
    }
    m_textureList.clear();
}
