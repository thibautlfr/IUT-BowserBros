#include "bowser.h"

Bowser::Bowser(float x, float y, int width, int height)
    :Entity(x, y, width, height)
{
    itsX = x;
    itsY = y;
    itsXSpeed = 0.5;
    itsRect = QRect(x, y, width, height);

    itsFireBalls = new vector<FireBall*>;
}

Bowser::~Bowser()
{
    for (FireBall * fireball : *itsFireBalls)
    {
        delete fireball;
    }
    delete itsFireBalls;
}

vector<FireBall *> * Bowser::getItsFireBalls()
{
    return itsFireBalls;
}

void Bowser::dropFireBall()
{
    itsFireBalls->push_back(new FireBall(itsX, itsY + 59));
}
