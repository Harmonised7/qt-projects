#include "clickHighlightTask.h"

using namespace cv;

ClickHighlightTask::ClickHighlightTask()
{

}

void ClickHighlightTask::execute( BotInfo *info )
{
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

    MouseController::mc.mousePress( MouseStates::Left, info->x + 4 + clickPoint->x(), info->y + 4 + clickPoint->y(), 50, 75 );

    int rand = Util::genRand( 1, 5 );
    if( rand == 1 )
        AntiBanTask::doAntiBan( info );
    else if( rand > 2 )
    {
        QPoint mousePos = MouseController::mc.getMousePos();
        MouseController::mc.mouseMove( mousePos.x() + Util::genRand( -20, 20 ), mousePos.y() + Util::genRand( -20, 20 ) );
    }
}
