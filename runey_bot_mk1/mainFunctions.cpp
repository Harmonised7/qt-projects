#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

void MainWindow::init()
{
    connect( &_refreshTimer, SIGNAL( timeout() ), this, SLOT( handleFrame() ) );
    _refreshTimer.start( 1000 / FPS );
}

void MainWindow::handleFrame()
{
    int i = 0;

    for( BotInstance *bot : _botInstances )
    {
        if( i++ == 0 )
        {
            ui->videoLabel->setPixmap( bot->handleFrame( Util::pixMapToMat( qApp->screens().at(0)->grabWindow( QDesktopWidget().winId() ) ) ) );
        }
//        else
//        {
//            ui->videoLabel_2->setPixmap( botInstance.handleFrame( Util::pixMapToMat( qApp->screens().at(0)->grabWindow( QDesktopWidget().winId() ) ) ) );
//        }
    }
}
