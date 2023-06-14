#include "trainingform.h"
#include "ui_trainingform.h"

#include <QFontDatabase>

TrainingForm::TrainingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingForm)
{
    ui->setupUi(this);

    setFixedSize(800, 600);

    // --------------------------------------------------------------------------------------------------------------------------------

    // Charger les images
    itsBackground.load(":Assets/Assets/background/backgroundMenu.png");
    itsFloor.load(":Assets/Assets/other/floor.png");
    itsMario.load(":Assets/Assets/mario/mario6.png");
    itsBowser.load(":Assets/Assets/bowser/bowsermenu.png");

    // --------------------------------------------------------------------------------------------------------------------------------

    // Bouton menu
    QPixmap menuAsset(":/Assets/Assets/menu/menu.png");
    ui->menuButton->setIcon(menuAsset);
    ui->menuButton->setIconSize(QSize(200, 70));

    // Création des images des boutons du jeu
    QPixmap lvl1Asset(":Assets/Assets/menu/screenlvl1.png");
    ui->level1Button->setIcon(lvl1Asset);
    ui->level1Button->setIconSize(lvl1Asset.size());

    QPixmap lvl2Asset(":Assets/Assets/menu/screenlvl2.png");
    ui->level2Button->setIcon(lvl2Asset);
    ui->level2Button->setIconSize(lvl2Asset.size());

    QPixmap lvl3Asset(":Assets/Assets/menu/screenlvl3.png");
    ui->level3Button->setIcon(lvl3Asset);
    ui->level3Button->setIconSize(lvl3Asset.size());

    QPixmap lvl4Asset(":Assets/Assets/menu/screenlvl4.png");
    ui->level4Button->setIcon(lvl4Asset);
    ui->level4Button->setIconSize(lvl4Asset.size());

    QPixmap lvl5Asset(":Assets/Assets/menu/screenlvl5.png");
    ui->level5Button->setIcon(lvl5Asset);
    ui->level5Button->setIconSize(lvl5Asset.size());

    // --------------------------------------------------------------------------------------------------------------------------------

    // Charger la police depuis le fichier
    QString fontPath = ":Fonts/Fonts/policeMario2.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily, 22);

    ui->niv1Label->setFont(font);
    ui->niv1Label->setStyleSheet("font-size: 15px; color: white;");

    ui->niv2Label->setFont(font);
    ui->niv2Label->setStyleSheet("font-size: 15px; color: white;");

    ui->niv3Label->setFont(font);
    ui->niv3Label->setStyleSheet("font-size: 15px; color: white;");

    ui->niv4Label->setFont(font);
    ui->niv4Label->setStyleSheet("font-size: 15px; color: white;");

    ui->niv5Label->setFont(font);
    ui->niv5Label->setStyleSheet("font-size: 15px; color: white;");

    // --------------------------------------------------------------------------------------------------------------------------------

    // Connect du bouton MENU
    connect(ui->menuButton, &QPushButton::clicked, this, &TrainingForm::menuButtonClicked);

    // Connects des boutons NIVEAUX
    connect(ui->level1Button, &QPushButton::clicked, this, &TrainingForm::level1ButtonClicked);
    connect(ui->level2Button, &QPushButton::clicked, this, &TrainingForm::level2ButtonClicked);
    connect(ui->level3Button, &QPushButton::clicked, this, &TrainingForm::level3ButtonClicked);
    connect(ui->level4Button, &QPushButton::clicked, this, &TrainingForm::level4ButtonClicked);
    connect(ui->level5Button, &QPushButton::clicked, this, &TrainingForm::level5ButtonClicked);

    repaint();
}

TrainingForm::~TrainingForm()
{
    delete ui;
}

void TrainingForm::level1ButtonClicked()
{
    emit levelSelected(1);
}

void TrainingForm::level2ButtonClicked()
{
    emit levelSelected(2);
}

void TrainingForm::level3ButtonClicked()
{
    emit levelSelected(3);
}

void TrainingForm::level4ButtonClicked()
{
    emit levelSelected(4);
}

void TrainingForm::level5ButtonClicked()
{
    emit levelSelected(5);
}



void TrainingForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter * painter = new QPainter(this);
    painter->drawImage(0, 0, itsBackground);
    painter->drawImage(0, height()-20, itsFloor);
    painter->drawImage(90, height()-20-45, itsMario);
    painter->drawImage(width() - 170, height()-20-86, itsBowser);
    delete painter;
}
