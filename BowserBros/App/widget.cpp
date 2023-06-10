#include "widget.h"
#include "qicon.h"
#include "ui_widget.h"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QScrollArea>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //=======================================================================

    // Change le titre et l'icone de la fenêtre
    setWindowTitle("BowserBros");
    QIcon newIcon(":Assets/Assets/other/chest.png");
    setWindowIcon(newIcon);

    // Création du stacked widget
    stackedWidget = new QStackedWidget;
    stackedWidget->setFixedSize(800, 600);

    // Création du widget de menu
    menuForm = new MenuForm;
    stackedWidget->addWidget(menuForm);

    //=======================================================================

    // Connect pour lancer une partie avec le bouton Jouer
    connect(menuForm, &MenuForm::playButtonClicked, this, [=]() {
        // Arret de la musique du menu
        menuForm->stopMusic();

        // Création et affichage du widget pour la partie
        gameForm = new GameForm;
        stackedWidget->addWidget(gameForm->getScrollArea());
        stackedWidget->setCurrentWidget(gameForm->getScrollArea());
        gameForm->setFocus();

        connect(gameForm, &GameForm::quitButtonClicked, this, [=]() {
            if (gameForm != nullptr)
            {
                qDebug() << "GameForm deleted";
                delete gameForm;
            }
            stackedWidget->setCurrentWidget(menuForm);
            menuForm->playMusic();
        });
    });

    // Connect pour quitter le jeu avec le bouton quitter
    connect(menuForm, &MenuForm::quitButtonClicked, this, [=]() {
        QApplication::quit(); // Cette ligne de code quitte l'application
    });

    //=======================================================================

    // Créez un layout pour centrer la fenêtre en plsin écran
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addStretch(1);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(stackedWidget);
    hLayout->addStretch(1);
    vLayout->addLayout(hLayout);
    vLayout->addStretch(1);

    this->setLayout(vLayout);

}

Widget::~Widget()
{
    if (menuForm != nullptr)
    {
        delete menuForm;
    }
    delete ui;
}
