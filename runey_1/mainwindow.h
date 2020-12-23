#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Classes
#include <iteminfo.h>

// QT includes
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkReply>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QCompleter>
#include <QFile>
#include <QDebug>

// OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

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
    void on_lineEdit_textChanged(const QString &arg1);

    void on_listWidget_itemSelectionChanged();

public slots:
    void onResult(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    // Methods
    void init();

    // Objects //

    // Strings
    QCompleter *_stringCompleter;
    QString _urlString;
    QString _resultString;
    QStringList _itemStringList;

    // Networking
    QNetworkAccessManager _networkManager;
    QNetworkRequest _request;

    // Files
    QFile _rsJsonFile;
    QFile _osBuddyJsonFile;

    // Json
    json _json;

    // Items
    QMap<QString, Item> _itemMap;

    // Temp
};
#endif // MAINWINDOW_H
