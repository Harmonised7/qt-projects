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
#include <QtWidgets/QHBoxLayout>
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
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pauseButton;
    QPushButton *unpauseButton;
    QPushButton *logoutButton;
    QPushButton *showButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(134, 229);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pauseButton = new QPushButton(centralwidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(pauseButton);

        unpauseButton = new QPushButton(centralwidget);
        unpauseButton->setObjectName(QString::fromUtf8("unpauseButton"));

        verticalLayout->addWidget(unpauseButton);

        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName(QString::fromUtf8("logoutButton"));

        verticalLayout->addWidget(logoutButton);

        showButton = new QPushButton(centralwidget);
        showButton->setObjectName(QString::fromUtf8("showButton"));

        verticalLayout->addWidget(showButton);


        horizontalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 134, 28));
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
        pauseButton->setText(QApplication::translate("MainWindow", "pauseAll", nullptr));
        unpauseButton->setText(QApplication::translate("MainWindow", "unpauseAll", nullptr));
        logoutButton->setText(QApplication::translate("MainWindow", "logoutAll", nullptr));
        showButton->setText(QApplication::translate("MainWindow", "showAll", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
