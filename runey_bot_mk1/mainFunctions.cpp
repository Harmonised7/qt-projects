#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

void MainWindow::init()
{
    _timer->start();
    Sleeper::msleep( 1000 );
    connect( &_refreshTimer, SIGNAL( timeout() ), this, SLOT( handleFrame() ) );
    _refreshTimer.start( 1000 / FPS );
}

void MainWindow::handleFrame()
{
    if( _frameFinished )
    {
        _frameFinished = false;
        if( _botsRunning )
        {
//            try
//            {
                for( BotInstance *bot : _botInstances )
                {
                    Mat mat = bot->handleFrame( Util::pixMapToMat( qApp->screens().at(0)->grabWindow( 0 ) ) );
    //                imshow( "bot", mat );
                }

                if( _timeoutCondition->checkCondition( _timer ) )
                    AntiBanTask::doAntiBan( _clickSafeArea );
//            }
//            catch( Exception e )
//            {
//                qDebug() << QString::fromStdString( e.msg );
//            }
        }
        _frameFinished = true;
    }
}
