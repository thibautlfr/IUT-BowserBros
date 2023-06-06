#include "menuform.h"
#include "QtGui/qpainter.h"
#include "ui_menuform.h"

#include <QPixmap>
#include <QPalette>

MenuForm::MenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuForm)
{
    ui->setupUi(this);

    setFixedSize(800, 600);
    itsBackground.load(":Assets/Assets/background/background4.png");
    itsFloor.load(":Assets/Assets/other/floor.png");
    itsGameTitle.load(":Assets/Assets/menu/gametitle.png");
    itsMario.load(":Assets/Assets/mario/mario6.png");
    itsBowser.load(":Assets/Assets/bowser/bowsermenu.png");

    // Création des images des boutons du jeu
    QPixmap playAsset(":Assets/Assets/menu/playbutton.png");
    ui->playButton->setIcon(playAsset);
    ui->playButton->setIconSize(playAsset.size());

    QPixmap quitAsset(":Assets/Assets/menu/quitbutton.png");
    ui->quitButton->setIcon(quitAsset);
    ui->quitButton->setIconSize(quitAsset.size());

    connect(ui->playButton, &QPushButton::clicked, this, &MenuForm::playButtonClicked);
    connect(ui->quitButton, &QPushButton::clicked, this, &MenuForm::quitButtonClicked);

    repaint();
}

MenuForm::~MenuForm()
{
    delete ui;
}

void MenuForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter * painter = new QPainter(this);
    painter->drawImage(0, 0, itsBackground);
    painter->drawImage(0, height()-20, itsFloor);
    painter->drawImage(135, 100, itsGameTitle);
    painter->drawImage(70, height()-20-45, itsMario);
    painter->drawImage(width() - 150, height()-20-86, itsBowser);
    delete painter;
}


