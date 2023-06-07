/**
@file fireball.h
@brief Defines the FireBall class.
*/
#ifndef FIREBALL_H
#define FIREBALL_H

#include <QImage>
#include <QRect>
#include <QPainter>

/**
@class FireBall
@brief Represents a fireball projectile.
The FireBall class represents a fireball projectile in the game.
*/

class FireBall
{
private:
    float itsX; /**< The x-coordinate of the fireball's position. */
    float itsY; /**< The y-coordinate of the fireball's position. */
    float itsYSpeed; /**< The speed of the fireball along the y-axis. */
    QImage itsAsset; /**< The image asset of the fireball. */
    QRect itsRect; /**< The bounding rectangle of the fireball. */

public:
    /**
     * @brief Constructs a FireBall object with position.
     * @param x The x-coordinate of the fireball's position.
     * @param y The y-coordinate of the fireball's position.
    */
    FireBall(float x, float y);
    /**
      * @brief Returns the bounding rectangle of the fireball.
      * @return The bounding rectangle of the fireball.
    */
    QRect getItsRect();
    /**
      * @brief Calculates the new position of the fireball.
     */
    void calculatePosition();
    /**
      * @brief Draws the fireball on a QPainter object.
      * @param aPainter A pointer to the QPainter object.
    */
    void draw(QPainter *aPainter);
};

#endif // FIREBALL_H






