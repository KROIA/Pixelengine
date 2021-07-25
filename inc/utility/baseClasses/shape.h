#ifndef SHAPE_H
#define SHAPE_H

#include "base.h"
#include "drawUtilities.h"
#include "mathFunctions.h"
#include "AABB.h"

class Shape
{
    public:
        Shape();
        Shape(const Shape &other);
        Shape(const vector<Vector2f> &Vertexs);
        ~Shape();
        const Shape &operator=(const Shape &other);

        void setSize(size_t size);
        void reserve(size_t size);
        size_t getSize() const;

        void setVertex(size_t index, const Vector2f &pos);
        void addVertex(const Vector2f &pos);
        void removeVertex(size_t index);
        void clear();
        void setPos(const Vector2f &pos);
        void move(const Vector2f delta);

        void setRotation(float angle);
        void setRotation(Vector2f rotVertex, float angle);
        void rotate(float angle);
        void rotate(Vector2f rotVertex, float angle);


        const Vector2f &getVertex(size_t index) const;
        const vector<Vector2f> &getVertexs() const;
        const Vector2f &getPos() const;
        const Vector2f &getOrigin() const;
        float getRotation();

        VertexPath* getDrawable(const Color &color);

        void setCollisionResolveVec(const Vector2f &vec);
        const Vector2f &getCollisionResolveVec() const;
        static void resolveCollision(Shape &s);
        static void resolveCollision(Shape &s1, Shape &s2);
        void setStatic(bool enable);
        void setMass(float mass);
        bool getStatic()const;
        float getMass()const;

        bool checkForCollision(Shape &other);

        AABB getFrame();

    protected:
        void calculateOrigin();
        void recalculateOriginAddedVertex(const Vector2f &newVertex);
        void recalculateOriginRemovedVertex(const Vector2f &oldVertex);
        void recalculateOrigin(const Vector2f &oldVertex,const Vector2f &newVertex);
        bool indexInvalid(size_t index) const;

        // Collision detection
        static void projectVertecies(const vector<Vector2f> &vertecies, Vector2f axis,float &min, float &max);
        static bool shapeOverlap_SAX(Shape &s1, Shape &s2);

        Vector2f            m_pos;
        Vector2f            m_origin;
        float               m_rotation;
        vector<Vector2f>    m_vertexList;
        Vector2f            m_dummyVertex;

        Vector2f            m_collisionResolveVec;
        bool                m_static;
        float               m_mass;
    private:

};
#endif // SHAPE_H
