#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

using namespace cv;

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _screen( QGuiApplication::primaryScreen() ),
    _screenGeometry( _screen->geometry() ),
    _timer( new Timer )
{
    ui->setupUi(this);
    setRes();

    _clickSafeArea = cv::Rect( BAR_WIDTH, BAR_HEIGHT, _screen->size().width() - BAR_WIDTH, _screen->size().height() - BAR_HEIGHT );
    _timer->start();
    _timeoutCondition = new TimeoutCondition( 3000, 30000 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_unpauseButton_clicked()
{
    Mat screen = Util::pixMapToMat( qApp->screens().at(0)->grabWindow( QDesktopWidget().winId() ) );

    rectangle( screen, Rect( _leftX, _topY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );
    rectangle( screen, Rect( _leftX, _botY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );
    rectangle( screen, Rect( _rightX, _topY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );
    rectangle( screen, Rect( _rightX, _botY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );

    imshow( "test", screen );
//    init();
//    for( BotInstance *bot : _botInstances )
//    {
//        bot->info->states.insert( BotState::Pause, false );
//    }
}

void MainWindow::on_pauseButton_clicked()
{
    for( BotInstance *bot : _botInstances )
    {
        bot->info->states.insert( BotState::Pause, true );
    }
}

void MainWindow::setRes()
{
    int width = _screen->size().width();
    int height = _screen->size().height();

    if( width == 1920 && height == 1080 )
    {
        //1920x1080
        _rightX = _screen->size().width() - RUNELITE_WIDTH - BORDER_SIZE;
        _leftX = BAR_WIDTH + BORDER_SIZE;
        _botY = _screen->size().height() - RUNELITE_HEIGHT - BORDER_SIZE;
        _topY = _botY - 510;
    }
    else if( width == 1680 && height == 1050 )
    {
        //1680x1050

    }
}
