#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

void MainWindow::init()
{
    Sleeper::msleep( 2500 );
    connect( &_refreshTimer, SIGNAL( timeout() ), this, SLOT( handleFrame() ) );
    _refreshTimer.start( 1000 / FPS );
}

void MainWindow::handleFrame()
{
    int i = 0;
    for( BotInstance *bot : _botInstances )
    {
        Mat mat = bot->handleFrame( Util::pixMapToMat( qApp->screens().at(0)->grabWindow( QDesktopWidget().winId() ) ) );
//        imshow( "bot" + ++i, mat );
    }

    if( _timeoutCondition->checkCondition( _timer ) )
        AntiBanTask::doAntiBan( _clickSafeArea );
}
