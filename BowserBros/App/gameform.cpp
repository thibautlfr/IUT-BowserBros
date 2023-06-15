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
#include <QThread>
#include <QSoundEffect>

using namespace std;

const float GRAVITY = 0.25;

GameForm::GameForm(int level, int availableLevelsNb, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameForm)
{
    ui->setupUi(this);

    // Fixe la taille du widget
    setFixedSize(800, 1200);

    //=============================================================

    // Initialisation du temps écoulé depuis le début de la partie
    elapsedTime = 0;

    // Gestionnaire de son
    soundManager = new SoundManager;

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
    upArrow.load(":Assets/Assets/other/uparrow.png");

    // Initialise le Y du background
    backgroundY = height() - itsBackground.height();

    // Création de la "caméra"
    itsScrollArea = new QScrollArea;
    itsScrollArea->setWidget(this);
    itsScrollArea->setFocusPolicy(Qt::NoFocus);
    itsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    itsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // désactiver la barre de défilement

    //====================================================================

    // Création du sol, du personnage et du boss
    itsFloor = new Element(0, height() - 20, ":Assets/Assets/other/floor.png");
    itsCharacter = new Mario(50, height() - 50, ":Assets/Assets/mario/mario4.png");
    itsBoss = new Bowser(width()-80, height()-570, 41, 59, ":Assets/Assets/bowser/bowserright.png");

    // Chargement du premier niveau
    if (level == 0 && availableLevelsNb == 0)
    {
        itsLevel = 1;
        itsAvalaibleLevelsNb = QDir(":Levels/Levels").entryInfoList().count();
        trainingMode = false;
    }
    else
    {
        itsLevel = level;
        itsAvalaibleLevelsNb = availableLevelsNb;
        trainingMode = true;
    }
    loadLevel();

    //====================================================================

    // Création et lancement du timer
    itsTimer = new QTimer(this);
    marioTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(gameloop()));
    connect(marioTimer, SIGNAL(timeout()), this, SLOT(animationDeath()));
    start();
}


GameForm::~GameForm()
{
    // Suppression du gestionnaire de son
    itsBlocks.clear();
    delete soundManager;
    delete itsCharacter;
    delete itsBoss;
    delete levelLabel;
    delete timeLabel;
    delete itsTimer;
    delete marioTimer;
    delete ui;
}

// ---------------------------------------------------------------------------------------------------------

QScrollArea* GameForm::getScrollArea() const {
    return itsScrollArea;
}

// ---------------------------------------------------------------------------------------------------------

// Charger un niveau à partir du fichier texte correspondant
void GameForm::loadLevel() {

    if(itsLevel > itsAvalaibleLevelsNb)
    {
        return ;
    }

    if(itsLevel > 1 && trainingMode == false)
    {
        soundManager->playMainMusic();
    }

    // Chargement du fichier texte du niveau ainsi que du background
    QString filename = ":Levels/Levels/level" + QString::number(itsLevel) + ".txt";
    QString backgroundName = ":Assets/Assets/background/background" + QString::number(itsLevel) + ".png";
    itsBackground.load(backgroundName);
    qDebug() << filename;
    QFile levelFile(filename);
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
                if(type == CHEST)
                {
                    itsChest = new Element(x, height() - y, CHEST) ;
                }
                else if(type == 11)
                {
                    itsGoombas.push_back(new Goomba(x, height()-y, ":Assets/Assets/ennemis/goombaR1.png"));
                }
                else if(type == 12)
                {
                    itsKoopas.push_back(new Koopa(x, height()-y, ":Assets/Assets/ennemis/koopaR1.png"));
                }
                else if (type == LADDER)
                {
                    itsLadders.push_back(new Element(x, height() - y, ElementType(type)));
                }
                else
                {
                    qDebug() << "Bloc créé en " << x << " ; " << y ;
                    itsBlocks.push_back(new Element(x, height() - y, ElementType(type)));
                }
            } else {
                qDebug() << "Erreur de lecture du fichier du niveau!";
                break;
            }
        }
        levelFile.close();

        // Mettre à jour le label du niveau
        levelLabel->setText(QString("world %1").arg(itsLevel));

    }
    else
    {
        qDebug() << "Impossible d'ouvrir le fichier du niveau!";
        return;
    }

}

// ---------------------------------------------------------------------------------------------------------

