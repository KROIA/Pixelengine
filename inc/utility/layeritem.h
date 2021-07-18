#ifndef LAYERITEM_H
#define LAYERITEM_H

#include "base.h"

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
        virtual void swapRotationToLastRotation();

        virtual void setPosInitial(const Vector2f &pos);
        virtual void setPosInitial(const Vector2i &pos);
        virtual void setPosInitial(int x, int y);
        virtual void setPosInitial(float x, float y);


        virtual void setPos(int x, int y);
        virtual void setPos(float x, float y);
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


        virtual void rotate(float deg);
        virtual void setRotationInitial(float deg);
        virtual void setRotation(float deg);
        virtual float getRotation() const;
        virtual float getLastRotation() const;



        virtual void setToLastPos();
        virtual void setToLastRotation();

    protected:
        Vector2f  m_pos;
        Vector2f  m_lastPos;
        float     m_rotation;
        float     m_lastRotation;
    private:


};
#endif // LAYERITEM_H
