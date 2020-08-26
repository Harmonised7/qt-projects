#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _urlString("https://secure.runescape.com/m=itemdb_oldschool/api/catalogue/detail.json?item="),
    _itemCode(0)
{
    ui->setupUi(this);

    this->window()->setFixedSize(this->window()->size());

    // Connections
    connect(&_networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onResult(QNetworkReply *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    _request.setUrl(QUrl(_urlString + QString::number(_itemCode)));
    _networkManager.get(_request);  // GET
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    _itemCode = arg1;
}
