#include "mouseTask.h"

using namespace cv;

MouseTask::MouseTask( MouseTaskType type ) :
    _type( type )
{
}
void MouseTask::execute( BotInfo *info )
{
    execute( _type, Util::resizeRect( Rect( info->x + 4, info->y + 4, RS_INNER_WIDTH, RS_INNER_WIDTH ), -50 ) );
}

void MouseTask::execute( MouseTaskType type, Rect area )
{
    if( type == MouseTaskType::MoveCamera )
    {
        Point middleClickPoint = Util::genRandPoint( area );
        MouseController::mc.mouseMove( Util::PointToQPoint( middleClickPoint ) );
        MouseController::mc.mouseDragRelative( MouseState::Middle, Util::genRandQPointOffset( Util::PointToQPoint( middleClickPoint ), 10 ) );
    }
    else if( type == MouseTaskType::LeftClick )
        MouseController::mc.mousePress( MouseState::Left );
    else if( type == MouseTaskType::MoveRelative )
        MouseController::mc.mouseMoveRelative( QPoint( Util::genRand( -20, 20 ), Util::genRand( 5, 25 ) ) );
}
