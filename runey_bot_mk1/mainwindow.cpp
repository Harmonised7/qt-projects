#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _screen( QGuiApplication::primaryScreen() ),
    _screenGeometry( _screen->geometry() )
{
    ui->setupUi(this);

    InventoryCondition *condition = new InventoryCondition( new DropItemsTask, 1, 5 );

    BotInstance *bot = new BotInstance( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT );
    bot->addCondition( condition );
    _botInstances.push_back( bot );
//    _botInstances.push_back( BotInstance( BAR_WIDTH + BORDER_SIZE, _screen->size().height() - RS_HEIGHT - BORDER_SIZE ) );
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testButton_clicked()
{
}
