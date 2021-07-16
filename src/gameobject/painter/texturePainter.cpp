#include "texturePainter.h"

TexturePainter::TexturePainter()
    :   SpritePainter()
{
    m_textureObj    = nullptr;
    m_texture       = nullptr;
}

TexturePainter::~TexturePainter()
{

}
void TexturePainter::setTexture(Texture *texture)
{
    m_textureObj = texture;
    m_texture = &m_textureObj->getTexture();
    m_sprite->setTexture(*m_texture);
    SpritePainter::setOrigin(texture->getOrigin());
}
Texture *TexturePainter::getTexture()
{
    return m_textureObj;
}
