#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include "base.h"

#include "rect.h"
#include "pixel.h"
#include "drawUtilities.h"
#include "painter.h"
#include "pixelPainter.h"
#include "signalSubscriber.h"
#include "displayInterface.h"

using sf::Color;
using sf::RenderWindow;
using sf::View;
using sf::Vector2u;
using sf::Image;
using sf::Sprite;
using std::vector;

typedef void (*fp)();


class PixelDisplay  : private PainterSignal, public DisplayInterface
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

        virtual void setPixel(const Vector2u &pos, const Color &color);
        virtual void setPixel(const Pixel &pixel);
        virtual void setPixel(const vector<Pixel> &pixelList);

        virtual bool isOpen() const;

        virtual void handleEvents();
        virtual const vector<sf::Event> &getLastEvents() const;
        virtual void zoomViewAt(sf::Vector2i pixel, float zoom);
        virtual void updateRenderFrame();
        virtual void setView(const RectF &frame);
        virtual void setCameraZoom(float zoom);
        virtual void setCameraPos(const Vector2f &pos);

        virtual const Vector2u &getWindowSize() const;
        virtual const Vector2u &getMapSize() const;

        virtual RenderWindow *getRenderWindow();
        virtual const RectF &getRenderFrame() const;

        virtual const DisplayStats &getStats() const;

        virtual void subscribePainter(Painter *painter);
        virtual void unsubscribePainter(Painter *painter);
        virtual void subscribePainter(const vector<Painter *> painterList);
        virtual void unsubscribePainter(const vector<Painter *> painterList);


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

        PixelPainter *m_localPixelPainter;
        bool m_localPixlerUsed;

        Color m_backgroundColor;

        vector<sf::Event>    m_lastEventList;
        vector<RenderLayer > m_renderLayerList;
        size_t               m_maxRenderLayers;

    private:
        void constructor(const Settings &settings);
        bool                m_dragMap;
        Vector2f            m_lastMousePos;
        float               m_viewPortZoom;

        DisplayStats        m_stats;
        pthread_mutex_t     m_mutex;

};
#endif // PIXELDISPLAY_H
