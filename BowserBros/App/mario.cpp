#include "mario.h"

Mario::Mario(float x, float y, int width, int height, float jumpSpeed) :
    Entity(x, y, width, height), itsJumpSpeed(jumpSpeed){}

void Mario::jump()
{
    itsYSpeed = itsJumpSpeed;
}

void Mario::updateAsset()
{
    //A faire lorsqu'on aura ajouté les assets au jeu
}

bool Mario::intersect(QRect anObstacle)
{
    return anObstacle.intersects(itsRect);
}

