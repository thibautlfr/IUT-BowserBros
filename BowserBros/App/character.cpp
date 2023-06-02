#include "character.h"


Character::Character(float x, float y)
{
    itsX = x;
    itsY = y;
    itsRect = QRect(itsX, itsY, 20, 45);
    itsXSpeed = 0;
    itsYSpeed = 0;
    itsJumpSpeed = -9;
}

QRect Character::getItsRect()
{
    return itsRect;
}

void Character::setItsY(float Y)
{
    itsY = Y;
}

void Character::setItsX(float X)
{
    itsX = X;
}

void Character::setXSpeed(float aSpeed)
{
    itsXSpeed = aSpeed;
}

void Character::setYSpeed(float aSpeed)
{
    itsYSpeed = aSpeed;
}

float Character::getItsY()
{
    return itsY;
}

float Character::getYSpeed()
{
    return itsYSpeed;
}

float Character::getXSpeed()
{
    return itsXSpeed;
}

void Character::jump()
{
    itsYSpeed = itsJumpSpeed;
}

void Character::calculatePosition()
{

    itsX += itsXSpeed;
    itsY += itsYSpeed;
}

void Character::draw(QPainter * aPainter)
{
    itsRect.moveTo(itsX, itsY);
    aPainter->setPen(Qt::blue);
    aPainter->setBrush(Qt::SolidPattern);
    aPainter->drawRect(itsRect);
}

void Character::reverseXSpeed()
{
    itsXSpeed *= -1;
}

void Character::reverseYSpeed()
{
    itsYSpeed *= -1;
}

bool Character::intersect(QRect anObstacle)
{
    return anObstacle.intersects(itsRect);
}
