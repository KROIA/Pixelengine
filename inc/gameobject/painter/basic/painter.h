#ifndef PAINTER_H
#define PAINTER_H

#include "layeritem.h"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "pixelDisplay.h"
#include "pixel.h"
#include "point.h"
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
        virtual RectF getFrame() const;

        virtual void draw(PixelDisplay &display);

        virtual void setPos(const Vector2f &pos);

        virtual void setX(int x);
        virtual void setY(int y);

        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;

        virtual float getRotation() const;
        virtual void setRotation(const float &deg);
        virtual void rotate(const float &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const Vector2f &rotPoint,const float &deg);
        virtual void rotate_90(const Vector2f &rotPoint);
        virtual void rotate_180(const Vector2f &rotPoint);
        virtual void rotate_270(const Vector2f &rotPoint);

        virtual void updateOrigin();
        virtual void setOrigin(const Vector2f &origin);
        virtual void setOriginType(Origin origin);
        virtual Origin getOriginType() const;
        virtual const Vector2f getOrigin() const;

    protected:
        virtual void internal_rotate(const Vector2f &rotPoint,const float &deg);
        virtual void internal_rotate(const float &deg);
        virtual void internalUpdateOrigin();
        virtual void internalSetOrigin(const Vector2f &origin);

        bool    m_isVisible;

        sf::Sprite  *m_sprite;
        sf::Texture *m_texture;
        sf::Image   *m_image;
        Origin  m_originType;

    private:

        Pixel m_const_dummy_pixel;
};
#endif
