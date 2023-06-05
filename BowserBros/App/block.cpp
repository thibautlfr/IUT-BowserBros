#include "block.h"

Block::Block(float x, float y)
{
    itsX = x;
    itsY = y;

    itsRect = QRect(itsX, itsY, 20, 20);
}

QRect Block::getRect()
{
    return itsRect;
}

float Block::getYSpeed()
{
    return itsYSpeed;
}

void Block::calculatePosition()
{
    itsY += itsYSpeed;
}

void Block::draw(QPainter *aPainter)
{
    itsRect.moveTo(itsX, itsY);
    aPainter->setPen(Qt::red);
    aPainter->setBrush(Qt::SolidPattern);
    aPainter->drawRect(itsRect);
}

void Block::setYSpeed(float YSpeed)
{
    itsYSpeed = YSpeed;
}

void Block::moveDown(int speed) {
    itsRect.moveTop(itsRect.top() + speed);
}


