#ifndef PAINTER_H
#define PAINTER_H

#include "base.h"
#include "layeritem.h"
//#include "pixelDisplay.h"
#include "signalSubscriber.h"
#include "texture.h"

class Painter   :   public  LayerItem
{
    public:

        Painter();
        Painter(const Painter &other);

        virtual ~Painter();
        virtual const Painter &operator=(const Painter &other);
        virtual RectF getFrame() const;

       // void setDisplay(PixelDisplay *display);
        virtual void setVisibility(bool isVisible);
        virtual bool isVisible() const;
        virtual bool needsRendering(const RectF &renderRect);
        virtual void render(sf::RenderWindow *window,
                            float viewPortZoom,
                            DisplayStats &stats) = 0;

        virtual void setPos(const Vector2f &pos);
        virtual void move(const Vector2f vec);

        float getRotation() const;
        void setRotation(float deg);
        void rotate(float deg);
        void rotate_90();
        void rotate_180();
        void rotate_270();
        void setRotation(const Vector2f &rotPoint,float deg);
        void rotate(const Vector2f &rotPoint,float deg);
        void rotate_90(const Vector2f &rotPoint);
        void rotate_180(const Vector2f &rotPoint);
        void rotate_270(const Vector2f &rotPoint);

        void updateOrigin();
        void setOrigin(const Vector2f &origin);
        void setOriginType(Origin origin);
        Origin getOriginType() const;
        const Vector2f getOrigin() const;

        void setRenderLayer(size_t layer);
        size_t getRenderLayer() const;

        void subscribe_painterSignal(PainterSignal *subscriber);
        void unsubscribe_painterSignal(PainterSignal *subscriber);
        void unsubscribeAll_painterSignal();


    protected:
        virtual void internal_setPos(const Vector2f &pos) = 0;
        virtual float internal_getRotation() const = 0;
        virtual void internal_setRotation(const Vector2f &rotPoint,float deg) = 0;
        virtual void internal_setRotation(const float &deg) = 0;
        virtual void internal_UpdateOrigin() = 0;
        virtual void internal_SetOrigin(const Vector2f &origin) = 0;
        virtual const Vector2f &internal_getOrigin() const = 0;
        virtual void internal_CalculateFrame() = 0;



        bool        m_isVisible;

        Origin      m_originType;
        RectF       m_frame;
        size_t      m_renderlayer;

        PainterSubscriberList m_signalSubscriber;
      //  PixelDisplay    *m_display;

    private:
};
#endif
