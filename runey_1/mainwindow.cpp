#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _url(QString::fromLocal8Bit("https://secure.runescape.com/m=itemdb_oldschool/api/catalogue/detail.json?item=4151"))
{
    ui->setupUi(this);

    // Connections
    connect(&_networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onResult(QNetworkReply *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    _request.setUrl(_url);
    _networkManager.get(_request);  // GET
}
