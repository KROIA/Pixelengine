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
        LayerItem(const PointF &pos);
        virtual ~LayerItem();

        virtual LayerItem &operator=(const LayerItem &other);

        virtual void swapPosToLastPos();

        virtual void setPosInitial(const PointU &pos);
        virtual void setPosInitial(const Point &pos);
        virtual void setPosInitial(const PointF &pos);
        virtual void setPosInitial(int x, int y);
        virtual void setPosInitial_F(const double &x, const double &y);

        virtual void setPos(const PointU &pos);
        virtual void setPos(const Point &pos);
        virtual void setPos(const PointF &pos);
        virtual void setPos(int x, int y);
        virtual void setPos_F(const double &x, const double &y);
        virtual Point getPos() const;
        virtual Point getLastPos() const;

        virtual void setX(int x);
        virtual void setX_F(const double &x);
        virtual void setY(int y);
        virtual void setY_F(const double &y);

        virtual int getX() const;
        virtual int getY() const;

        virtual void move(const VectorU &vec);
        virtual void move(const Vector &vec);
        virtual void move(const VectorF &vec);
        virtual void move(int deltaX, int deltaY);
        virtual void move_F(const double &deltaX, const double &deltaY);
        virtual void moveX(int delta);
        virtual void moveX_F(const double &delta);
        virtual void moveY(int delta);
        virtual void moveY_F(const double &delta);

        virtual void setToLastPos();

    protected:
        PointF  m_floatingPos;
        PointF  m_lastPos;
    private:


};
#endif // LAYERITEM_H
