#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include <QMap>

class SoundManager : public QObject {
    Q_OBJECT

public:
    explicit SoundManager(QObject *parent = nullptr);
    ~SoundManager();

public slots:
    void playEffect(const QString &file);
    void stopEffect(const QString &file);
    void clear();

signals:
    void finished();

private:
    QMap<QString, QSoundEffect*> m_soundEffects; // Chaque effet sonore est associé à un fichier
};

#endif // SOUNDMANAGER_H
