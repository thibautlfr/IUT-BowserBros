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

    menuForm = new MenuForm;
    setWindowTitle("BrowserBros");
    QIcon newIcon(":Assets/Assets/other/chest.png");
    setWindowIcon(newIcon);
    stackedWidget = new QStackedWidget;
    stackedWidget->setFixedSize(800, 600);
    stackedWidget->addWidget(menuForm);

    connect(menuForm, &MenuForm::playButtonClicked, this, [=]() {
        gameForm = new GameForm;
        stackedWidget->addWidget(gameForm->getScrollArea());
        stackedWidget->setCurrentWidget(gameForm->getScrollArea());
        gameForm->setFocus();

        connect(gameForm, &GameForm::quitButtonClicked, this, [=]() {
            stackedWidget->setCurrentWidget(menuForm);
            //delete gameForm;
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
