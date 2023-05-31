#include "block.h"

Block::Block(int x, int y)
{
    itsX = x;
    itsY = y;

    itsRect = QRect(itsX, itsY, 20, 20);
}

QRect Block::getRect()
{
    return itsRect;
}

void Block::draw(QPainter *aPainter)
{
    itsRect.moveTo(itsX, itsY);
    aPainter->setPen(Qt::green);
    QBrush b;
    b.setColor(Qt::green);
    b.setStyle(Qt::SolidPattern);
    aPainter->setBrush(b);
    aPainter->drawRect(itsRect);
}

void Block::moveDown(int speed) {
    itsRect.moveTop(itsRect.top() + speed);
}


