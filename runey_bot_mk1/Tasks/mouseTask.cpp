#include "mouseTask.h"

using namespace cv;

MouseTask::MouseTask( MouseTaskType type ) :
    _type( type )
{
}

void MouseTask::execute( BotInfo *info )
{
    if( _type == MouseTaskType::MoveCamera )
    {
        Point middleClickPoint = Point( info->x, info->y ) + Util::genRandPoint( Util::resizeRect( Rect( 4, 4, RS_INNER_WIDTH, RS_INNER_WIDTH ), -50 ) );
        MouseController::mc.mouseMove( Util::PointToQPoint( middleClickPoint ) );
        MouseController::mc.mouseDragRelative( MouseState::Middle, Util::genRandQPointOffset( Util::PointToQPoint( middleClickPoint ), 10 ) );
    }
    else if( _type == MouseTaskType::LeftClick )
        MouseController::mc.mousePress( MouseState::Left );
    else if( _type == MouseTaskType::MoveRelative )
        MouseController::mc.mouseMoveRelative( QPoint( Util::genRand( -20, 20 ), Util::genRand( 0, 20 ) ) );
}
