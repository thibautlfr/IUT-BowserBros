#ifndef FIREBALL_H
#define FIREBALL_H

#include <QImage>
#include <QRect>

class FireBall
{
private:
    float itsX;
    float itsY;
    float itsYSpeed;

    QImage itsAsset;
    QRect itsRect;

public:
    FireBall(float x, float y);
    QRect getItsRect();
    void calculatePosition();
};

#endif // FIREBALL_H
