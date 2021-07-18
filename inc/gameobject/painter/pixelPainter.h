#ifndef PIXELPAINTER_H
#define PIXELPAINTER_H

//#include "base.h"

#include "spritePainter.h"
#include <SFML/Window/GlResource.hpp>
#include <gl\gl.h>								// Header File For The OpenGL32 Library
#include <gl\glu.h>								// Header File For The GLu32 Library
#include <gl\glaux.h>

class PixelPainter  : public SpritePainter
{
    public:
        PixelPainter();
        ~PixelPainter();

        virtual void render(sf::RenderWindow *window,
                    float viewPortZoom,
                    DisplayStats &stats);

        void setPixel(const Pixel &pixel);
        void setPixel(const vector<Pixel> &pixelList);
      // void addPixel(unsigned int x, unsigned int y, Color color);
      // void addPixel(const Pixel &pixel);
      // void addPixel(const vector<Pixel> &pixelList);
        const Pixel getPixel(const Vector2u &pixelPos) const;
        const Pixel getPixel(unsigned int x,unsigned int y) const;
        void setPixelColor(const Vector2u &pixelPos, const Color &color);
        void setPixelColor(unsigned int x,unsigned int y, const Color &color);

        const Uint8* getPixelsPtr() const;
        const Uint8* getPixelsPtr(unsigned int x,unsigned int y) const;



        void update();
        void resize(Vector2u size);
        void clear();

    protected:
        //virtual void internal_UpdateOrigin();


        void internalSetPixel(const vector<Pixel> &pixelList);
       // void internalAddPixel(const Pixel &pixel);
       // void internalAddPixel(const vector<Pixel> &pixelList);

        sf::Image   *m_image;
        bool         m_needsUpdate;
       // Uint8*       m_pixels;
       // size_t       m_width;
       // size_t       m_height;
       // unsigned int m_textureID;

    private:





};
#endif // PIXELPAINTER_H
