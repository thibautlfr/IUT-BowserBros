#ifndef TRAININGFORM_H
#define TRAININGFORM_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class TrainingForm;
}

class TrainingForm : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingForm(QWidget *parent = nullptr);
    ~TrainingForm();

    QImage itsBackground; /**< The background image of the scoreboard form. */
    QImage itsFloor; /**< The floor image of the scoreboard form. */
    QImage itsMario; /**< The Mario image of the scoreboard form. */
    QImage itsBowser; /**< The Bowser image of the scoreboard form. */

public slots:
    void level1ButtonClicked(); /**< Slot for handling the level 1 button clicked event. */
    void level2ButtonClicked(); /**< Slot for handling the level 2 button clicked event. */
    void level3ButtonClicked(); /**< Slot for handling the level 3 button clicked event. */
    void level4ButtonClicked(); /**< Slot for handling the level 4 button clicked event. */
    void level5ButtonClicked(); /**< Slot for handling the level 5 button clicked event. */

signals:
    /**
     * @brief Signal emitted when the menu button is clicked.
     */
    void menuButtonClicked();

    /**
     * @brief Signal emitted when a level button is clicked.
     * @param level The number of level which is selected
     */
    void levelSelected(int level);

private:
    Ui::TrainingForm *ui;

    /**
     * @brief Paints the scoreboard form.
     * @param event The QPaintEvent object.
     */
    void paintEvent(QPaintEvent *event);
};

#endif // TRAININGFORM_H
