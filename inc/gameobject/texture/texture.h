#ifndef Texture_H
#define Texture_H
#include "string.h"
#include "SFML/Graphics/Image.hpp"
#include "pixel.h"
#include "vector.h"
#include "rect.h"
#include "point.h"
#include "QDebug"
//#include "painter.h"
//#include "collider.h"

using std::string;
using sf::Image;
using sf::Color;
using std::vector;


class Texture
{
    public:
        Texture();
        Texture(const Texture &other);
        virtual ~Texture();
        virtual Texture &operator=(const Texture &other);

        virtual void setFilePath(const string &filePath);
        virtual const string &getFilePath() const;

        virtual void setAlphaColor(const Color &alphaColor);
        virtual const Color &getAlphaColor() const;

        virtual bool loadTexture(); // returns true if succeded
        virtual bool loadTexture(const string &filePath); // returns true if succeded

    //    virtual bool applayToPainter(Painter *painter); // returns true if succeded
    //    virtual bool

        virtual const vector<Pixel> &getPixels() const; // Returns all Pixel's of the Texture
        virtual const vector<Rect>  &getRects() const;  // Returns all Rects which cover the Texture (for collider)

        virtual bool changesAvailable();
        virtual void changesApplied();

    protected:
        virtual void fillPixelList(const Image &image);
        virtual void calculateBoxes(const vector<Pixel> &pixelList);
        virtual void optimize_HitboxMap(vector<vector<Rect*>  > &map,vector<Rect> &outputColliderList);

        string m_textureFileName;
        Image  m_image;
        Color  m_alpha;
        vector<Pixel> m_pixelList;
        vector<Rect>  m_pixelRectList;

        bool   m_changesAvailable;
    private:


};
#endif
