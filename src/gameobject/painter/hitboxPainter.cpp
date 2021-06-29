#include "hitboxPainter.h"

void HitboxPainter::makeVisibleCollider(Collider *collider,
                                        PixelPainter  *painter)
{
    EASY_FUNCTION(profiler::colors::Cyan);
    painter->clear();
    RectF b = collider->getBoundingBox();
    RectI boundingBox = RectI(b.getPos().x,b.getPos().y,b.getSize().x,b.getSize().y);
    painter->resize(Vector2u (boundingBox.getSize().x,boundingBox.getSize().y));
    Vector2i offset(boundingBox.getCornerPoint_TL());
    for(size_t i=0; i<collider->getHitbox().size(); i++)
    {
        Color color(100+rand()%155,100+rand()%155,100+rand()%155);
        painter->addPixel(Pixel(Vector2i(collider->getHitbox(i).getCornerPoint_TL())-offset,color));
        painter->addPixel(Pixel(Vector2i(collider->getHitbox(i).getCornerPoint_TR())-offset,color));
        painter->addPixel(Pixel(Vector2i(collider->getHitbox(i).getCornerPoint_BL())-offset,color));
        painter->addPixel(Pixel(Vector2i(collider->getHitbox(i).getCornerPoint_BR())-offset,color));
    }
    Color color(0,0,255);
    painter->addPixel(Pixel(boundingBox.getCornerPoint_TL()-offset,color));
    painter->addPixel(Pixel(boundingBox.getCornerPoint_TR()-offset,color));
    painter->addPixel(Pixel(boundingBox.getCornerPoint_BL()-offset,color));
    painter->addPixel(Pixel(boundingBox.getCornerPoint_BR()-offset,color));
    painter->update();
    Vector2f origin = collider->getPos() - Vector2f(offset);
    painter->setOrigin(origin);
}

