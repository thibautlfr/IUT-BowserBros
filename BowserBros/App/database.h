/**
 * @file database.h
 * @brief Statement of the DataBase class
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QDebug>
#include <iostream>

using namespace std;

/**
 * @class DataBase
 * @brief Class used to intercat with the SQLite 3 database
 * @details This class serve the application to make some SQL querys to the database and acces the best players in it
 */
class DataBase
{
private :
    QSqlDatabase db; ///< The DataBase wich will be openned using QtSql
    bool open; ///< A boolean wich is true if the databas is correctly openned and false either

public:
    /**
     * @brief Constructor for the DataBase class
     * @details Open the database and verify that it has been openned correctly
     */
    DataBase();

    /**
     * @brief Destructor for the class DataBase
     * @details Closes the database connection
     */
    ~DataBase();

    // -------------------------------------------------------------------------------------------------

    /**
     * @brief Add a score of a player in the database
     * @param playerName : the name of the player
     * @param score : the score of the player
     */
    void addScore(const QString& playerName, double score);

    /**
     * @brief Return the top "count" players in the database
     * @param count the number of polayers we want to get
     * @return A List of the names and score of each players
     */
    QList<QPair<QString, double>> getTopPlayers(int count);

};

#endif // DATABASE_H
