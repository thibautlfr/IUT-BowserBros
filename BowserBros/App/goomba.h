#ifndef GOOMBA_H
#define GOOMBA_H

#include "entity.h"

using namespace std;

class Goomba : public Entity
{
private:
    bool isDead;
    bool isOnPlatform;
public:
    Goomba(float x, float y, string asset);

    /**
      * @brief Return if the the player is on a platform
      * @author PILOTTE Clément
      * @return Returns true if the player is on a platform
    */
    bool getOnPlatform();
    /**
      * @brief Sets whether Mario is on a platform or not.
      * @param onPlatform Flag indicating if Mario is on a platform.
    */
    void setOnPlatform(bool onPlatform);

    void updateAsset(int timeElapsed);
    bool getIsDead() const;
    void setIsDead(bool newIsDead);
};

#endif // GOOMBA_H
