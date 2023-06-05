#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include "menuform.h"
#include "gameform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    MenuForm * menuForm;
    GameForm * gameForm;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QStackedWidget* stackedWidget;
};
#endif // WIDGET_H
