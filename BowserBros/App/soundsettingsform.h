/**
 * @file SoundSettingsForm.h
 * @brief The SoundSettingsForm class represents a form for sound settings.
 */

#ifndef SOUNDSSETTINGSFORM_H
#define SOUNDSSETTINGSFORM_H

#include <QWidget>
#include <QJsonObject>
#include <QFile>
#include "qlabel.h"
#include "soundmanager.h"
#include <fstream>
#include <iostream>
#include <istream>

using namespace std ;

namespace Ui {
class SoundSettingsForm;
}

/**
 * @class SoundSettingsForm
 * @brief The SoundSettingsForm class represents a form for sound settings.
 *
 * The SoundSettingsForm class provides a graphical user interface for adjusting sound settings.
 * It allows the user to control the general volume and effects volume using sliders.
 * The class emits a signal when the user has finished with the sound settings.
 */
class SoundSettingsForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a SoundSettingsForm object.
     * @param parent The parent widget (default is nullptr).
     * @param soundMenuManager The sound manager object for menu sounds (default is nullptr).
     */
    explicit SoundSettingsForm(QWidget *parent = nullptr, SoundManager *soundMenuManager = nullptr);

    /**
     * @brief Destroys the SoundSettingsForm object.
     */
    ~SoundSettingsForm();

    SoundManager * menuSoundManager; /**< The sound manager object for menu sounds. */

    QImage itsBackground; /**< The background image of the scoreboard form. */
    QImage itsFloor; /**< The floor image of the scoreboard form. */
    QImage itsMario; /**< The Mario image of the scoreboard form. */
    QImage itsBowser; /**< The Bowser image of the scoreboard form. */

    QLabel * itsTitle; /**< The title label of the sound settings form. */

    /**
     * @brief Sets the paused state of the game.
     * @param newIsOnPaused The new paused state of the game.
     */
    void setIsOnPaused(bool newIsOnPaused);

    /**
     * @brief Gets the paused state of the game.
     * @return The paused state of the game.
     */
    bool getIsOnPaused() const;

    /**
     * @brief Saves the sound settings to a file.
     */
    void saveSettings();

    /**
     * @brief Loads the sound settings from a file.
     */
    void loadSettings();

signals:
    /**
     * @brief Signal emitted when the user has finished with the sound settings.
     */
    void finished();

    /**
     * @brief Signal emitted when the user wants to restart the game (if it was paused).
     */
    void restarted();

private slots:
    /**
     * @brief Slot called when the value of the "generalVolumeSlider" changes.
     * @param value The new value of the general volume slider.
     */
    void on_generalVolumeSlider_valueChanged(int value);

    /**
     * @brief Slot called when the value of the "effectsVolumeSlider" changes.
     * @param value The new value of the effects volume slider.
     */
    void on_effectsVolumeSlider_valueChanged(int value);

private:
    Ui::SoundSettingsForm *ui; /**< The user interface object for the sound settings form. */

    /**
     * @brief Paints the sound settings form.
     * @param event The QPaintEvent object.
     */
    void paintEvent(QPaintEvent *event);

    QLabel* musicVolumeLabel; /**< The label for displaying the music volume. */
    QLabel* effectsVolumeLabel; /**< The label for displaying the effects volume. */

    bool isOnPaused = false; /**< Flag indicating if the game is currently paused. */

    fstream settingsFile; /**< The file stream for saving and loading sound settings. */
};

#endif // SOUNDSSETTINGSFORM_H
