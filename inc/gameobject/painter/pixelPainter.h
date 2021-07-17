#ifndef PIXELPAINTER_H
#define PIXELPAINTER_H

#include "base.h"

#include "spritePainter.h"

class PixelPainter  : public Painter
{
    public:
        PixelPainter();
        ~PixelPainter();

        virtual inline void render(sf::RenderWindow *window,
                            float viewPortZoom,
                            DisplayStats &stats);

        void setPixel(const Pixel &pixel);
        void setPixel(const vector<Pixel> &pixelList);
        void addPixel(unsigned int x, unsigned int y, Color color);
        void addPixel(const Pixel &pixel);
        void addPixel(const vector<Pixel> &pixelList);
        const Pixel getPixel(const Vector2i&pixelPos) const;
        const Pixel getPixel(unsigned int x,unsigned int y) const;
        void setPixelColor(const Vector2i&pixelPos, const Color &color);
        void setPixelColor(unsigned int x,unsigned int y, const Color &color);

        void update();
        void resize(Vector2u size);
        void clear();

    protected:
        virtual inline void internal_setPos(const Vector2f &pos);
        virtual inline float internal_getRotation() const;
        virtual inline void internal_setRotation(const Vector2f &rotPoint,float deg);
        virtual inline void internal_setRotation(const float &deg);
        virtual inline void internal_UpdateOrigin();
        virtual inline void internal_SetOrigin(const Vector2f &origin);
        virtual inline const Vector2f &internal_getOrigin() const;
        virtual inline void internal_CalculateFrame();



        void internalSetPixel(const vector<Pixel> &pixelList);
        void internalAddPixel(const Pixel &pixel);
        void internalAddPixel(const vector<Pixel> &pixelList);

        //sf::Image   *m_image;
        vector<vector<sf::VertexArray> > m_pixMap;
        Vector2f m_lastPos;
    private:





};
#endif // PIXELPAINTER_H
