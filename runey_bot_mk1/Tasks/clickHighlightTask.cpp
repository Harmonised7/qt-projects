#include "clickHighlightTask.h"

using namespace cv;

ClickHighlightTask::ClickHighlightTask()
{

}

void ClickHighlightTask::execute( BotInfo *info )
{
    BotInfo::updateFlood( info->rsMat( Rect( 0, 0, RS_INNER_WIDTH, RS_INNER_HEIGHT ) ).clone(), &info->rsFloodMatches );

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

    MouseController::mc.setClickDelay( 750, 1250 );
    MouseController::mc.mousePress( MouseStates::Left, info->x + 4 + clickPoint->x(), info->y + 4 + clickPoint->y() );
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
