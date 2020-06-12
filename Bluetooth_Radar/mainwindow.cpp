#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->window()->setFixedSize( this->window()->size() );
}

MainWindow::~MainWindow()
{
    delete ui;
}



