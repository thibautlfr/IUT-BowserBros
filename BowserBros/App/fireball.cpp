#include "fireball.h"

FireBall::FireBall(float x, float y)
{
    itsX = x;
    itsY = y;
    itsYSpeed = 2; 
    itsAsset.load(":Assets/Assets/other/fireball.png");

    itsRect = QRect(itsX, itsY, itsAsset.width(), itsAsset.height());
    //Q_ASSERT(! itsAsset.isNull());
}

QRect FireBall::getItsRect()
{
    QRect fireBallRect = QRect(itsX, itsY, itsAsset.width(), itsAsset.height());
    return fireBallRect;
}

void FireBall::calculatePosition()
{
    itsY += itsYSpeed;
}

void FireBall::draw(QPainter * aPainter)
{
    aPainter->drawImage(itsX , itsY , itsAsset);
}
