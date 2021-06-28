/*
    Pixelpainter erbt von Painter und instanziert
    Image, Texture und Sprite vom Painter

    Image bearbeitbar mit einer fixen grösse

 */
#ifndef PIXELPAINTER_H
#define PIXELPAINTER_H

#include "painter.h"
#include "SFML/Graphics/Rect.hpp"

class PixelPainter  : public Painter
{
    public:
        PixelPainter();
        ~PixelPainter();

        virtual void draw(PixelDisplay &display);

        virtual void setPixel(const vector<Pixel> &pixelList);
        virtual void addPixel(unsigned int x, unsigned int y, Color color);
        virtual void addPixel(const Pixel &pixel);
        virtual void addPixel(const vector<Pixel> &pixelList);
        //virtual const Pixel &getPixel(const size_t &index) const;
        virtual const Pixel getPixel(const Point &pixelPos) const;
        virtual const Pixel getPixel(unsigned int x,unsigned int y) const;
        //virtual size_t getPixelAmount() const;
        //virtual void setPixelColor(const size_t &index, const Color &color);
        virtual void setPixelColor(const Point &pixelPos, const Color &color);
        virtual void setPixelColor(unsigned int x,unsigned int y, const Color &color);
        //virtual void setPixelColor(const Color &color);

        virtual void resize(PointU size);
        virtual void clear();

        // dummy
        //void setTextureOnPainter(Texture &texture){return;}
        //bool checkTextureUpdateForPainter(){return false;}
    protected:
        virtual void internalUpdateOrigin();


        virtual void internalSetPixel(const vector<Pixel> &pixelList);
        virtual void internalAddPixel(const Pixel &pixel);
        virtual void internalAddPixel(const vector<Pixel> &pixelList);


      //  sf::Texture m_sfTexture;
      //  Image m_image;
    private:





};
#endif // PIXELPAINTER_H
