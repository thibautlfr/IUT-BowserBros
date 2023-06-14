#include "soundsettingsform.h"
#include "qgraphicseffect.h"
#include "qpainter.h"
#include "ui_soundsettingsform.h"

#include <QFontDatabase>
#include <QDebug>
#include <QSettings>


SoundSettingsForm::SoundSettingsForm(QWidget *parent,  SoundManager *soundMenuManager) :
    QWidget(parent),
    menuSoundManager(soundMenuManager),
    ui(new Ui::SoundSettingsForm),
    settingsFile()
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


    // Initialise les valeurs des sliders avec les valeurs actuelles du SoundManager
    ui->generalVolumeSlider->setValue(static_cast<int>(100));
    ui->effectsVolumeSlider->setValue(static_cast<int>(100));

    // --------------------------------------------------------------------------------------------------------------------------------


    // Bouton menu
    QPixmap menuAsset(":/Assets/Assets/menu/menu.png");
    ui->finishedButton->setIcon(menuAsset);
    ui->finishedButton->setIconSize(QSize(200, 70));

    connect(ui->finishedButton, &QPushButton::clicked, this, &SoundSettingsForm::finished);

    // Bouton reprendre
    QPixmap restartAsset(":/Assets/Assets/menu/restart.png");
    ui->itsRestartButton->setIcon(restartAsset);
    ui->itsRestartButton->setIconSize(QSize(200, 70));

    connect(ui->itsRestartButton, &QPushButton::clicked, this, &::SoundSettingsForm::restarted);



    // --------------------------------------------------------------------------------------------------------------------------------

    // Créer l'effet d'ombre
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(1, 1);
    shadowEffect->setBlurRadius(2);


    // Charger la police depuis le fichier
    QString fontPath = ":Fonts/Fonts/policeMario2.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily, 22);

    // Créer le titre du widget
    itsTitle = new QLabel("REGLAGES", this);
    itsTitle->setStyleSheet("font-size: 35px; color: white;");
    itsTitle->setGraphicsEffect(shadowEffect);
    itsTitle->setFont(font);
    itsTitle->setAlignment(Qt::AlignCenter);
    itsTitle->setGeometry(30, 50, 740, 150 );
    itsTitle->show();

    //Crée les titres pour les sliders
    musicVolumeLabel = new QLabel("Volume Musique", this);
    effectsVolumeLabel = new QLabel("Volume FX", this);

    QFont labelFont = QFont(fontFamily, 8);
    musicVolumeLabel->setFont(labelFont);
    effectsVolumeLabel->setFont(labelFont);
    musicVolumeLabel->setStyleSheet("QLabel { color : rgb(223,178,73); }");
    effectsVolumeLabel->setStyleSheet("QLabel { color : rgb(223,178,73); }");

    // --------------------------------------------------------------------------------------------------------------------------------

    #if defined _WIN32
        settingsFile.open("../../Settings/settings.txt", std::ios::in);
    #elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
        settingsFile.open("../../../../../Settings/settings.txt", std::ios::in);
    #endif

    loadSettings();
}


SoundSettingsForm::~SoundSettingsForm()
{
    delete ui;
    saveSettings();
}

void SoundSettingsForm::on_generalVolumeSlider_valueChanged(int value)
{
    //En fonction de la valeur du sliders, divise par 100 pour avoir la valeur comprise entre 0 et 1
    menuSoundManager->setMainVolume(static_cast<float>(value) / 100.0f);
}

void SoundSettingsForm::on_effectsVolumeSlider_valueChanged(int value)
{
    menuSoundManager->setEffectsVolume(static_cast<float>(value) / 100.0f);
}

