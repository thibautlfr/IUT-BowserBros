#include "menuform.h"
#include "ui_menuform.h"

MenuForm::MenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuForm)
{
    ui->setupUi(this);

    setFixedSize(800, 600);

    connect(ui->playButton, &QPushButton::clicked, this, &MenuForm::playButtonClicked);
}

MenuForm::~MenuForm()
{
    delete ui;
}


