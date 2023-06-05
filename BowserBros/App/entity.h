#ifndef ENTITY_H
#define ENTITY_H

#include <QRect>
#include <QPainter>

class Entity
{
protected:
    float itsX;
    float itsY;
    float itsXSpeed;
    float itsYSpeed;
    QRect itsRect;
    QImage itsImage;
public:
    Entity(float x, float y, int width, int height);

    void setItsY(float Y);
    void setItsX(float X);

    void setXSpeed(float aSpeed);
    void setYSpeed(float aSpeed);

    float getItsY();

    float getYSpeed();
    float getXSpeed();

    void calculatePosition();
    void draw(QPainter *aPainter);

    void reverseXSpeed();
    void reverseYSpeed();

    QRect getItsRect();

};

#endif // ENTITY_H
