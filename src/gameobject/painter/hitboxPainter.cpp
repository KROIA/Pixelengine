#include "hitboxPainter.h"

void HitboxPainter::makeVisibleCollider(Collider *collider,
                                        PixelPainter  *painter)
{
    painter->clear();
    Rect boundingBox = collider->getBoundingBox();
    painter->resize(PointU(boundingBox.getSize().getX(),boundingBox.getSize().getY()));
    Point offset(boundingBox.getCornerPoint_TL());
    for(size_t i=0; i<collider->getHitbox().size(); i++)
    {
        Color color(100+rand()%155,100+rand()%155,100+rand()%155);
        painter->addPixel(Pixel(Vector(collider->getHitbox(i).getCornerPoint_TL())-Vector(offset),color));
        painter->addPixel(Pixel(Vector(collider->getHitbox(i).getCornerPoint_TR())-Vector(offset),color));
        painter->addPixel(Pixel(Vector(collider->getHitbox(i).getCornerPoint_BL())-Vector(offset),color));
        painter->addPixel(Pixel(Vector(collider->getHitbox(i).getCornerPoint_BR())-Vector(offset),color));
    }
    Color color(0,0,255);
    painter->addPixel(Pixel(Vector(collider->getBoundingBox().getCornerPoint_TL())-Vector(offset),color));
    painter->addPixel(Pixel(Vector(collider->getBoundingBox().getCornerPoint_TR())-Vector(offset),color));
    painter->addPixel(Pixel(Vector(collider->getBoundingBox().getCornerPoint_BL())-Vector(offset),color));
    painter->addPixel(Pixel(Vector(collider->getBoundingBox().getCornerPoint_BR())-Vector(offset),color));
}

