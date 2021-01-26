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

    int maxAttempts = Util::genRand( 1, 8 );
    int attempts = 0;

    move_and_click:
    int matchNumber = Util::genRand( info->rsFloodMatches.size() );
    if( matchNumber == 0 )
        return;
    QSet<QPoint *>::iterator iterator = info->rsFloodMatches.begin();
    int i = 0;
    while( ++i < matchNumber )
    {
        iterator = iterator.operator++();
    }

    QPoint *clickPoint = iterator.operator*();

//    rectangle( info->rsMat, Rect( clickPoint->x() - 3, clickPoint->y() - 3, 6, 6 ), Scalar( 255, 255, 255 ) );
    MouseController::mc.mouseMove( info->x + 4 + clickPoint->x(), info->y + 4 + clickPoint->y() );

    info->processScreen();
    BotInfo::updateFlood( info->gameMat( Rect( Point( 4, 4 ), Point( info->gameMat.cols, info->gameMat.rows ) ) ), &info->rsFloodMatches, _p1, _p2 );

    if( _click )
    {
        if( attempts <= maxAttempts )
        {
            QPoint mousePos = MouseController::mc.getMousePos();
            QPoint relativeMousePos = QPoint( mousePos.x() - info->x, mousePos.y() - info->y );

            bool matched = false;
            for( QPoint *pos : info->rsFloodMatches )
            {
                if( relativeMousePos == *pos )
                {
                    matched = true;
                    break;
                }
            }

            if( matched )
            {
                MouseController::mc.setClickDelay( 200, 400 );
                MouseController::mc.mousePress( MouseState::Left );
                MouseController::mc.resetClickDelay();
            }
            else
            {
                attempts++;
                goto move_and_click;
            }
        }

        if( attempts > maxAttempts )
           MouseTask::execute( MouseTaskType::MoveCamera, Util::resizeRect( Rect( info->x + 4, info->y + 4, RS_INNER_WIDTH, RS_INNER_WIDTH ), -50 ) );

    }

    if( Util::genRand( 1, 20 ) == 1 )
        AntiBanTask::doAntiBan( info );
}
