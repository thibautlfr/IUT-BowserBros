#include "soundsettingsform.h"
#include "ui_soundsettingsform.h"

#include <QDebug>

SoundSettingsForm::SoundSettingsForm(QWidget *parent,  SoundManager *soundMenuManager) :
    QWidget(parent),
    menuSoundManager(soundMenuManager),
    ui(new Ui::SoundSettingsForm)

{
    ui->setupUi(this);

    setFixedSize(800, 600);

    // Initialise les valeurs des sliders avec les valeurs actuelles du SoundManager
    ui->generalVolumeSlider->setValue(static_cast<int>(100));
    ui->effectsVolumeSlider->setValue(static_cast<int>(100));

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
    //En fonction de la valeur du sliders, divise par 100 pour avoir la valeur comprise entre 0 et 1
    menuSoundManager->setMainVolume(static_cast<float>(value) / 100.0f);
}

void SoundSettingsForm::on_effectsVolumeSlider_valueChanged(int value)
{
    menuSoundManager->setEffectsVolume(static_cast<float>(value) / 100.0f);
}
