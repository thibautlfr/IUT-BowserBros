#include "gameform.h"
#include "ui_gameform.h"

#include <iostream>
#include <QDebug>
#include <QFile>
#include <string>
#include <thread>
#include <chrono>
#include <QDir>
#include <QFontDatabase>

using namespace std;

const float GRAVITY = 0.25;

GameForm::GameForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameForm)
{
    ui->setupUi(this);

    // Fixe la taille du widget
    setFixedSize(800, 1200);

    // Initialisation du temps écoulé depuis le début de la patie
    elapsedTime = 0;

    // Création du gestionnaire de son
    sound = new SoundController;

    //=============================================================

    // Charger la police depuis le fichier
    QString fontPath = ":Fonts/Fonts/policeMario2.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily, 22);

    // Créer une étiquette pour afficher le temps écoulé
    timeLabel = new QLabel(this);
    timeLabel->setStyleSheet("font-size: 21px; color: white");
    timeLabel->setFont(font);
    timeLabel->setAlignment(Qt::AlignLeft);
    timeLabel->setGeometry(30, 800, 200, 300);

    // Créer une étiquette pour afficher le temps écoulé
    levelLabel = new QLabel(this);
    levelLabel->setStyleSheet("font-size: 21px; color: white");
    levelLabel->setFont(font);
    levelLabel->setAlignment(Qt::AlignLeft);
    levelLabel->setGeometry(30, 830, 200, 300);

    //====================================================================

    // Chargement des assets d'aide au joueur
    rightArrow.load(":Assets/Assets/other/rightarrow.png");
    leftArrow.load(":Assets/Assets/other/leftarrow.png");
    spaceBar.load(":Assets/Assets/other/spacebar.png");
    chestArrow.load(":Assets/Assets/other/chest-arrow.png");

    // Initialise le Y du background
    backgroundY = height() - itsBackground.height();

    // Création de la "caméra"
    itsScrollArea = new QScrollArea;
    itsScrollArea->setWidget(this);
    itsScrollArea->setFocusPolicy(Qt::NoFocus);
    itsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    itsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // désactiver la barre de défilement

    //====================================================================

    // Chargement du premier niveau
    itsLevel = 1;
    itsAvalaibleLevelsNb = QDir(":Levels/Levels").entryInfoList().count();
    loadLevel(itsLevel);

    // Création du sol, du personnage et du boss
    itsFloor = new Element(0, height() - 20, ":Assets/Assets/other/floor.png");
    itsCharacter = new Mario(50, height() - 100, ":Assets/Assets/mario/mario4.png");
    itsBoss = new Bowser(width()-80, height()-570, 41, 59, ":Assets/Assets/bowser/bowserright.png");

    //====================================================================

    // Création et lancement du timer
    itsTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(gameloop()));
    start();
}


GameForm::~GameForm()
{
    delete itsCharacter;
    delete itsBoss;
    delete sound;
    delete levelLabel;
    delete timeLabel;
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
    if(levelNumber > 1)
    {
        itsCharacter->setItsX(50);
        itsCharacter->setItsY(height() - 100);
        itsBlocks.clear();
    }
    QString filename = ":Levels/Levels/level" + QString::number(levelNumber) + ".txt";
    QString backgroundName = ":Assets/Assets/background/background" + QString::number(levelNumber) + ".png";
    itsBackground.load(backgroundName);
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
                    break;
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
        if (itsLevel > 1)
        {
            start();
        }
    }
    else
    {
        qDebug() << "Impossible d'ouvrir le fichier du niveau!";
        sound->StopMainSound();
        itsTimer->stop();
        itsLevel = 1;
        loadLevel(itsLevel);
        emit quitButtonClicked();
        return;
    }
    // Mettre à jour le label du niveau
    levelLabel->setText(QString("world %1").arg(itsLevel));

}

// ---------------------------------------------------------------------------------------------------------

