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

signals:
    /**
     * @brief Signal emitted when the music finishes playing.
     */
    void musicFinished();

private:
    QSoundEffect* jumpEffect;           /**< The jump sound effect object. */
    QSoundEffect* mainMusic;            /**< The main music sound effect object. */
    QSoundEffect* deathMusic;           /**< The death music sound effect object. */
    QSoundEffect* winMusic;             /**< The win music sound effect object. */
    QSoundEffect* menuMusic;            /**< The menu music sound effect object. */
    QSoundEffect* levelPassedMusic;     /**< The level passed music sound effect object. */
    float itsVolume;                    /**< The main music volume. */
    float itsEffectsVolume;             /**< The sound effects volume. */
};

#endif // SOUNDMANAGER_H
