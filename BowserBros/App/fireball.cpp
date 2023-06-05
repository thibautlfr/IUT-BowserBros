#include "fireball.h"

FireBall::FireBall(float x, float y)
{
    itsX = x;
    itsY = y;
    itsYSpeed = 2;
    itsAsset.load(":Assets/Assets/other/fireball.png");
}

QRect FireBall::getItsRect()
{
    return itsAsset.rect();
}

void FireBall::calculatePosition()
{
    itsY += itsYSpeed;
}

void FireBall::draw(QPainter * aPainter)
{
    aPainter->drawImage(itsX , itsY , itsAsset);
}
