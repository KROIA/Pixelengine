#include "displayText.h"

DisplayText::DisplayText()
{
    setFont("C:\\Windows\\Fonts\\consolab.ttf");
    setCharacterSize(20);
    setColor(Color(255,255,255,255));
    setText("");
    setVisibility(false);
    setPixelRatio(1);
}
DisplayText::~DisplayText()
{

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
