#ifndef MARIO_H
#define MARIO_H

#include "entity.h"

class Mario : public Entity
{
private:
    float itsJumpSpeed ;
public:
    Mario(float x, float y, int width, int height, float jumpSpeed);

    void jump();
    void updateAsset();

    bool intersect(QRect anObstacle);

};

#endif // MARIO_H
