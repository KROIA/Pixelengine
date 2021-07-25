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


        void setPos(Vector2f pos);
        void setSize(Vector2f size);

        Vector2f getPos() const;
        Vector2f getSize() const;

        static bool intersects(const AABB &a, const AABB &b);
        static unsigned long getStats_intersectionCheckCounter();
        static void stats_reset();

        VertexPath* getDrawable(const Color &color);

    private:
        Vector2f m_pos;
        Vector2f m_size;

        static unsigned long stats_intersectionCheckCounter;
};
#endif // AABB_H
