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

    // Création du widget de paramètres
    SoundSettingsForm* soundSettingsForm = new SoundSettingsForm(this, menuForm->getSoundManager());

    //=======================================================================

    // Connect pour lancer une partie avec le bouton Jouer
    connect(menuForm, &MenuForm::playButtonClicked, this, [=]() {
        // Arrêt de la musique du menu
        menuForm->stopMusic();

        // Création et affichage du widget pour la partie
        gameForm = new GameForm;
        // Initialise les volumes sonores identiques aux volumes du Menu
        gameForm->setVolume(menuForm->getSoundManager());
        stackedWidget->addWidget(gameForm->getScrollArea());
        stackedWidget->setCurrentWidget(gameForm->getScrollArea());
        gameForm->setFocus();

        // Connect pour gérer la fin de la partie
        connect(gameForm, &GameForm::gameLosed, this, [=]() {
            if (gameForm != nullptr)
            {
                qDebug() << "GameForm deleted";
                delete gameForm;
                stackedWidget->setCurrentWidget(menuForm);
                menuForm->playMusic();
            }
        });

        // Connect pour gérer la victoire dans le jeu
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

                // Connect pour revenir au menu depuis le formulaire de classement
                connect(scoreboardForm, &ScoreboardForm::menuButtonClicked, this, [=]() {
                    stackedWidget->setCurrentWidget(menuForm);
                    menuForm->setFocus();
                    delete scoreboardForm;
                });
            }
        });
    });

    // Connect pour quitter le jeu avec le bouton quitter
    connect(menuForm, &MenuForm::quitButtonClicked, this, &QApplication::quit);

    // Connect pour afficher le formulaire de classement
    connect(menuForm, &MenuForm::podiumButtonClicked, this, [=]() {
        scoreboardForm = new ScoreboardForm(this, 0);
        stackedWidget->addWidget(scoreboardForm);
        stackedWidget->setCurrentWidget(scoreboardForm);
        scoreboardForm->setFocus();

        // Connect pour revenir au menu depuis le formulaire de classement
        connect(scoreboardForm, &ScoreboardForm::menuButtonClicked, this, [=]() {
            stackedWidget->setCurrentWidget(menuForm);
            menuForm->setFocus();
            delete scoreboardForm;
        });
    });

    // Connect pour afficher le widget des paramètres
    connect(menuForm, &MenuForm::soundSettingsButtonClicked, this, [=]() {

        stackedWidget->addWidget(soundSettingsForm);

        stackedWidget->setCurrentWidget(soundSettingsForm);
        soundSettingsForm->setFocus();
        menuForm->hide();// Cachez le formulaire de menu lorsque le formulaire de paramètres sonores est affiché

        // Connect pour revenir au menu depuis le formulaire de classement
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
    if (soundSettingsForm != nullptr)
    {
        delete soundSettingsForm;
    }
    if (menuForm != nullptr)
    {
        delete menuForm;
    }
    delete stackedWidget;

    delete ui;
}
