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

#include "mario.h"
#include "bowser.h"
#include "element.h"

using namespace std;

namespace Ui {
class GameForm;
}

class GameForm : public QWidget
{
    Q_OBJECT

public:
    explicit GameForm(QWidget *parent = 0);
    ~GameForm();

    void checkCharacterCollision();
    void checkBowserCollision();
    void checkCollisionFireBalls();

    void updateScroll();
    void updateFireBalls();
    void loadLevel(int levelNumber);



    QScrollArea* getScrollArea() const;

public slots:
    void gameloop();
    void start();

private:

    int elapsedTime;
    int backgroundY;

    Ui::GameForm *ui;
    QTimer *itsTimer;
    Mario * itsCharacter;
    Bowser * itsBoss;
    Element * itsFloor;
    Element * itsChest;
    QScrollArea *itsScrollArea;
    QImage itsBackground;

    list<Element*> itsBlocks;

    void keyPressEvent (QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);



};
#endif // WIDGET_H
