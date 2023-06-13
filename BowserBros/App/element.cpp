#include "element.h"

Element::Element(float x, float y, ElementType type)
{
    itsX = x;
    itsY = y;
    itsType = type;

    switch (type) {
    case BREAKABLE1:
        itsImage.load(QString::fromStdString(":Assets/Assets/block/block1.jpg"));
        break;
    case BREAKABLE2:
        itsImage.load(QString::fromStdString(":Assets/Assets/block/block5.jpg"));
        break;
    case UNBREAKABLE:
        itsImage.load(QString::fromStdString(":Assets/Assets/block/block6.jpg"));
        break;
    case LUCKYBLOCK1:
        itsImage.load(QString::fromStdString(":Assets/Assets/block/block3.jpg"));
        break;
    case LUCKYBLOCK2:
        itsImage.load(QString::fromStdString(":Assets/Assets/block/block2.jpg"));
        break;
    case CRACKELED:
        itsImage.load(QString::fromStdString(":Assets/Assets/block/block4.jpg"));
        break;
    case CHEST:
        itsImage.load(QString::fromStdString(":Assets/Assets/other/chest.png"));
        break;
    default:
        break;
    }
    itsRect = QRect(itsX, itsY, itsImage.width(), itsImage.height());
    Q_ASSERT(!itsImage.isNull());
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

ElementType Element::getItsType() const
{
    return itsType;
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
