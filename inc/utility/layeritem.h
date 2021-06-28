#ifndef LAYERITEM_H
#define LAYERITEM_H

#include <SFML/System/Vector2.hpp>
#include "profiler.h"
#include <QDebug>

using sf::Vector2f;
using sf::Vector2i;


class LayerItem
{
    public:
        LayerItem();
        LayerItem(const LayerItem &other);
        LayerItem(int x, int y);
        LayerItem(float x, float y);
        LayerItem(const Vector2f &pos);
        LayerItem(const Vector2i &pos);
        virtual ~LayerItem();

        virtual LayerItem &operator=(const LayerItem &other);

        virtual void swapPosToLastPos();

        virtual void setPosInitial(const Vector2f &pos);
        virtual void setPosInitial(const Vector2i &pos);
        virtual void setPosInitial(int x, int y);
        virtual void setPosInitial(float x, float y);


        virtual void setPos(const Vector2f &pos);
        virtual void setPos(const Vector2i &pos);
        virtual const Vector2f &getPos() const;
        virtual const Vector2f &getLastPos() const;
        virtual Vector2i getPosI() const;
        virtual Vector2i getLastPosI() const;

        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setX(float x);
        virtual void setY(float y);

        virtual float getX() const;
        virtual float getY() const;
        virtual int getXI() const;
        virtual int getYI() const;

        virtual void move(const Vector2f &vec);
        virtual void move(const Vector2i &vec);

        virtual void setToLastPos();

    protected:
        Vector2f  m_pos;
        Vector2f  m_lastPos;
    private:


};
#endif // LAYERITEM_H
