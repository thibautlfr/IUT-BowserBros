#include "fireball.h"

FireBall::FireBall(float x, float y)
{
    itsX = x;
    itsY = y;
    itsYSpeed = 2;
}

QRect FireBall::getItsRect()
{
    return itsAsset.rect();
}

void FireBall::calculatePosition()
{
    itsY += itsYSpeed;
}
