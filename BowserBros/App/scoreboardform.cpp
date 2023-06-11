#include "scoreboardform.h"
#include "ui_scoreboardform.h"

#include <QHeaderView>
#include <QTime>
#include <QLabel>
#include <QFontDatabase>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>

ScoreboardForm::ScoreboardForm(QWidget *parent, int elapsedTime) :
    QWidget(parent),
    ui(new Ui::ScoreboardForm)
{
    ui->setupUi(this);

    setFixedSize(800, 600);

    // --------------------------------------------------------------------------------------------------------------------------------

    // Charger les images
    itsBackground.load(":Assets/Assets/background/backgroundMenu.png");
    itsFloor.load(":Assets/Assets/other/floor.png");
    itsMario.load(":Assets/Assets/mario/mario6.png");
    itsBowser.load(":Assets/Assets/bowser/bowsermenu.png");

    // --------------------------------------------------------------------------------------------------------------------------------

    // Bouton menu
    QPixmap menuAsset(":/Assets/Assets/menu/menu.png");
    ui->menuButton->setIcon(menuAsset);
    ui->menuButton->setIconSize(QSize(200, 70));

    connect(ui->menuButton, &QPushButton::clicked, this, &ScoreboardForm::menuButtonClicked);

    // --------------------------------------------------------------------------------------------------------------------------------

    // Charger la police depuis le fichier
    QString fontPath = ":Fonts/Fonts/policeMario2.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily, 22);

    // Créer l'effet d'ombre
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(1, 1);
    shadowEffect->setBlurRadius(2);

    // Créer le titre du widget
    itsTitle = new QLabel("CLASSEMENT", this);
    itsTitle->setStyleSheet("font-size: 35px; color: white;");
    itsTitle->setGraphicsEffect(shadowEffect);
    itsTitle->setFont(font);
    itsTitle->setAlignment(Qt::AlignCenter);
    itsTitle->setGeometry(30, 10, 740, 150 );
    itsTitle->show();


    // --------------------------------------------------------------------------------------------------------------------------------

    // Ouverture de la base de données
    itsScoreBoard = new ScoreBoard();

    // Créer la QTableWidget
    itsRankingTable = new QTableWidget(this);

    setSettingsTable(); // Appeler la fonction pour configurer la table de classement

    if (elapsedTime != 0)
    {
        // Calculer les secondes et les millisecondes à partir du temps écoulé
        int seconds = elapsedTime / 1000;
        int milliseconds = elapsedTime % 1000;

        // Calculer le score du joueur en ajoutant les secondes et les millisecondes converties en décimales
        playerScore = seconds + static_cast<double>(milliseconds) / 1000.0;

        // Créer un QLabel pour afficher le temps du joueur
        itsPlayerTimeLabel = new QLabel(this);
        itsPlayerTimeLabel->setStyleSheet("font-size: 24px; color: white");
        itsPlayerTimeLabel->setFont(font);
        itsPlayerTimeLabel->setAlignment(Qt::AlignCenter);
        itsPlayerTimeLabel->setGeometry(30, 115, 740, 50);
        itsPlayerTimeLabel->setText("Votre temps : " + QString::number(playerScore, 'f', 1) + "s"); // Définir le texte affiché avec le score du joueur

        qDebug() << playerScore;

        // Créer un QLabel pour afficher les instructions
        itsInstructionsLabel = new QLabel("Veuillez entrer votre pseudo :", this);
        itsInstructionsLabel->setStyleSheet("font-size: 21px; color: white");
        itsInstructionsLabel->setFont(font);
        itsInstructionsLabel->setAlignment(Qt::AlignCenter);
        itsInstructionsLabel->setGeometry(160, 400, 500, 30);

        // Créer un QLineEdit pour permettre à l'utilisateur de saisir son pseudo
        itsPseudoLineEdit = new QLineEdit(this);
        itsPseudoLineEdit->setAlignment(Qt::AlignCenter);
        itsPseudoLineEdit->setGeometry(160, 550, 400, 30);

        // Appliquer un style personnalisé au QLineEdit pour l'apparence
        itsPseudoLineEdit->setStyleSheet("font-size: 18px;"
                                         "background-color: white;"
                                         "border: 2px solid black;"
                                         "border-radius: 10px;"
                                         "padding: 5px;"
                                         "color: black;");

        // Connecter le signal returnPressed() de itsPseudoLineEdit à un slot
        connect(itsPseudoLineEdit, &QLineEdit::returnPressed, this, &ScoreboardForm::onNameEntered);

        // Calculer la position X pour centrer les éléments
        int labelX = (width() - itsInstructionsLabel->width()) / 2;
        int lineEditX = (width() - itsPseudoLineEdit->width()) / 2;

        // Définir les positions X calculées
        itsInstructionsLabel->move(labelX, 400);
        itsPseudoLineEdit->move(lineEditX, 450);


        // Créer le bouton de validation
        enterButton = new QPushButton(this);
        QPixmap enterButtonImage(":/Assets/Assets/other/enter_key.png");
        enterButton->setIcon(enterButtonImage);
        enterButton->setStyleSheet("QPushButton { border: none; }");
        enterButton->setIconSize(QSize(200, 68)); // Définir la taille de l'icône du bouton
        enterButton->move(295, 500);
        // Connecter le signal clicked() du bouton à un slot
        connect(enterButton, &QPushButton::clicked, this, &ScoreboardForm::onNameEntered);
    }

    // Remplir le tableau de classement
    fillScoreboardTable();

    // --------------------------------------------------------------------------------------------------------------------------------

    repaint() ;
}

