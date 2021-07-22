#include "textPainter.h"


bool     TextPainter::m_standardFontLoaded = false;
Font     TextPainter::m_standardFont;
TextPainter::TextPainter()
    :   Painter()
{
    constructor(__defaultSettings);
    setRenderLayer(RenderLayerIndex::texts);
}
TextPainter::TextPainter(const Settings &settings)
    :   Painter()
{
    constructor(settings);
}
void TextPainter::constructor(const Settings &settings)
{
    if(!m_standardFontLoaded)
    {
        bool ret = m_standardFont.loadFromFile(settings.fontPath);
        if (!ret)
        {
            qDebug()  << "can't load font: "<<settings.fontPath.c_str();
        }
        else
        {

        }
        m_standardFontLoaded = true;
    }
    setVisibility(settings.isVisible);
    setPositionFix(settings.positionFix);
    setPos(settings.position);
    m_text.setFont(m_standardFont);
    m_font = m_standardFont;
  //  setFont(settings.fontPath);
    setColor(settings.color);
    setCharacterSize(settings.characterSize);
    m_text.setScale(0.1,0.1);
    m_text.setOrigin(0,0);
    Painter::setRenderLayer(settings.renderLayer);
    setScale(Vector2f(0.1,0.1));
    setEnableRelativePosition(true);
}
TextPainter::~TextPainter()
{

}
TextPainter &TextPainter::operator=(const TextPainter &other)
{
    Painter::operator=(other);
    this->m_text        = other.m_text;
    this->m_font        = other.m_font;
    this->m_positionFix = other.m_positionFix;
    return *this;
}
TextPainter::Settings  TextPainter::getSettings()const
{
    Settings settings;
    settings.fontPath       = m_fontPath;
    settings.isVisible      = m_isVisible;
    settings.position       = m_pos;
    settings.positionFix    = m_positionFix;
    settings.color          = m_text.getFillColor();
    settings.characterSize  = m_text.getCharacterSize();
    return settings;
}
bool TextPainter::needsRendering(const RectF &renderRect)
{
    if(!m_isVisible)
        return false;
    return true;
}
void TextPainter::render(sf::RenderWindow *window,
                         float viewPortZoom,
                         DisplayStats &stats)
{
    PAINTER_FUNCTION(profiler::colors::Cyan600);
 //   if(!m_isVisible || (!m_frame.intersects_fast(renderFrame) && !m_positionFix))
 //       return;

    if(m_positionFix)
    {
        sf::View m_view = window->getView();

        Vector2f textPos = m_view.getCenter()-m_view.getSize()/2.f + m_pos*viewPortZoom;
        m_text.setPosition(textPos);
        m_text.setScale(viewPortZoom*m_scale.x,viewPortZoom*m_scale.y);
    }

    window->draw(m_text);
    internal_CalculateFrame();
    /*VertexPath *frame = m_frame.getDrawable();
    window->draw(frame->line, frame->length, frame->type);
    delete frame;*/
    stats.renderText ++;
}

void TextPainter::setString(const string &text)
{
    m_text.setString(text);
    internal_CalculateFrame();
}
void TextPainter::setText(const string &text)
{
    setString(text);
}
const Text &TextPainter::getText() const
{
    return m_text;
}

void TextPainter::setFont(const string &fontPath)
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
const sf::Font *TextPainter::getFont() const
{
    return m_text.getFont();
}

void TextPainter::setCharacterSize(unsigned int size)
{
    m_text.setCharacterSize(size);
}
unsigned int TextPainter::getCharacterSize() const
{
    return m_text.getCharacterSize();
}

void TextPainter::setScale(float scale)
{
    setScale(Vector2f(scale,scale));
}
void TextPainter::setScale(const Vector2f &scale)
{
    m_scale  = scale;
    if(!m_positionFix)
    {
        m_text.setScale(m_scale);
    }
}
const Vector2f &TextPainter::getScale() const
{
    return m_scale;
}

void TextPainter::setLineSpacing(float spacingFactor)
{
    m_text.setLineSpacing(spacingFactor);
}
float TextPainter::getLineSpacing() const
{
    return m_text.getLineSpacing();
}

void TextPainter::setColor(const Color &color)
{
    m_text.setFillColor(color);
}
const Color &TextPainter::getColor() const
{
    return m_text.getFillColor();
}

void TextPainter::setPositionFix(bool fix)
{
    m_positionFix = fix;
}
bool TextPainter::getPositionFix() const
{
    return m_positionFix;
}
void TextPainter::internal_setPos(const Vector2f &pos)
{
    m_text.setPosition(pos);
}
float TextPainter::internal_getRotation() const
{
    return m_text.getRotation();
}
void TextPainter::internal_setRotation(const Vector2f &rotPoint,float deg)
{
    m_text.setRotation(deg);
}
void TextPainter::internal_setRotation(const float &deg)
{
    m_text.setRotation(deg);
}
void TextPainter::internal_UpdateOrigin()
{
    switch(m_originType)
    {
        case Origin::topLeft:
            internal_SetOrigin(Vector2f(0,0));
        break;
        case Origin::topRight:
            internal_SetOrigin(Vector2f(m_frame.getSize().x,0));
        break;
        case Origin::bottomLeft:
            internal_SetOrigin(Vector2f(0,m_frame.getSize().y));
        break;
        case Origin::bottomRight:
            internal_SetOrigin(Vector2f(m_frame.getSize().x,m_frame.getSize().y));
        break;
        case Origin::center:
            internal_SetOrigin(Vector2f(m_frame.getSize().x/2,m_frame.getSize().y/2));
        break;
        default:

        break;
    }
}
void TextPainter::internal_SetOrigin(const Vector2f &origin)
{
    m_text.setOrigin(origin);
}
const Vector2f &TextPainter::internal_getOrigin() const
{
    return m_text.getOrigin();
}
void TextPainter::internal_CalculateFrame()
{
    m_frame.setPos(m_text.getPosition());
    m_frame.setSize(m_text.getLocalBounds().getSize().x*m_text.getScale().x,
                    m_text.getLocalBounds().getSize().y*m_text.getScale().y);
}
