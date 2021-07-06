#ifndef TEXTUREPAINTER_H
#define TEXTUREPAINTER_H

#include "base.h"

#include "painter.h"
#include "texture.h"

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
