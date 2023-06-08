#include "database.h"

DataBase::DataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    // Copier le fichier de ressources vers un emplacement temporaire
    QString dbPath = ":/DataBase/DataBase/scoreboard.db";
    QString tempDbPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/scoreboard.db";
    if (QFile::copy(dbPath, tempDbPath)) {
        db.setDatabaseName(tempDbPath);

        if (!db.open()) {
            qDebug() << "Erreur base de données:" << db.lastError().text();
            open = false;
        } else {
            open = true;
        }
    } else {
        qDebug() << "Erreur lors de la copie du fichier de ressources";
        open = false;
    }
}

DataBase::~DataBase()
{
    db.close();
}

// --------------------------------------------------------------------------------

void DataBase::addScore(const QString& playerName, double score)
{
    QSqlQuery query;

    // Vérifier si le joueur existe déjà dans la table
    query.prepare("SELECT score FROM player WHERE name = ?");
    query.addBindValue(playerName);
    if (query.exec() && query.next()) {
        // Le joueur existe déjà, vérifier si le nouveau score est meilleur
        double currentScore = query.value(0).toDouble();
        if (score > currentScore) {
            // Mettre à jour le score du joueur
            query.prepare("UPDATE player SET score = ? WHERE name = ?");
            query.addBindValue(score);
            query.addBindValue(playerName);
            query.exec();
        }
    } else {
        // Le joueur n'existe pas, l'insérer dans la table
        query.prepare("INSERT INTO player (name, score) VALUES (?, ?)");
        query.addBindValue(playerName);
        query.addBindValue(score);
        query.exec();
    }
}

QList<QPair<QString, double>> DataBase::getTopPlayers(int count)
{
    QList<QPair<QString, double>> topPlayers;
    QSqlQuery query;

    if (count <= 0) {
        // Si count est inférieur ou égal à 0, récupérer le classement complet
        if (query.exec("SELECT name, score FROM player ORDER BY score DESC")) {
            while (query.next()) {
                QString name = query.value(0).toString();
                double score = query.value(1).toDouble();
                topPlayers.append(QPair<QString, double>(name, score));
            }
        }
    } else {
        // Récupérer les X meilleurs joueurs
        if (query.exec(QString("SELECT name, score FROM player ORDER BY score DESC LIMIT %1").arg(count))) {
            while (query.next()) {
                QString name = query.value(0).toString();
                double score = query.value(1).toDouble();
                topPlayers.append(QPair<QString, double>(name, score));
            }
        }
    }

    return topPlayers;
}
