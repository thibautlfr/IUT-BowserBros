#include "mario.h"
#include "qdebug.h"

#include <iostream>

Mario::Mario(float x, float y, int width, int height) :
    Entity(x, y, width, height)
{
    itsJumpSpeed = -12;
}

Mario::Mario(float x, float y, string asset) :
    Entity(x, y, asset)
{

}

void Mario::jump()
{
    itsYSpeed = itsJumpSpeed;
}

void Mario::updateAsset(string Direction)
{
    //A faire lorsqu'on aura ajouté les assets au jeu

}

bool Mario::intersect(QRect anObstacle)
{
    if(itsImage.isNull())
    {
        return anObstacle.intersects(itsRect);

    }
    else
    {
        QRect marioRect = QRect(itsX, itsY, itsImage.width(), itsImage.height());
        return anObstacle.intersects(marioRect);
    }

}
