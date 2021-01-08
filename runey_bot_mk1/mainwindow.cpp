#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _screen( QGuiApplication::primaryScreen() ),
    _screenGeometry( _screen->geometry() )
{
    ui->setupUi(this);

    _botInstances.push_back( BotFactory::makeWcBot( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT ) );
    _botInstances.push_back( BotFactory::makeMiningBot( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT + 510 ) );
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testButton_clicked()
{
}
