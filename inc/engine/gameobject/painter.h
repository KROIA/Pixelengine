#ifndef PAINTER_H
#define PAINTER_H

#include "SFML/Graphics.hpp"
#include "pixelDisplay.h"
#include "pixel.h"
#include "point.h"
#include "vector.h"

using std::vector;

class Painter
{
    public:
        Painter();
        Painter(const Painter &other);

        virtual ~Painter();

        virtual void draw(PixelDisplay &display);

        virtual void setPos(const Point &pos);
        virtual void setPos(const int &x, const int &y);
        virtual const Point &getPos() const;

    protected:

    private:
        Point m_bodyPos;
        vector<Pixel> m_pixelList;
};
#endif
