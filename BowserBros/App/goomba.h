/**
 * @file goomba.h
 * @brief Defines the Goomba class.
 */

#ifndef GOOMBA_H
#define GOOMBA_H

#include "entity.h"

/**
 * @class Goomba
 * @brief Represents a Goomba enemy.
 *
 * The Goomba class represents a Goomba enemy in the game. It inherits from the Entity class.
 * It contains properties and functionalities specific to the Goomba enemy.
 */
class Goomba : public Entity
{
private:
    bool isDead; /**< Flag indicating if the Goomba is dead. */
    bool isOnPlatform; /**< Flag indicating if the Goomba is on a platform. */

public:
    /**
     * @brief Constructs a Goomba object.
     * @param x The initial x-coordinate of the Goomba.
     * @param y The initial y-coordinate of the Goomba.
     * @param asset The asset file path for the Goomba's image.
     */
    Goomba(float x, float y, string asset);

    /**
     * @brief Returns whether the Goomba is on a platform.
     * @return True if the Goomba is on a platform, false otherwise.
     */
    bool getOnPlatform();

    /**
     * @brief Sets whether the Goomba is on a platform.
     * @param onPlatform Flag indicating if the Goomba is on a platform.
     */
    void setOnPlatform(bool onPlatform);

    /**
     * @brief Updates the asset of the Goomba based on the elapsed time.
     * @param timeElapsed The elapsed time since the last update.
     */
    void updateAsset(int timeElapsed);

    /**
     * @brief Returns whether the Goomba is dead.
     * @return True if the Goomba is dead, false otherwise.
     */
    bool getIsDead() const;

    /**
     * @brief Sets whether the Goomba is dead.
     * @param newIsDead Flag indicating if the Goomba is dead.
     */
    void setIsDead(bool newIsDead);
};

#endif // GOOMBA_H
