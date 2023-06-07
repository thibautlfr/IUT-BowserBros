/**
@file widget.h
@brief Defines the Widget class.
*/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>

#include "menuform.h"
#include "gameform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

/**
@class Widget
@brief Represents the main widget of the game.
The Widget class represents the main widget of the game, which contains the menu form and the game form.
It inherits from the QWidget class.
*/
class Widget : public QWidget
{
    Q_OBJECT
    MenuForm* menuForm; /**< The menu form object. */
    GameForm*gameForm; /**< The game form object. */
public:
    /**
      * @brief Constructs a Widget object.
      * @param parent The parent QWidget object.
     */
    Widget(QWidget *parent = nullptr);

    /**
      * @brief Destructs the Widget object.
     */
    ~Widget();

private:
    Ui::Widget *ui;
    QStackedWidget* stackedWidget; /**< The stack widget to switch between level and menu */
};

#endif // WIDGET_H
