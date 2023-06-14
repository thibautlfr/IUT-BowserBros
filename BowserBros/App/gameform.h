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
#include <QLabel>
#include <list>
#include <vector>

#include "soundmanager.h"
#include "mario.h"
#include "bowser.h"
#include "goomba.h"
#include "koopa.h"
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

    // --------------------------------------------------------------------------------------------

    /**
     * @brief Getter for itsScrollArea
     * @return The scroll area element of the GameForm
     */
    QScrollArea* getScrollArea() const;

    // --------------------------------------------------------------------------------------------

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
<<<<<<< HEAD
     * @brief Check for the goombas collisions
     */
    void checkGoombasCollision();

    /**
     * @brief Checks for the koopas collisions
     */
    void checkKoopasCollision();

    /**
     * @brief Checks the collisions between the floor and an entity
     * @param anEntity : the entity we want to verify
     */
    void checkFloorCollision(Entity * anEntity);

    // ----------------------------------------------------------------------------------------------

    /**
     * @brief Checks the collisions between an entity and the blocks near theme
     * @param anEntity : the entity we want to verify
     * @param nearlyBlocks : the blocks near the entity
     */
    void checkPlatformCollision(Entity * anEntity, vector<Element*> nearlyBlocks);

    /**
     * @brief Checks if an entity is on a block and the collisions associated
     * @param anEntity : the entity we want to verify
     * @param nearlyBlocks : the blocks near the entity
     * @return true if the entity is on a block and false either
     */
    bool checkEntityOnBlocks(Entity * anEntity, vector<Element*> nearlyBlocks);

    /**
     * @brief Checks if an entity is on the floor and the collisions associated
     * @param anEntity : the entity we want to verify
     * @param nearlyBlocks : the blocks near the entity
     * @return true if the entity is on the floor and false either
     */
    bool checkEntityOnFloor(Entity * anEntity, vector<Element*> nearlyBlocks);

    /**
     * @brief Gets the blocks near an entity
     * @param anEntity : the entity we want to check
     * @return
     */
    vector<Element*> getNearlyBlocks(Entity * anEntity);

    /**
     * @brief Checks for collisions with ladders.
     */
    void checkLadderCollision();

    // --------------------------------------------------------------------------------------------

    /**
      * @brief Paints the player's helps.
      * @param painter A pointer to the QPainter object.
     */
    void paintPlayerHelps(QPainter *painter);

    /**
      * @brief Updates the position of the scroll area in the game.
     */
    void updateScroll();

    /**
      * @brief Updates the position of fireballs in the game.
     */
    void updateFireBalls();

    /**
      * @brief Loads a specific level.
     */
    void loadLevel();

    /**
     * @brief Displays the chrono at the top right corner
     */
    void displayChrono();

    SoundManager* getSoundManager() const;

    void setVolume(SoundManager *menuSoundManager);

    void setIsOnGamed(bool newIsOnGamed);

public slots:
    /**
      * @brief The game loop that updates the game state.
     */
    void gameloop();
    /**
      * @brief Starts the game.
     */
    void start();

    /**
     * @brief Animations of mario's death
     */
    void animationDeath();

signals:
    /**
      * @brief Signal emitted when the game is losed.
    */
    void gameLosed();

    /**
      * @brief Signal emitted when the game is won.
      * @param The integer of the timer of the game loop
    */
    void gameWon(int elapsedTime);

    /**
      * @brief Signal emitted when the game is paused.
    */
    void gamePaused();


private:

    Ui::GameForm *ui; /**< The user interface for the game form. */
    int itsLevel; /**< The current number level in the game. */
    int itsAvalaibleLevelsNb; /**< The amount of avalaible numbers in the game */
    int elapsedTime; /**< The elapsed time in the game. */
    int backgroundY; /**< The y-coordinate of the background. */
    bool isGameEnded; /**< Flag indicating if the game has ended. */
    QLabel *timeLabel; /**< Text indicating the time spent since the start of the game */
    QLabel* levelLabel; /**< Text indicating the current level */

    // --------------------------------------------------------------------------------------------

    Mario *itsCharacter; /**< The player character. */
    Bowser *itsBoss; /**< The boss character. */
    vector<Goomba*> itsGoombas;
    vector<Koopa*> itsKoopas;
    Element *itsFloor; /**< The floor element. */
    Element *itsChest; /**< The chest element. */

    // --------------------------------------------------------------------------------------------

    QImage itsBackground; /**< The background image. */
    QImage leftArrow; /**< The left arrow image for player help. */
    QImage rightArrow; /**< The right arrow image for player help. */
    QImage chestArrow; /**< The chest arrow image for player help. */
    QImage spaceBar; /**< The space bar image for player help. */

    // --------------------------------------------------------------------------------------------


    QScrollArea *itsScrollArea; /**< The scroll area for the game. */
    QTimer *itsTimer; /**< The timer for the game loop. */

    QTimer * marioTimer; /**< The timer for the mario animation death */
    list<Element*> itsBlocks; /**< The list of blocks in the game. */
    list<Element*> itsLadders; /**< The list of ladders in the game. */

    SoundManager *soundManager; /**< Attribute used to mange sounds during the game */
    float itsVolumesGen;
    float itsVolumesEffect;

    bool isOnGamed ;

    // --------------------------------------------------------------------------------------------

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
