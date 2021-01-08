#include "antiBanTask.h"

using namespace cv;

AntiBanTask::AntiBanTask()
{
}

void AntiBanTask::execute( BotInfo *info )
{
    doAntiBan( info );
}

void AntiBanTask::doAntiBan( BotInfo *info )
{
    MouseController::mc.changeSpeed( 0.004, 0.002 );
    MouseController::mc.changeJitter( 1 );

    int type = Util::genRand( 1, 3 );

    if( type == 1 )
    {
        MouseController::mc.mouseMove( info->tl() + Util::genRandPoint( info->rsMat ) );
    }
    else if( type == 2 )
    {
        QPoint rightClickPoint = info->tl() + Util::genRandPoint( info->rsMat );
        MouseController::mc.mousePress( MouseStates::Right, rightClickPoint, 50, 75 );
        Sleeper::msleep( Util::genRand( 50, 300 ) );
        if( Util::genRand( 1, 3 ) == 1 )
            MouseController::mc.mousePress( MouseStates::Right, QPoint( rightClickPoint.x() + Util::genRand( -RIGHTCLICK_SAFE_HORIZONTAL, RIGHTCLICK_SAFE_HORIZONTAL ), rightClickPoint.y() - 2 - Util::genRand( RIGHTCLICK_SAFE_DOWN ) ), 50, 75 );
    }
    else if( type == 3 )
    {
//        while( Util::genRand( 1, 2 ) != 1 )
//        {
//            QPoint middleClickPoint1 = info->tl() + Util::genRandPoint( Rect( BORDER_SIZE, BORDER_SIZE, RS_INNER_WIDTH, RS_INNER_WIDTH ) );
//            QPoint middleClickPoint2 = QPoint( middleClickPoint1.x() + Util::genRand( -MOUSE_MOVE_DISTANCE, MOUSE_MOVE_DISTANCE ), Util::genRand( -MOUSE_MOVE_DISTANCE, MOUSE_MOVE_DISTANCE ) );
//            MouseController::mc.mouseMove( middleClickPoint1 );
//            MouseController::mc.mouseDrag( MouseStates::Middle, middleClickPoint2, 50, 75 );
//        }
    }

    if( Util::genRand( 1, 10 ) == 1 )
        doAntiBan( info );
    MouseController::mc.resetSpeed();
    MouseController::mc.resetJitter();
}
