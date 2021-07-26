#ifndef AABB_H
#define AABB_H

#include "base.h"
#include "drawUtilities.h"

class AABB
{
    public:
        AABB();
        AABB(const AABB &other);
        AABB(Vector2f pos, Vector2f size);
        ~AABB();
        const AABB &operator=(const AABB &other);
        bool operator==(const AABB &other) const;


        void setPos(Vector2f pos);
        void setSize(Vector2f size);
        void setWidth(float width);
        void setHeight(float height);
        void move(Vector2f delta);


        Vector2f getPos() const;
        Vector2f getSize() const;
        float getWidth() const;
        float getHeight() const;

        bool intersects(const AABB &b);
        bool intersectsInverseOf(const AABB &b);
        bool isLeftOf(const AABB &b);
        bool isRightOf(const AABB &b);
        bool isOnTopOf(const AABB &b);
        bool isBeneathOf(const AABB &b);
        bool intersectsTopOf(const AABB &b);
        bool intersectsLeftOf(const AABB &b);
        bool intersectsBottomOf(const AABB &b);
        bool intersectsRightOf(const AABB &b);


        static bool intersects(const AABB &a, const AABB &b);
        static bool intersectsInverseOf(const AABB &a, const AABB &b);
        static bool isLeftOf(const AABB &a, const AABB &b);
        static bool isRightOf(const AABB &a, const AABB &b);
        static bool isOnTopOf(const AABB &a, const AABB &b);
        static bool isBeneathOf(const AABB &a, const AABB &b);
        static bool intersectsTopOf(const AABB &a, const AABB &b);
        static bool intersectsLeftOf(const AABB &a, const AABB &b);
        static bool intersectsBottomOf(const AABB &a, const AABB &b);
        static bool intersectsRightOf(const AABB &a, const AABB &b);



        static unsigned long getStats_intersectionCheckCounter();
        static void stats_reset();

        static AABB getFrame(const vector<AABB> &list);

        VertexPath* getDrawable(const Color &color) const;

    private:
        Vector2f m_pos;
        Vector2f m_size;

        static unsigned long stats_intersectionCheckCounter;
};
#endif // AABB_H
