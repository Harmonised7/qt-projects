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

    _botInstances.push_back( BotFactory::makeGathererBot( _leftX, _topY, StrPair( "s6cskills@mail.com", "einblicke" ) ) );
    _botInstances.push_back( BotFactory::makeGathererBot( _leftX, _botY, StrPair( "s7cskills@mail.com", "einblicke" ) ) );
    _botInstances.push_back( BotFactory::makeGathererBot( _rightX, _topY, StrPair( "s8cskills@mail.com", "einblicke" ) ) );
    _botInstances.push_back( BotFactory::makeGathererBot( _rightX, _botY, StrPair( "s9cskills@mail.com", "einblicke" ) ) );

    _clickSafeArea = cv::Rect( BAR_WIDTH, BAR_HEIGHT, _screen->size().width() - BAR_WIDTH, _screen->size().height() - BAR_HEIGHT );
    _timeoutCondition = new TimeoutCondition( 3000, 30000 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_unpauseButton_clicked()
{
    init();
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
        qDebug() << "Set resolution to 1920x1080";
        _rightX = _screen->size().width() - RUNELITE_WIDTH - BORDER_SIZE;
        _leftX = BAR_WIDTH + BORDER_SIZE;
        _botY = _screen->size().height() - RUNELITE_HEIGHT - BORDER_SIZE;
        _topY = _botY - 510;
    }
    else if( width == 1600 && height == 1200 )
    {
        qDebug() << "Set resolution to 1600x1200";
        _rightX = 831;
        _leftX = 14;
        _botY = 693;
        _topY = 61;
    }
    else
        qDebug() << "WARNING WRONG RESOLUTION" << width << height;
}

void MainWindow::on_showButton_clicked()
{
        Mat screen = Util::pixMapToMat( qApp->screens().at(0)->grabWindow( QDesktopWidget().winId() ) );

        rectangle( screen, Rect( _leftX, _topY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );
        rectangle( screen, Rect( _leftX, _botY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );
        rectangle( screen, Rect( _rightX, _topY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );
        rectangle( screen, Rect( _rightX, _botY, RUNELITE_WIDTH, RUNELITE_HEIGHT ), Scalar( 255, 255, 255 ) );

        imshow( "test", screen );
}
