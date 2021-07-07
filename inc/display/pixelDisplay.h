#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include "base.h"

#include "rect.h"
#include "pixel.h"
#include "displayText.h"
#include "drawUtilities.h"

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
        virtual void addSprite(Sprite *sprite);
        virtual void subscribeSprite(Sprite *sprite);
        virtual void unsubscribeSprite(Sprite *sprite);

        virtual void clearVertexLine();
        virtual void addVertexLine(VertexPath* path);
        virtual void addVertexLine(const vector<VertexPath*> &pathList);

        virtual bool isOpen() const;


        virtual void handleEvents();
        virtual void handleEvents(const KeyEvent &eventHandler);
        virtual void handleEvents(const vector<KeyEvent> &eventHandlerList);
        virtual const vector<sf::Event> &getLastEvents() const;
        virtual void zoomViewAt(sf::Vector2i pixel, float zoom);
        virtual void updateRenderFrame();
        virtual void setView(const RectF &frame);

        virtual bool addText(DisplayText *text);       // This function will not own the Text Object!
        virtual bool removeText(DisplayText *text);
        virtual void clearText();

        virtual Vector2u getWindowSize() const;
        virtual Vector2u getMapSize() const;

        virtual RenderWindow *getRenderWindow();
        //virtual Vector2f getRenderScale();

        //virtual void setRenderFramePosCenter(const Vector2f &pos);
        //virtual void setRenderFramePos(const Vector2f &pos);
        //virtual void moveRenderFrame(const Vector2f &vec);
        //virtual void setRenderFrame(const RectF &frame);
        virtual const RectF getRenderFrame() const;

        virtual unsigned long long stats_getRenderSprites() const;
        virtual unsigned long long stats_getRenderVertexPaths() const;
        virtual unsigned long long stats_getRenderText() const;

    protected:


        Vector2u m_windowSize;
        Vector2u m_pixelMapSize;

        RenderWindow *m_renderWindow;
        RectF m_renderFrame;
        sf::View m_view;

        sf::Texture m_texture;
        Image m_image;
        Sprite m_sprite;
        bool m_localPixlerUsed;

        Color m_clearColor;
        vector<DisplayText*> m_textList;
        bool                 m_textListUsed;

        vector<Sprite*>       m_spriteList;
        vector<Sprite*>      m_spriteSubscriberList;
        bool                 m_spriteListUsed;
        vector<VertexPath*>   m_vertexPathList;
        bool                 m_vertexPathUsed;
       // Vector2f             m_renderScale;
       // RectF                m_globalDisplayFrame;

        vector<sf::Event>    m_lastEventList;

    private:
        bool                 m_dragMap;
        Vector2f             m_lastMousePos;
        float                m_viewPortZoom;

        unsigned long long m_stats_renderSprites;
        unsigned long long m_stats_renderVertexPaths;
        unsigned long long m_stats_renderText;

};
#endif // PIXELDISPLAY_H
