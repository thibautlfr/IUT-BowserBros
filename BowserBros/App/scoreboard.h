#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <algorithm>

class ScoreBoard {
public:
    ScoreBoard();
    ~ScoreBoard();

    void addScore(const QString& playerName, double score);
    QList<QPair<QString, double>> getTopPlayers(int count);

private:
    QJsonObject scoreboard;
    const QString filePath = "ScoreBoard.json";
};

#endif // SCOREBOARD_H
