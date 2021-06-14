#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include "SFML/Graphics.hpp"
#include "vector"
#include "point.h"
#include "pixel.h"

using sf::Color;
using sf::RenderWindow;
using sf::View;
using sf::Texture;
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
        struct Text
        {
                sf::Text text;
                bool     isVisible;
        };


        PixelDisplay(const PointU &windowSize, const PointU &pixelSize);
        PixelDisplay(const PixelDisplay &other);
        virtual ~PixelDisplay();

        virtual void display();
        virtual void clear();

        virtual void setPixel(const PointU &pos, const Color &color);
        virtual void setPixel(const Pixel &pixel);
        virtual void setPixel(const vector<Pixel> &pixelList);

        virtual bool isOpen() const;

       // virtual bool
        virtual sf::Event handleEvents();
        virtual sf::Event handleEvents(const KeyEvent &eventHandler);
        virtual sf::Event handleEvents(const vector<KeyEvent> &eventHandlerList);

        virtual bool loadFontFromFile(const std::string& filename);
        virtual bool addText(Text *text);       // This function will not own the Text Object!
        virtual bool removeText(Text *text);
        virtual void clearText();

    protected:


        PointU m_windowSize;
        PointU m_pixelSize;

        RenderWindow *m_renderWindow;
        View m_windowView;
        Texture m_texture;
        Image m_image;
        Sprite m_sprite;

        Color m_clearColor;
        //sf::Text text;
        vector<Text*> m_textList;
        sf::Font m_font;
    private:



};
#endif // PIXELDISPLAY_H
