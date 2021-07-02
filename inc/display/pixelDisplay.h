#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include "SFML/Graphics.hpp"
//#include "vector"
//#include "point.h"
#include "rect.h"
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
        virtual void addVertexLine(const VertexPath &path);
        virtual void addVertexLine(const vector<VertexPath> &pathList);

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

        virtual void setRenderFramePosCenter(const Vector2f &pos);
        virtual void setRenderFramePos(const Vector2f &pos);
        virtual void moveRenderFrame(const Vector2f &vec);
        virtual void setRenderFrame(const RectF &frame);
        virtual const RectF &getRenderFrame() const;

    protected:


        Vector2u m_windowSize;
        Vector2u m_pixelMapSize;

        RenderWindow *m_renderWindow;
        View m_windowView;

        sf::Texture m_texture;
        Image m_image;
        Sprite m_sprite;
        bool m_localPixlerUsed;

        Color m_clearColor;
        vector<DisplayText*> m_textList;
        bool                 m_textListUsed;

        vector<Sprite>       m_spriteList;
        bool                 m_spriteListUsed;
        vector<VertexPath>   m_vertexPathList;
        bool                 m_vertexPathUsed;
        Vector2f             m_spriteScale;
        RectF                m_globalDisplayFrame;

    private:
        bool                 m_dragMap;
        Vector2f             m_lastMousePos;


};
#endif // PIXELDISPLAY_H
