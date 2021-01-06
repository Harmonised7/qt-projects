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

//    InventoryCondition *fullInvCondition = new InventoryCondition( 1, true, 5 );
//    ClickItemsTask *ClickItemsTask = new ClickItemsTask( 1, 3 );

    cv::Mat beer = Util::pixMapToMat( QPixmap( ":/icons/Images/Beer.png" ) );
    cv::Mat grapes = Util::pixMapToMat( QPixmap( ":/icons/Images/Grapes.png" ) );
    cv::Mat jugOfWater = Util::pixMapToMat( QPixmap( ":/icons/Images/Jug_of_water.png" ) );

    InventoryCondition *fullInvCondition = new InventoryCondition( 1, true, 1 );
    ClickItemsTask *ClickItemsTask = new ClickItemsTask( 1, 1 );

    Module *fullInvDropItemsModule = new Module( fullInvCondition, ClickItemsTask );

    BotInstance *bot = new BotInstance( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT );
//    bot->addModule( fullInvDropItemsModule );

    bot->addImage( 1, beer );
    bot->addImage( 2, grapes );
    bot->addImage( 3, jugOfWater );

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
