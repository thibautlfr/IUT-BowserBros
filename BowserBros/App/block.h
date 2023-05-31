#ifndef BLOCK_H
#define BLOCK_H

#include <QRect>
#include <QPainter>

class Block
{
private:
    float itsX;
    float itsY;
    float itsYSpeed;
    QRect itsRect;
public:
    Block(float x, float y);
    void setYSpeed(float YSpeed);
    void moveDown(int speed);

    void calculatePosition();
    void draw(QPainter *aPainter);
    QRect getRect();
    float getYSpeed();
};

#endif // PLATFORM_H
