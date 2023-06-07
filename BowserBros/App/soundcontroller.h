#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H
#include <iostream>
using namespace std;

//Song
#include <QMediaPlayer>
#include <QSoundEffect>


class SoundController
{
private:
    QSoundEffect * mainsound;
    QSoundEffect * jumpsound;
    QSoundEffect * gameoversound;
    QSoundEffect * winsound;

public:
    SoundController();
    ~SoundController();
    void MainSound();
    void StopMainSound();
    void JumpSound();
    void GameoverSound();
    void WinSound();
};

#endif // SOUNDCONTROLLER_H
