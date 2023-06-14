#include "trainingform.h"
#include "ui_trainingform.h"

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

    // Connect du bouton MENU
    connect(ui->menuButton, &QPushButton::clicked, this, &TrainingForm::menuButtonClicked);

    // Connects des boutons NIVEAUX
    connect(ui->level1Button, &QPushButton::clicked, this, &TrainingForm::level1ButtonClicked);
    connect(ui->level2Button, &QPushButton::clicked, this, &TrainingForm::level2ButtonClicked);
    connect(ui->level3Button, &QPushButton::clicked, this, &TrainingForm::level3ButtonClicked);
    connect(ui->level4Button, &QPushButton::clicked, this, &TrainingForm::level4ButtonClicked);

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
