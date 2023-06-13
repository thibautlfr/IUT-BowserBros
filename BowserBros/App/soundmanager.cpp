#include "soundmanager.h"
#include "qdebug.h"

#include <QThread>

SoundManager::SoundManager(QObject *parent) : QObject(parent)
{
    // Initialise les volume à 1 lors de la création du soundManager
    itsVolume = 1.0f;
    itsEffectsVolume = 1.0f;

    // Création et pré-chargement de tout les sons du jeu
    jumpEffect = new QSoundEffect(this);
    jumpEffect->setSource(QUrl::fromLocalFile(":Song/Song/JumpSound.wav"));

    mainMusic = new QSoundEffect(this);
    mainMusic->setSource(QUrl::fromLocalFile(":Song/Song/MainMusic.wav"));

    deathMusic = new QSoundEffect(this);
    deathMusic->setSource(QUrl::fromLocalFile(":Song/Song/gameover.wav"));

    winMusic = new QSoundEffect(this);
    winMusic->setSource(QUrl::fromLocalFile(":Song/Song/win.wav"));

    menuMusic = new QSoundEffect(this);
    menuMusic->setSource(QUrl::fromLocalFile(":Song/Song/menumusic.wav"));

    levelPassedMusic = new QSoundEffect(this);
    levelPassedMusic->setSource(QUrl::fromLocalFile(":Song/Song/endlevel.wav"));
}

SoundManager::~SoundManager()
{
    jumpEffect->deleteLater();
    mainMusic->deleteLater();
    deathMusic->deleteLater();
    winMusic->deleteLater();
    levelPassedMusic->deleteLater();
    menuMusic->deleteLater();
}
// ---------------------------------------------------------------------------------------------------------

//Catch les attributs qui sont une copie de ceux du MenuForm

float SoundManager::getVolume() const
{
    return itsVolume;
}

float SoundManager::getEffectsVolume() const
{
    return itsEffectsVolume;
}

// ---------------------------------------------------------------------------------------------------------

void SoundManager::playJumpEffect()
{
    jumpEffect->play();
}

// ---------------------------------------------------------------------------------------------------------

void SoundManager::playMainMusic()
{
    stopAllSounds();
    mainMusic->setLoopCount(QSoundEffect::Infinite);
    mainMusic->play();
}

void SoundManager::playMenuMusic()
{
    stopAllSounds();
    menuMusic->setLoopCount(QSoundEffect::Infinite);
    menuMusic->play();
}

void SoundManager::playDeathMusic()
{
    stopAllSounds();
    QObject::connect(deathMusic, &QSoundEffect::playingChanged, this, [this]() {
        if (!deathMusic->isPlaying()) {
            emit musicFinished();
        }
    });

    deathMusic->play();
}

void SoundManager::playWinMusic()
{
    stopAllSounds();
    QObject::connect(winMusic, &QSoundEffect::playingChanged, this, [this]() {
        if (!winMusic->isPlaying()) {
            emit musicFinished();
        }
    });

    winMusic->play();
}

void SoundManager::playLevelPassedMusic()
{
    stopAllSounds();
    QObject::connect(levelPassedMusic, &QSoundEffect::playingChanged, this, [this]() {
        if (!levelPassedMusic->isPlaying()) {
            emit musicFinished();
        }
    });

    levelPassedMusic->play();
}

// ---------------------------------------------------------------------------------------------------------

void SoundManager::setMainVolume(float volume)
{
    //Change tous les volumes
    mainMusic->setVolume(volume);
    deathMusic->setVolume(volume);
    menuMusic->setVolume(volume);
    winMusic->setVolume(volume);
    qDebug()<<"Volume Général : " << volume;

    //Initialise l'attribut pour le sauvegarder et le copier dans le gameform
    itsVolume=volume;

}

void SoundManager::setEffectsVolume(float volume)
{
    //Modifie tous les sons
    jumpEffect->setVolume(volume);
    levelPassedMusic->setVolume(volume);

    //Initialise l'attribut pour le sauvegarder et le copier dans le gameform
    itsEffectsVolume=volume;
}

// ---------------------------------------------------------------------------------------------------------

void SoundManager::stopAllSounds()
{
    if (mainMusic->isPlaying())
    {
        mainMusic->stop();
    }
    if (menuMusic->isPlaying())
    {
        menuMusic->stop();
    }
    if (jumpEffect->isPlaying())
    {
        jumpEffect->stop();
    }
    if (deathMusic->isPlaying())
    {
        deathMusic->stop();
    }
    if (winMusic->isPlaying())
    {
        winMusic->stop();
    }
    if (levelPassedMusic->isPlaying())
    {
        levelPassedMusic->stop();
    }
}


