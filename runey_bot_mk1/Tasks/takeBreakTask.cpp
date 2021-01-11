#include "takeBreakTask.h"

using namespace cv;

TakeBreakTask::TakeBreakTask( unsigned long minBreakTime, unsigned long maxBreakTime ) :
    _minBreakTime( minBreakTime ),
    _maxBreakTime( maxBreakTime )
{
}

void TakeBreakTask::execute( BotInfo *info )
{
    info->states.insert( BotState::Pause, true );
    info->pauseLength = Util::genRand( _minBreakTime, _maxBreakTime );
    info->pauseCount++;

    KeyboardController::kc.press( KeyboardState::Press, "Escape" );

    Mat logoutDoor = Util::pixMapToMat( QPixmap( ":/icons/Images/Logout_door.png" ) );
    Mat logoutButton = Util::pixMapToMat( QPixmap( ":/icons/Images/Logout_button.png" ) );

    Rect logoutDoorArea = Rect( Point( LOGOUT_DOOR_X1, LOGOUT_DOOR_Y1 ), Point( LOGOUT_DOOR_X2, LOGOUT_DOOR_Y2 ) );
    Rect logoutButtonArea = Rect( Point( LOGOUT_BUTTON_X1, LOGOUT_BUTTON_Y1 ), Point( LOGOUT_BUTTON_X2, LOGOUT_BUTTON_Y2 ) );

    bool matches = info->rsMat.at<Vec3b>( LOGOUT_BUTTON_LINE_Y, LOGOUT_BUTTON_LINE_X )[2] > 150;

//    qDebug() << matches;

//    rectangle( info->rsMat, logoutDoorArea, Scalar( 255, 0, 255 ) );
//    rectangle( info->rsMat, logoutButtonArea, Scalar( 0, 255, 0 ) );
//    imshow( "breaktime", info->rsMat );

    qDebug() << "Taking break #" << info->pauseCount << info->pauseLength;
    MouseController::mc.mousePress( MouseState::Left, info->tl() + Util::genRandQPoint( matches ? logoutButtonArea : logoutDoorArea ) );
}
