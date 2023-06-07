/**
@file soundcontroller.h
@brief Defines the SoundController class.
*/

#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H
#include <iostream>
using namespace std;

//Song
#include <QMediaPlayer>
#include <QSoundEffect>

/**
@class SoundController
@brief This class is used to manage the sound of the game
*/
class SoundController
{
private:
    QSoundEffect * mainsound; /**< The main music of the game. */
    QSoundEffect * jumpsound; /**< The jump sound asset. */
    QSoundEffect * gameoversound; /**< The game over sound. */
    QSoundEffect * winsound; /**< The win sound. */

public:

    /**
     * @brief Constructor for SoundController
     */
    SoundController();

    /**
     * @brief Destructor for SoundController
     */
    ~SoundController();

    // --------------------------------------------------------------------------------------------

    /**
     * @brief Starts the main music of the level
     */
    void MainSound();

    /**
     * @brief Stops the main music of the level
     */
    void StopMainSound();

    /**
     * @brief Play the sound asset for the mario jump
     */
    void JumpSound();

    /**
     * @brief Plays the game over sound
     */
    void GameoverSound();

    /**
     * @brief Plays the winning sound assset
     */
    void WinSound();
};

#endif // SOUNDCONTROLLER_H
