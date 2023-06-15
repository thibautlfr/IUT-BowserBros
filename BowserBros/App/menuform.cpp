#include "menuform.h"
#include "QtGui/qpainter.h"
#include "soundsettingsform.h"
#include "ui_menuform.h"

#include <QPixmap>
#include <QPalette>

MenuForm::MenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuForm)
{
    ui->setupUi(this);

    // Définition de la taille
    setFixedSize(800, 600);

    // Chargement des images
    itsBackground.load(":Assets/Assets/background/backgroundMenu.png");
    itsFloor.load(":Assets/Assets/other/floor.png");
    itsGameTitle.load(":Assets/Assets/menu/gametitle.png");
    itsMario.load(":Assets/Assets/mario/mario6.png");
    itsBowser.load(":Assets/Assets/bowser/bowsermenu.png");

    // Création du manager de son
    soundManager = new SoundManager;
    soundManager->playMenuMusic();

    // Création des images des boutons du jeu
    QPixmap playAsset(":Assets/Assets/menu/playbutton.png");
    ui->playButton->setIcon(playAsset);
    ui->playButton->setIconSize(playAsset.size());

    QPixmap quitAsset(":Assets/Assets/menu/quitbutton.png");
    ui->quitButton->setIcon(quitAsset);
    ui->quitButton->setIconSize(quitAsset.size());

    // Création des images des boutons du jeu
    QPixmap trainingAsset(":Assets/Assets/menu/training.png");
    ui->trainingButton->setIcon(trainingAsset);
    ui->trainingButton->setIconSize(QSize(200, 50));

    QPixmap podiumAsset(":/Assets/Assets/other/podium.png");
    ui->podiumButton->setIcon(podiumAsset);
    ui->podiumButton->setIconSize(QSize(110, 110));

    QPixmap soundSettingsAsset(":/Assets/Assets/menu/setting.png");
    ui->soundSettingsButton->setIcon(soundSettingsAsset);
    ui->soundSettingsButton->setIconSize(soundSettingsAsset.size());


    connect(ui->playButton, &QPushButton::clicked, this, &MenuForm::playButtonClicked);
    connect(ui->quitButton, &QPushButton::clicked, this, &MenuForm::quitButtonClicked);
    connect(ui->podiumButton, &QPushButton::clicked, this, &MenuForm::podiumButtonClicked);
    connect(ui->trainingButton, &QPushButton::clicked, this, &MenuForm::trainingButtonClicked);
    connect(ui->soundSettingsButton, &QPushButton::clicked, this, &MenuForm::soundSettingsButtonClicked);


    repaint();
}

MenuForm::~MenuForm()
{
    delete ui;
}

SoundManager* MenuForm::getSoundManager() const
{
    return soundManager;
}

void MenuForm::playMusic()
{
    soundManager->playMenuMusic();
}

void MenuForm::stopMusic()
{
    soundManager->stopAllSounds();
}

void MenuForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter * painter = new QPainter(this);
    painter->drawImage(0, 0, itsBackground);
    painter->drawImage(0, height()-20, itsFloor);
    painter->drawImage(135, 100, itsGameTitle);
    painter->drawImage(90, height()-20-45, itsMario);
    painter->drawImage(width() - 170, height()-20-86, itsBowser);
    delete painter;
}

