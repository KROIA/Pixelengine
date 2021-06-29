#ifndef ANIMATEDTEXTURE_H
#define ANIMATEDTEXTURE_H
#include "texture.h"
#include "vector.h"
#include "QDebug"

using std::vector;

class AnimatedTexture   :   public Texture
{
    public:
        AnimatedTexture();
        AnimatedTexture(const AnimatedTexture &other);
        virtual ~AnimatedTexture();
        virtual AnimatedTexture &operator=(const AnimatedTexture &other);

        virtual void setFilePath(unsigned int textureIndex, const string &filePath);
        virtual const string &getFilePath() const; // of the selected Texture
        virtual const string &getFilePath(unsigned int textureIndex) const;
        virtual vector<string> getFilePathList() const;

        virtual bool loadTexture(); // returns true if succeded
        virtual bool loadTexture(const string &filePath); // of the selected Texture
        virtual bool loadTexture(unsigned int textureIndex); // returns true if succeded
        virtual bool loadTexture(unsigned int textureIndex, const string &filePath); // returns true if succeded

        virtual bool addTexture(const string &filePath);

        virtual void setOriginType(Origin origin);
        virtual Origin getOriginType() const;
        virtual void setOrigin(const Vector2f &origin);
        virtual const Vector2f &getOrigin() const;


        //virtual vector< vector<Pixel>  > getPixelsList() const;
        //virtual const vector<Pixel> &getPixels(unsigned int textureIndex) const; // Returns all Pixel's of the Texture
        virtual vector< vector<RectI>  > getRectsList() const;
        virtual const vector<RectI>  &getRects(unsigned int textureIndex) const;  // Returns all Rects which cover the Texture (for collider)

        virtual unsigned int getTextureAmount() const;
        virtual void select(unsigned int textureIndex);
        virtual void selectForward(bool goAround = true);
        virtual void selectBackward(bool goAround = true);
        virtual unsigned int getSelected() const;

    protected:
        virtual void clearTextureList();

        vector<Texture*> m_textureList;
        unsigned int m_selectedTexture;

    private:

        string m_const_dummy_str;
        vector<Pixel> m_const_dummy_pixelList;
        vector<RectI>  m_const_dummy_rectList;
};
#endif // ANIMATEDTEXTURE_H
