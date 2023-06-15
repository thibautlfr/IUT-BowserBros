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

    QLabel * itsTitle;

    void setIsOnPaused(bool newIsOnPaused);

    bool getIsOnPaused() const;

    void saveSettings();

    void loadSettings();

signals:
    /**
     * @brief Signal emitted when the user has finished with the sound settings.
     */
    void finished();

    /**
     * @brief Signal emitted when the user want to restart the game (if he paused it).
     */
    void restarted();

private slots:
    /**
     * @brief Slot called when the "generalVolumeSlider" value changes.
     * @param value The new value of the general volume slider.
     */
    void on_generalVolumeSlider_valueChanged(int value);

    /**
     * @brief Slot called when the "effectsVolumeSlider" value changes.
     * @param value The new value of the effects volume slider.
     */
    void on_effectsVolumeSlider_valueChanged(int value);

private:
    Ui::SoundSettingsForm *ui; /**< The user interface object for the sound settings form. */
    void paintEvent(QPaintEvent *event);
    QLabel* musicVolumeLabel;
    QLabel* effectsVolumeLabel;

    bool isOnPaused = false ;

    fstream settingsFile;
};

#endif // SOUNDSSETTINGSFORM_H
