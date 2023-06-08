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

    QIcon newIcon(":Assets/Assets/other/chest.png");
    setWindowTitle("BowserBros");
    setWindowIcon(newIcon);

    stackedWidget = new QStackedWidget;
    stackedWidget->setFixedSize(800, 600);

    menuForm = new MenuForm;
    stackedWidget->addWidget(menuForm);

    scoreboardForm = new ScoreboardForm;
    stackedWidget->addWidget(scoreboardForm);

    connect(menuForm, &MenuForm::playButtonClicked, this, [=]() {
        gameForm = new GameForm;
        stackedWidget->addWidget(gameForm->getScrollArea());
        stackedWidget->setCurrentWidget(gameForm->getScrollArea());
        gameForm->setFocus();

        connect(gameForm, &GameForm::gameLosed, this, [=]() {
            stackedWidget->setCurrentWidget(menuForm);
            //delete gameForm;
        });
        connect(gameForm, &GameForm::gameWon, this, [=]() {
            stackedWidget->setCurrentWidget(scoreboardForm);
            scoreboardForm->setFocus();
        });

    });

    connect(menuForm, &MenuForm::quitButtonClicked, this, [=]() {
        QApplication::quit(); // Cette ligne de code quitte l'application
    });


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}
