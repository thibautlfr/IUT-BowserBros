#include "widget.h"
#include "ui_widget.h"
#include <iostream>

#include <QDebug>

const float GRAVITY = 0.25;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    itsFloor = new QRect(0, this->height(), this->width(), 100);
    itsCharacter = new Character;

    // Première plateforme
    itsBlocks.push_back(new Block(100, 450));
    itsBlocks.push_back(new Block(120, 450));
    itsBlocks.push_back(new Block(140, 450));
    itsBlocks.push_back(new Block(160, 450));

    itsBlocks.push_back(new Block(300, 350));
    itsBlocks.push_back(new Block(320, 350));
    itsBlocks.push_back(new Block(340, 350));
    itsBlocks.push_back(new Block(360, 350));
    itsBlocks.push_back(new Block(360, 330));
    itsBlocks.push_back(new Block(380, 330));
    itsBlocks.push_back(new Block(400, 330));
    itsBlocks.push_back(new Block(420, 330));

    itsBlocks.push_back(new Block(120, 220));
    itsBlocks.push_back(new Block(140, 220));
    itsBlocks.push_back(new Block(160, 220));
    itsBlocks.push_back(new Block(180, 220));


    itsBlocks.push_back(new Block(540, 220));
    itsBlocks.push_back(new Block(560, 220));
    itsBlocks.push_back(new Block(580, 220));
    itsBlocks.push_back(new Block(600, 220));



    itsTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(gameloop()));
    start();
}

Widget::~Widget()
{
    delete itsCharacter;
    delete itsTimer;
    delete ui;
}

void Widget::gameloop()
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
    for (std::list<Block*>::iterator it = itsBlocks.begin(); it != itsBlocks.end(); ++it)
    {
        //qDebug() << (*it)->getRect().top() - itsCharacter->getItsRect().bottom();
        if (
            // Si le rectangle est déja sur la plateforme
            ((*it)->getRect().top() - itsCharacter->getItsRect().bottom() == 1) &&
            // ...ET qu'il n'est PAS PAS sur la plateforme (sur l'axe X)
            !( (itsCharacter->getItsRect().right() < (*it)->getRect().left()) ||
              (itsCharacter->getItsRect().left() > (*it)->getRect().right()) )
            )
        {
            isOnPlatform = true;
        }
    }

    // Si il est ni sur le sol ni sur une plateforme alors il est soit en train de rentrer dans quelque chose ou soit dans les airs
    if (isOnPlatform == false)
    {
        // Gérer les collisions avec les plateformes
        for (std::list<Block*>::iterator it = itsBlocks.begin(); it != itsBlocks.end(); ++it)
        {
            // Récupérer les rectangles du personnage et de la plateforme
            QRect platformRect = (*it)->getRect();

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
                    itsCharacter->setItsY(platformRect.top()-50);
                    itsCharacter->setYSpeed(0);
                    isOnPlatform = true;
                }
            }
        }

        // Gérer les collision avec le sol
        if (itsCharacter->intersect(*itsFloor))
        {
            itsCharacter->setYSpeed(0);
            itsCharacter->setItsY(this->height() - 50);
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

            else if(itsCharacter->getYSpeed()==0 && itsCharacter->getItsY() != (this->height() - 51) && !isOnPlatform)
            {
                itsCharacter->setYSpeed(itsCharacter->getYSpeed() + GRAVITY);
            }
        }
    }

    itsCharacter->calculatePosition();

    repaint();
}


void Widget::start()
{
    if(itsTimer->isActive())
    {
        itsTimer->stop();
    }
    else
    {
        itsTimer->start(10);
    }
}

void Widget::keyPressEvent (QKeyEvent * event)
{
    if (event->key() == Qt::Key_Left)
    {
        itsCharacter->setXSpeed(-2);
    }
    else if(event->key() == Qt::Key_Right)
    {
        itsCharacter->setXSpeed(2);
    }

    if(event->key() == Qt::Key_Space && itsCharacter->getYSpeed() == 0 )
    {
        itsCharacter->jump();
    }
}

void Widget::keyReleaseEvent (QKeyEvent * event)
{
    if ((event->key() == Qt::Key_Left) || event->key() == Qt::Key_Right)
    {
        itsCharacter->setXSpeed(0);
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter * painter = new QPainter(this);

    itsCharacter->draw(painter);

    for (std::list<Block*>::iterator it = itsBlocks.begin(); it != itsBlocks.end(); ++it)
    {
        (*it)->draw(painter);
    }

    delete painter;
}
