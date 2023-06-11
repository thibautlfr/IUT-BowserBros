/**
@file menuform.h
@brief Defines the MenuForm class.
*/
#ifndef MENUFORM_H
#define MENUFORM_H

#include <QWidget>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include <QPaintEvent>
#include <list>

#include "soundmanager.h"

namespace Ui {
class MenuForm;
}

/**
@class MenuForm
@brief Represents the menu form of the game.
The MenuForm class represents the menu form of the game, where players can start or quit the game.
It inherits from the QWidget class.
*/
class MenuForm : public QWidget
{
    Q_OBJECT
public:
    QImage itsBackground; /**< The background image of the menu form. */
    QImage itsFloor; /**< The floor image of the menu form. */
    QImage itsMario; /**< The Mario image of the menu form. */
    QImage itsBowser; /**< The Bowser image of the menu form. */
    QImage itsGameTitle; /**< The game title image of the menu form. */

    SoundManager *soundManager;

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Constructs a MenuForm object.
      * @param parent The parent QWidget object.
    */
    explicit MenuForm(QWidget *parent = nullptr);

    void playMusic();

    void stopMusic();

    /**
      * @brief Destructs the MenuForm object.
    */
    ~MenuForm();

signals:
    /**
      * @brief Signal emitted when the play button is clicked.
    */
    void playButtonClicked();

    /**
      * @brief Signal emitted when the quit button is clicked.
     */
    void quitButtonClicked();

    /**
      * @brief Signal emitted when the podium button is clicked.
     */
    void podiumButtonClicked();

private:
    Ui::MenuForm *ui;

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Paints the menu form.
      * @param event The QPaintEvent object.
     */
    void paintEvent(QPaintEvent *event);
};

#endif // MENUFORM_H
