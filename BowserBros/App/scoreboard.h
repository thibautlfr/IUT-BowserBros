/**
@file scoreboard.h
@brief Defines the ScoreBoard class.
*/
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <algorithm>

/**
@class ScoreBoard
@brief This class is used to interact with the players ScoreBoard
@author Colin
*/
class ScoreBoard {

private:
    QJsonObject scoreboard; /**< The scoreboard implemented with a Json file. */
    const QString filePath = "../../Database/ScoreBoard.json"; /**< The path to the json file. */

public:
    /**
     * @brief Constructor for the ScoreBoard class
     * @author Colin
     */
    ScoreBoard();

    /**
     * @brief Destructor for the ScoreBoard class
     * @author Colin
     */
    ~ScoreBoard();

    /**
     * @brief Adds a score to the JSON ScoreBoard File (only if the players does not exists or if the score is below the previous)
     * @param playerName : the name of the player
     * @param score : the time of the player
     * @author Colin
     */
    void addScore(const QString& playerName, double score);

    /**
     * @brief Gets the top X players in the players ranking
     * @param count : the number of players we want to extract
     * @return a list of paire of the top X players
     * @author Colin
     */
    QList<QPair<QString, double>> getTopPlayers(int count);
};

#endif // SCOREBOARD_H
