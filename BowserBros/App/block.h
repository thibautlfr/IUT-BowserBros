#ifndef BLOCK_H
#define BLOCK_H

#include <QRect>
#include <QPainter>

class Block
{
private:
    int itsX;
    int itsY;
    QRect itsRect;
public:
    Block(int x, int y);
    void moveDown(int speed);
    void draw(QPainter *aPainter);
    QRect getRect();
};

#endif // PLATFORM_H
