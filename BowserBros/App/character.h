#ifndef CHARACTER_H
#define CHARACTER_H

#include <QRect>
#include <QPainter>

class Character
{
private:
    float itsX;
    float itsY;
    float itsXSpeed;
    float itsYSpeed;
    float itsJumpSpeed;
    bool platform;
    QRect itsRect;
public:
    Character();

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

    void jump();
    bool intersect(QRect anObstacle);

    bool isOnPlatform();
    void setPlatform(bool B);

    QRect getItsRect();


};

#endif // CHARACTER_H
