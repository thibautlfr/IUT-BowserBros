/**
@file soundmanager.h
@brief Defines the SoundManager class.
*/

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QSoundEffect>

/**
@class ScoreBoard
@brief This class is used to interact with the players ScoreBoard
@author Colin, Lilian, Pierre
*/
class SoundManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for SoundManager
     * @details Loads each .wav files for the game
     */
    explicit SoundManager(QObject *parent = nullptr);

    /**
     * @brief Destructor for SoundManager
     */
    ~SoundManager();

    // ---------------------------------------------------------------------------------------------------------

    /**
     * @brief Plays the jump effect sound
     */
    void playJumpEffect();

    /**
     * @brief Plays the main music of the game
     */
    void playMainMusic();

    /**
     * @brief Play a different music when mario hits an ennemy and looses the game
     */
    void playDeathMusic();

    /**
     * @brief Plays the winning theme of the mario game
     */
    void playWinMusic();

    /**
     * @brief Plays a sound effect when mario passes a level
     */
    void playLevelPassedMusic();

    /**
     * @brief Plays the main theme of the menu
     */
    void playMenuMusic();

    /**
     * @brief Stop all of the currently playing sounds
     */
    void stopAllSounds();

private:
    QSoundEffect *jumpEffect; /**< A jump sound effect. */
    QSoundEffect *mainMusic; /**< The main music of the game. */
    QSoundEffect *deathMusic; /**< Music theme for loosing the game. */
    QSoundEffect *winMusic; /**< Music theme when winning the game. */
    QSoundEffect *levelPassedMusic; /**< Sound effect happening when mario passes a level. */
    QSoundEffect *menuMusic; /**< Main menu music theme. */

signals:
    /**
     * @brief Signal launched when a sound effect has finished to play
     */
    void musicFinished();
};


#endif // SOUNDMANAGER_H
