/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QPushButton *unpauseButton;
    QPushButton *pauseButton;
    QPushButton *res1Button;
    QPushButton *res2Button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(160, 227);
        MainWindow->setMaximumSize(QSize(160, 320));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        unpauseButton = new QPushButton(centralwidget);
        unpauseButton->setObjectName(QString::fromUtf8("unpauseButton"));

        verticalLayout_4->addWidget(unpauseButton);

        pauseButton = new QPushButton(centralwidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));

        verticalLayout_4->addWidget(pauseButton);

        res1Button = new QPushButton(centralwidget);
        res1Button->setObjectName(QString::fromUtf8("res1Button"));

        verticalLayout_4->addWidget(res1Button);

        res2Button = new QPushButton(centralwidget);
        res2Button->setObjectName(QString::fromUtf8("res2Button"));

        verticalLayout_4->addWidget(res2Button);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 160, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        unpauseButton->setText(QApplication::translate("MainWindow", "unpauseAll", nullptr));
        pauseButton->setText(QApplication::translate("MainWindow", "pauseAll", nullptr));
        res1Button->setText(QApplication::translate("MainWindow", "1920x1080", nullptr));
        res2Button->setText(QApplication::translate("MainWindow", "1680x1050", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
