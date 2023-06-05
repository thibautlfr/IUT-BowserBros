#ifndef MARIO_H
#define MARIO_H

#include "entity.h"

using namespace std ;

class Mario : public Entity
{
private:
    float itsJumpSpeed ;
public:
    Mario(float x, float y, int width, int height);
    Mario(float x, float y, string asset);

    void jump();
    void updateAsset(string Direction);

    bool intersect(QRect anObstacle);

};

#endif // MARIO_H
