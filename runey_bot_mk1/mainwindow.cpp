#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _screen( QGuiApplication::primaryScreen() ),
    _screenGeometry( _screen->geometry() ),
    _timer( new QElapsedTimer )
{
    ui->setupUi(this);

    _clickSafeArea = cv::Rect( BAR_WIDTH, BAR_HEIGHT, _screen->size().width() - BAR_WIDTH, _screen->size().height() - BAR_HEIGHT );
    _timer->start();
    _timeoutCondition = new TimeoutCondition( 3000, 30000 );

    _botInstances.push_back( BotFactory::makeGathererBot( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT ) );
//    _botInstances.push_back( BotFactory::makeGathererBot( BAR_WIDTH + BORDER_SIZE, BAR_HEIGHT + BORDER_HEIGHT + 510 ) );
//    _botInstances.push_back( BotFactory::makeGathererBot( BAR_WIDTH + BORDER_SIZE + 1040, BAR_HEIGHT + BORDER_HEIGHT ) );
//    _botInstances.push_back( BotFactory::makeGathererBot( BAR_WIDTH + BORDER_SIZE + 1040, BAR_HEIGHT + BORDER_HEIGHT + 510 ) );
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
