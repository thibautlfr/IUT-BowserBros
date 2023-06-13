#ifndef SOUNDSSETTINGSFORM_H
#define SOUNDSSETTINGSFORM_H

#include <QWidget>
#include "soundmanager.h"

namespace Ui {
class SoundSettingsForm;
}

class SoundSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SoundSettingsForm(QWidget *parent = nullptr, SoundManager *soundGameManager = nullptr, SoundManager *soundMenuManager = nullptr);
    ~SoundSettingsForm();

signals:
    void finished();  // Ce signal est émis lorsque l'utilisateur a terminé avec les paramètres sonores

private slots: // Ce slot est appelé lorsque le bouton "Terminé" est cliqué
    void on_generalVolumeSlider_valueChanged(int value);  // Ce slot est appelé lorsque la valeur du slider de volume général change
    void on_effectsVolumeSlider_valueChanged(int value);  // Ce slot est appelé lorsque la valeur du slider de volume des effets change

private:
    Ui::SoundSettingsForm *ui;
    SoundManager * menuSoundManager;
    SoundManager * gameSoundManager;
};


#endif // SOUNDSSETTINGSFORM_H
