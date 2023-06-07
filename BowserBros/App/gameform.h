/**
@file gameform.h
@brief Defines the GameForm class.
*/
#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QWidget>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QScrollBar>
#include <QScrollArea>
#include <list>

//Song
#include <QMediaPlayer>
#include <QSoundEffect>

#include "mario.h"
#include "bowser.h"
#include "element.h"

using namespace std;
namespace Ui {
class GameForm;
}

/**
@class GameForm
@brief Represents the game interface.
The GameForm class represents the game interface where the game is played.
It handles various game functionalities such as character movement, collisions, level loading, etc.
*/
class GameForm : public QWidget
{
    Q_OBJECT

public:
    /**
      * @brief Constructs a GameForm object.
      * @param parent The parent QWidget object.
     */
    explicit GameForm(QWidget *parent = 0);
    /**
      * @brief Destructs the GameForm object.
     */
    ~GameForm();
    /**
     * @brief Checks for character collisions.
     */
    void checkCharacterCollision();
    /**
     * @brief Checks for collisions with Bowser.
     */
    void checkBowserCollision();
    /**
      * @brief Checks for collisions with fireballs.
     */
    void checkCollisionFireBalls();
    /**
      * @brief Paints the player's helps.
      * @param painter A pointer to the QPainter object.
     */
    void paintPlayerHelps(QPainter *painter);
    /**
      * @brief Updates the scrolling of the game.
     */
    void updateScroll();
    /**
      * @brief Updates the fireballs in the game.
     */
    void updateFireBalls();
    /**
      * @brief Loads a specific level.
      * @param levelNumber The number of the level to load.
     */
    void loadLevel(int levelNumber);
    /**
      * @brief Plays the main music of the game.
     */
    void playMainMusic();
    /**
      * @brief Plays the jump sound effect.
     */
    void playJumpSound();
    /**
      * @brief Stops the main music of the game.
     */
    void stopMainMusic();
    /**
      * @brief Returns the QScrollArea object used in the game.
      * @return The QScrollArea object.
     */
    QScrollArea* getScrollArea() const;

public slots:
    /**
      * @brief The game loop that updates the game state.
     */
    void gameloop();
    /**
      * @brief Starts the game.
     */
    void start();

signals:
    /**
      * @brief Signal emitted when the quit button is clicked.
    */
    void quitButtonClicked();

private:
    int elapsedTime; /**< The elapsed time in the game. */
    int backgroundY; /**< The y-coordinate of the background. */
    QSoundEffect *mainsound; /**< The main sound effect. */
    Ui::GameForm *ui; /**< The user interface for the game form. */
    bool isGameEnded; /**< Flag indicating if the game has ended. */
    QTimer *itsTimer; /**< The timer for the game loop. */
    Mario *itsCharacter; /**< The player character. */
    Bowser *itsBoss; /**< The boss character. */
    Element *itsFloor; /**< The floor element. */
    Element *itsChest; /**< The chest element. */
    QScrollArea *itsScrollArea; /**< The scroll area for the game. */
    QImage itsBackground; /**< The background image. */
    QImage leftArrow; /**< The left arrow image for player help. */
    QImage rightArrow; /**< The right arrow image for player help. */
    QImage chestArrow; /**< The chest arrow image for player help. */
    QImage spaceBar; /**< The space bar image for player help. */
    list<Element*> itsBlocks; /**< The list of blocks in the game. */
    /**
      * @brief Handles the key press event.
      * @param event The QKeyEvent object.
     */
    void keyPressEvent(QKeyEvent *event);
    /**
      * @brief Handles the key release event.
      * @param event The QKeyEvent object.
    */
    void keyReleaseEvent(QKeyEvent *event);
    /**
      * @brief Handles the paint event.
      * @param event The QPaintEvent object.
     */
    void paintEvent(QPaintEvent *event);
};

#endif // GAMEFORM_H
