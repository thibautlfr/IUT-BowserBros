/**
 * @file SoundManager.h
 * @brief The SoundManager class manages the playback of various sounds and music in the application.
 */

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QThread>
#include <QSoundEffect>

/**
 * @class SoundManager
 * @brief The SoundManager class manages the playback of various sounds and music in the application.
 *
 * The SoundManager class provides functionality to play jump sound effects,
 * main music, menu music, death music, win music, and level passed music.
 * It also allows setting the main and effects volume, stopping all sounds, and retrieving volume levels.
 */
class SoundManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a SoundManager object.
     * @param parent The parent object (default is nullptr).
     */
    explicit SoundManager(QObject *parent = nullptr);

    /**
     * @brief Destroys the SoundManager object.
     */
    ~SoundManager();

    /**
     * @brief Plays the jump sound effect.
     */
    void playJumpEffect();

    void playKoopaBumpEffect();

    void playEnnemyDeathEffect();


    // ---------------------------------------------------------------------------------------------------------

    /**
     * @brief Plays the main music.
     */
    void playMainMusic();

    /**
     * @brief Plays the menu music.
     */
    void playMenuMusic();

    /**
     * @brief Plays the death music.
     */
    void playDeathMusic();

    /**
     * @brief Plays the win music.
     */
    void playWinMusic();

    /**
     * @brief Plays the level passed music.
     */
    void playLevelPassedMusic();

    // -----------------------------------------------------------------------------------------

    /**
     * @brief Returns the current main music volume.
     * @return The main music volume level.
     */
    float getVolume() const;

    /**
     * @brief Returns the current sound effects volume.
     * @return The sound effects volume level.
     */
    float getEffectsVolume() const;

    // -----------------------------------------------------------------------------------------

    /**
     * @brief Sets the main music volume.
     * @param volume The volume level to set (0.0 to 1.0).
     */
    void setMainVolume(float volume);

    /**
     * @brief Sets the sound effects volume.
     * @param volume The volume level to set (0.0 to 1.0).
     */
    void setEffectsVolume(float volume);

    /**
     * @brief Stops all currently playing sounds.
     */
    void stopAllSounds();

private:
    QSoundEffect *jumpEffect; /**< A jump sound effect. */
    QSoundEffect *koopaBumpEffect;
    QSoundEffect *ennemyDeathEffect;

    // -----------------------------------------------------------------------------------------

    QSoundEffect *mainMusic; /**< The main music of the game. */
    QSoundEffect *deathMusic; /**< Music theme for loosing the game. */
    QSoundEffect *winMusic; /**< Music theme when winning the game. */
    QSoundEffect *levelPassedMusic; /**< Sound effect happening when mario passes a level. */
    QSoundEffect *menuMusic; /**< Main menu music theme. */

    // -----------------------------------------------------------------------------------------

    float itsVolume;                    /**< The main music volume. */
    float itsEffectsVolume;             /**< The sound effects volume. */

signals:
    /**
     * @brief Signal emitted when the music finishes playing.
     */
    void musicFinished();

};

#endif // SOUNDMANAGER_H
