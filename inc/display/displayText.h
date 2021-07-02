#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
//#include "point.h"

#include <QDebug>
#include "profiler.h"

using sf::Text;
using sf::Font;
using sf::Color;
using sf::Vector2f;
using std::string;

class DisplayText
{
    public:
        DisplayText();
        virtual ~DisplayText();

        virtual DisplayText &operator=(const DisplayText &other);

        virtual void setVisibility(bool isVisible);
        virtual bool isVisible() const;

        virtual void setString(const string &text);
        virtual void setText(const string &text);
        virtual const Text &getText() const;
        virtual void setPixelRatio(float ratio);

        virtual void setFont(const string &fontPath);
        virtual const Font *getFont() const;

        virtual void setCharacterSize(unsigned int size);
        virtual unsigned int getCharacterSize() const;

        virtual void setLineSpacing(float spacingFactor);
        virtual float getLineSpacing() const;

        virtual void setColor(const Color &color);
        virtual const Color &getColor() const;

        virtual void setPos(const Vector2f &position);
        virtual const Vector2f &getPos() const;

        virtual void move(const Vector2f &vec);

        virtual void setPositionFix(bool fix);
        virtual bool getPositionFix() const;

    protected:
        bool            m_isVisible;
        Vector2f        m_position;
        Text            m_text;
        Font            m_font;
        float           m_pixelRatio;
        bool            m_positionFix;
    private:

};

#endif // DISPLAYTEXT_H
