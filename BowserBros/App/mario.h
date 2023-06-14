/**
@file mario.h
@brief Defines the Mario class.
*/
#ifndef MARIO_H
#define MARIO_H

#include "entity.h"

/**
@class Mario
@brief Represents the player character Mario.
The Mario class represents the player character in the game. It inherits from the Entity class.
It contains specific functionalities and properties related to Mario.
*/
class Mario : public Entity
{
private:
    float itsJumpSpeed; /**< The jump speed of Mario. */
    bool isOnPlatform; /**< Flag indicating if Mario is on a platform. */
    bool isOnLadder; /**< Indicates if Mario is on a ladder. */
    bool isDead; /**< Indicates if Mario is dead. */
public:
    /**
      * @brief Constructs a Mario object.
      * @param x The initial x-coordinate of Mario.
      * @param y The initial y-coordinate of Mario.
      * @param width The width of Mario.
      * @param height The height of Mario.
     */
    Mario(float x, float y, int width, int height);

    //~Mario();

    /**
      * @brief Constructs a Mario object.
      * @param x The initial x-coordinate of Mario.
      * @param y The initial y-coordinate of Mario.
      * @param asset The asset file path for Mario's image.
    */
    Mario(float x, float y, string asset);

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Returns if the the player is on a platform
      * @return Returns true if the player is on a platform
    */
    bool getOnPlatform();
    /**
      * @brief Sets whether Mario is on a platform or not.
      * @param isOnPlatform Flag indicating if Mario is on a platform.
    */
    void setOnPlatform(bool onPlatform);

    /**
      * @brief Returns if the the player is on a ladder
      * @return Returns true if the player is on a ladder
    */
    bool getOnLadder();
    /**
      * @brief Sets whether Mario is on a ladder or not.
      * @param isOnLadder Flag indicating if Mario is on a ladder.
    */
    void setOnLadder(bool onLadder);
    /**
      * @brief Returns if the the player is dead
      * @return Returns true if the player is dead
    */
    bool getIsDead();
    /**
      * @brief Sets whether Mario is dead or not
      * @param isDead Flag indicating if Mario is dead
    */
    void setIsDead(bool dead);

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Makes Mario jump.
     */
    void jump();

    /**
      * @brief Updates the asset of Mario based on the elapsed time.
      * @param timeElapsed The elapsed time since the last update.
    */
    void updateAsset(int timeElapsed);

    /**
      * @brief Checks if Mario intersects with an obstacle.
      * @param anObstacle The QRect object representing the obstacle.
      * @return True if Mario intersects with the obstacle, false otherwise.
    */
    bool intersect(QRect anObstacle);
};

#endif // MARIO_H
