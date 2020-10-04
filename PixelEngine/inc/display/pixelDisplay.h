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

struct KeyEvent{
        sf::Keyboard::Key key;
        fp callbackFunction;
};


class PixelDisplay
{
    public:
        PixelDisplay(const PointU &windowSize, const PointU &pixelSize);
        PixelDisplay(const PixelDisplay &other);
        virtual ~PixelDisplay();

        virtual void display();
        virtual void clear();

        virtual void setPixel(const PointU &pos, const Color &color);
        virtual void setPixel(const Pixel &pixel);
        virtual void setPixel(const vector<Pixel> &pixelList);

        virtual bool isOpen() const;

        virtual bool handleEvents();
        virtual bool handleEvents(const KeyEvent &eventHandler);
        virtual bool handleEvents(const vector<KeyEvent> &eventHandlerList);

    protected:


        PointU m_windowSize;
        PointU m_pixelSize;

        RenderWindow *m_renderWindow;
        View m_windowView;
        Texture m_texture;
        Image m_image;
        Sprite m_sprite;

        Color m_clearColor;

    private:



};
#endif // PIXELDISPLAY_H