// Gère les collisions entre le personnage et les éléments du jeu
void GameForm::checkCharacterCollision()
{

    // Maximum distance for the blocks concerned
    const int DISTANCE_THRESHOLD = 25;

    // Vector with blocs near to Mario
    vector<Element*> nearlyBlocks;

    for (Element * block : itsBlocks)
    {
        int distanceX = abs(itsCharacter->getItsRect().center().x() - block->getRect().center().x());

        // Add only the block near to the player
        if (distanceX < DISTANCE_THRESHOLD)
        {
            nearlyBlocks.push_back(block);

        }
    }

    itsCharacter->setOnPlatform(false);

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
        sound->StopMainSound();
        if (itsLevel == itsAvalaibleLevelsNb)
        {
            sound->WinSound();
        }
        this_thread::sleep_for(chrono::milliseconds(300));
        itsTimer->stop();
        itsLevel ++;
        loadLevel(itsLevel);
        return;
    }

    // On vérifie que le cube n'est pas sur le sol
    if ((itsFloor->getRect().top() - (itsCharacter->getItsRect().bottom()) == 1) ||
        itsFloor->getRect().top() - (itsCharacter->getItsRect().bottom() + 5) == 1  )
    {
        for (Element * block : nearlyBlocks)
        {
            // Récupérer les rectangles du personnage et de la plateforme
            QRect platformRect = block->getRect();

            if(itsCharacter->intersect(platformRect))
            {
                // Si il arrive de la droite
                if(itsCharacter->getXSpeed() < 0 and itsCharacter->getItsRect().left() - platformRect.left() > 0)
                {
                    itsCharacter->setItsX(platformRect.right()+1);
                }
                else if(itsCharacter->getXSpeed() > 0 and itsCharacter->getItsRect().right() - platformRect.right() < 0)
                {
                    itsCharacter->setItsX(platformRect.left()-itsCharacter->getItsRect().width());
                }
            }
        }
        //isOnPlatform = true;
        itsCharacter->setOnPlatform(true);
        if (itsFloor->getRect().top() - (itsCharacter->getItsRect().bottom() + 5) == 1)
        {
            itsCharacter->setItsY(itsCharacter->getItsY() + 5);
        }
        itsCharacter->calculatePosition();
        itsCharacter->updateAsset(elapsedTime);
        return;
    }
    // On vérifie que le cube n'est sur aucunes des plateformes
    for (Element * block : nearlyBlocks)
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
            for (Element * otherBlock : nearlyBlocks)
            {
                // Récupérer les rectangles de la plateforme
                QRect platformRect = otherBlock->getRect();

                if(itsCharacter->intersect(platformRect))
                {
                    // Si il arrive de la droite
                    if(itsCharacter->getXSpeed() < 0 and itsCharacter->getItsRect().left() - platformRect.left() > 0)
                    {
                        itsCharacter->setItsX(platformRect.right()+1);
                    }
                    else if(itsCharacter->getXSpeed() > 0 and itsCharacter->getItsRect().right() - platformRect.right() < 0)
                    {
                        itsCharacter->setItsX(platformRect.left()-itsCharacter->getItsRect().width());
                    }
                }
            }
            itsCharacter->setOnPlatform(true);
            if (block->getRect().top() - (itsCharacter->getItsRect().bottom() + 5) == 1)
            {
                itsCharacter->setItsY(itsCharacter->getItsY() + 5);
            }
            itsCharacter->calculatePosition();
            itsCharacter->updateAsset(elapsedTime);
            return;
        }
    }

    // Si il est ni sur le sol ni sur une plateforme alors il est soit en train de rentrer dans quelque chose ou soit dans les airs
    if (itsCharacter->getOnPlatform() == false)
    {
        // Gérer les collisions avec les plateformes
        for (Element * block : nearlyBlocks)
        {
            // Récupérer les rectangles du personnage et de la plateforme
            QRect platformRect = block->getRect();

            // Si le personnage touche une plateforme
            if(itsCharacter->intersect(platformRect))
            {

                // Si le joueur arrive de la droite
                if((itsCharacter->getItsRect().left() - platformRect.right() <= 0 and itsCharacter->getItsRect().left() - platformRect.right() >=-1) )
                {
                    itsCharacter->setItsX(itsCharacter->getItsX()+1);
                    itsCharacter->setXSpeed(0);
                    //collisionRight = true;

                }
                // Si le joueur arrive de la gauche
                else if (itsCharacter->getItsRect().right() - platformRect.left() >= 0 and itsCharacter->getItsRect().right() - platformRect.left() <=1)
                {
                    itsCharacter->setItsX(itsCharacter->getItsX()-1);
                    itsCharacter->setXSpeed(0);
                    //collisionLeft = true;

                }
                // Si il arrive d'en bas
                else if(itsCharacter->getYSpeed() < 0)
                {
                    itsCharacter->setItsY(platformRect.bottom()+1);
                    itsCharacter->reverseYSpeed();
                }

                // Si il arrive d'en haut
                else if ( (itsCharacter->getYSpeed() >= 0) && ( platformRect.top() - itsCharacter->getItsY() >= 0) )
                {
                    itsCharacter->setItsY(platformRect.top() - itsCharacter->getItsRect().height());
                    itsCharacter->setYSpeed(0);
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

            else if(itsCharacter->getYSpeed()==0 && itsCharacter->getItsY() != (this->height() - (itsCharacter->getItsRect().height() + 1)) && !itsCharacter->getOnPlatform())
            {
                itsCharacter->setYSpeed(itsCharacter->getYSpeed() + GRAVITY);
            }
        }
    }

    itsCharacter->calculatePosition();
    itsCharacter->updateAsset(elapsedTime);

}

void GameForm::checkBowserCollision()
{
    // Vitesse minimum et maximum pour Bowser
    float minSpeed = -0.5;
    float maxSpeed = 0.5;

    // Change la vitesse de Bowser en fonction du X de Mario
    if (itsBoss->getItsX() > itsCharacter->getItsX() && itsBoss->getXSpeed() > minSpeed) // Si Bowser est à droite
    {
        itsBoss->setXSpeed(itsBoss->getXSpeed() - 0.005);
        itsBoss->setItsImage(":Assets/Assets/bowser/bowserleft.png");
    }
    else if (itsBoss->getItsX() < itsCharacter->getItsX() && itsBoss->getXSpeed() < maxSpeed) // Si il est à gauche
    {
        itsBoss->setXSpeed(itsBoss->getXSpeed() + 0.005);
        itsBoss->setItsImage(":Assets/Assets/bowser/bowserright.png");
    }

    // Collision avec les "bords invisibles"
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

    // Mise à jour de la position de Bowser
    itsBoss->calculatePosition();
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

    double coefficient = (1 - (0.1 * (itsLevel - 1))); // Accélérer la fréquence en fonction du niveau
    if(elapsedTime % int(1000 * coefficient) == 0)
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
            sound->StopMainSound();
            sound->GameoverSound();
            this_thread::sleep_for(chrono::milliseconds(300));
            itsTimer->stop();
            itsLevel = 1;
            //loadLevel(itsLevel);
            emit quitButtonClicked();
            return; // Sortir de la boucle car une boule de feu a touché Mario
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

        // Vérifier les collisions avec le coffre
        if ((*it)->getItsRect().intersects(itsChest->getRect()))
        {
            isCollision = true;
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
    displayChrono();
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
        sound->MainSound();
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
        sound->JumpSound();
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

void GameForm::paintPlayerHelps(QPainter* painter)
{
    if (itsCharacter->getItsY() > height() - 300)
    {
        painter->drawImage(600, height() - 65, leftArrow);
        painter->drawImage(650, height() - 65, spaceBar);
        painter->drawImage(750, height() - 65, rightArrow);
        painter->drawImage(itsChest->getRect().x(), height() - 600, chestArrow);
    }
    else if (itsCharacter->getItsY() - 300 < 0)
    {
        painter->drawImage(600, 535, leftArrow);
        painter->drawImage(650, 535, spaceBar);
        painter->drawImage(750, 535, rightArrow);
    }
    else
    {
        painter->drawImage(600, itsCharacter->getItsY() + 235, leftArrow);
        painter->drawImage(650, itsCharacter->getItsY() + 235, spaceBar);
        painter->drawImage(750, itsCharacter->getItsY() + 235, rightArrow);
        if (itsCharacter->getItsY() - 300 > itsChest->getRect().y())
        {
            painter->drawImage(itsChest->getRect().x(), itsCharacter->getItsY() - 300, chestArrow);
        }
    }
    // Position du chrono
    int timerX = width() - 80; // Position en X du timeLabel (à droite de l'écran)
    int timerY = itsBoss->getItsY()-20; // Position en Y du timeLabel ajustée en fonction de la position de itsBoss
    timeLabel->move(timerX, timerY); // Déplacer le timeLabel à la position calculée

    // Position du nom du niveau
    int levelx = 10;
    int levely = itsBoss->getItsY()-20;
    levelLabel->move(levelx, levely); // Déplacer le timeLabel à la position calculée
}

void GameForm::displayChrono()
{
    // Mettre à jour l'affichage du temps écoulé
    int seconds = elapsedTime / 1000;
    int milliseconds = elapsedTime % 1000;
    QString timeString = QString("time\n%1.%2").arg(seconds).arg(milliseconds / 100, 1, 10, QChar('0'));
    timeLabel->setText(timeString);
}







