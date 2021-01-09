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
    doAntiBan( Util::RectFromTwoQPoints( info->tl(), info->br() ) );
}

void AntiBanTask::doAntiBan( Rect area )
{
    MouseController::mc.setSpeed( 0.002, 0.004 );
    MouseController::mc.setJitter( 1 );

    int type = Util::genRand( 1, 5 );

    if( Util::genRand( 1, 5 ) == 1 )
        KeyboardController::kc.pressKeyDown( "Right" );
    else if( Util::genRand( 1, 5 ) == 1 )
        KeyboardController::kc.pressKeyDown( "Left" );


    if( type <= 4 )
    {
        MouseController::mc.mouseMove( Util::genRandQPoint( area ) );
    }
    else if( type <= 6 )
    {
        Point rightClickPoint = Util::genRandPoint( area );
        MouseController::mc.mousePress( MouseStates::Right, Util::PointToQPoint( rightClickPoint ) );
        Sleeper::msleep( Util::genRand( 50, 300 ) );
        if( Util::genRand( 1, 2 ) == 1 )
            MouseController::mc.mouseMoveRelative( Util::genRandQPointOffset( Util::PointToQPoint( rightClickPoint ), 25 ) );
    }
    else if( type <= 7 )
    {
        Point middleClickPoint = area.tl() + Util::genRandPoint( Rect( BORDER_SIZE, BORDER_SIZE, RS_INNER_WIDTH, RS_INNER_WIDTH ) );
        MouseController::mc.mouseMove( Util::PointToQPoint( middleClickPoint ) );
        MouseController::mc.mouseDragRelative( MouseStates::Middle, Util::genRandQPointOffset( Util::PointToQPoint( middleClickPoint ), 10 ) );
    }

    if( Util::genRand( 1, 10 ) == 1 )
        doAntiBan( area );

    Sleeper::msleep( Util::genRand( 25, 125 ) );
    KeyboardController::kc.pressKeyUp( "Right" );
    KeyboardController::kc.pressKeyUp( "Left" );

    MouseController::mc.resetSpeed();
    MouseController::mc.resetJitter();
}
