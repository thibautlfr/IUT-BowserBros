#ifndef BOWSER_H
#define BOWSER_H

#include <vector>

#include "fireball.h"
#include "entity.h"

using namespace std;

class Bowser : public Entity
{
private:
    vector<FireBall*> * itsFireBalls;
public:
    Bowser(float x, float y, int width, int heigth, string asset);
    ~Bowser();

    vector<FireBall*> * getItsFireBalls();
    void dropFireBall();
};

#endif // BOWSER_H
