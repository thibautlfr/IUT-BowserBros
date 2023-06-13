/**
@file entity.h
@brief Defines the Entity class.
*/

#ifndef ENTITY_H
#define ENTITY_H

#include <QRect>
#include <QPainter>

using namespace std;

/**
@class Entity
@brief Represents a game entity.
The Entity class provides common attributes and functionalities for game entities.
*/
class Entity
{
protected:
    float itsX; /**< The x-coordinate of the entity's position. */
    float itsY; /**< The y-coordinate of the entity's position. */
    float itsXSpeed; /**< The speed of the entity along the x-axis. */
    float itsYSpeed; /**< The speed of the entity along the y-axis. */
    QRect itsRect; /**< The bounding rectangle of the entity. */
    QImage itsImage; /**< The image of the entity. */

public:
    /**
      * @brief Constructs an Entity object with position and size.
      * @param x The x-coordinate of the entity's position.
      * @param y The y-coordinate of the entity's position.
      * @param width The width of the entity.
      * @param height The height of the entity.
      */
    Entity(float x, float y, int width, int height);

     /**
       * @brief Constructs an Entity object with position and asset.
       * @param x The x-coordinate of the entity's position.
       * @param y The y-coordinate of the entity's position.
       * @param asset The asset file path for the entity's image.
     */
    Entity(float x, float y, string asset);

    /**
     * @brief Destructor for entity
     */
    virtual ~Entity();

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Sets the y-coordinate of the entity's position.
      * @param Y The new y-coordinate value.
     */
    void setItsY(float Y);

    /**
      * @brief Sets the x-coordinate of the entity's position.
      * @param X The new x-coordinate value.
     */
    void setItsX(float X);

    /**
      * @brief Sets the speed of the entity along the x-axis.
      * @param aSpeed The new x-speed value.
     */
    void setXSpeed(float aSpeed);

    /**
      * @brief Sets the speed of the entity along the y-axis.
      * @param aSpeed The new y-speed value.
     */
    void setYSpeed(float aSpeed);

    /**
      * @brief Sets the image asset of the entity.
      * @param newAssetPath The new asset file path for the entity's image.
     */
    void setItsImage(string newAssetPath);

    /**
     * @brief Set the attribute onPlatform
     * @param onPlatform : boolean
     */
    virtual void setOnPlatform(bool onPlatform);

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Returns the y-coordinate of the entity's position.
      * @return The y-coordinate of the entity's position.
     */
    float getItsY();

    /**
      * @brief Returns the x-coordinate of the entity's position.
      * @return The x-coordinate of the entity's position.
     */
    float getItsX();

    /**
      * @brief Returns the speed of the entity along the y-axis.
      * @return The speed of the entity along the y-axis.
     */
    float getYSpeed();

    /**
      * @brief Returns the speed of the entity along the x-axis.
      * @return The speed of the entity along the x-axis.
    */
    float getXSpeed();

    /**
      * @brief Returns the bounding rectangle of the entity.
      * @return The bounding rectangle of the entity.
     */
    QRect getItsRect();

    /**
     * @brief Getter for the onPlatform attribute
     * @return
     */
    virtual bool getOnPlatform();

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Calculates the new position of the entity based on its speed.
    */
    void calculatePosition();

    /**
      * @brief Draws the entity on a QPainter object.
      * @param aPainter A pointer to the QPainter object.
     */
    void draw(QPainter *aPainter);

    /**
      * @brief Reverses the x-speed of the entity.
    */
    void reverseXSpeed();

    /**
      * @brief Reverses the y-speed of the entity.
    */
    void reverseYSpeed();
};
#endif // ENTITY_H






