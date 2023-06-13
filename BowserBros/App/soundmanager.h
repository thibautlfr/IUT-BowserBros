#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>

class SoundManager : public QObject
{
    Q_OBJECT

public:
    explicit SoundManager(QObject *parent = nullptr);
    ~SoundManager();

    void playJumpEffect();
    void playMainMusic();
    void playMenuMusic();
    void playDeathMusic();
    void playWinMusic();
    void playLevelPassedMusic();

    void setVolume(float volume);
    void setEffectsVolume(float volume);
    void stopAllSounds();

    float getVolume() const;
    float getEffectsVolume() const;

signals:
    void musicFinished();

private:

    QSoundEffect* jumpEffect;
    QSoundEffect* mainMusic;
    QSoundEffect* deathMusic;
    QSoundEffect* winMusic;
    QSoundEffect* menuMusic;
    QSoundEffect* levelPassedMusic;

    float volume;
    float effectsVolume;
};

#endif // SOUNDMANAGER_H
