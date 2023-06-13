/**
 * @file SoundSettingsForm.h
 * @brief The SoundSettingsForm class represents a form for sound settings.
 */

#ifndef SOUNDSSETTINGSFORM_H
#define SOUNDSSETTINGSFORM_H

#include <QWidget>
#include "soundmanager.h"

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

signals:
    /**
     * @brief Signal emitted when the user has finished with the sound settings.
     */
    void finished();

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
};

#endif // SOUNDSSETTINGSFORM_H
