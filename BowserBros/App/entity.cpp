#include "entity.h"

Entity::Entity(float x, float y, int width, int height)
{
    itsX = x;
    itsY = y;
    itsRect = QRect(itsX, itsY, width, height);
    itsXSpeed = 0;
    itsYSpeed = 0;
}

void Entity::draw(QPainter * aPainter)
{
    itsRect.moveTo(itsX, itsY);
    aPainter->setPen(Qt::blue);
    aPainter->setBrush(Qt::SolidPattern);
    aPainter->drawRect(itsRect);
}

void Entity::reverseXSpeed()
{
    itsXSpeed *= -1;
}

void Entity::reverseYSpeed()
{
    itsYSpeed *= -1;
}

void Entity::calculatePosition()
{
    itsX += itsXSpeed;
    itsY += itsYSpeed;
}

QRect Entity::getItsRect()
{
    return itsRect;
}

void Entity::setItsY(float Y)
{
    itsY = Y;
}

void Entity::setItsX(float X)
{
    itsX = X;
}

void Entity::setXSpeed(float aSpeed)
{
    itsXSpeed = aSpeed;
}

void Entity::setYSpeed(float aSpeed)
{
    itsYSpeed = aSpeed;
}

float Entity::getItsY()
{
    return itsY;
}

float Entity::getYSpeed()
{
    return itsYSpeed;
}

float Entity::getXSpeed()
{
    return itsXSpeed;
}


