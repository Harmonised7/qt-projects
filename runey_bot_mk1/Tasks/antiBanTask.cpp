#include "antiBanTask.h"

using namespace cv;

AntiBanTask::AntiBanTask( int region, bool doMouse, bool doKeyboard ) :
    _region( region ),
    _doMouse( doMouse ),
    _doKeyboard( doKeyboard )
{
}

void AntiBanTask::execute( BotInfo *info )
{
    if( _region == 2 )
        doAntiBan( Util::RectFromTwoQPoints( info->tl(), info->br() ), _doMouse, _doKeyboard );
    else
        doAntiBan( Rect( INV_SLOTS_X, INV_SLOTS_Y, INV_SLOT_WIDTH*4, INV_SLOT_HEIGHT*7 ), _doMouse, _doKeyboard );
}

void AntiBanTask::doAntiBan( BotInfo *info, bool doMouse, bool doKeyboard )
{
    doAntiBan( Util::RectFromTwoQPoints( info->tl(), info->br() ), doMouse, doKeyboard );
}

void AntiBanTask::doAntiBan( Rect area, bool doMouse, bool doKeyboard )
{
    if( doKeyboard )
    {
        int keyboardType = Util::genRand( 1, 5 );

        if( keyboardType == 1 )
            KeyboardController::kc.press( KeyboardState::Down, "Right" );
        else if( keyboardType == 2 )
            KeyboardController::kc.press( KeyboardState::Down, "Left" );

        if( Util::genRand( 1, 10 ) <= 7 )
            KeyboardController::kc.press( KeyboardState::Down, "Up" );

        Sleeper::msleep( Util::genRand( 25, 75 ) );
        if( Util::genRand( 1, 17 ) < 8 )
        {
            KeyboardController::kc.press( KeyboardState::Up, "Right" );
            KeyboardController::kc.press( KeyboardState::Up, "Left" );
            KeyboardController::kc.press( KeyboardState::Up, "Up" );
        }
    }

    if( doMouse )
    {
        MouseController::mc.setSpeed( 0.002, 0.004 );
        MouseController::mc.setJitter( 1 );

        int type = Util::genRand( 1, 5 );

        if( type <= 4 )
        {
            MouseController::mc.mouseMove( Util::genRandQPoint( area ) );
        }
        else if( type <= 6 )
        {
            Point rightClickPoint = Util::genRandPoint( area );
            MouseController::mc.mousePress( MouseState::Right, Util::PointToQPoint( rightClickPoint ) );
            Sleeper::msleep( Util::genRand( 50, 250 ) );
            if( Util::genRand( 1, 2 ) == 1 )
                MouseController::mc.mouseMoveRelative( Util::genRandQPointOffset( Util::PointToQPoint( Util::movePoint( rightClickPoint, 0, 30 ) ), 25 ) );
        }
        else if( type <= 7 )
        {
            Point middleClickPoint = area.tl() + Util::genRandPoint( Rect( 4, 4, RS_INNER_WIDTH, RS_INNER_WIDTH ) );
            MouseController::mc.mouseMove( Util::PointToQPoint( middleClickPoint ) );
            MouseController::mc.mouseDragRelative( MouseState::Middle, Util::genRandQPointOffset( Util::PointToQPoint( middleClickPoint ), 10 ) );
        }

        MouseController::mc.resetSpeed();
        MouseController::mc.resetJitter();
    }

    if( Util::genRand( 1, 10 ) == 1 )
        doAntiBan( area, doMouse, doKeyboard );

    if( doKeyboard )
    {
        KeyboardController::kc.press( KeyboardState::Up, "Right" );
        KeyboardController::kc.press( KeyboardState::Up, "Left" );
        KeyboardController::kc.press( KeyboardState::Up, "Up" );
    }

    Sleeper::msleep( Util::genRand( 25, 75 ) );
}
