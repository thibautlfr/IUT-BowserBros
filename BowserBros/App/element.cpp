#include "element.h"

//#include <QString>

Element::Element(float x, float y, int width, int height)
{
    itsX = x;
    itsY = y;

    itsRect = QRect(itsX, itsY, width, height);
}

Element::Element(float x, float y, string asset)
{
    itsX = x;
    itsY = y;

    itsImage.load(QString::fromStdString(asset));
    itsRect = QRect(itsX, itsY, itsImage.width(), itsImage.height());
    Q_ASSERT(! itsImage.isNull());
}

QRect Element::getRect()
{
    return itsRect;
}

void Element::draw(QPainter *aPainter)
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
