/**
@file bowser.h
@brief Defines the Bowser class.
*/

#ifndef BOWSER_H
#define BOWSER_H

#include <vector>

#include "fireball.h"
#include "entity.h"

using namespace std;

/**
@class Bowser
@brief Represents the Bowser enemy.
The Bowser class is derived from the Entity class and provides functionalities specific to Bowser.
*/
class Bowser : public Entity
{
private:
    vector<FireBall*> * itsFireBalls; /**< Pointer to the vector of FireBall objects. */
public:
    /**
      * @brief Constructs a Bowser object.
      * @param x The x-coordinate of the Bowser's position.
      * @param y The y-coordinate of the Bowser's position.
      * @param width The width of the Bowser's sprite.
      * @param height The height of the Bowser's sprite.
      * @param asset The asset file path for the Bowser's sprite.
    */
    Bowser(float x, float y, int width, int height, string asset);

    /**
      * @brief Destroys the Bowser object.
    */
    ~Bowser();

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Returns a pointer to the vector of FireBall objects.
      * @return A pointer to the vector of FireBall objects.
    */
    vector<FireBall*> * getItsFireBalls();

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Drops a FireBall.
      *
      * Creates a new FireBall object and adds it to the vector of FireBall objects.
     */
    void dropFireBall();

    /**
      * @brief Erases a FireBall.
      * @param it An iterator pointing to the FireBall to be erased.
     */
    void eraseFireBall(vector<FireBall*>::iterator it);
};
#endif // BOWSER_H
