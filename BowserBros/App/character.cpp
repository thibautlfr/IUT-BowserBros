#include "character.h"


Character::Character()
{
    itsX = 100;
    itsY = 500;
    itsRect = QRect(itsX, itsY, 50, 50);
    itsXSpeed = 0;
    itsYSpeed = 0;
    itsJumpSpeed = -10;
    platform = true;
}

bool Character::isOnPlatform()
{
    return platform;
}

QRect Character::getItsRect()
{
    return itsRect;
}

void Character::setPlatform(bool B)
{
    platform = B;
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
    QBrush b;
    b.setColor(Qt::blue);
    b.setStyle(Qt::SolidPattern);
    aPainter->setBrush(b);
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
