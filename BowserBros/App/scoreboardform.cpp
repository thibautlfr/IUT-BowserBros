#include "scoreboardform.h"
#include "ui_scoreboardform.h"

#include <QTableWidget>
#include <QHeaderView>
#include <QTime>


ScoreboardForm::ScoreboardForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreboardForm)
{
    ui->setupUi(this);

    setFixedSize(800, 600);
    itsBackground.load(":Assets/Assets/background/backgroundMenu.png");
    itsFloor.load(":Assets/Assets/other/floor.png");
    itsMario.load(":Assets/Assets/mario/mario6.png");
    itsBowser.load(":Assets/Assets/bowser/bowsermenu.png");

    // --------------------------------------------------------------------------------------------------------------------------------

    // Créer la QTableWidget
    QTableWidget* tableWidget = new QTableWidget(this);
    tableWidget->setFixedSize(400, 300); // Définir la taille de la table
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // Désactiver l'édition des cellules
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection); // Désactiver la sélection des cellules
    tableWidget->setFocusPolicy(Qt::NoFocus); // Désactiver le focus sur la table

    // Appliquer un style personnalisé pour arrondir les bords de la table et la couleur de fond
    // Appliquer un style personnalisé pour arrondir les bords de la table et la couleur de fond
    tableWidget->setStyleSheet("QTableWidget { background-color: #9f4f0a; border: 1px solid black; }"
                               "QHeaderView::section { background-color: #e7b12a; }"); // Changer la couleur du texte

    // Définir le nombre de colonnes
    tableWidget->setColumnCount(2);

    // Définir les en-têtes des colonnes
    QStringList headers;

    headers << "Player" << "Time";
    tableWidget->setHorizontalHeaderLabels(headers);

    // Centrer le texte et appliquer la couleur de fond aux en-têtes des colonnes
    QHeaderView* headerView = tableWidget->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignCenter); // Centrer le texte des en-têtes des colonnes

    // Désactiver la possibilité de cliquer sur les noms des colonnes
    headerView->setSectionsClickable(false);

    // Masquer les numéros de lignes à gauche
    tableWidget->verticalHeader()->setVisible(false);

    // Ajouter des noms aléatoires et des temps aléatoires à la table
    QTime time = QTime::currentTime();
    srand(static_cast<uint>(time.msec())); // Initialiser le générateur de nombres aléatoires avec le temps actuel

    tableWidget->setRowCount(5); // Définir le nombre de lignes à 5

    for (int row = 0; row < 5; ++row) {
        QString playerName = "Player " + QString::number(row + 1);
        QString timeStr = QString::number(rand() % 100 + 1) + " s";

        QTableWidgetItem* playerItem = new QTableWidgetItem(playerName);
        playerItem->setTextAlignment(Qt::AlignCenter); // Centrer le texte de la cellule
        tableWidget->setItem(row, 0, playerItem);

        QTableWidgetItem* timeItem = new QTableWidgetItem(timeStr);
        timeItem->setTextAlignment(Qt::AlignCenter); // Centrer le texte de la cellule
        tableWidget->setItem(row, 1, timeItem);
    }

    // Définir le mode de redimensionnement des colonnes à "Stretch" pour les faire occuper toute la largeur
    headerView->setSectionResizeMode(QHeaderView::Stretch);

    // Étendre les lignes jusqu'en bas de la table
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Centrer le texte et appliquer la couleur de fond aux cellules
    QTableWidgetItem* playerItem = new QTableWidgetItem("Player");
    playerItem->setTextAlignment(Qt::AlignCenter); // Centrer le texte de la cellule
    tableWidget->setItem(0, 0, playerItem);

    QTableWidgetItem* timeItem = new QTableWidgetItem("Time");
    timeItem->setTextAlignment(Qt::AlignCenter); // Centrer le texte de la cellule
    tableWidget->setItem(0, 1, timeItem);

    // Centrer la table au milieu de l'écran
    int tableX = (width() - tableWidget->width()) / 2;
    int tableY = (height() - tableWidget->height()) / 2;
    tableWidget->move(tableX, tableY);

    // --------------------------------------------------------------------------------------------------------------------------------

    repaint() ;
}

ScoreboardForm::~ScoreboardForm()
{
    delete ui;
}

void ScoreboardForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter * painter = new QPainter(this);
    painter->drawImage(0, 0, itsBackground);
    painter->drawImage(0, height()-20, itsFloor);
    //painter->drawImage(135, 100, itsGameTitle);
    painter->drawImage(70, height()-20-45, itsMario);
    painter->drawImage(width() - 150, height()-20-86, itsBowser);
    delete painter;
}
