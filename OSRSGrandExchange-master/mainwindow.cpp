#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _jsonFileObj(":/json/items/sources/json/Objects_87.json")
{
    ui->setupUi(this);

    // Init
    init();

    // Main code
}

MainWindow::~MainWindow()
{
    delete ui;
}
