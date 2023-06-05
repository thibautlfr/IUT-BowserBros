#include "element.h"

Element::Element(float x, float y, int width, int height)
{
    itsX = x;
    itsY = y;

    itsRect = QRect(itsX, itsY, width, height);
}

QRect Element::getRect()
{
    return itsRect;
}

void Element::draw(QPainter *aPainter)
{
    itsRect.moveTo(itsX, itsY);
    aPainter->setPen(Qt::red);
    aPainter->setBrush(Qt::SolidPattern);
    aPainter->drawRect(itsRect);
}
