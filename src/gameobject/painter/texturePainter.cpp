#include "texturePainter.h"

TexturePainter::TexturePainter()
    :   Painter()
{
    m_sprite = new sf::Sprite;
    m_textureObj = nullptr;
}

TexturePainter::~TexturePainter()
{
    delete m_sprite;
}

void TexturePainter::draw(PixelDisplay &display)
{
    Painter::internalUpdateOrigin();
    m_sprite->setTexture(*m_texture);
    Painter::draw(display);
}
void TexturePainter::setTexture(Texture *texture)
{
    m_textureObj = texture;
    m_texture = &m_textureObj->getTexture();
    Painter::setOrigin(texture->getOrigin());
    //Painter::internalUpdateOrigin();
   // m_sprite->setTexture(*m_texture);
}
Texture *TexturePainter::getTexture()
{
    return m_textureObj;
}