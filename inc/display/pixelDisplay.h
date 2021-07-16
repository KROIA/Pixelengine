#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include "base.h"

#include "rect.h"
#include "pixel.h"
#include "drawUtilities.h"
#include "painter.h"
#include "signalSubscriber.h"

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
struct DisplayStats
{
    unsigned long long renderSprites;
    unsigned long long renderVertexPaths;
    unsigned long long renderText;
    unsigned long long activePainters;
    vector<unsigned long long> avtivePaintersInLayer;
};


class PixelDisplay  : private PainterSignal
{
    public:

        struct Settings
        {
            Vector2u windowSize;
            Vector2u pixelMapSize;
            Color    backgroundColor;
            sf::ContextSettings sf_contextSettings;
            size_t   renderLayers;
        };
        struct RenderLayer
        {
            bool enabled;
            size_t index;
            HashTable<Painter *>    table;
        };


        static Settings __defaultSettings;


        PixelDisplay();
        PixelDisplay(const Settings &settings);
        PixelDisplay(const Vector2u &windowSize,
                     const Vector2u &pixelMapSize,
                     const Color &backgroundColor = Color(0,0,0));
        PixelDisplay(const PixelDisplay &other);
        virtual ~PixelDisplay();

        virtual Settings getSettings() const;

        virtual void display();
        virtual void clear();

        virtual void setLayerVisibility(size_t layer, bool visibility);
        virtual bool getLayerVisibility(size_t layer);

        virtual void setPixel(const Vector2i &pos, const Color &color);
        virtual void setPixel(const Pixel &pixel);
        virtual void setPixel(const vector<Pixel> &pixelList);

        virtual void clearSprite();
        virtual void addSprite(Sprite *sprite);
        virtual void subscribeSprite(SpritePainter *sprite);
        virtual void unsubscribeSprite(SpritePainter *sprite);

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

        //virtual bool addText(DisplayText *text);       // This function will not own the Text Object!
        //virtual bool removeText(DisplayText *text);
        virtual void clearText();

        virtual const Vector2u &getWindowSize() const;
        virtual const Vector2u &getMapSize() const;

        virtual RenderWindow *getRenderWindow();
        //virtual Vector2f getRenderScale();

        //virtual void setRenderFramePosCenter(const Vector2f &pos);
        //virtual void setRenderFramePos(const Vector2f &pos);
        //virtual void moveRenderFrame(const Vector2f &vec);
        //virtual void setRenderFrame(const RectF &frame);
        virtual const RectF &getRenderFrame() const;

        virtual const DisplayStats &getStats() const;

        virtual void subscribePainter(Painter *painter);
        virtual void unsubscribePainter(Painter *painter);


    protected:

        // Signals from Painter
        virtual void renderLayerChanged(Painter *sender, size_t lastLayer, size_t &newLayer);
        virtual void isInvisible(Painter *sender);
        virtual void isVisible(Painter *sender);

        RenderWindow *m_renderWindow;
        Vector2u m_windowSize;
        Vector2u m_pixelMapSize;


        RectF m_renderFrame;
        sf::View m_view;

        sf::Texture m_texture;
        Image m_image;
        Sprite m_sprite;
        bool m_localPixlerUsed;

        Color m_backgroundColor;
        //vector<DisplayText*> m_textList;
        bool                 m_textListUsed;

        vector<Sprite*>       m_spriteList;
        vector<SpritePainter*>      m_spriteSubscriberList;
        bool                 m_spriteListUsed;
        vector<VertexPath*>   m_vertexPathList;
        bool                 m_vertexPathUsed;
       // Vector2f           m_renderLayerList       // RectF                m_globalDisplayFrame;

        vector<sf::Event>    m_lastEventList;
        vector<RenderLayer > m_renderLayerList;
        size_t               m_maxRenderLayers;

    private:
        void constructor(const Settings &settings);
        bool                m_dragMap;
        Vector2f            m_lastMousePos;
        float               m_viewPortZoom;

        DisplayStats        m_stats;


};
#endif // PIXELDISPLAY_H
