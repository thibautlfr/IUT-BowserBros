/**
 * @file koopa.h
 * @brief Defines the Koopa class.
 */

#ifndef KOOPA_H
#define KOOPA_H

#include "entity.h"

/**
 * @class Koopa
 * @brief Represents a Koopa enemy.
 *
 * The Koopa class represents a Koopa enemy in the game. It inherits from the Entity class.
 * It contains properties and functionalities specific to the Koopa enemy.
 */
class Koopa : public Entity
{
private:
    bool isDead; /**< Flag indicating if the Koopa is dead. */
    bool isOnPlatform; /**< Flag indicating if the Koopa is on a platform. */

public:
    /**
     * @brief Constructs a Koopa object.
     * @param x The initial x-coordinate of the Koopa.
     * @param y The initial y-coordinate of the Koopa.
     * @param asset The asset file path for the Koopa's image.
     */
    Koopa(float x, float y, string asset);

    /**
     * @brief Returns whether the Koopa is on a platform.
     * @return True if the Koopa is on a platform, false otherwise.
     */
    bool getOnPlatform();

    /**
     * @brief Sets whether the Koopa is on a platform.
     * @param onPlatform Flag indicating if the Koopa is on a platform.
     */
    void setOnPlatform(bool onPlatform);

    /**
     * @brief Updates the asset of the Koopa based on the elapsed time.
     * @param timeElapsed The elapsed time since the last update.
     */
    void updateAsset(int timeElapsed);

    /**
     * @brief Returns whether the Koopa is dead.
     * @return True if the Koopa is dead, false otherwise.
     */
    bool getIsDead() const;

    /**
     * @brief Sets whether the Koopa is dead.
     * @param newIsDead Flag indicating if the Koopa is dead.
     */
    void setIsDead(bool newIsDead);
};

#endif // KOOPA_H
