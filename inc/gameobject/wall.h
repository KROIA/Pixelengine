#ifndef WALL_H
#define WALL_H

#include "gameobject.h"

class Wall  :   public GameObject
{
    public:
        Wall();
        Wall(const Wall &other);

        virtual  ~Wall();

        virtual void setDimension(const Vector2u  &dimension);
        virtual void setDimension(const unsigned int &width,
                                  const unsigned int &height);
        virtual const Vector2u  &getDimension() const;
        virtual const unsigned int &getWidth() const;
        virtual const unsigned int &getHeight() const;

        virtual void setColor(const Color &color);
        virtual const Color &getColor() const;

        virtual Controller *getController();

    protected:

        virtual void generateObject();

        Vector2u  m_dimension;
        Color  m_color;

        Collider    *m_collider;
        Controller  *m_controller;
        Painter     *m_painter;

    private:


};
#endif // WALL_H
