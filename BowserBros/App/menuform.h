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
    explicit MenuForm(QWidget *parent = nullptr);
    ~MenuForm();

signals:
    void playButtonClicked();

private:
    Ui::MenuForm *ui;
};

#endif // MENUFORM_H