// Gère les collisions entre le personnage et les échelles du jeu
void GameForm::checkLadderCollision()
{
    // Distance maximum des échelles considérés comme "proche" de Mario
    const int DISTANCE_THRESHOLD = 25;

    vector<Element*> nearlyLadders;
    bool characterIntersectsLadder = false;

    for (Element* ladder : itsLadders)
    {
        int distanceX = abs(itsCharacter->getItsRect().center().x() - ladder->getRect().center().x());

        if (distanceX < DISTANCE_THRESHOLD)
        {
            nearlyLadders.push_back(ladder);
        }

        if (itsCharacter->intersect(ladder->getRect()))
        {
            characterIntersectsLadder = true;
        }
    }

    if (!characterIntersectsLadder)
    {
        itsCharacter->setOnLadder(false);
        return;
    }


    for(Element* ladder : nearlyLadders)
    {
        if(itsCharacter->getItsRect().center().x()+5 >= ladder->getRect().left() &&
           itsCharacter->getItsRect().center().x()-5 <= ladder->getRect().right() &&
            ladder->getRect().bottom() >= itsCharacter->getItsRect().bottom()
             )
        {
            if(itsCharacter->getYSpeed() > 0 and ladder->getRect().top() - itsCharacter->getItsRect().bottom() >= 0 and ladder->getRect().top() - itsCharacter->getItsRect().bottom() <= 10)
            {
                itsCharacter->setItsY(ladder->getRect().top()-47);
                itsCharacter->setOnLadder(false);
                itsCharacter->setOnPlatform(true);
                itsCharacter->setYSpeed(0);
            }
            else if(ladder->getRect().top() <= itsCharacter->getItsRect().top() - 1 && itsCharacter->getOnPlatform())
            {
                itsCharacter->setOnLadder(true);
                itsCharacter->setOnPlatform(false);
            }
        }
        else
        {
            itsCharacter->setOnLadder(false);
            itsCharacter->setOnPlatform(true);
        }
    }

}

// Gère les collisions entre le personnage et les éléments du jeu
void GameForm::checkCharacterCollision()
{
    //Vérifier que le character n'atteint pas la bordure du jeu
    if(itsCharacter->getItsRect().left() <= 0)
    {
        itsCharacter->setItsX(1) ;
    }
    else if(itsCharacter->getItsRect().right() >= 800)
    {
        itsCharacter->setItsX(800 - itsCharacter->getItsRect().width()) ;
    }

    // On vérifie si le joueur touche le coffre
    if (itsCharacter->getItsRect().intersects(itsChest->getRect()))
    {

        // Arrêtez le jeu et revenez au menu
        if (itsLevel == itsAvalaibleLevelsNb)
        {
            itsCharacter->setItsImage(":/Assets/Assets/mario/mariowin.png");
            itsCharacter->setItsY(itsCharacter->getItsY() - 5); // Déplace vers le haut de 10 pixels
            itsTimer->stop();
            soundManager->playWinMusic();

            QObject::connect(soundManager, &SoundManager::musicFinished, this, [this]() {
                replaceAndDeleteActors();
                emit gameWon(elapsedTime);
            });
        }
        else
        {
            itsCharacter->setItsImage(":/Assets/Assets/mario/mariowin.png");
            itsCharacter->setItsY(itsCharacter->getItsY() - 5); // Déplace vers le haut de 10 pixels
            itsTimer->stop();
            soundManager->playLevelPassedMusic();
            itsLevel ++;

            QObject::connect(soundManager, &SoundManager::musicFinished, this, [this]() {
                itsTimer->start();

                // Replacement des acteurs du jeu
                replaceAndDeleteActors();
                loadLevel();
            });
        }
        return;
    }

    //------------------------------------------------------------------------------------------------------

    // Vector with blocs near to Mario
    vector<Element*> nearlyBlocks = getNearlyBlocks(itsCharacter);

    // On vérifie que le cube n'est pas sur le sol
    itsCharacter->setOnPlatform(false);

    if(checkEntityOnFloor(itsCharacter, nearlyBlocks) )
    {
        itsCharacter->updateAsset(elapsedTime);
        return;
    }

    // On vérifie que le cube n'est sur aucunes des plateformes
    if (!itsCharacter->getOnLadder())
    {
        if(checkEntityOnBlocks(itsCharacter, nearlyBlocks))
        {
            itsCharacter->updateAsset(elapsedTime);
            return;
        }
    }


    // Si il est ni sur le sol ni sur une plateforme alors il est soit en train de rentrer dans quelque chose ou soit dans les airs
    if (itsCharacter->getOnPlatform() == false)
    {
        // Gérer les collisions avec les plateformes
        if (!itsCharacter->getOnLadder())
        {
            checkPlatformCollision(itsCharacter, nearlyBlocks);
        }

        // Gérer les collision avec le sol
        if (!itsCharacter->getOnLadder())
        {
            checkFloorCollision(itsCharacter);
        }

    }

    itsCharacter->calculatePosition();
    itsCharacter->updateAsset(elapsedTime);

}

// Gère les déplacements de Bowser
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

