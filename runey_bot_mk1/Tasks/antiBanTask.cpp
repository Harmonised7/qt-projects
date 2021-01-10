#include "antiBanTask.h"

using namespace cv;

AntiBanTask::AntiBanTask( int region ) :
    _region( region )
{
}

void AntiBanTask::execute( BotInfo *info )
{
    if( _region == 2 )
        doAntiBan( Util::RectFromTwoQPoints( info->tl(), info->br() ) );
    else
        doAntiBan( Rect( INV_SLOTS_X, INV_SLOTS_Y, INV_SLOT_WIDTH*4, INV_SLOT_HEIGHT*7 ) );
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
    int keyboardType = Util::genRand( 1, 5 );

    if( keyboardType == 1 )
        KeyboardController::kc.press( KeyboardStates::Down, "Right" );
    else if( keyboardType == 2 )
        KeyboardController::kc.press( KeyboardStates::Down, "Left" );

    if( Util::genRand( 1, 10 ) == 1 )
        KeyboardController::kc.press( KeyboardStates::Down, "Up" );

    Sleeper::msleep( Util::genRand( 25, 75 ) );
    if( Util::genRand( 1, 17 ) < 8 )
    {
        KeyboardController::kc.press( KeyboardStates::Up, "Right" );
        KeyboardController::kc.press( KeyboardStates::Up, "Left" );
        KeyboardController::kc.press( KeyboardStates::Up, "Up" );
    }

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

    Sleeper::msleep( Util::genRand( 25, 75 ) );
    KeyboardController::kc.press( KeyboardStates::Up, "Right" );
    KeyboardController::kc.press( KeyboardStates::Up, "Left" );
    KeyboardController::kc.press( KeyboardStates::Up, "Up" );

    MouseController::mc.resetSpeed();
    MouseController::mc.resetJitter();
}
