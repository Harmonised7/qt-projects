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
            Mat screen = Util::pixMapToMat( qApp->screens().at(0)->grabWindow( 0 ) );
            try
            {
                QList<int> botKeys = _botInstances.keys();
                while( botKeys.size() > 0 )
                {
                    int botKeyIndex = Util::genRand( 0, botKeys.size() - 1 );
                    int botKey = botKeys[ botKeyIndex ];
                    /*Mat mat = */_botInstances.value( botKey )->handleFrame( screen.clone() );
//                    imshow( "bot", mat );
                    botKeys.remove( botKeyIndex );
//                    qDebug() << botKey;
                }

                if( _timeoutCondition->checkCondition( _timer ) )
                    AntiBanTask::doAntiBan( _clickSafeArea );
            }
            catch( Exception e )
            {
                qDebug() << QString::fromStdString( e.msg );
            }

            screen.release();
        }
        _frameFinished = true;
    }
}
