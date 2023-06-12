#include "goomba.h"



Goomba::Goomba(float x, float y, string asset)
    :Entity(x, y, asset)
{
    itsX = x;
    itsY = y;
    itsXSpeed = 0;

    isDead = false;

    itsImage.load(QString::fromStdString(asset));
    itsRect = QRect(x, y, itsImage.width(), itsImage.height());
}

// ---------------------------------------------------------------------------------------------

bool Goomba::getOnPlatform()
{
    return isOnPlatform;
}

void Goomba::setOnPlatform(bool onPlatform)
{
    isOnPlatform = onPlatform;
}

bool Goomba::getIsDead() const
{
    return isDead;
}

void Goomba::setIsDead(bool newIsDead)
{
    isDead = newIsDead;
}

// ---------------------------------------------------------------------------------------------

void Goomba::updateAsset(int timeElapsed)
{
    if (isDead)
    {
        itsImage.load(":Assets/Assets/ennemis/goombaDead.png");
    }
    else
    {
        if(itsXSpeed > 0)
        {
            int(timeElapsed / 150) % 2 == 1? itsImage.load(":Assets/Assets/ennemis/goombaR1.png"): itsImage.load(":Assets/Assets/ennemis/goombaR2.png");
        }
        else if(itsXSpeed < 0)
        {
            int(timeElapsed / 150) % 2 == 1? itsImage.load(":Assets/Assets/ennemis/goombaL1.png"): itsImage.load(":Assets/Assets/ennemis/goombaL2.png");
        }
    }
    itsRect = itsImage.rect();
}
