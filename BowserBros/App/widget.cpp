#include "widget.h"
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

    stackedWidget = new QStackedWidget;
    stackedWidget->setFixedSize(800, 600);
    stackedWidget->addWidget(menuForm);

    connect(menuForm, &MenuForm::playButtonClicked, this, [=]() {
        gameForm = new GameForm;
        stackedWidget->addWidget(gameForm->getScrollArea());
        stackedWidget->setCurrentWidget(gameForm->getScrollArea());
        gameForm->setFocus();
    });

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}
