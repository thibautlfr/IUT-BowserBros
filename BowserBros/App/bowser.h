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
    string itsAsset;
public:
    Bowser(float x, float y, int width, int heigth, string asset);
    ~Bowser();

    vector<FireBall*> * getItsFireBalls();
    void dropFireBall();
    void eraseFireBall(vector<FireBall*>::iterator it);
};

#endif // BOWSER_H
