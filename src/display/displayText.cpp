#include "displayText.h"

DisplayText::DisplayText()
{
    setFont("C:\\Windows\\Fonts\\consolab.ttf");
    setCharacterSize(20);
    setColor(Color(255,255,255,255));
    setText("");
    setVisibility(false);
    setPixelRatio(1);
    setPositionFix(false);
    m_text.setScale(0.1,0.1);
    m_text.setOrigin(0,0);
}
DisplayText::~DisplayText()
{

}
DisplayText &DisplayText::operator=(const DisplayText &other)
{
    this->m_isVisible   = other.m_isVisible;
    this->m_position    = other.m_position;
    this->m_text        = other.m_text;
    this->m_font        = other.m_font;
    this->m_pixelRatio  = other.m_pixelRatio;
    this->m_positionFix = other.m_positionFix;
    return *this;
}
void DisplayText::setVisibility(bool isVisible)
{
    m_isVisible = isVisible;
}
bool DisplayText::isVisible() const
{
    return m_isVisible;
}

void DisplayText::setString(const string &text)
{
    m_text.setString(text);
}
void DisplayText::setText(const string &text)
{
    m_text.setString(text);
}
const Text &DisplayText::getText() const
{
    return m_text;
}
void DisplayText::setPixelRatio(float ratio)
{
    m_pixelRatio = ratio;
    m_text.setPosition(m_position * m_pixelRatio);
}

void DisplayText::setFont(const string &fontPath)
{
    bool ret = m_font.loadFromFile(fontPath);
    if (!ret)
    {
        qDebug()  << "can't load font: "<<fontPath.c_str();
    }
    else
    {
        m_text.setFont(m_font);
    }

}
const sf::Font *DisplayText::getFont() const
{
    return m_text.getFont();
}

void DisplayText::setCharacterSize(unsigned int size)
{
    m_text.setCharacterSize(size);
}
unsigned int DisplayText::getCharacterSize() const
{
    return m_text.getCharacterSize();
}

void DisplayText::setLineSpacing(float spacingFactor)
{
    m_text.setLineSpacing(spacingFactor);
}
float DisplayText::getLineSpacing() const
{
    return m_text.getLineSpacing();
}

void DisplayText::setColor(const Color &color)
{
    m_text.setFillColor(color);
}
const Color &DisplayText::getColor() const
{
    return m_text.getFillColor();
}

void DisplayText::setPos(const Vector2f &position)
{
    m_position = position;
    m_text.setPosition(m_position * m_pixelRatio);
}
const Vector2f &DisplayText::getPos() const
{
    return m_position;
}
void DisplayText::move(const Vector2f &vec)
{
    m_position += vec;
    m_text.setPosition(m_position * m_pixelRatio);
}
void DisplayText::setPositionFix(bool fix)
{
    m_positionFix = fix;
    /*if(m_positionFix)
        m_pixelRatio = 1;
    else
        m_pixelRatio = globalScale.x;*/
}
bool DisplayText::getPositionFix() const
{
    return m_positionFix;
}
