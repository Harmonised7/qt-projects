#include "highlightTask.h"

//#include "mainwindow.h"

using namespace cv;

HighlightTask::HighlightTask( Vec3b pixel, bool click ) :
    _p1( pixel ),
    _p2( pixel ),
    _click( click )
{
}

HighlightTask::HighlightTask( Vec3b p1, Vec3b p2, bool click ) :
    _p1( p1 ),
    _p2( p2 ),
    _click( click )
{
}

void HighlightTask::execute( BotInfo *info )
{
    BotInfo::updateFlood( info->gameMat( Rect( Point( 4, 4 ), Point( info->gameMat.cols, info->gameMat.rows ) ) ), &info->rsFloodMatches, _p1, _p2 );

//    for( QPoint *p : info->rsFloodMatches )
//    {
//        info->rsMat.at<Vec3b>( p->y(), p->x() ) = Vec3b( 255, 255, 255 );
//    }

//    imshow( "flood result", info->rsMat );

    int matchNumber = Util::genRand( info->rsFloodMatches.size() );
    if( matchNumber == 0 )
        return;
    QSet<QPoint>::iterator iterator = info->rsFloodMatches.begin();
    int i = 0;
    while( ++i < matchNumber )
    {
        iterator = iterator.operator++();
    }
    QPoint clickPoint = iterator.operator*();

//    rectangle( info->rsMat, Rect( clickPoint->x() - 3, clickPoint->y() - 3, 6, 6 ), Scalar( 255, 255, 255 ) );
    move_and_click:
    MouseController::mc.mouseMove( info->x + 4 + clickPoint.x(), info->y + 4 + clickPoint.y() );

    info->processScreen();
    BotInfo::updateFlood( info->gameMat( Rect( Point( 4, 4 ), Point( info->gameMat.cols, info->gameMat.rows ) ) ), &info->rsFloodMatches, _p1, _p2 );

    if( _click )
    {
        QPoint mousePos = MouseController::mc.getMousePos();
        QPoint relativeMousePos = QPoint( mousePos.x() - info->x, mousePos.y() - info->y );
//        qDebug() << "relative" << relativeMousePos;
//        qDebug() << "size" << info->rsFloodMatches.size();
//        if( info->rsFloodMatches.size() > 0 )
//            qDebug() << "First Element" << info->rsFloodMatches.begin().operator*();

        if( info->rsFloodMatches.contains( relativeMousePos ) )
        {
//            qDebug() << "match";
//            Mat testMat = Mat( info->rsMat.rows, info->rsMat.cols, CV_8UC3, Scalar( 0 ) );

//            for( QPoint pos : info->rsFloodMatches )
//            {
//                testMat.at<Vec3b>( pos.y(), pos.x() ) = Vec3b( 255 );
//            }

//            rectangle( testMat, Rect( relativeMousePos.x() - 5, relativeMousePos.y() - 5, 10, 10 ), Scalar( 255, 0, 255 ) );

//            imshow( "debug", testMat );
            MouseController::mc.setClickDelay( 200, 400 );
            MouseController::mc.mousePress( MouseState::Left );
            MouseController::mc.resetClickDelay();
        }
        else if( info->rsFloodMatches.size() > 0 )
        {
//            Sleeper::msleep( Util::genRand( 50, 200 ) );
//            goto move_and_click;
        }
    }

    if( Util::genRand( 1, 20 ) == 1 )
        AntiBanTask::doAntiBan( info );
}
