#ifndef TEXTUREPAINTER_H
#define TEXTUREPAINTER_H

#include "base.h"

#include "spritePainter.h"
#include "texture.h"

class TexturePainter    :   public  SpritePainter
{
    public:
        TexturePainter();
        virtual ~TexturePainter();

        virtual void setTexture(Texture *texture);
        virtual Texture *getTexture();
    protected:
        Texture *m_textureObj;
    private:
};
#endif // TEXTUREPAINTER_H
