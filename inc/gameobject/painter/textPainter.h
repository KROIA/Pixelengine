#ifndef TEXTPAINTER_H
#define TEXTPAINTER_H

#include "painter.h"

using sf::Text;
using sf::Font;
using sf::Color;
using sf::Vector2f;
using std::string;


class TextPainter   :   public Painter
{
    public:
        struct Settings
        {
            bool isVisible;
            bool positionFix;
            Vector2f position;
            string fontPath;
            Color color;
            unsigned int characterSize;
            size_t renderLayer;
        };
        static Settings __defaultSettings;

        TextPainter();
        TextPainter(const Settings &settings);
        virtual ~TextPainter();

        virtual TextPainter &operator=(const TextPainter &other);
        virtual Settings  getSettings()const;

        bool needsRendering(const RectF &renderRect);
        void render(sf::RenderWindow *window,
                    float viewPortZoom,
                    DisplayStats &stats);

        virtual void setString(const string &text);
        virtual void setText(const string &text);
        virtual const Text &getText() const;

        virtual void setFont(const string &fontPath);
        virtual const Font *getFont() const;

        virtual void setCharacterSize(unsigned int size);
        virtual unsigned int getCharacterSize() const;

        virtual void setScale(float scale);
        virtual void setScale(const Vector2f &scale);
        virtual const Vector2f &getScale() const;

        virtual void setLineSpacing(float spacingFactor);
        virtual float getLineSpacing() const;

        virtual void setColor(const Color &color);
        virtual const Color &getColor() const;


        virtual void setPositionFix(bool fix);
        virtual bool getPositionFix() const;

    protected:
        virtual void internal_setPos(const Vector2f &pos);
        virtual float internal_getRotation() const;
        virtual void internal_setRotation(const Vector2f &rotPoint,float deg);
        virtual void internal_setRotation(const float &deg);
        virtual void internal_UpdateOrigin();
        virtual void internal_SetOrigin(const Vector2f &origin);
        virtual const Vector2f &internal_getOrigin() const;
        virtual void internal_CalculateFrame();

        //Vector2f        m_position;
        Text            m_text;
        Font            m_font;
        bool            m_positionFix;
        string          m_fontPath;
        Vector2f        m_scale;
    private:
        void constructor(const Settings &settings);
        static bool     m_standardFontLoaded;
        static Font     m_standardFont;
};

#endif // TEXTPAINTER_H
