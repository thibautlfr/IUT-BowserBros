/********************************************************************************
** Form generated from reading UI file 'menuform.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUFORM_H
#define UI_MENUFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuForm
{
public:
    QPushButton *playButton;
    QPushButton *quitButton;

    void setupUi(QWidget *MenuForm)
    {
        if (MenuForm->objectName().isEmpty())
            MenuForm->setObjectName("MenuForm");
        MenuForm->resize(800, 600);
        MenuForm->setMaximumSize(QSize(800, 600));
        MenuForm->setAutoFillBackground(false);
        MenuForm->setStyleSheet(QString::fromUtf8("background-image: url(:Assets/Assets/background/background4.png);"));
        playButton = new QPushButton(MenuForm);
        playButton->setObjectName("playButton");
        playButton->setGeometry(QRect(270, 250, 225, 60));
        playButton->setMaximumSize(QSize(800, 600));
        playButton->setStyleSheet(QString::fromUtf8("QPushButton {border: none; padding: 0; margin: 0; background: transparent;}"));
        quitButton = new QPushButton(MenuForm);
        quitButton->setObjectName("quitButton");
        quitButton->setGeometry(QRect(270, 330, 224, 59));
        quitButton->setStyleSheet(QString::fromUtf8("QPushButton {border: none; padding: 0; margin: 0; background: transparent;}"));

        retranslateUi(MenuForm);

        QMetaObject::connectSlotsByName(MenuForm);
    } // setupUi

    void retranslateUi(QWidget *MenuForm)
    {
        MenuForm->setWindowTitle(QCoreApplication::translate("MenuForm", "Form", nullptr));
        playButton->setText(QString());
        quitButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MenuForm: public Ui_MenuForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUFORM_H
