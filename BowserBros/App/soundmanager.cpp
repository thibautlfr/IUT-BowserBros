#include "soundmanager.h"

#include <QThread>

SoundManager::SoundManager(QObject *parent) : QObject(parent)
{
    // Création et pré-chargement de tout les sons du jeu
    jumpEffect = new QSoundEffect(this);
    jumpEffect->setSource(QUrl::fromLocalFile(":Song/Song/JumpSound.wav"));

    koopaBumpEffect = new QSoundEffect(this);
    koopaBumpEffect->setSource(QUrl::fromLocalFile(":Song/Song/KoopaBump.wav"));

    ennemyDeathEffect = new QSoundEffect(this);
    ennemyDeathEffect->setSource(QUrl::fromLocalFile(":Song/Song/EnnemiDeathEffect.wav"));

    // ---------------------------------------------------------------------------------------

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
    ennemyDeathEffect->deleteLater();
    koopaBumpEffect->deleteLater();

    //====================================

    mainMusic->deleteLater();
    deathMusic->deleteLater();
    winMusic->deleteLater();
    levelPassedMusic->deleteLater();
    menuMusic->deleteLater();
}

// ---------------------------------------------------------------------------------------------------------

void SoundManager::playJumpEffect()
{
    jumpEffect->play();
}

void SoundManager::playEnnemyDeathEffect()
{
    ennemyDeathEffect->play();
}

void SoundManager::playKoopaBumpEffect()
{
    koopaBumpEffect->play();
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

    //deathMusic->setSource(QUrl::fromLocalFile(":Song/Song/gameover.wav"));
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

    //winMusic->setSource(QUrl::fromLocalFile(":Song/Song/win.wav"));
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

    //levelPassedMusic->setSource(QUrl::fromLocalFile(":Song/Song/endl.wav"));
    QObject::connect(levelPassedMusic, &QSoundEffect::playingChanged, this, [this]() {
        if (!levelPassedMusic->isPlaying()) {
            emit musicFinished();
        }
    });

    levelPassedMusic->play();
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

}