// Gère les collisions des boules de feu
void GameForm::checkCollisionFireBalls()
{
    vector<FireBall *> *fireBalls = itsBoss->getItsFireBalls();

    for (FireBall *fireBall : *fireBalls)
    {
        if (fireBall->getItsRect().intersects(itsCharacter->getItsRect()))
        {
            // Arrêtez le jeu et revenez au menu
            soundManager->playDeathMusic();

            // On regle l'asset et la vitesse de mario
            itsCharacter->setIsDead(true);
            itsCharacter->setXSpeed(0);
            itsCharacter->setItsImage(":/Assets/Assets/mario/mariodead.png");

            // Arret du timer principal
            itsTimer->stop();

            // Désactive le focus pour ne plus controler mario lors de l'animation
            this->setEnabled(false);

            // Lancement de l'animation de mort de mario
            marioTimer->start(10);
            itsCharacter->setYSpeed(-5);

            QObject::connect(soundManager, &SoundManager::musicFinished, this, [this]() {
                replaceAndDeleteActors();
                marioTimer->stop();
                emit gameLosed();
            });

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
                // Vérifier si le bloc est de type 6 (BREAKABLE2) et détruire le bloc
                if (block->getItsType() == CRACKELED)
                {
                    delete block;
                    itsBlocks.erase(remove(itsBlocks.begin(), itsBlocks.end(), block), itsBlocks.end());
                }

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

// Gère les collisions des goomba
void GameForm::checkGoombasCollision()
{
    // Vecteur contenant les goombas dans le champ de vision de mario
    vector<Goomba*> visibleGoombas;

    float characterY = itsCharacter->getItsY();
    for (Goomba * goomba : itsGoombas)
    {
        if (characterY > height()-300 && goomba->getItsY() >= height()-600)
        {
            visibleGoombas.push_back(goomba);
        }
        else if (characterY < height()-300 && characterY > 300 && goomba->getItsY() > characterY-300)
        {
            visibleGoombas.push_back(goomba);
        }
        else if (characterY < 300 && goomba->getItsY() < 600)
        {
            visibleGoombas.push_back(goomba);
        }
    }

    // On parcours chaque goomba du vecteur
    for (Goomba * goomba : visibleGoombas)
    {
        QRect goombaRect = goomba->getItsRect();
        QRect characterRect = itsCharacter->getItsRect();

        // Changement de la vitesse du goomba si il vient d'apparaitre dans le champ de vision du joueur
        if (goomba->getXSpeed() == 0 and !goomba->getIsDead())
        {
            goomba->getItsX() > itsCharacter->getItsX() ? goomba->setXSpeed(-0.4) : goomba->setXSpeed(0.4);
        }

        //Vérifier que le goomba n'atteint pas la bordure du jeu
        if(goomba->getItsRect().left() <= 0)
        {
            goomba->setItsX(1) ;
            goomba->reverseXSpeed();
        }
        else if(goomba->getItsRect().right() >= 800)
        {
            goomba->setItsX(800 - goomba->getItsRect().width());
            goomba->reverseXSpeed();
        }

        // Vérifie les collisions entre le goomba et mario
        if (goombaRect.intersects(characterRect))
        {
            // Si le joueur arrive du haut
            if ( (itsCharacter->getYSpeed() > 0) && ( goombaRect.top() - characterRect.top() > 0) && !goomba->getIsDead())
            {
                soundManager->playEnnemyDeathEffect();
                goomba->setXSpeed(0);
                goomba->setIsDead(true);
                itsCharacter->setYSpeed(-5);
            }
            // Sinon, le joueur perds
            else if(!goomba->getIsDead())
            {
                // Arrêtez le jeu et revenez au menu
                soundManager->playDeathMusic();

                // On regle l'asset et la vitesse de mario
                itsCharacter->setIsDead(true);
                itsCharacter->setXSpeed(0);
                itsCharacter->setItsImage(":/Assets/Assets/mario/mariodead.png");

                // Arret du timer principal
                itsTimer->stop();

                // Désactive le focus pour ne plus controler mario lors de l'animation
                this->setEnabled(false);

                // Lancement de l'animation de mort de mario
                marioTimer->start(10);
                itsCharacter->setYSpeed(-5);

                QObject::connect(soundManager, &SoundManager::musicFinished, this, [this]() {
                    replaceAndDeleteActors();
                    marioTimer->stop();
                    emit gameLosed();
                });

                return; // Sortir de la boucle car un ennemi à touché mario
            }
        }

        // Vérifie les collisions avec les autres goombas
        for (Goomba * otherGoomba : itsGoombas)
        {
            if(otherGoomba != goomba && goomba->getItsRect().intersects(otherGoomba->getItsRect()))
            {
                otherGoomba->reverseXSpeed();
                goomba->reverseXSpeed();
            }
        }

       // ---------------------------------------------------------------------------------------------

        // Vecteur contenant les blocs proche du goomba
        vector<Element*> nearlyBlocks = getNearlyBlocks(goomba);

        // ---------------------------------------------------------------------------------------------

        goomba->setOnPlatform(false);
        // On vérifie que le goomba n'est pas sur le sol
        if(checkEntityOnFloor(goomba, nearlyBlocks))
        {
            goomba->updateAsset(elapsedTime);
        }

        // On vérifie que le goomba n'est sur aucunes des plateformes
        if(checkEntityOnBlocks(goomba, nearlyBlocks))
        {
            goomba->updateAsset(elapsedTime);
            return;
        }

        // Si il est ni sur le sol ni sur une plateforme alors il est soit en train de rentrer dans quelque chose ou soit dans les airs
        if (goomba->getOnPlatform() == false)
        {
            // Gérer les collisions avec les plateformes
            checkPlatformCollision(goomba, nearlyBlocks);

            // Gérer les collision avec le sol
            checkFloorCollision(goomba);
        }

        goomba->calculatePosition();
        goomba->updateAsset(elapsedTime);
    }
}

// Gère les collisions des koopas
void GameForm::checkKoopasCollision()
{

    // Vecteur contenant les koopas dans le champ de vision de mario
    vector<Koopa*> visibleKoopas;

    float characterY = itsCharacter->getItsY();
    for (Koopa * koopa : itsKoopas)
    {
        if (characterY > height()-300 && koopa->getItsY() >= height()-600)
        {
            visibleKoopas.push_back(koopa);
        }
        else if (characterY < height()-300 && characterY > 300 && koopa->getItsY() > characterY-300)
        {
            visibleKoopas.push_back(koopa);
        }
        else if (characterY < 300 && koopa->getItsY() < 600)
        {
            visibleKoopas.push_back(koopa);
        }

    }

    // ---------------------------------------------------------------------------------------------------

    // On parcours chaque koopa du vecteur
    for (Koopa * koopa : visibleKoopas)
    {
        QRect koopaRect = koopa->getItsRect();
        QRect characterRect = itsCharacter->getItsRect();

        // Changement de la vitesse du koopa si il vient d'apparaitre dans le champ de vision du joueur
        if (koopa->getXSpeed() == 0 and !koopa->getIsDead())
        {
            koopa->getItsX() > itsCharacter->getItsX() ? koopa->setXSpeed(-0.4) : koopa->setXSpeed(0.4);
        }

        //Vérifier que le koopa n'atteint pas la bordure du jeu
        if(koopaRect.left() <= 0)
        {
            if(koopa->getIsDead())
            {
                soundManager->playKoopaBumpEffect();
            }
            koopa->setItsX(1) ;
            koopa->reverseXSpeed();

        }
        else if(koopa->getItsRect().right() >= 800)
        {
            if(koopa->getIsDead())
            {
                soundManager->playKoopaBumpEffect();
            }
            koopa->setItsX(800 - koopaRect.width());
            koopa->reverseXSpeed();
        }

        // -----------------------------------------------------------------------------

        // Vérifie les collisions entre le koopa et mario
        if (koopaRect.intersects(characterRect))
        {
            float characterCenter = itsCharacter->getItsRect().center().x();
            float koopaCenter = koopa->getItsRect().center().x();
            // Si le joueur arrive du haut et que le koopa est vivant
            if ( (itsCharacter->getYSpeed() > 0) && ( koopaRect.top() - characterRect.top() > 0) && !koopa->getIsDead())
            {
                soundManager->playEnnemyDeathEffect();
                koopa->setXSpeed(0);
                koopa->setIsDead(true);
                itsCharacter->setYSpeed(-5);
            }
            // Si il arrive du haut et que le koopa est mort
            else if ( (itsCharacter->getYSpeed() > 0) && ( koopaRect.top() - characterRect.top() > 0) && koopa->getIsDead())
            {
                if(characterCenter < koopaCenter && koopa->getXSpeed() == 0)
                {
                    koopa->setXSpeed(1.5);
                }
                else if (characterCenter > koopaCenter && koopa->getXSpeed() == 0)
                {
                    koopa->setXSpeed(-1.5);
                }
                else
                {
                    itsCharacter->setYSpeed(-5);
                    koopa->setXSpeed(0);
                }
            }
            // Si koopa est mort
            else if (koopa->getIsDead() && koopa->getXSpeed() == 0)
            {
                // Si le joueur arrive de la droite
                if (characterCenter > koopaCenter && itsCharacter->getXSpeed() < 0)
                {
                    itsCharacter->setItsX(koopa->getItsRect().right() + 1);
                }
                // Si il arrive de la gauche
                else if (characterCenter < koopaCenter && itsCharacter->getXSpeed() > 0)
                {
                    itsCharacter->setItsX(koopa->getItsRect().left() - itsCharacter->getItsRect().width() - 1);
                }
            }
            // Sinon, le joueur perds
            else if(!koopa->getIsDead() || (koopa->getIsDead() && koopa->getXSpeed() != 0) )
            {
                // Arrêtez le jeu et revenez au menu
                soundManager->playDeathMusic();

                // On regle l'asset et la vitesse de mario
                itsCharacter->setIsDead(true);
                itsCharacter->setXSpeed(0);
                itsCharacter->setItsImage(":/Assets/Assets/mario/mariodead.png");

                // Arret du timer principal
                itsTimer->stop();

                // Désactive le focus pour ne plus controler mario lors de l'animation
                this->setEnabled(false);

                // Lancement de l'animation de mort de mario
                marioTimer->start(10);
                itsCharacter->setYSpeed(-5);

                QObject::connect(soundManager, &SoundManager::musicFinished, this, [this]() {
                    replaceAndDeleteActors();
                    marioTimer->stop();
                    emit gameLosed();
                });

                return; // Sortir de la boucle car un ennemi à touché mario
            }
        }

        // -------------------------------------------------------------------------------------------------


        // Vérifie les collisions avec les goombas
        for (Goomba * otherGoomba : itsGoombas)
        {
            if(koopa->getItsRect().intersects(otherGoomba->getItsRect()) && !otherGoomba->getIsDead())
            {
                if (koopa->getIsDead() && koopa->getXSpeed() != 0)
                {
                    otherGoomba->setXSpeed(0);
                    otherGoomba->setIsDead(true);
                }
                otherGoomba->reverseXSpeed();
                koopa->reverseXSpeed();
            }
        }

        // Vérifie les collisions avec les autres koopas
        for (Koopa * otherKoopa : itsKoopas)
        {
            if(koopa != otherKoopa && koopa->getItsRect().intersects(otherKoopa->getItsRect()))
            {
                if (!otherKoopa->getIsDead() && !koopa->getIsDead())
                {
                    koopa->reverseXSpeed();
                    otherKoopa->reverseXSpeed();
                }
                else if(koopa->getIsDead() && !otherKoopa->getIsDead() && koopa->getXSpeed() != 0)
                {
                    koopa->reverseXSpeed();
                    otherKoopa->setXSpeed(0);
                    otherKoopa->setIsDead(true);
                }
                else if(otherKoopa->getIsDead() && !koopa->getIsDead() && otherKoopa->getXSpeed() != 0)
                {
                    otherKoopa->reverseXSpeed();
                    koopa->setXSpeed(0);
                    koopa->setIsDead(true);
                }
                else if (koopa->getIsDead() && otherKoopa->getIsDead() && koopa->getXSpeed() != 0)
                {
                    koopa->reverseXSpeed();
                    otherKoopa->setXSpeed(koopa->getXSpeed()*-1);
                }
            }
        }

        // ---------------------------------------------------------------------------------------------

        // Vecteur contenant les blocs proche du koopa
        vector<Element*> nearlyBlocks = getNearlyBlocks(koopa);

        // ---------------------------------------------------------------------------------------------

        // On vérifie que le cube n'est pas sur le sol
        koopa->setOnPlatform(false);
        if(checkEntityOnFloor(koopa, nearlyBlocks))
        {
            koopa->updateAsset(elapsedTime);
        }

        // On vérifie que le cube n'est sur aucunes des plateformes (on utilise pas la fonction générique car koopa ne peux pas tomber d'une plateforme)
        for (Element * block : nearlyBlocks)
        {
            if (
                // Si le rectangle est déjà sur la plateforme
                ((block->getRect().top() - (koopa->getItsRect().bottom()) == 1) ||
                 (block->getRect().top() - (koopa->getItsRect().bottom() + 5) == 1)) &&
                // ...ET qu'il n'est PAS PAS sur la plateforme (sur l'axe X)
                !( (koopa->getItsRect().right() < block->getRect().left()) ||
                  (koopa->getItsRect().left() > block->getRect().right()) )
                )
            {
                bool needToReverse = true;
                for (Element * otherBlock : nearlyBlocks)
                {
                    // Récupérer les rectangles de la plateforme
                    QRect platformRect = otherBlock->getRect();

                    if(koopa->getItsRect().intersects(platformRect))
                    {
                        // Si il arrive de la droite
                        if(koopa->getXSpeed() < 0 and koopa->getItsRect().left() - platformRect.left() > 0)
                        {
                            koopa->setItsX(platformRect.right()+1);
                            koopa->reverseXSpeed();
                        }
                        else if(koopa->getXSpeed() > 0 and koopa->getItsRect().right() - platformRect.right() < 0)
                        {
                            koopa->setItsX(platformRect.left()-koopa->getItsRect().width());
                            koopa->reverseXSpeed();
                        }
                    }

                    // Vérifie si il y'a un bloc apres le bloc sur lequel on est
                    float koopaCenter = koopa->getItsRect().center().x();

                    if (koopaCenter > otherBlock->getRect().left() && koopaCenter < otherBlock->getRect().right() && block != otherBlock)
                    {
                        needToReverse = false;
                    }

                }
                koopa->setOnPlatform(true);
                // Si le Koopa doit inverser sa position au risque de se retrouver dans le vide
                if(needToReverse && !koopa->getIsDead())
                {
                    koopa->reverseXSpeed();
                }
            }
        }

        // Si il est ni sur le sol ni sur une plateforme alors il est soit en train de rentrer dans quelque chose ou soit dans les airs
        if (koopa->getOnPlatform() == false && koopa->getIsDead())
        {
            // Gérer les collisions avec les plateformes
            checkPlatformCollision(koopa, nearlyBlocks);

            // Gérer les collision avec le sol
            checkFloorCollision(koopa);

        }

        koopa->calculatePosition();
        koopa->updateAsset(elapsedTime);
    }
}

// Gère les collisions avec le sol
void GameForm::checkFloorCollision(Entity * anEntity)
{
    if (anEntity->getItsRect().intersects(itsFloor->getRect()))
    {
        anEntity->setYSpeed(0);
        anEntity->setItsY(itsFloor->getRect().top() - anEntity->getItsRect().height());
    }
    else
    {
        // Si le personnage est en train de sauter, appliquez une force de gravité pour faire redescendre le personnage
        if (anEntity->getYSpeed() < 0)
        {
            anEntity->setYSpeed(anEntity->getYSpeed() + GRAVITY);
            if(anEntity->getYSpeed() == 0)
            {
                anEntity->setYSpeed(anEntity->getYSpeed() + GRAVITY);
            }
        }
        // Si le personnage est en train de tomber, appliquer une force de gravité pour le faire descendre plus vite
        else if (anEntity->getYSpeed() > 0)
        {
            anEntity->setYSpeed(anEntity->getYSpeed() + GRAVITY);
        }

        else if(anEntity->getYSpeed()==0 && anEntity->getItsY() != (this->height() - (anEntity->getItsRect().height() + 1)) && !anEntity->getOnPlatform())
        {
            anEntity->setYSpeed(anEntity->getYSpeed() + GRAVITY);
        }
    }
}

// Gère les collisions avec les blocks
void GameForm::checkPlatformCollision(Entity * anEntity, vector<Element*> nearlyBlocks)
{
    for (Element * block : nearlyBlocks)
    {
        // Récupérer les rectangles du personnage et de la plateforme
        QRect platformRect = block->getRect();
        QRect entityRect = anEntity->getItsRect();

        // Si le personnage touche une plateforme
        if(entityRect.intersects(platformRect))
        {

            // Si le joueur arrive de la droite
            if((entityRect.left() - platformRect.right() <= 0 and entityRect.left() - platformRect.right() >=-1) )
            {
                anEntity->setItsX(anEntity->getItsX()+1);
                anEntity->setXSpeed(0);
            }
            // Si le joueur arrive de la gauche
            else if (entityRect.right() - platformRect.left() >= 0 and entityRect.right() - platformRect.left() <=1)
            {
                anEntity->setItsX(anEntity->getItsX()-1);
                anEntity->setXSpeed(0);
            }
            // Si il arrive d'en bas
            else if(anEntity->getYSpeed() < 0)
            {
                anEntity->setItsY(platformRect.bottom()+1);
                anEntity->reverseYSpeed();
            }

            // Si il arrive d'en haut
            else if ( (anEntity->getYSpeed() >= 0) && ( platformRect.top() - anEntity->getItsY() >= 0) )
            {
                anEntity->setItsY(platformRect.top() - entityRect.height());
                anEntity->setYSpeed(0);
                anEntity->setOnPlatform(true);
            }
        }
    }
}

// ----------------------------------------------------------------------------------------------------------

// Vérifie si une entité est sur une plateforme (retourne true si c'est le cas)
bool GameForm::checkEntityOnBlocks(Entity * anEntity, vector<Element*> nearlyBlocks)
{
    for (Element * block : nearlyBlocks)
    {
        // On récupère le rectangle de l'entité et du bloc
        QRect blockRect = block->getRect();

        if (
            // Si le rectangle est déjà sur la plateforme
            ((blockRect.top() - (anEntity->getItsRect().bottom()) == 1) ||
             (blockRect.top() - (anEntity->getItsRect().bottom() + 5) == 1)) &&
            // ...ET qu'il n'est PAS PAS sur la plateforme (sur l'axe X)
            !( (anEntity->getItsRect().right() < blockRect.left()) ||
              (anEntity->getItsRect().left() > blockRect.right()) )
            )
        {
            for (Element * otherBlock : nearlyBlocks)
            {
                // Récupérer les rectangles de la plateforme
                QRect platformRect = otherBlock->getRect();

                if(anEntity->getItsRect().intersects(platformRect))
                {
                    // Si il arrive de la droite
                    if(anEntity->getXSpeed() < 0 and anEntity->getItsRect().left() - platformRect.left() > 0)
                    {
                        anEntity->setItsX(platformRect.right()+1);
                    }
                    else if(anEntity->getXSpeed() > 0 and anEntity->getItsRect().right() - platformRect.right() < 0)
                    {
                        anEntity->setItsX(platformRect.left()-anEntity->getItsRect().width());
                    }
                }
            }
            anEntity->setOnPlatform(true);
            if (block->getRect().top() - (anEntity->getItsRect().bottom() + 5) == 1)
            {
                anEntity->setItsY(anEntity->getItsY() + 5);
            }
            anEntity->calculatePosition();
            //anEntity->updateAsset(elapsedTime);
            return true;
        }
    }
    return false;
}

// Vérifie si une entité est sur le sol (retourne true si c'est le cas)
bool GameForm::checkEntityOnFloor(Entity * anEntity, vector<Element*> nearlyBlocks)
{
    if ((itsFloor->getRect().top() - (anEntity->getItsRect().bottom()) == 1) ||
        itsFloor->getRect().top() - (anEntity->getItsRect().bottom() + 5) == 1  )
    {
        for (Element * block : nearlyBlocks)
        {
            // Récupérer les rectangles du personnage et de la plateforme
            QRect platformRect = block->getRect();

            if(anEntity->getItsRect().intersects(platformRect))
            {
                // Si il arrive de la droite
                if(anEntity->getXSpeed() < 0 and anEntity->getItsRect().left() - platformRect.left() > 0)
                {
                    anEntity->setItsX(platformRect.right()+1);
                    // Si la vitesse correspond a celle d'un koopa ou d'un goomba alors on reverse la xspeed
                    if (anEntity->getXSpeed() == float(-0.4) || anEntity->getXSpeed() == float(-0.5) || anEntity->getXSpeed() == float(-1.5))
                    {
                        // Son de bump si koopa est mort et touche bump un objet
                        if(anEntity->getXSpeed() == float(-1.5)) { soundManager->playKoopaBumpEffect(); }
                        anEntity->reverseXSpeed();
                    }

                }
                else if(anEntity->getXSpeed() > 0 and anEntity->getItsRect().right() - platformRect.right() < 0)
                {
                    anEntity->setItsX(platformRect.left()-anEntity->getItsRect().width());
                    if (anEntity->getXSpeed() == float(0.4) || anEntity->getXSpeed() == float(0.5) || anEntity->getXSpeed() == float(1.5))
                    {
                        if(anEntity->getXSpeed() == float(1.5)) { soundManager->playKoopaBumpEffect(); }
                        anEntity->reverseXSpeed();
                    }
                }
            }
        }
        anEntity->setOnPlatform(true);
        if (itsFloor->getRect().top() - (anEntity->getItsRect().bottom() + 5) == 1)
        {
            anEntity->setItsY(anEntity->getItsY() + 5);
        }
        anEntity->calculatePosition();
        return true;
    }
    return false;
}

// Récupère les blocs proche d'une entité
vector<Element *> GameForm::getNearlyBlocks(Entity * anEntity)
{
    const int DISTANCE_THRESHOLD = 25;
    vector<Element*> nearlyBlocks;

    for (Element * block : itsBlocks)
    {
        int distanceX = abs(anEntity->getItsRect().center().x() - block->getRect().center().x());

        // Add only the block near to the player
        if (distanceX < DISTANCE_THRESHOLD)
        {
            nearlyBlocks.push_back(block);

        }
    }

    return nearlyBlocks;
}

// ---------------------------------------------------------------------------------------------------------

void GameForm::updateScroll() {
    int characterY = itsCharacter->getItsY();

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
    static int previousTime;
    if(elapsedTime == 10)
    {
        previousTime = 0; // Variable pour conserver le temps précédent
    }

    int currentTime = elapsedTime;

    for (FireBall* fireball : *itsBoss->getItsFireBalls())
    {
        fireball->calculatePosition();
    }

    double coefficient = (1 - (0.05 * (itsLevel - 1))); // Accélérer la fréquence en fonction du niveau

    if (currentTime - previousTime >= 1000 * coefficient)
    {
        itsBoss->dropFireBall();
        previousTime = currentTime; // Mettre à jour le temps précédent
    }
}

void GameForm::replaceAndDeleteActors()
{
    // Replacement des acteurs du jeu
    itsCharacter->setItsX(50);
    itsCharacter->setItsY(height() - 100);

    itsGoombas.clear();
    itsKoopas.clear();

    itsBoss->setItsX(width()-80);
    itsBoss->setItsY(height()-570);

    itsBoss->getItsFireBalls()->clear();
    itsBlocks.clear();
    itsLadders.clear();
}

// ---------------------------------------------------------------------------------------------------------

void GameForm::gameloop()
{
    if(isOnGamed)
    {
        elapsedTime += 10;
        displayChrono();

        checkLadderCollision();
        checkCharacterCollision();

        checkGoombasCollision();
        checkKoopasCollision();

        checkBowserCollision();
        checkCollisionFireBalls();

        updateScroll();
        updateFireBalls();
        repaint();
    }
}

void GameForm::animationDeath()
{
    itsCharacter->setYSpeed(itsCharacter->getYSpeed()+ GRAVITY/2 );
    itsCharacter->calculatePosition();
    repaint();
}

void GameForm::setIsOnGamed(bool newIsOnGamed)
{
    isOnGamed = newIsOnGamed;

    // Si le setter passe à vrai, c'est qu'une partie redémarre et qu'il faut donc relancer le timer et la musique
    if(newIsOnGamed == true)
    {
        itsTimer->start();
    }
}

void GameForm::displayChrono()
{
    // Mettre à jour l'affichage du temps écoulé
    int seconds = elapsedTime / 1000;
    int milliseconds = elapsedTime % 1000;
    QString timeString = QString("time\n%1.%2").arg(seconds).arg(milliseconds / 100, 1, 10, QChar('0'));
    timeLabel->setText(timeString);
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
        isOnGamed = true ;
    }
}


// ---------------------------------------------------------------------------------------------------------

void GameForm::keyPressEvent (QKeyEvent * event)
{
    // Gérez les déplacements X
    if (event->key() == Qt::Key_Left)
    {
        itsCharacter->setXSpeed(-2);
    }
    else if(event->key() == Qt::Key_Right)
    {
        itsCharacter->setXSpeed(2);
    }

    // Sauter
    if(event->key() == Qt::Key_Space && itsCharacter->getYSpeed() == 0 and !itsCharacter->getOnLadder())
    {
        soundManager->playJumpEffect();
        itsCharacter->jump();
    }

    // Monter et descendre de l'échelle
    if(event->key() == Qt::Key_Up and itsCharacter->getOnLadder() and itsCharacter->getXSpeed() == 0 and itsCharacter->getYSpeed() == 0 )
    {
        itsCharacter->setYSpeed(-2);
        itsCharacter->setItsImage(":Assets/Assets/mario/mario8.png");
    }
    if(event->key() == Qt::Key_Down and itsCharacter->getOnLadder() and itsCharacter->getXSpeed() == 0 and itsCharacter->getYSpeed() == 0)
    {
        itsCharacter->setYSpeed(2);
        itsCharacter->setItsImage(":Assets/Assets/mario/mario8.png");
    }

    // Menu Pause
    if (event->key() == Qt::Key_Escape)
    {
        emit gamePaused();
        soundManager->stopAllSounds();
        itsTimer->stop();
        isOnGamed = false ;
    }
}

void GameForm::keyReleaseEvent (QKeyEvent * event)
{
    // Arrêt des déplacement X
    if ((event->key() == Qt::Key_Left) || event->key() == Qt::Key_Right)
    {
        itsCharacter->setXSpeed(0);
    }
    // Arret des déplacements Y
    if((event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) and itsCharacter->getOnLadder())
    {
        itsCharacter->setYSpeed(0);
    }
}

void GameForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter * painter = new QPainter(this);

    painter->drawImage(0, backgroundY, itsBackground);

    itsFloor->draw(painter);

    for (Element * block : itsBlocks)
    {
        block->draw(painter);        
    }

    for (FireBall * fireball : *itsBoss->getItsFireBalls())
    {
        fireball->draw(painter);
    }

    for(Element * ladder : itsLadders)
    {
        ladder->draw(painter);
    }
    itsChest->draw(painter);

    // Afficher les aides au joueur
    if(!itsCharacter->getIsDead())
    {
        paintPlayerHelps(painter);
    }

    // Afficher les entités du jeu
    for (Goomba * goomba : itsGoombas)
    {
        goomba->draw(painter);
    }
    for (Koopa * koopa : itsKoopas)
    {
        koopa->draw(painter);
    }
    itsCharacter->draw(painter);
    itsBoss->draw(painter);

    delete painter;
}

void GameForm::paintPlayerHelps(QPainter* painter)
{
    if (itsLevel == 1 && (itsCharacter->getItsRect().bottom() + 300) > height() - 80)
    {
        painter->drawImage(180, height() - 80, upArrow);
    }
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

SoundManager* GameForm::getSoundManager() const
{
    return soundManager;
}

void GameForm::setVolume(SoundManager * menuSoundManager){
    //Récupère les volumes sonores du MenuForm en récupérant son SoundManager
    itsVolumesGen = menuSoundManager->getVolume();
    itsVolumesEffect = menuSoundManager->getEffectsVolume();

    //Modifie les volumes du gameForm
    soundManager->setEffectsVolume(itsVolumesEffect);
    soundManager->setMainVolume(itsVolumesGen);

    soundManager->playMainMusic();
}
