#ifndef PAINTER_H
#define PAINTER_H

#include "layeritem.h"
#include "SFML/Graphics.hpp"
#include "pixelDisplay.h"
#include "pixel.h"
#include "point.h"
#include "vector.h"

using std::vector;

class Painter   :   public  LayerItem
{
    public:
        Painter();
        Painter(const Painter &other);

        virtual ~Painter();

        virtual void addPixel(const Pixel &pixel);

        virtual void draw(PixelDisplay &display);

        virtual void setPos(const Point &pos);
        virtual void setPos(const int &x, const int &y);

    protected:
        vector<Pixel> m_pixelList;
    private:

};
#endif
