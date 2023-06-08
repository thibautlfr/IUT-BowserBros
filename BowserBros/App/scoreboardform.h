#ifndef SCOREBOARDFORM_H
#define SCOREBOARDFORM_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class ScoreboardForm;
}

class ScoreboardForm : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreboardForm(QWidget *parent = nullptr);

    ~ScoreboardForm();

    QImage itsBackground; /**< The background image of the scoreboard form. */
    QImage itsFloor; /**< The floor image of the scoreboard form. */
    QImage itsMario; /**< The Mario image of the scoreboard form. */
    QImage itsBowser; /**< The Bowser image of the scoreboard form. */

signals:
    /**
      * @brief Signal emitted when the play button is clicked.
    */
    void playButtonClicked();

    /**
      * @brief Signal emitted when the quit button is clicked.
     */
    void quitButtonClicked();

private:
    Ui::ScoreboardForm *ui;

    /**
      * @brief Paints the scoreboard form.
      * @param event The QPaintEvent object.
     */
    void paintEvent(QPaintEvent *event);
};

#endif // SCOREBOARDFORM_H
