#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _screen( QGuiApplication::primaryScreen() ),
    _screenGeometry( _screen->geometry() )
{
    ui->setupUi(this);

    _botInstances.push_back( new BotInstance( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT ) );
//    _botInstances.push_back( BotInstance( BAR_WIDTH + BORDER_SIZE, _screen->size().height() - RS_HEIGHT - BORDER_SIZE ) );
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testButton_clicked()
{
    _botInstances[0]->dropItems();
}
