#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Native Qt
#include <QMainWindow>
#include <QCompleter>
#include <QDebug>
#include <QFile>

// Json
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>

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

private:
    // Objects
    Ui::MainWindow *ui;

    QFile _jsonFileObj;
    json _jsonObj;
    QStringList _itemStringList;
    QCompleter *_stringCompleter;

    // Methods
    void init();
};
#endif // MAINWINDOW_H
