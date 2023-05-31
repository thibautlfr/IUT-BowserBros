#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QWidget>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QScrollBar>
#include <list>

#include "character.h"
#include "block.h"

using namespace std;

namespace Ui {
class GameForm;
}

class GameForm : public QWidget
{
    Q_OBJECT

public:
    explicit GameForm(QWidget *parent = nullptr);
    ~GameForm();

public slots:
    void gameloop();
    void start();

private:
    Ui::GameForm *ui;
    QTimer *itsTimer;
    Character * itsCharacter;
    QRect * itsFloor;

    list<Block*> itsBlocks;

    void keyPressEvent (QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

    QRect viewport;
};
#endif // WIDGET_H
