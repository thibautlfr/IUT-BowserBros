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
#include "soundsettingsform.h"
#include "scoreboardform.h"
#include "trainingform.h"

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

public:
    /**
      * @brief Constructs a Widget object.
      * @param parent The parent QWidget object.
     */
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QStackedWidget* stackedWidget;
    MenuForm * menuForm; /**< The menu form object. */
    GameForm * gameForm;/**< The game form object. */
    TrainingForm * trainingForm;
    SoundSettingsForm * soundSettingsForm; /**< The sound settings board form object */
    ScoreboardForm * scoreboardForm; /**< The score board form object */
    QMetaObject::Connection gamePausedConnection;
};

#endif // WIDGET_H
