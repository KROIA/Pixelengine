#ifndef HITBOXPAINTER_H
#define HITBOXPAINTER_H

#include "painter.h"
#include "collider.h"

namespace HitboxPainter
{
     void makeVisibleCollider(Collider *collider,
                              Painter  *painter);

};
#endif // HITBOXPAINTER_H
