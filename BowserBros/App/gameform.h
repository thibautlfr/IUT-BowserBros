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
    void updateScroll();
    void loadLevel(int levelNumber);

    QScrollArea* getScrollArea() const;

public slots:
    void gameloop();
    void start();

private:
    Ui::GameForm *ui;
    QTimer *itsTimer;
    Mario * itsCharacter;
    QRect * itsFloor;
    QScrollArea *itsScrollArea;

    list<Element*> itsBlocks;

    void keyPressEvent (QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

};
#endif // WIDGET_H
