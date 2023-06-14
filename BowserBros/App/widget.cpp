#include "widget.h"
#include "qicon.h"
#include "soundsettingsform.h"
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

    // Change le titre de la fenêtre
    setWindowTitle("Bowser Bros");

    // Changer l'icône du widget
    setWindowIcon(QIcon(":Assets/Assets/other/chest.png"));

    // Changer l'icône de l'application
    QApplication::setWindowIcon(QIcon(":Assets/Assets/other/logo.png"));

    //=======================================================================

    // Création du stacked widget
    stackedWidget = new QStackedWidget;
    stackedWidget->setFixedSize(800, 600);

    // Création du widget de menu
    menuForm = new MenuForm;
    stackedWidget->addWidget(menuForm);

    // Création du widget de paramètres
    SoundSettingsForm* soundSettingsForm = new SoundSettingsForm(this, menuForm->getSoundManager());
    stackedWidget->addWidget(soundSettingsForm);

    //=======================================================================

    // CONNECT POUR CHAQUE BOUTONS DU MENU

    // Bouton JOUER
    connect(menuForm, &MenuForm::playButtonClicked, this, [=]() {
        // Arrêt de la musique du menu
        menuForm->stopMusic();

        // Création et affichage du widget pour la partie
        gameForm = new GameForm;

        // Initialise les volumes sonores identiques aux volumes du Menu
        gameForm->setVolume(menuForm->getSoundManager());

        // Ajoute la scrollArea au stackedWidget ce qui permet de suivre le joueur
        stackedWidget->addWidget(gameForm->getScrollArea());
        stackedWidget->setCurrentWidget(gameForm->getScrollArea());
        gameForm->setFocus();

        // Retou au MENU quand la partie est perdue
        connect(gameForm, &GameForm::gameLosed, this, [=]() {
            if (gameForm != nullptr)
            {
                qDebug() << "GameForm deleted";
                delete gameForm;
                stackedWidget->setCurrentWidget(menuForm);
                menuForm->playMusic();
            }
        });

        // Affichage du temps et CLASSEMENT quand la partie est gagnée
        connect(gameForm, &GameForm::gameWon, this, [=](int elapsedTime) {
            menuForm->playMusic();
            if (gameForm != nullptr)
            {
                scoreboardForm = new ScoreboardForm(this, elapsedTime);
                stackedWidget->addWidget(scoreboardForm);
                stackedWidget->setCurrentWidget(scoreboardForm);
                scoreboardForm->setFocus();
                qDebug() << "GameForm deleted";
                delete gameForm;

                // Bouton MENU dans CLASSEMENT
                connect(scoreboardForm, &ScoreboardForm::menuButtonClicked, this, [=]() {
                    stackedWidget->setCurrentWidget(menuForm);
                    menuForm->setFocus();
                    delete scoreboardForm;
                });
            }
        });
    });

    // Bouton QUITTER
    connect(menuForm, &MenuForm::quitButtonClicked, this, &QApplication::quit);

    // Bouton CLASSEMENT
    connect(menuForm, &MenuForm::podiumButtonClicked, this, [=]() {
        scoreboardForm = new ScoreboardForm(this, 0);
        stackedWidget->addWidget(scoreboardForm);
        stackedWidget->setCurrentWidget(scoreboardForm);
        scoreboardForm->setFocus();

        // Bouton MENU dans CLASSEMENT
        connect(scoreboardForm, &ScoreboardForm::menuButtonClicked, this, [=]() {
            stackedWidget->setCurrentWidget(menuForm);
            menuForm->setFocus();
            delete scoreboardForm;
        });
    });

    // Bouton PARAMÈTRES
    connect(menuForm, &MenuForm::soundSettingsButtonClicked, this, [=]() {

        stackedWidget->setCurrentWidget(soundSettingsForm);
        soundSettingsForm->setFocus();

        // Bouton MENU dans les PARAMÈTRES
        connect(soundSettingsForm, &SoundSettingsForm::finished, this, [=]() {
            stackedWidget->setCurrentWidget(menuForm);
            menuForm->setFocus();
        });

    });

    //=======================================================================

    // Création d'un layout pour centrer la fenêtre en plein écran
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addStretch(1);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(stackedWidget);
    hLayout->addStretch(1);
    vLayout->addLayout(hLayout);
    vLayout->addStretch(1);

    setLayout(vLayout);
}

Widget::~Widget()
{
    if (stackedWidget != nullptr)
    {
        delete stackedWidget;
    }

    delete ui;
}
