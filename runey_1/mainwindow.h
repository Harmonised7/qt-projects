#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// QT includes
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkReply>
#include <QMessageBox>
#include "QDebug"

// OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

// Json includes
#include <nlohmann/json.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

public slots:
    void onResult(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    // Methods

    // Objects
    QString _urlString;
    int _itemCode;
    QNetworkAccessManager _networkManager;
    QNetworkRequest _request;
};
#endif // MAINWINDOW_H
