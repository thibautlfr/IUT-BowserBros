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
    void level1ButtonClicked();
    void level2ButtonClicked();
    void level3ButtonClicked();
    void level4ButtonClicked();

signals:
    /**
     * @brief Signal emitted when the menu button is clicked.
     */
    void menuButtonClicked();

    void levelSelected(int level);

private:
    Ui::TrainingForm *ui;

    void paintEvent(QPaintEvent *event);
};

#endif // TRAININGFORM_H
