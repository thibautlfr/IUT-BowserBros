/**
 * @file scoreboardform.h
 * @brief The ScoreboardForm class represents a form for displaying and managing a scoreboard.
 *
 * This class provides a graphical user interface for displaying a scoreboard with player names and scores.
 * It allows adding new scores, updating the scoreboard, and navigating back to the main menu.
 * @author Thibaut LEFRANCOIS
*/
#ifndef SCOREBOARDFORM_H
#define SCOREBOARDFORM_H

#include "scoreboard.h"
#include "ui_scoreboardform.h"
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>



class ScoreboardForm : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Constructs a ScoreboardForm object.
     * @param parent The parent widget (default is nullptr).
     * @param elapsedTime The elapsed time for the player's score in milliseconds (default is 0).
     */
    explicit ScoreboardForm(QWidget *parent = nullptr, int elapsedTime = 0);
    /**
     * @brief Destructor for the ScoreboardForm object.
     */
    ~ScoreboardForm();

    /**
     * @brief Fills the scoreboard table with player names and scores.
     */
    void fillScoreboardTable();

    /**
     * @brief Sets the settings for the scoreboard table.
     */
    void setSettingsTable();

    ScoreBoard * itsScoreBoard; /**< The scoreboard object for managing scores. */

    QTableWidget* itsRankingTable; /**< The table widget for displaying the scoreboard. */

    QImage itsBackground; /**< The background image of the scoreboard form. */
    QImage itsFloor; /**< The floor image of the scoreboard form. */
    QImage itsMario; /**< The Mario image of the scoreboard form. */
    QImage itsBowser; /**< The Bowser image of the scoreboard form. */

    QString playerName; /**< The name of the player. */
    float playerScore; /**< The score of the player. */

    QLabel * itsTitle; /**< The title label of the scoreboard form. */
    QLabel * itsPlayerTimeLabel; /**< The label for displaying the player's time. */
    QLabel * itsInstructionsLabel; /**< The label for displaying instructions. */
    QLineEdit * itsPseudoLineEdit; /**< The line edit for entering the player's name. */

    QPushButton * enterButton; /**< The button for entering the player's name. */

signals:
    /**
     * @brief Signal emitted when the menu button is clicked.
     */
    void menuButtonClicked();

private slots:
    /**
     * @brief Slot for handling the event when the player's name is entered.
     */
    void onNameEntered();

private:
    Ui::ScoreboardForm *ui;

    /**
     * @brief Paints the scoreboard form.
     * @param event The QPaintEvent object.
     */
    void paintEvent(QPaintEvent *event);
};

#endif // SCOREBOARDFORM_H
