#include "mario.h"
#include <iostream>

Mario::Mario(float x, float y, int width, int height) :
    Entity(x, y, width, height)
{
    itsJumpSpeed = -10;
}

Mario::Mario(float x, float y, string asset) :
    Entity(x, y, asset)
{
    itsJumpSpeed = -10;
    itsImage.load(QString::fromStdString(asset));
}

void Mario::jump()
{
    itsYSpeed = itsJumpSpeed;
}

void Mario::updateAsset(int timeElapsed)
{
    //A faire lorsqu'on aura ajouté les assets au jeu
    if (isOnPlatform)
    {
        if(itsXSpeed == 0 )
        {
            itsImage.load(":Assets/Assets/mario/mario4.png");
        }
        else if(itsXSpeed > 0)
        {
            int(timeElapsed / 150) % 2 == 1? itsImage.load(":Assets/Assets/mario/mario9.png"): itsImage.load(":Assets/Assets/mario/mario10.png");
        }
        else if(itsXSpeed < 0)
        {
            int(timeElapsed / 150) % 2 == 1? itsImage.load(":Assets/Assets/mario/mario1.png"): itsImage.load(":Assets/Assets/mario/mario2.png");
        }
    }
    else
    {
        itsXSpeed > 0 ? itsImage.load(":Assets/Assets/mario/mario11.png"): itsImage.load(":Assets/Assets/mario/mario12.png");
    }
}

void Mario::setOnPlatform(bool onPlatform)
{
    isOnPlatform = onPlatform;
}

bool Mario::intersect(QRect anObstacle)
{
    if(itsImage.isNull())
    {
        return anObstacle.intersects(itsRect);

    }
    else
    {
        QRect marioRect = QRect(itsX, itsY, itsImage.width(), itsImage.height());
        return anObstacle.intersects(marioRect);
    }

}
