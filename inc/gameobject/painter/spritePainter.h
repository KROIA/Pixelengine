#ifndef SPRITEPAINTER_H
#define SPRITEPAINTER_H

#include "painter.h"

class SpritePainter   :   public  Painter
{
    public:

        SpritePainter();
        SpritePainter(const SpritePainter &other);

        virtual ~SpritePainter();
        virtual const SpritePainter &operator=(const SpritePainter &other);

        inline void render(sf::RenderWindow *window,
                    float viewPortZoom,
                    DisplayStats &stats);

        //sf::Sprite *getSprite() const;

    protected:
        virtual inline void internal_setPos(const Vector2f &pos);
        virtual inline float internal_getRotation() const;
        virtual inline void internal_setRotation(const Vector2f &rotPoint,float deg);
        virtual inline void internal_setRotation(const float &deg);
        virtual inline void internal_UpdateOrigin();
        virtual inline void internal_SetOrigin(const Vector2f &origin);
        virtual inline const Vector2f &internal_getOrigin() const;
        virtual inline void internal_CalculateFrame();

        sf::Sprite  *m_sprite;
        sf::Texture *m_texture;
        //sf::Image   *m_image;

    private:
        Pixel m_const_dummy_pixel;
};
#endif
