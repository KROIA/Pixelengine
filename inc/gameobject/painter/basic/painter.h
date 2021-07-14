#ifndef PAINTER_H
#define PAINTER_H

#include "base.h"

#include "layeritem.h"
#include "pixelDisplay.h"
#include "pixel.h"
#include "texture.h"

class Painter   :   public  LayerItem
{
    public:

        Painter();
        Painter(const Painter &other);

        virtual ~Painter();
        virtual const Painter &operator=(const Painter &other);
        virtual RectF getFrame() const;

        virtual void draw(PixelDisplay &display);
        virtual void subscribeToDisplay(PixelDisplay &display);
        virtual void unsubscribeToDisplay(PixelDisplay &display);

        virtual void setPos(const Vector2f &pos);

        virtual void setX(int x);
        virtual void setY(int y);

        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;

        virtual float getRotation() const;
        virtual void setRotation(float deg);
        virtual void rotate(float deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const Vector2f &rotPoint,float deg);
        virtual void rotate_90(const Vector2f &rotPoint);
        virtual void rotate_180(const Vector2f &rotPoint);
        virtual void rotate_270(const Vector2f &rotPoint);

        virtual void updateOrigin();
        virtual void setOrigin(const Vector2f &origin);
        virtual void setOriginType(Origin origin);
        virtual Origin getOriginType() const;
        virtual const Vector2f getOrigin() const;

        virtual sf::Sprite *getSprite() const;

    protected:
        virtual void internal_rotate(const Vector2f &rotPoint,float deg);
        virtual void internal_rotate(const float &deg);
        virtual void internalUpdateOrigin();
        virtual void internalSetOrigin(const Vector2f &origin);
        virtual void internalCalculateFrame();

        bool    m_isVisible;

        sf::Sprite  *m_sprite;
        sf::Texture *m_texture;
        sf::Image   *m_image;
        Origin       m_originType;

        RectF        m_frame;

    private:

        bool m_spriteHasSubscribedToDisplay;
        //Vector2f m_renderScale;
        Pixel m_const_dummy_pixel;
};
#endif
