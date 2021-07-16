#ifndef PIXELPAINTER_H
#define PIXELPAINTER_H

#include "base.h"

#include "spritePainter.h"

class PixelPainter  : public SpritePainter
{
    public:
        PixelPainter();
        ~PixelPainter();

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
        //virtual inline void internal_UpdateOrigin();


        void internalSetPixel(const vector<Pixel> &pixelList);
        void internalAddPixel(const Pixel &pixel);
        void internalAddPixel(const vector<Pixel> &pixelList);

        sf::Image   *m_image;

    private:





};
#endif // PIXELPAINTER_H
