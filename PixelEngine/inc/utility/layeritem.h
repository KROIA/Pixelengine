#ifndef LAYERITEM_H
#define LAYERITEM_H

#include "vector"
#include "point.h"
#include "vector.h"

#include <QDebug>

using std::vector;

class LayerItem
{
    public:
        LayerItem();
        LayerItem(const LayerItem &other);
        LayerItem(const Point &pos);
        virtual ~LayerItem();

        virtual LayerItem &operator=(const LayerItem &other);

        virtual void setPosInitial(const Point &pos);
        virtual void setPosInitial(const int &x, const int &y);

        virtual void setPos(const Point &pos);
        virtual void setPos(const int &x, const int &y);
        virtual const Point &getPos() const;

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual const int &getX() const;
        virtual const int &getY() const;

        virtual void move(const Vector &vec);
        virtual void move(const int &deltaX, const int &deltaY);
        virtual void moveX(const int &delta);
        virtual void moveY(const int &delta);

        virtual void setToLastPos();

    protected:
        Point m_pos;
        Point m_lastPos;
    private:

};
#endif // LAYERITEM_H
