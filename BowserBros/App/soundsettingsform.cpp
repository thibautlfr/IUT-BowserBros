#include "soundsettingsform.h"
#include "ui_soundsettingsform.h"

#include <QDebug>

SoundSettingsForm::SoundSettingsForm(QWidget *parent, SoundManager *soundGameManager, SoundManager *soundMenuManager) :
    QWidget(parent),
    ui(new Ui::SoundSettingsForm),
    menuSoundManager(soundMenuManager),
    gameSoundManager(soundGameManager)

{
    ui->setupUi(this);

    // Initialise les valeurs des sliders avec les valeurs actuelles du SoundManager
    ui->generalVolumeSlider->setValue(static_cast<int>(100));  // Convertit une valeur de volume (0.0-1.0) en une valeur de slider (0-100)
    ui->effectsVolumeSlider->setValue(static_cast<int>(100));  // Convertit une valeur de volume (0.0-1.0) en une valeur de slider (0-100)

    // --------------------------------------------------------------------------------------------------------------------------------

    // Bouton menu
    QPixmap menuAsset(":/Assets/Assets/menu/menu.png");
    ui->finishedButton->setIcon(menuAsset);
    ui->finishedButton->setIconSize(QSize(200, 70));

    connect(ui->finishedButton, &QPushButton::clicked, this, &SoundSettingsForm::finished);

    // --------------------------------------------------------------------------------------------------------------------------------


}


SoundSettingsForm::~SoundSettingsForm()
{
    delete ui;
}

void SoundSettingsForm::on_generalVolumeSlider_valueChanged(int value)
{
    gameSoundManager->setVolume(static_cast<float>(value) / 100.0f);
    menuSoundManager->setVolume(static_cast<float>(value) / 100.0f);
    qDebug()<<"Volume Changer"<<value;// Convertit la valeur du slider (0-100) en une valeur de volume (0.0-1.0)
    qDebug()<<gameSoundManager->getVolume();
}

void SoundSettingsForm::on_effectsVolumeSlider_valueChanged(int value)
{
    //soundManager->setEffectsVolume(static_cast<float>(value) / 100.0f);  // Convertit la valeur du slider (0-100) en une valeur de volume (0.0-1.0)
    gameSoundManager->setEffectsVolume(static_cast<float>(value) / 100.0f);
    menuSoundManager->setEffectsVolume(static_cast<float>(value) / 100.0f);
}
