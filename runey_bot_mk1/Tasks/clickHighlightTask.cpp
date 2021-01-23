#include "clickHighlightTask.h"

using namespace cv;

ClickHighlightTask::ClickHighlightTask( Vec3b pixel ) :
    _p1( pixel ),
    _p2( pixel )
{
}

ClickHighlightTask::ClickHighlightTask( Vec3b p1, Vec3b p2 ) :
    _p1( p1 ),
    _p2( p2 )
{
}

void ClickHighlightTask::execute( BotInfo *info )
{
    BotInfo::updateFlood( info->gameMat, &info->rsFloodMatches, _p1, _p2 );

//    for( QPoint *p : info->rsFloodMatches )
//    {
//        info->rsMat.at<Vec3b>( p->y(), p->x() ) = Vec3b( 255, 255, 255 );
//    }

//    imshow( "flood result", info->rsMat );

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

    rectangle( info->rsMat, Rect( clickPoint->x() - 3, clickPoint->y() - 3, 6, 6 ), Scalar( 255, 255, 255 ) );

    MouseController::mc.setClickDelay( 200, 400 );
    MouseController::mc.mousePress( MouseState::Left, info->x + 4 + clickPoint->x(), info->y + 4 + clickPoint->y() );
    MouseController::mc.resetClickDelay();

    if( Util::genRand( 1, 20 ) == 1 )
        AntiBanTask::doAntiBan( info );
    else if( Util::genRand( 1, 21 ) < 18 )
    {
        QPoint mousePos = MouseController::mc.getMousePos();
        MouseController::mc.setJitter( 1 );
        MouseController::mc.mouseMove( Util::genRandQPointOffset( mousePos, 20 ) );
        MouseController::mc.resetJitter();
    }
}
