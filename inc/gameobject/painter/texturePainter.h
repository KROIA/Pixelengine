#ifndef TEXTUREPAINTER_H
#define TEXTUREPAINTER_H

#include "painter.h"
#include "texture.h"
/*
 TexturePainter erbt von Painter und implementiert
 die Klasse Texture.

 Texture hat hat ein sf::Image, sf::texture welche dem TexturePainter
 als ptr übergeben werden.

 TexturePainter instanziert m_sprite selbst und ist auf eine Textur angewiesen.

 */
class TexturePainter    :   public  Painter
{
    public:
        TexturePainter();
        virtual ~TexturePainter();

        virtual void draw(PixelDisplay &display);

        virtual void setTexture(Texture *texture);
        virtual Texture *getTexture();
    protected:
        Texture *m_textureObj;

    private:
};
#endif // TEXTUREPAINTER_H
