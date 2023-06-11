#include "scoreboard.h"

ScoreBoard::ScoreBoard() {
    QFile file(filePath);
    if (!file.exists()) {
        // Crée un nouveau fichier JSON s'il n'existe pas
        file.open(QIODevice::WriteOnly);
        file.write("{}");
        file.close();
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open scoreboard file.");
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(fileData));
    scoreboard = doc.object();
}

ScoreBoard::~ScoreBoard() {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open scoreboard file for writing.");
        return;
    }

    QJsonDocument doc(scoreboard);
    if (file.write(doc.toJson()) == -1) {
        qWarning("Couldn't write to scoreboard file.");
    }
}

void ScoreBoard::addScore(const QString& playerName, double score) {
    QJsonArray playerScores = scoreboard[playerName].toArray();

    // Le score est ajouté que si c'est un nouveau record pour le joueur
    if (playerScores.isEmpty() || score < playerScores[0].toDouble()) {
        playerScores.insert(0, score);
        scoreboard[playerName] = playerScores;
    }
}

QList<QPair<QString, double>> ScoreBoard::getTopPlayers(int count) {
    QList<QPair<QString, double>> topPlayers;

    // Récupérer tous les scores dans une liste
    for (const QString& player : scoreboard.keys()) {
        const QJsonArray& scores = scoreboard[player].toArray();
        for (const QJsonValue& score : scores) {
            topPlayers.append(QPair<QString, double>(player, score.toDouble()));
        }
    }

    // Tri des scores par ordre croissant
    std::sort(topPlayers.begin(), topPlayers.end(), [](const QPair<QString, double>& a, const QPair<QString, double>& b) {
        return a.second < b.second;
    });

    // Si count est inférieur ou égal à 0, retourner tous les scores
    if (count <= 0) {
        return topPlayers;
    } else {
        // Sinon, retourner seulement les 'count' premiers scores
        return topPlayers.mid(0, count);
    }
}
