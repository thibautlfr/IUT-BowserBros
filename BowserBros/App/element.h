#ifndef ELEMENT_H
#define ELEMENT_H

#include <QRect>
#include <QPainter>
#include <QImage>

enum ElementType{
    BLOCK,
    CHEST
};

class Element
{
private:
    float itsX;
    float itsY;
    QRect itsRect;
    QImage itsImage;
public:
    Element(float x, float y, int widht, int height);
    void draw(QPainter *aPainter);
    QRect getRect();
    float getYSpeed();
};

#endif // ELEMENT_H
