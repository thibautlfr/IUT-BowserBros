#include "soundmanager.h"

#include <QTimer>

//SoundManager::SoundManager(QObject *parent) : QObject(parent) {}

//SoundManager::~SoundManager() {
//    for(SoundEffectWrapper *wrapper : m_soundEffects) {
//        delete wrapper->effect;
//        delete wrapper;
//    }
//}

//void SoundManager::playEffect(const QString &file) {
//    SoundEffectWrapper *wrapper = new SoundEffectWrapper;
//    wrapper->effect = new QSoundEffect;
//    wrapper->effect->setSource(QUrl::fromLocalFile(file));
//    wrapper->filePath = file;
//    if(file == ":Song/Song/MainMusic.wav" ) {   wrapper->effect->setLoopCount(QSoundEffect::Infinite); }
//    wrapper->effect->play();
//    m_soundEffects.append(wrapper);
//}

//void SoundManager::stopEffect(const QString &file) {
//    for(SoundEffectWrapper *wrapper : m_soundEffects) {
//        if(wrapper->filePath == file) {
//            wrapper->effect->stop();
//            break;
//        }
//    }
//}

//void SoundManager::clear() {
//    for(SoundEffectWrapper *wrapper : m_soundEffects) {
//        delete wrapper->effect;
//        delete wrapper;
//    }
//    m_soundEffects.clear();
//}

SoundManager::SoundManager(QObject *parent)
    : QObject(parent)
{
}

SoundManager::~SoundManager()
{
    // Libérer la mémoire allouée pour chaque effet sonore.
    for(auto &effect : m_soundEffects) {
        effect->stop();
        delete effect;
    }
    m_soundEffects.clear();
}

void SoundManager::playEffect(const QString &file) {
    QSoundEffect *effect = m_soundEffects.value(file);
    if (!effect) {
        effect = new QSoundEffect;
        effect->setSource(QUrl::fromLocalFile(file));
        m_soundEffects.insert(file, effect);
    }
    effect->play();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this, effect, timer]() {
        if (!effect->isPlaying()) {
            emit finished();
            timer->stop();
            timer->deleteLater();
        }
    });
    timer->start(100); // Vérifiez toutes les 100 millisecondes
}

void SoundManager::stopEffect(const QString &file) {
    QSoundEffect *effect = m_soundEffects.value(file);
    if (effect) {
        effect->stop();
    }
}

void SoundManager::clear() {
    qDeleteAll(m_soundEffects);
    m_soundEffects.clear();
}
