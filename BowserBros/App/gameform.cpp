#include "gameform.h"
#include "ui_gameform.h"

#include <iostream>
#include <QDebug>
#include <QFile>
#include <string>

using namespace std;

const float GRAVITY = 0.25;

GameForm::GameForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameForm)
{
    ui->setupUi(this);

    setFixedSize(800, 1200);

    itsScrollArea = new QScrollArea;
    itsScrollArea->setWidget(this);
    itsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    itsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // désactiver la barre de défilement

    loadLevel(1);

    qDebug() << this->height();

    itsFloor = new QRect(0, height() - 20, width()-2, 20);
    itsCharacter = new Mario(50, height() - 100, 20, 45);
    itsBoss = new Bowser(30, height()-570, 41, 59);

    itsTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(gameloop()));
    start();
}

GameForm::~GameForm()
{
    delete itsCharacter;
    delete itsTimer;
    delete ui;
}

// ---------------------------------------------------------------------------------------------------------

QScrollArea* GameForm::getScrollArea() const {
    return itsScrollArea;
}

// ---------------------------------------------------------------------------------------------------------

// Charger un niveau à partir du fichier texte correspondant
void GameForm::loadLevel(int levelNumber) {
    QString filename = ":Levels/Levels/level" + QString::number(levelNumber) + ".txt";
    qDebug() << filename;
    QFile levelFile(filename);
    //QFile levelFile("qrc:///Levels/level1.txt");
    if (levelFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&levelFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList coords = line.split(';');
            if (coords.size() == 2) {
                int x = coords[0].toInt();
                int y = coords[1].toInt();
                qDebug() << "Bloc créé en " << x << " ; " << y << "\n";
                itsBlocks.push_back(new Element(x, height() - y, 20, 20));
            } else {
                qDebug() << "Erreur de lecture du fichier du niveau!";
                break;
            }
        }
        levelFile.close();
    }
    else
    {
        qDebug() << "Impossible d'ouvrir le fichier du niveau!";
    }
}


// ---------------------------------------------------------------------------------------------------------

// Gère les collisions entre le personnage et les éléments du jeu
void GameForm::checkCharacterCollision()
{
    // Vaut true si le cube est sur quelque chose
    bool isOnPlatform = false;

    // On vérifie que le cube n'est pas sur le sol
    //qDebug() << (itsFloor->top() - itsCharacter->getItsRect().bottom());
    if (itsFloor->top() - itsCharacter->getItsRect().bottom() == 1)
    {
        isOnPlatform = true;
    }


    // On vérifie que le cube n'est sur aucunes des plateformes
    for (Element * block : itsBlocks)
    {
        //qDebug() << (*it)->getRect().top() - itsCharacter->getItsRect().bottom();
        if (
            // Si le rectangle est déja sur la plateforme
            (block->getRect().top() - itsCharacter->getItsRect().bottom() == 1) &&
            // ...ET qu'il n'est PAS PAS sur la plateforme (sur l'axe X)
            !( (itsCharacter->getItsRect().right() < block->getRect().left()) ||
              (itsCharacter->getItsRect().left() > block->getRect().right()) )
            )
        {
            isOnPlatform = true;
        }
    }

    // Si il est ni sur le sol ni sur une plateforme alors il est soit en train de rentrer dans quelque chose ou soit dans les airs
    if (isOnPlatform == false)
    {
        // Gérer les collisions avec les plateformes
        for (Element * block : itsBlocks)
        {
            // Récupérer les rectangles du personnage et de la plateforme
            QRect platformRect = block->getRect();

            // Si le personnage touche une plateforme
            if(itsCharacter->intersect(platformRect))
            {
                // Si il arrive d'en bas
                if(itsCharacter->getYSpeed() < 0)
                {
                    itsCharacter->setItsY(platformRect.bottom()+1);
                    itsCharacter->reverseYSpeed();
                }

                // Si il arrive d'en haut
                else if ( (itsCharacter->getYSpeed() >= 0) && ( platformRect.top() - itsCharacter->getItsY() >= 0) )
                {
                    itsCharacter->setItsY(platformRect.top() - itsCharacter->getItsRect().height());
                    itsCharacter->setYSpeed(0);
                    isOnPlatform = true;
                }
            }
        }

        // Gérer les collision avec le sol
        if (itsCharacter->intersect(*itsFloor))
        {
            itsCharacter->setYSpeed(0);
            itsCharacter->setItsY(itsFloor->top() - itsCharacter->getItsRect().height());
        }
        else
        {
            // Si le personnage est en train de sauter, appliquez une force de gravité pour faire redescendre le personnage
            if (itsCharacter->getYSpeed() < 0)
            {
                itsCharacter->setYSpeed(itsCharacter->getYSpeed() + GRAVITY);
                if(itsCharacter->getYSpeed() == 0)
                {
                    itsCharacter->setYSpeed(itsCharacter->getYSpeed() + GRAVITY);
                }
            }
            // Si le personnage est en train de tomber, appliquer une force de gravité pour le faire descendre plus vite
            else if (itsCharacter->getYSpeed() > 0)
            {
                itsCharacter->setYSpeed(itsCharacter->getYSpeed() + GRAVITY);
            }

            else if(itsCharacter->getYSpeed()==0 && itsCharacter->getItsY() != (this->height() - (itsCharacter->getItsRect().height() + 1)) && !isOnPlatform)
            {
                itsCharacter->setYSpeed(itsCharacter->getYSpeed() + GRAVITY);
            }
        }
    }

    itsCharacter->calculatePosition();

}

