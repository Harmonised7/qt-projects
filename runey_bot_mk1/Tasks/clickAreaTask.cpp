#include "clickAreaTask.h"

using namespace cv;

ClickAreaTask::ClickAreaTask( MouseStates state, Point p ) :
    _state( state ),
    _clickArea( Rect( p, p ) )
{
}

ClickAreaTask::ClickAreaTask( MouseStates state, Rect area ) :
    _state( state ),
    _clickArea( area )
{
}

void ClickAreaTask::execute( BotInfo *info )
{
    MouseController::mc.mousePress( _state, Util::genRandQPoint( _clickArea ) );
}