ScoreboardForm::~ScoreboardForm()
{
    delete ui;
    delete itsRankingTable;
    delete itsScoreBoard ;
}

void ScoreboardForm::onNameEntered()
{
    // Récupérer le texte saisi par l'utilisateur
    playerName = itsPseudoLineEdit->text();

    // Vérifier si le nom a déjà été validé
    if (playerName.isEmpty())
        return;

    // Masquer les instructions, la zone de saisie utilisateur et le bouton "Entrée"
    itsInstructionsLabel->hide();
    itsPseudoLineEdit->hide();
    enterButton->hide();

    // Désactiver le QLineEdit et le QPushButton
    itsPseudoLineEdit->setEnabled(false);
    enterButton->setEnabled(false);

    //Ajoute le joueur et son score dans le fichier JSON
    itsScoreBoard->addScore(playerName, playerScore);

    // Afficher le pseudo dans la console pour vérification
    qDebug() << "Pseudo: " << playerName;

    // Actualiser le tableau de classement
    fillScoreboardTable();
}


void ScoreboardForm::setSettingsTable()
{
    itsRankingTable->setObjectName("scoreboardTable"); // Définir un nom d'objet pour la QTableWidget
    itsRankingTable->setFixedSize(400, 200); // Définir la taille de la table
    itsRankingTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Désactiver l'édition des cellules
    itsRankingTable->setSelectionMode(QAbstractItemView::NoSelection); // Désactiver la sélection des cellules
    itsRankingTable->setFocusPolicy(Qt::NoFocus); // Désactiver le focus sur la table

    // Appliquer un style personnalisé pour arrondir les bords de la table et la couleur de fond
    itsRankingTable->setStyleSheet("QTableWidget { background-color: #9f4f0a; border: 1px solid black; }"
                                   "QHeaderView::section { background-color: #e7b12a; }"); // Changer la couleur du texte

    // Définir le nombre de colonnes
    itsRankingTable->setColumnCount(2);

    // Définir les en-têtes des colonnes
    QStringList headers;
    headers << "Player" << "Time";
    itsRankingTable->setHorizontalHeaderLabels(headers);

    // Centrer le texte et appliquer la couleur de fond aux en-têtes des colonnes
    QHeaderView* headerView = itsRankingTable->horizontalHeader();
    headerView->setDefaultAlignment(Qt::AlignCenter); // Centrer le texte des en-têtes des colonnes

    // Désactiver la possibilité de cliquer sur les noms des colonnes
    headerView->setSectionsClickable(false);

    // Masquer les numéros de lignes à gauche
    itsRankingTable->verticalHeader()->setVisible(false);

    // Définir le mode de redimensionnement des colonnes à "Stretch" pour les faire occuper toute la largeur
    headerView->setSectionResizeMode(QHeaderView::Stretch);

    // Étendre les lignes jusqu'en bas de la table
    itsRankingTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Centrer le texte et appliquer la couleur de fond aux cellules
    QTableWidgetItem* playerItem = new QTableWidgetItem("Player");
    playerItem->setTextAlignment(Qt::AlignCenter); // Centrer le texte de la cellule
    itsRankingTable->setItem(0, 0, playerItem);

    QTableWidgetItem* timeItem = new QTableWidgetItem("Time");
    timeItem->setTextAlignment(Qt::AlignCenter); // Centrer le texte de la cellule
    itsRankingTable->setItem(0, 1, timeItem);

    // Centrer la table au milieu de l'écran
    int tableX = (width() - itsRankingTable->width()) / 2;
    itsRankingTable->move(tableX, 175);
}
void ScoreboardForm::fillScoreboardTable()
{
    if (!itsRankingTable)
    return;

    // Récupérer les meilleurs joueurs et leurs temps à partir de ScoreBoard
    QList<QPair<QString, double>> topPlayers = itsScoreBoard->getTopPlayers(5);

    // Définir le nombre de lignes à 5
    itsRankingTable->setRowCount(5);

    for (int row = 0; row < topPlayers.count(); ++row)
    {
        // Récupérer les informations du joueur et du score
        QString playerName = topPlayers[row].first;
        double score = topPlayers[row].second;

        // Convertir le score en chaîne de caractères avec le format "X.X s"
        QString timeStr = QString::number(score, 'f', 1) + " s";

        // Créer un nouvel élément pour le nom du joueur
        QTableWidgetItem* playerItem = new QTableWidgetItem(playerName);
        playerItem->setTextAlignment(Qt::AlignCenter); // Centrer le texte de la cellule

        // Définir l'élément dans la colonne 0 de la ligne actuelle
        itsRankingTable->setItem(row, 0, playerItem);

        // Créer un nouvel élément pour le temps
        QTableWidgetItem* timeItem = new QTableWidgetItem(timeStr);
        timeItem->setTextAlignment(Qt::AlignCenter); // Centrer le texte de la cellule

        // Définir l'élément dans la colonne 1 de la ligne actuelle
        itsRankingTable->setItem(row, 1, timeItem);
    }
}


void ScoreboardForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter * painter = new QPainter(this);
    painter->drawImage(0, 0, itsBackground);
    painter->drawImage(0, height()-20, itsFloor);
    painter->drawImage(90, height()-20-45, itsMario);
    painter->drawImage(width() - 170, height()-20-86, itsBowser);
    delete painter;
}
