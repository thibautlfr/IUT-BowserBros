#ifndef MENUFORM_H
#define MENUFORM_H

#include <QWidget>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include <QPaintEvent>
#include <list>

namespace Ui {
class MenuForm;
}

class MenuForm : public QWidget
{
    Q_OBJECT

public:
    QImage itsBackground;
    QImage itsFloor;
    QImage itsMario;
    QImage itsBowser;
    QImage itsGameTitle;

    explicit MenuForm(QWidget *parent = nullptr);
    ~MenuForm();

signals:
    void playButtonClicked();
    void quitButtonClicked();

private:
    Ui::MenuForm *ui;
    void paintEvent(QPaintEvent *event);
};

#endif // MENUFORM_H
