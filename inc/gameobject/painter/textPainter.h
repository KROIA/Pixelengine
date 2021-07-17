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
        inline void render(sf::RenderWindow *window,
                    float viewPortZoom,
                    DisplayStats &stats);

        virtual void setString(const string &text);
        virtual void setText(const string &text);
        virtual const Text &getText() const;

        virtual void setFont(const string &fontPath);
        virtual const Font *getFont() const;

        virtual void setCharacterSize(unsigned int size);
        virtual unsigned int getCharacterSize() const;

        virtual void setLineSpacing(float spacingFactor);
        virtual float getLineSpacing() const;

        virtual void setColor(const Color &color);
        virtual const Color &getColor() const;


        virtual void setPositionFix(bool fix);
        virtual bool getPositionFix() const;

    protected:
        virtual inline void internal_setPos(const Vector2f &pos);
        virtual inline float internal_getRotation() const;
        virtual inline void internal_setRotation(const Vector2f &rotPoint,float deg);
        virtual inline void internal_setRotation(const float &deg);
        virtual inline void internal_UpdateOrigin();
        virtual inline void internal_SetOrigin(const Vector2f &origin);
        virtual inline const Vector2f &internal_getOrigin() const;
        virtual inline void internal_CalculateFrame();

        //Vector2f        m_position;
        Text            m_text;
        Font            m_font;
        bool            m_positionFix;
        string          m_fontPath;
    private:
        void constructor(const Settings &settings);
};

#endif // TEXTPAINTER_H
