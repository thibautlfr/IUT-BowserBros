#include "soundcontroller.h"

SoundController::SoundController()
{
    mainsound     = new QSoundEffect();
    jumpsound     = new QSoundEffect();
    winsound      = new QSoundEffect();
    gameoversound = new QSoundEffect();

}

SoundController::~SoundController()
{
    delete mainsound;
    delete jumpsound;
    delete winsound;
    delete gameoversound;
}

void SoundController::MainSound()
{
    mainsound->setSource(QUrl::fromLocalFile(":/Song/Song/MainMusic.wav"));
    mainsound->setVolume(0.3);
    mainsound->setLoopCount(9000);
    mainsound->play();
}

void SoundController::StopMainSound()
{
    mainsound->stop();
}

void SoundController::JumpSound()
{
    jumpsound->setSource(QUrl::fromLocalFile(":/Song/Song/JumpSound.wav"));
    jumpsound->setVolume(0.1);
    jumpsound->play();
}

void SoundController::GameoverSound()
{
    gameoversound->setSource(QUrl::fromLocalFile(":/Song/Song/gameover.wav"));
    gameoversound->setVolume(0.3);
    gameoversound->play();

}

void SoundController::WinSound()
{
    winsound->setSource(QUrl::fromLocalFile(":/Song/Song/win.wav"));
    winsound->setVolume(0.3);
    winsound->play();
}
