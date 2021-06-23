#ifndef PAINTER_H
#define PAINTER_H

#include "layeritem.h"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "pixelDisplay.h"
#include "pixel.h"
#include "point.h"
#include "vector.h"
#include "texture.h"

#include "profiler.h"

using std::vector;
using sf::Vector2f;

class Painter   :   public  LayerItem
{
    public:
        Painter();
        Painter(const Painter &other);

        virtual ~Painter();
        virtual const Painter &operator=(const Painter &other);

        //virtual void reserve(const size_t amount);

       // virtual void setPixel(const vector<Pixel> &pixelList);
       // virtual void addPixel(const Pixel &pixel);
       // virtual void addPixel(const vector<Pixel> &pixelList);
       // virtual const Pixel &getPixel(const size_t &index) const;
       // virtual const Pixel &getPixel(const Point &pixelPos) const;
       // virtual const Pixel &getPixel(int x, int y) const;
       // virtual size_t getPixelAmount() const;
       // virtual void setPixelColor(const size_t &index, const Color &color);
       // virtual void setPixelColor(const Point &pixelPos, const Color &color);
       // virtual void setPixelColor(int x, int y, const Color &color);
       // virtual void setPixelColor(const Color &color);
       // virtual Rect getFrame() const;
       // virtual void setFrameVisibility(bool isVisible);
       // virtual bool isFrameVisible();

        virtual void draw(PixelDisplay &display);

        virtual void setPos(const Point &pos);
        virtual void setPos(int x, int y);

        virtual void setX(int x);
        virtual void setY(int y);

        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;

       // virtual void erasePixel(const size_t &index);
       // virtual void erasePixel(const Point &pixelPos);
       // virtual void erasePixel(int x, int y);
       // virtual void clear(); // Deletes all pixels

        virtual double getRotation() const;
        virtual void setRotation(const double &deg);
        virtual void rotate(const double &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const PointF &rotationPoint,const double &deg);
        virtual void rotate_90(const PointF &rotationPoint);
        virtual void rotate_180(const PointF &rotationPoint);
        virtual void rotate_270(const PointF &rotationPoint);

        virtual void setTexture(Texture *texture);

        virtual void setOrigin(const PointF &origin);
        virtual void setOriginType(Texture::Origin origin);
        virtual Texture::Origin getOriginType() const;
        virtual const PointF &getOrigin() const;

    protected:
       // virtual void internalSetPixel(const vector<Pixel> &pixelList);
       // virtual void internalAddPixel(const Pixel &pixel);
       // virtual void internalAddPixel(const vector<Pixel> &pixelList);
       // virtual void updateFrame();

        //vector<Pixel> m_pixelList;
        bool    m_isVisible;

        double  m_rotationRad;
        //Rect    m_frame;
        //bool    m_frameVisible;

        //sf::Texture m_texture;
        sf::Sprite  m_sprite;
        Texture   *m_texture;
    private:

        virtual void internal_rotate(const PointF &rotPoint,const double &deg);
        virtual void internal_rotate(const double &deg);

        Pixel m_const_dummy_pixel;
};
#endif
