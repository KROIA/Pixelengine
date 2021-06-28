#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include "SFML/Graphics.hpp"
//#include "vector"
//#include "point.h"
#include "pixel.h"
#include "displayText.h"
#include "drawUtilities.h"

#include "profiler.h"

using sf::Color;
using sf::RenderWindow;
using sf::View;
using sf::Vector2u;
using sf::Image;
using sf::Sprite;
using std::vector;

typedef void (*fp)();

struct KeyEvent
{
        sf::Keyboard::Key key;
        fp callbackFunction;
};



class PixelDisplay
{
    public:

       /* struct Text
        {
                sf::Text text;
                bool     isVisible;
        };*/


        PixelDisplay(const Vector2u &windowSize, const Vector2u &pixelSize);
        PixelDisplay(const PixelDisplay &other);
        virtual ~PixelDisplay();

        virtual void display();
        virtual void clear();

        virtual void setPixel(const Vector2i &pos, const Color &color);
        virtual void setPixel(const Pixel &pixel);
        virtual void setPixel(const vector<Pixel> &pixelList);

        virtual void clearSprite();
        virtual void addSprite(Sprite &sprite);

        virtual void clearVertexLine();
        virtual void addVertexLine(VertexPath path);

        virtual bool isOpen() const;


        virtual sf::Event handleEvents();
        virtual sf::Event handleEvents(const KeyEvent &eventHandler);
        virtual sf::Event handleEvents(const vector<KeyEvent> &eventHandlerList);

        virtual bool addText(DisplayText *text);       // This function will not own the Text Object!
        virtual bool removeText(DisplayText *text);
        virtual void clearText();

        virtual Vector2u getWindowSize() const;
        virtual Vector2u getMapSize() const;

        virtual RenderWindow *getRenderWindow();
        virtual Vector2f getRenderScale();

    protected:


        Vector2u m_windowSize;
        Vector2u m_pixelMapSize;

        RenderWindow *m_renderWindow;
        View m_windowView;

        sf::Texture m_texture;
        Image m_image;
        Sprite m_sprite;

        Color m_clearColor;
        //sf::Text text;
        vector<DisplayText*> m_textList;
        //sf::Font m_font;

        vector<Sprite>       m_spriteList;
        vector<VertexPath>   m_vertexPathList;
        Vector2f             m_spriteScale;
    private:



};
#endif // PIXELDISPLAY_H
