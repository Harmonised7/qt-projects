#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

// Json includes
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

    // Objects
    QCompleter *_stringCompleter;
    QString _urlString;
    QString _resultString;
    QStringList _itemStringList;
    QMap<QString, int> idMap;
    int _itemCode;
    QNetworkAccessManager _networkManager;
    QNetworkRequest _request;
    QFile _jsonFile;
    json _json;
};
#endif // MAINWINDOW_H
