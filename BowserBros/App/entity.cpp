#include "entity.h"

Entity::Entity(float x, float y, int width, int height)
{
    itsX = x;
    itsY = y;
    itsRect = QRect(itsX, itsY, width, height);
    itsXSpeed = 0;
    itsYSpeed = 0;
}

Entity::Entity(float x, float y, string asset)
{
    itsX = x;
    itsY = y;
    itsXSpeed = 0;
    itsYSpeed = 0;

    itsImage.load(QString::fromStdString(asset));
    itsRect = QRect(itsX, itsY, itsImage.width(), itsImage.height());
    Q_ASSERT(! itsImage.isNull());
}

void Entity::draw(QPainter * aPainter)
{
    if (itsImage.isNull())
    {
        itsRect.moveTo(itsX, itsY);
        aPainter->setPen(Qt::red);
        aPainter->setBrush(Qt::SolidPattern);
        aPainter->drawRect(itsRect);
    }
    else
    {
        aPainter->drawImage(itsX , itsY , itsImage);
    }
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
    if(itsImage.isNull())
    {
        return itsRect;
    }
    else
    {
        QRect entityRect = QRect(itsX, itsY, itsImage.width(), itsImage.height());
        return entityRect;
    }
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

float Entity::getItsX()
{
    return itsX;
}

float Entity::getYSpeed()
{
    return itsYSpeed;
}

float Entity::getXSpeed()
{
    return itsXSpeed;
}

void Entity::setItsImage(string newAssetPath)
{
    itsImage.load(QString::fromStdString(newAssetPath));
    itsRect = QRect(itsX, itsY, itsImage.width(), itsImage.height());
    Q_ASSERT(! itsImage.isNull());
}
