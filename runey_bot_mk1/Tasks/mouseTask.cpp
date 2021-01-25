#include "mouseTask.h"

using namespace cv;

MouseTask::MouseTask( MouseTaskType type ) :
    _type( type )
{
}

void MouseTask::execute( BotInfo *info )
{
    Point middleClickPoint = Point( info->x, info->y ) + Util::genRandPoint( Rect( 4, 4, RS_INNER_WIDTH, RS_INNER_WIDTH ) );
    MouseController::mc.mouseMove( Util::PointToQPoint( middleClickPoint ) );
    MouseController::mc.mouseDragRelative( MouseState::Middle, Util::genRandQPointOffset( Util::PointToQPoint( middleClickPoint ), 10 ) );
}
