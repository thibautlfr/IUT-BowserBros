/**
@file element.h
@brief Defines the Element class.
*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include <QRect>
#include <QPainter>
#include <QImage>

using namespace std;

/**
@enum ElementType
@brief Represents the types of elements.
*/
enum ElementType {
    CHEST, /**< Chest element type. */
    BREAKABLE1, /**< Breakable1 element type. */
    BREAKABLE2, /**< Breakable2 element type. */
    LUCKYBLOCK1, /**< LuckyBlock1 element type. */
    LUCKYBLOCK2, /**< LuckyBlock2 element type. */
    UNBREAKABLE, /**< Unbreakable element type. */
    CRACKELED /**< Cracked element type. */
};

/**
@class Element
@brief Represents a game element.
The Element class provides common attributes and functionalities for game elements.
*/
class Element
{
private:
    float itsX; /**< The x-coordinate of the element's position. */
    float itsY; /**< The y-coordinate of the element's position. */
    QRect itsRect; /**< The bounding rectangle of the element. */
    QImage itsImage; /**< The image of the element. */

public:
    /**
      * @brief Constructs an Element object with position and size.
      * @param x The x-coordinate of the element's position.
      * @param y The y-coordinate of the element's position.
      * @param width The width of the element.
      * @param height The height of the element.
     */
    Element(float x, float y, int width, int height);

    /**
      * @brief Constructs an Element object with position and asset.
      * @param x The x-coordinate of the element's position.
      * @param y The y-coordinate of the element's position.
      * @param asset The asset file path for the element's image.
     */
    Element(float x, float y, string asset);

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Returns the bounding rectangle of the element.
      * @return The bounding rectangle of the element.
     */
    QRect getRect();

    /**
      * @brief Returns the y-speed of the element.
      * @return The y-speed of the element.
     */
    float getYSpeed();

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Draws the element on a QPainter object.
      * @param aPainter A pointer to the QPainter object.
     */
    void draw(QPainter *aPainter);

};
#endif // ELEMENT_H
