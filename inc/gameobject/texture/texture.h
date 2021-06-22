#ifndef Texture_H
#define Texture_H
#include "string.h"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "pixel.h"
#include "vector.h"
#include "rect.h"
#include "point.h"
#include "QDebug"

#include "profiler.h"

using std::string;
using sf::Image;
using sf::Color;
using std::vector;


class Texture
{
    public:
        enum Origin
        {
            topLeft,
            topRight,
            bottomLeft,
            bottomRight,
            middle,
            costumPos
        };
        Texture();
        Texture(const Texture &other);
        virtual ~Texture();
        virtual Texture &operator=(const Texture &other);

        virtual void setFilePath(const string &filePath);
        virtual const string &getFilePath() const;

        virtual void setAlphaThreshold(uint8_t alphaThreshold);
        virtual uint8_t getAlphaThreshold() const;

        virtual bool loadTexture(); // returns true if succeded
        virtual bool loadTexture(const string &filePath); // returns true if succeded

    //    virtual bool applayToPainter(Painter *painter); // returns true if succeded
    //    virtual bool
        virtual void setOriginType(Origin origin);
        virtual Origin getOriginType() const;
        virtual void setOrigin(const Point &origin);
        virtual const Point &getOrigin() const;

        virtual PointU getSize() const;
        virtual Color getColor(const Point &pos) const;

        virtual const vector<Pixel> &getPixels() const; // Returns all Pixel's of the Texture
        virtual const vector<Rect>  &getRects() const;  // Returns all Rects which cover the Texture (for collider)
        virtual const Rect          &getFrame() const;

        virtual bool changesAvailable();
        virtual void changesApplied();

        virtual const sf::Texture &getTexture() const;

    protected:
        virtual void internalSetOrigin(const Point &origin);
        virtual void fillPixelList(const Image &image);
        virtual void calculateBoxes(const vector<Pixel> &pixelList);
        virtual void optimize_HitboxMap(vector<vector<Rect*>  > &map,vector<Rect> &outputColliderList);

        string m_textureFileName;
        Image  m_image;
        //Color  m_alpha;
        uint8_t m_alphaThreshold;
        vector<Pixel> m_pixelList;
        vector<Rect>  m_pixelRectList;

        bool    m_changesAvailable;
        Point   m_origin;
        Origin  m_originType;
        Rect    m_frame;

        sf::Texture m_texture;

    private:


};
#endif
