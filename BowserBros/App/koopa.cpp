#include "koopa.h"

Koopa::Koopa(float x, float y, string asset)
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

bool Koopa::getOnPlatform()
{
    return isOnPlatform;
}

void Koopa::setOnPlatform(bool onPlatform)
{
    isOnPlatform = onPlatform;
}

bool Koopa::getIsDead() const
{
    return isDead;
}

void Koopa::setIsDead(bool newIsDead)
{
    isDead = newIsDead;
}

// ---------------------------------------------------------------------------------------------

void Koopa::updateAsset(int timeElapsed)
{
    if (isDead)
    {
        itsImage.load(":Assets/Assets/ennemis/koopaDead.png");
    }
    else
    {
        if(itsXSpeed > 0)
        {
            int(timeElapsed / 150) % 2 == 1? itsImage.load(":Assets/Assets/ennemis/koopaR1.png"): itsImage.load(":Assets/Assets/ennemis/koopaR2.png");
        }
        else if(itsXSpeed < 0)
        {
            int(timeElapsed / 150) % 2 == 1? itsImage.load(":Assets/Assets/ennemis/koopaL1.png"): itsImage.load(":Assets/Assets/ennemis/koopaL2.png");
        }
    }
    itsRect = itsImage.rect();
}
