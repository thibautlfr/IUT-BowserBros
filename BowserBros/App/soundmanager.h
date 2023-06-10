#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QSoundEffect>

class SoundManager : public QObject
{
    Q_OBJECT

public:
    explicit SoundManager(QObject *parent = nullptr);
    ~SoundManager();

    void playJumpEffect();

    void playMainMusic();
    void playDeathMusic();
    void playWinMusic();
    void playLevelPassedMusic();
    void playMenuMusic();

    void stopAllSounds();

private:
    QSoundEffect *jumpEffect;
    QSoundEffect *mainMusic;
    QSoundEffect *deathMusic;
    QSoundEffect *winMusic;
    QSoundEffect *levelPassedMusic;
    QSoundEffect *menuMusic;

signals:
    void musicFinished();
};


#endif // SOUNDMANAGER_H
