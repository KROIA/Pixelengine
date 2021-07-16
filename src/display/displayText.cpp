/*#include "displayText.h"



DisplayText::DisplayText()
{


    constructor(__defaultSettings);
}
DisplayText::DisplayText(const Settings &settings)
{
    constructor(settings);
}
void DisplayText::constructor(const Settings &settings)
{
    setVisibility(settings.isVisible);
    setPositionFix(settings.positionFix);
    setPos(settings.position);
    setFont(settings.fontPath);
    setColor(settings.color);
    setCharacterSize(settings.characterSize);
    m_text.setScale(0.1,0.1);
    m_text.setOrigin(0,0);
*/

    constructor(__defaultSettings);
}
DisplayText::DisplayText(const Settings &settings)
{
    constructor(settings);
}
void DisplayText::constructor(const Settings &settings)
{
    setVisibility(settings.isVisible);
    setPositionFix(settings.positionFix);
    setPos(settings.position);
    setFont(settings.fontPath);
    setColor(settings.color);
    setCharacterSize(settings.characterSize);
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
    //this->m_pixelRatio  = other.m_pixelRatio;
    this->m_positionFix = other.m_positionFix;
    return *this;
}
DisplayText::Settings  DisplayText::getSettings()const
{
    Settings settings;
    settings.fontPath       = m_fontPath;
    settings.isVisible      = m_isVisible;
    settings.position       = m_position;
    settings.positionFix    = m_positionFix;
    settings.color          = m_text.getFillColor();
    settings.characterSize  = m_text.getCharacterSize();
    return settings;
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
    m_text.setPosition(m_position );
}
const Vector2f &DisplayText::getPos() const
{
    return m_position;
}
void DisplayText::move(const Vector2f &vec)
{
    m_position += vec;
    m_text.setPosition(m_position );
}
void DisplayText::setPositionFix(bool fix)
{
    m_positionFix = fix;

}
bool DisplayText::getPositionFix() const
{
    return m_positionFix;
}
*/