void GameForm::checkBowserCollision()
{
    if (itsBoss->getItsRect().left() <= 30 && itsBoss->getXSpeed() < 0)
    {
        itsBoss->setItsX(31);
        itsBoss->reverseXSpeed();
    }
    else if (itsBoss->getItsRect().right() >= (width() - 30) && itsBoss->getXSpeed() > 0)
    {
        itsBoss->setItsX(width() - 31 - itsBoss->getItsRect().width());
        itsBoss->reverseXSpeed();
    }
    itsBoss->calculatePosition();
}

void GameForm::updateScroll() {
    int characterY = itsCharacter->getItsY();
    //qDebug() << characterY;

    // Si le personnage est dans la partie inférieure de la fenêtre
    if (characterY > height() - 300) {
        itsScrollArea->verticalScrollBar()->setValue(height() - 600);
        itsBoss->setItsY(height() - 570);
    }
    // Sinon, si le personnage est dans la partie superieur de la fenêtre
    else {
        // Assurez-vous que le personnage reste au milieu de la fenêtre
        itsScrollArea->verticalScrollBar()->setValue(characterY - 300);
        characterY - 270 > 30 ? itsBoss->setItsY(characterY - 270): itsBoss->setItsY(30);
    }

    itsBoss->calculatePosition();
}


void GameForm::gameloop()
{
    checkCharacterCollision();
    checkBowserCollision();
    updateScroll();
    repaint();
}

void GameForm::start()
{
    if(itsTimer->isActive())
    {
        itsTimer->stop();
    }
    else
    {
        qDebug() << "Timer lancé";
                    itsTimer->start(10);
    }
}

void GameForm::keyPressEvent (QKeyEvent * event)
{
    if (event->key() == Qt::Key_Left)
    {
        itsCharacter->setXSpeed(-2);
        qDebug() << "Left Key";
    }
    else if(event->key() == Qt::Key_Right)
    {
        itsCharacter->setXSpeed(2);
        qDebug() << "Right Key";
    }

    if(event->key() == Qt::Key_Space && itsCharacter->getYSpeed() == 0 )
    {
        itsCharacter->jump();
        qDebug() << "Space Key";
    }
}

void GameForm::keyReleaseEvent (QKeyEvent * event)
{
    if ((event->key() == Qt::Key_Left) || event->key() == Qt::Key_Right)
    {
        itsCharacter->setXSpeed(0);
    }
}

void GameForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter * painter = new QPainter(this);

    painter->setPen(Qt::green);
    painter->setBrush(Qt::SolidPattern);
    painter->drawRect(*itsFloor);
    //qDebug() << "REPAINT";

    for (Element * block : itsBlocks)
    {
        block->draw(painter);
    }

    itsCharacter->draw(painter);
    itsBoss->draw(painter);


    delete painter;
}
