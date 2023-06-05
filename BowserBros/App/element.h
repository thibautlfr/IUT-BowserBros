#ifndef ELEMENT_H
#define ELEMENT_H

#include <QRect>
#include <QPainter>
#include <QImage>

using namespace std;

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
    Element(float x, float y, string asset);
    void draw(QPainter *aPainter);
    QRect getRect();
    float getYSpeed();
};

#endif // ELEMENT_H