void SoundSettingsForm::paintEvent(QPaintEvent *event)
{
    // Si on est en pause, on affiche le bouton pour reprendre, sinon on le cache
    if(isOnPaused)
    {
        ui->itsRestartButton->show();
    }
    else
    {
        ui->itsRestartButton->hide();
    }

    Q_UNUSED(event);
    QPainter * painter = new QPainter(this);
    painter->drawImage(0, 0, itsBackground);
    painter->drawImage(0, height()-20, itsFloor);
    painter->drawImage(90, height()-20-45, itsMario);
    painter->drawImage(width() - 170, height()-20-86, itsBowser);

    // Code pour dessiner le rectangle
    int rectWidth = 400;  // largeur du rectangle
    int rectHeight = 200; // hauteur du rectangle
    int rectX = (width() - rectWidth) / 2;  // position x du rectangle (centré horizontalement)
    int rectY = (height() - rectHeight) / 2;  // position y du rectangle (centré verticalement)
    QRect rect(rectX, rectY, rectWidth, rectHeight);
    painter->setPen(Qt::NoPen); // Pas de bordure
    painter->setBrush(QColor(149,83,32)); // Couleur du rectangle
    painter->drawRect(rect);  // dessine le rectangle

    // Code pour positionner les sliders
    int sliderWidth = rectWidth - 80; // largeur du slider (un peu moins large que le rectangle pour un peu de marge)
    int sliderHeight = 20; // hauteur du slider
    int sliderX = rectX + (rectWidth - sliderWidth) / 2; // position x du slider (centré horizontalement dans le rectangle)
    int sliderY1 = rectY + rectHeight / 4 + 10; // position y du slider (un peu en dessous du label)
    int sliderY2 = rectY + 3 * rectHeight / 4 + 10; // position y du deuxième slider (un peu en dessous du deuxième label)
    ui->generalVolumeSlider->move(sliderX, sliderY1);
    ui->generalVolumeSlider->resize(sliderWidth, sliderHeight);
    ui->effectsVolumeSlider->move(sliderX, sliderY2);
    ui->effectsVolumeSlider->resize(sliderWidth, sliderHeight);

    // Code pour positionner les labels
    int labelWidth = sliderWidth;  // largeur du label (même largeur que le slider)
    int labelHeight = 30;  // hauteur du label (vous pouvez ajuster cela à votre convenance)
    int labelX = sliderX;  // position x du label (aligné avec le slider)
    int labelY1 = sliderY1 - labelHeight - 10;  // position y du label (au-dessus du slider, avec une petite marge)
    int labelY2 = sliderY2 - labelHeight - 10;  // position y du deuxième label (au-dessus du deuxième slider, avec une petite marge)
    musicVolumeLabel->move(labelX, labelY1);
    musicVolumeLabel->resize(labelWidth, labelHeight);
    effectsVolumeLabel->move(labelX, labelY2);
    effectsVolumeLabel->resize(labelWidth, labelHeight);

    delete painter;
}

bool SoundSettingsForm::getIsOnPaused() const
{
    return isOnPaused;
}

void SoundSettingsForm::setIsOnPaused(bool newIsOnPaused)
{
    isOnPaused = newIsOnPaused;
}

// Méthode pour sauvegarder les paramètres
void SoundSettingsForm::saveSettings()
{
    // Ouvrir le fichier en écriture
    settingsFile.open("../../Settings/settings.txt", std::ios::out);

    if (settingsFile.is_open())
    {
        // Convertir les valeurs des curseurs en chaînes de caractères
        std::string line = std::to_string(ui->generalVolumeSlider->value()) + ';' + std::to_string(ui->effectsVolumeSlider->value());

        // Écrire la ligne dans le fichier
        settingsFile << line;

        // Fermer le fichier
        settingsFile.close();
    }
    else
    {
        // Erreur lors de l'ouverture du fichier
        qDebug() << "Erreur lors de l'ouverture du fichier pour sauvegarder les paramètres";
            return;
    }
}


// Méthode pour restaurer les paramètres
void SoundSettingsForm::loadSettings()
{
    if (settingsFile.is_open())
    {
        // Lire la première ligne du fichier
        std::string line;
        getline(settingsFile, line);

        // Convertir la ligne en QString
        QString qLine = QString::fromStdString(line);
        qDebug() << qLine;

        // Diviser la ligne en deux parties
        QStringList volume = qLine.split(';');

        // Vérifier s'il y a deux parties
        if (volume.size() == 2)
        {
            // Récupérer les valeurs des curseurs à partir des parties divisées
            ui->generalVolumeSlider->setValue(volume[0].toFloat());
            ui->effectsVolumeSlider->setValue(volume[1].toFloat());
        }

        // Fermer le fichier
        settingsFile.close();
    }
    else
    {
        // Fichier non ouvert, les paramètres n'existent pas
        qDebug() << "Paramètres non existants, création du fichier lors de la fermeture du jeu";
        ui->generalVolumeSlider->setValue(50);
        ui->effectsVolumeSlider->setValue(50);
        return;
    }
}




