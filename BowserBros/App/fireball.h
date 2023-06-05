#ifndef FIREBALL_H
#define FIREBALL_H

#include <QImage>
#include <QRect>
#include <QPainter>

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
    void draw(QPainter * aPainter);
};

#endif // FIREBALL_H
