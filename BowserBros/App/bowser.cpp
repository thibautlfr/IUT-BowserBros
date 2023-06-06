#include "bowser.h"
#include <iostream>

Bowser::Bowser(float x, float y, int width, int height, string asset)
    :Entity(x, y,asset)
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

void Bowser::eraseFireBall(vector<FireBall*>::iterator it)
{
    delete *it;  // Supprime la boule de feu de la mémoire
    *itsFireBalls->erase(it);  // Supprime l'élément de la liste
}
