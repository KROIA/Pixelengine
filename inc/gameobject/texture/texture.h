#ifndef Texture_H
#define Texture_H
#include "string.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "pixel.h"
#include "rect.h"
#include "point.h"
#include "QDebug"

#include "profiler.h"

using std::string;
using sf::Image;
using sf::Color;
using std::vector;

enum Origin
{
    topLeft,
    topRight,
    bottomLeft,
    bottomRight,
    middle,
    costumPos
};
class Texture
{
    public:

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

        virtual void setOriginType(Origin origin);
        virtual Origin getOriginType() const;
        virtual void setOrigin(const Vector2f &origin);
        virtual const Vector2f &getOrigin() const;

        virtual Vector2u  getSize() const;
        virtual Color getColor(const Vector2i&pos) const;

        virtual const vector<RectI>  &getRects() const;  // Returns all Rects which cover the Texture (for collider)

        virtual bool changesAvailable();
        virtual void changesApplied();

        virtual sf::Texture &getTexture();
        virtual sf::Image   &getImage();

        virtual void rotate(float deg);
        virtual const float &getRotation() const;

    protected:
        virtual void internalUpdateOrigin();
        virtual void internalSetOrigin(const Vector2f &origin);
        virtual void calculateBoxes();
        virtual void optimize_HitboxMap(vector<vector<RectI*>  > &map,vector<RectI> &outputColliderList);

        string m_textureFileName;
        Image  m_image;
        uint8_t m_alphaThreshold;
        vector<RectI>  m_pixelRectList;

        bool    m_changesAvailable;
        Vector2f  m_origin;
        Origin  m_originType;

        sf::Texture m_texture;
        float m_rotation;
    private:


};
#endif
