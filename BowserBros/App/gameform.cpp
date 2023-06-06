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

    elapsedTime = 0;

    itsBackground.load(":Assets/Assets/background/background6.png");
    rightArrow.load(":Assets/Assets/other/rightarrow.png");
    leftArrow.load(":Assets/Assets/other/leftarrow.png");
    spaceBar.load(":Assets/Assets/other/spacebar.png");
    chestArrow.load(":Assets/Assets/other/chest-arrow.png");
    backgroundY = height() - itsBackground.height();

    itsScrollArea = new QScrollArea;
    itsScrollArea->setWidget(this);
    itsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    itsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // désactiver la barre de défilement

    loadLevel(1);

    qDebug() << this->height();

    itsFloor = new Element(0, height() - 20, ":Assets/Assets/other/floor.png");
    itsCharacter = new Mario(50, height() - 100, ":Assets/Assets/mario/mario4.png");
    itsBoss = new Bowser(30, height()-570, 41, 59, ":Assets/Assets/bowser/bowserright.png");

    itsBoss->dropFireBall();

    itsTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(gameloop()));
    start();
}

GameForm::~GameForm()
{
    delete itsCharacter;
    delete itsBoss;
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
            if (coords.size() == 3) {
                int x = coords[0].toInt();
                int y = coords[1].toInt();
                int type = coords[2].toInt();
                qDebug() << "Bloc créé en " << x << " ; " << y ;

                switch (ElementType(type)) {
                case BREAKABLE1:
                    itsBlocks.push_back(new Element(x, height() - y, ":Assets/Assets/block/block1.jpg"));
                    break;
                case BREAKABLE2:
                    itsBlocks.push_back(new Element(x, height() - y, ":Assets/Assets/block/block5.jpg"));
                    break;
                case UNBREAKABLE:
                    itsBlocks.push_back(new Element(x, height() - y, ":Assets/Assets/block/block6.jpg"));
                    break;
                case LUCKYBLOCK1:
                    itsBlocks.push_back(new Element(x, height() - y, ":Assets/Assets/block/block3.jpg"));
                    break;
                case LUCKYBLOCK2:
                    itsBlocks.push_back(new Element(x, height() - y, ":Assets/Assets/block/block2.jpg"));
                    break;
                case CRACKELED:
                    itsBlocks.push_back(new Element(x, height() - y, ":Assets/Assets/block/block4.jpg"));
                    break;
                case CHEST:
                    itsChest = new Element(x, height() - y, ":Assets/Assets/other/chest.png");
                default:
                    break;
                }
                ;
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
    itsCharacter->setOnPlatform(false);

    // On vérifie que le cube n'est pas sur le sol
    if ((itsFloor->getRect().top() - (itsCharacter->getItsRect().bottom()) == 1) ||
        itsFloor->getRect().top() - (itsCharacter->getItsRect().bottom() + 5) == 1  )
    {
        isOnPlatform = true;
        itsCharacter->setOnPlatform(true);
        if (itsFloor->getRect().top() - (itsCharacter->getItsRect().bottom() + 5) == 1)
        {
            itsCharacter->setItsY(itsCharacter->getItsY() + 5);
        }
    }
    // On vérifie que le cube n'est sur aucunes des plateformes
    for (Element * block : itsBlocks)
    {
        if (
            // Si le rectangle est déjà sur la plateforme
            ((block->getRect().top() - (itsCharacter->getItsRect().bottom()) == 1) ||
             (block->getRect().top() - (itsCharacter->getItsRect().bottom() + 5) == 1)) &&
            // ...ET qu'il n'est PAS PAS sur la plateforme (sur l'axe X)
            !( (itsCharacter->getItsRect().right() < block->getRect().left()) ||
              (itsCharacter->getItsRect().left() > block->getRect().right()) )
            )
        {
            isOnPlatform = true;
            itsCharacter->setOnPlatform(true);
            if (block->getRect().top() - (itsCharacter->getItsRect().bottom() + 5) == 1)
            {
                itsCharacter->setItsY(itsCharacter->getItsY() + 5);
            }
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
                    itsCharacter->setOnPlatform(true);
                }
            }
        }

        // Gérer les collision avec le sol
        if (itsCharacter->getItsRect().intersects(itsFloor->getRect()))
        {
            itsCharacter->setYSpeed(0);
            itsCharacter->setItsY(itsFloor->getRect().top() - itsCharacter->getItsRect().height());
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

    //Vérifier que le character n'atteint pas la bordure du jeu
    if(itsCharacter->getItsRect().left() <= 0)
    {
        itsCharacter->setItsX(1) ;
    }
    else if(itsCharacter->getItsRect().right() >= 800)
    {
        itsCharacter->setItsX(800 - itsCharacter->getItsRect().width()) ;
    }

    // Vérification de collision avec le coffre pour fin du jeu
    if (itsCharacter->getItsRect().intersects(itsChest->getRect()))
    {
        // Arrêtez le jeu et revenez au menu
        itsTimer->stop();
        emit quitButtonClicked();
    }

    itsCharacter->calculatePosition();
    itsCharacter->updateAsset(elapsedTime);

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
    itsBoss->getItsX() < itsCharacter->getItsX() ? itsBoss->setItsImage(":Assets/Assets/bowser/bowserright.png") : itsBoss->setItsImage(":Assets/Assets/bowser/bowserleft.png");
}

void GameForm::updateScroll() {
    int characterY = itsCharacter->getItsY();
    //qDebug() << characterY;

    // Si le personnage est dans la partie inférieure de la fenêtre
    if (characterY > height() - 300) {
        itsScrollArea->verticalScrollBar()->setValue(height() - 600);
        itsBoss->setItsY(height() - 570);
        backgroundY = height() - itsBackground.height();  // fixe l'arrière plan
    }
    // Sinon, si le personnage est dans la partie superieur de la fenêtre
    else {
        // Assurez-vous que le personnage reste au milieu de la fenêtre
        itsScrollArea->verticalScrollBar()->setValue(characterY - 300);
        characterY - 270 > 30 ? itsBoss->setItsY(characterY - 270): itsBoss->setItsY(30);
        if (characterY - 300 > 0 && characterY + 300 < height() - 20)
        {
            backgroundY = 0.5 * characterY - (600*0.5*0.5);  // déplace l'arrière-plan vers le haut
        }
    }

    itsBoss->calculatePosition();
}

void GameForm::updateFireBalls()
{
    for (FireBall * fireball : *itsBoss->getItsFireBalls())
    {
        fireball->calculatePosition();
    }

    if(elapsedTime % 1000 == 0)
    {
        itsBoss->dropFireBall();
    }
}


void GameForm::checkCollisionFireBalls()
{
    vector<FireBall *> *fireBalls = itsBoss->getItsFireBalls();

    for (FireBall *fireBall : *fireBalls)
    {
        if (fireBall->getItsRect().intersects(itsCharacter->getItsRect()))
        {
            // Arrêtez le jeu et revenez au menu
            itsTimer->stop();
            emit quitButtonClicked();
            break; // Sortir de la boucle car une boule de feu a touché Mario
        }
    }

    for (vector<FireBall *>::iterator it = fireBalls->begin(); it != fireBalls->end();)
    {
        bool isCollision = false;

        // Vérifier les collisions avec les blocs
        for (Element *block : itsBlocks)
        {
            if ((*it)->getItsRect().intersects(block->getRect()))
            {
                isCollision = true;
                break;
            }
        }

        // Vérifier les collisions avec le sol
        if ((*it)->getItsRect().intersects(itsFloor->getRect()))
        {
            isCollision = true;
        }

        // Vérifier les collisions avec le personnage (Mario)
        if ((*it)->getItsRect().intersects(itsCharacter->getItsRect()))
        {
            isCollision = true;
        }

        if (isCollision)
        {
            delete *it;  // Supprime la boule de feu de la mémoire
            it = fireBalls->erase(it);  // Supprime l'élément de la liste
        }
        else
        {
            ++it;
        }
    }
}


// ---------------------------------------------------------------------------------------------------------

void GameForm::gameloop()
{
    elapsedTime += 10;
    checkCharacterCollision();
    checkBowserCollision();
    checkCollisionFireBalls();
    updateScroll();
    updateFireBalls();
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

// ---------------------------------------------------------------------------------------------------------

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

    painter->drawImage(0, backgroundY, itsBackground);

    painter->setPen(Qt::green);
    painter->setBrush(Qt::SolidPattern);
    itsFloor->draw(painter);

    for (Element * block : itsBlocks)
    {
        block->draw(painter);        
    }

    for (FireBall * fireball : *itsBoss->getItsFireBalls())
    {
        fireball->draw(painter);
    }

    itsChest->draw(painter);

    // Afficher les aides au joueur
    paintPlayerHelps(painter);

    itsCharacter->draw(painter);
    itsBoss->draw(painter);

    delete painter;
}

void GameForm::paintPlayerHelps(QPainter * painter)
{
    if(itsCharacter->getItsY() > height() - 300)
    {
        painter->drawImage(600, height()-65, leftArrow);
        painter->drawImage(650, height()-65, spaceBar);
        painter->drawImage(750, height()-65, rightArrow);
        painter->drawImage(itsChest->getRect().x(), height()-600, chestArrow);
    }
    else if(itsCharacter->getItsY() - 300 < 0)
    {
        painter->drawImage(600, 535, leftArrow);
        painter->drawImage(650, 535, spaceBar);
        painter->drawImage(750, 535, rightArrow);
    }
    else
    {
        painter->drawImage(600, itsCharacter->getItsY()+235, leftArrow);
        painter->drawImage(650, itsCharacter->getItsY()+235, spaceBar);
        painter->drawImage(750, itsCharacter->getItsY()+235, rightArrow);
        if(itsCharacter->getItsY()-300 > itsChest->getRect().y())
        {
            painter->drawImage(itsChest->getRect().x(), itsCharacter->getItsY()-300, chestArrow);
        }
    }
}
