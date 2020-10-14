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
        virtual const Painter &operator=(const Painter &other);

        virtual void reserve(const size_t amount);

        virtual void addPixel(const Pixel &pixel);
        virtual const Pixel &getPixel(const size_t &index) const;
        virtual size_t getPixelAmount() const;
        virtual void setPixelColor(const size_t &index, const Color &color);
        virtual void setPixelColor(const Color &color);

        virtual void draw(PixelDisplay &display);

        virtual void setPos(const Point &pos);
        virtual void setPos(int x, int y);

        virtual void setX(int x);
        virtual void setY(int y);

        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;

        virtual void erasePixel(const size_t &index);
        virtual void clear(); // Deletes all pixels

        virtual double getRotation() const;
        virtual void setRotation(const double &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const PointF &rotationPoint,const double &deg);
        virtual void rotate_90(const PointF &rotationPoint);
        virtual void rotate_180(const PointF &rotationPoint);
        virtual void rotate_270(const PointF &rotationPoint);

    protected:
        vector<Pixel> m_pixelList;
        bool    m_isVisible;

        double  m_rotationRad;
    private:

        virtual void rotate(const PointF &rotPoint,const double &rad);

};
#endif
