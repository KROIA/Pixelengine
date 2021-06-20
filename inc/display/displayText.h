#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H

#include "SFML/Graphics/Text.hpp"
#include "point.h"

using sf::Text;
using sf::Font;
using sf::Color;
using std::string;

class DisplayText
{
    public:
        DisplayText();
        virtual ~DisplayText();

        virtual void setVisibility(bool isVisible);
        virtual bool isVisible() const;

        virtual void setString(const string &text);
        virtual void setText(const string &text);
        virtual const Text &getText() const;
        virtual void setPixelRatio(double ratio);

        virtual void setFont(const string &fontPath);
        virtual const sf::Font *getFont() const;

        virtual void setCharacterSize(unsigned int size);
        virtual unsigned int getCharacterSize() const;

        virtual void setLineSpacing(float spacingFactor);
        virtual float getLineSpacing() const;

        virtual void setColor(const Color &color);
        virtual const Color &getColor() const;

        virtual void setPos(const Point &position);
        virtual const Point &getPos() const;



    protected:
        bool    m_isVisible;
        Point   m_position;
        Text    m_text;
        Font    m_font;
        double  m_pixelRatio;
    private:

};

#endif // DISPLAYTEXT_H
