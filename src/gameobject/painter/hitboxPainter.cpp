#include "hitboxPainter.h"

void HitboxPainter::makeVisibleCollider(Collider *collider,
                                        PixelPainter  *painter)
{
    painter->clear();
    RectI boundingBox = collider->getBoundingBox();
    painter->resize(Vector2u (boundingBox.getSize().x,boundingBox.getSize().y));
    Vector2i offset(boundingBox.getCornerPoint_TL());
    for(size_t i=0; i<collider->getHitbox().size(); i++)
    {
        Color color(100+rand()%155,100+rand()%155,100+rand()%155);
        painter->addPixel(Pixel(collider->getHitbox(i).getCornerPoint_TL()-offset,color));
        painter->addPixel(Pixel(collider->getHitbox(i).getCornerPoint_TR()-offset,color));
        painter->addPixel(Pixel(collider->getHitbox(i).getCornerPoint_BL()-offset,color));
        painter->addPixel(Pixel(collider->getHitbox(i).getCornerPoint_BR()-offset,color));
    }
    Color color(0,0,255);
    painter->addPixel(Pixel(boundingBox.getCornerPoint_TL()-offset,color));
    painter->addPixel(Pixel(boundingBox.getCornerPoint_TR()-offset,color));
    painter->addPixel(Pixel(boundingBox.getCornerPoint_BL()-offset,color));
    painter->addPixel(Pixel(boundingBox.getCornerPoint_BR()-offset,color));
    //painter->setOrigin(Vector2f(offset.getX(),offset.getY()));
    Vector2f origin = collider->getPos() - Vector2f(offset);
    painter->setOrigin(origin);
}

