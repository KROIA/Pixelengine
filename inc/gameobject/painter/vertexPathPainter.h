#ifndef VERTEXPATHPAINTER_H
#define VERTEXPATHPAINTER_H

//#include "base.h"
#include "painter.h"
#include "drawUtilities.h"
#include "mathFunctions.h"
/*
class VertexPath
{
    public:
        VertexPath();
        ~VertexPath();
        const VertexPath &operator=(const VertexPath &other);

        void move(sf::Vector2f vec);
        void setColor(const Color &color);

        sf::Vertex *line;
        std::size_t length;
        sf::PrimitiveType type;


};*/


class VertexPathPainter :   public  Painter
{
    public:
        VertexPathPainter();
        ~VertexPathPainter();

        void render(sf::RenderWindow *window,
                    float viewPortZoom,
                    DisplayStats &stats);

        void addPath(VertexPath *path);
        void addPath(const vector<VertexPath*> &path);
        void addPath(const vector<Vector2f> &points);
        void addPath(VertexPath *path, const Color &color);
        void addPath(const vector<VertexPath*> &path,const Color &color);
        void addPath(const vector<Vector2f> &points, const Color &color);

        void setStandardColor(const Color &color);
        const Color &getStandardColor();

        void clear();
        //void erase(VertexPath *path);

    protected:
        virtual void internal_setPos(const Vector2f &pos);
        virtual float internal_getRotation() const;
        virtual void internal_setRotation(const Vector2f &rotPoint,float deg);
        virtual void internal_setRotation(const float &deg);
        virtual void internal_UpdateOrigin();
        virtual void internal_SetOrigin(const Vector2f &origin);
        virtual const Vector2f &internal_getOrigin() const;
        virtual void internal_CalculateFrame();


        HashTable<VertexPath*>  m_pathList;
        vector<Vector2f>        m_points;
        Color m_standardColor;
        Vector2f                m_origin;
        float                   m_rotation;

    private:

        void internal_addPath(VertexPath *path);
        void internal_addPath(VertexPath *path, const Color &color);
        VertexPath *intern_pointsToPath(const vector<Vector2f> &points);
};
#endif // VERTEXPATHPAINTER_H
