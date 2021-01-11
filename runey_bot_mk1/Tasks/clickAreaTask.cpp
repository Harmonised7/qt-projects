#include "clickAreaTask.h"

using namespace cv;

ClickAreaTask::ClickAreaTask( MouseState state, Point p ) :
    _state( state ),
    _clickArea( Rect( p, p ) )
{
}

ClickAreaTask::ClickAreaTask( MouseState state, Rect area ) :
    _state( state ),
    _clickArea( area )
{
}

void ClickAreaTask::execute( BotInfo *info )
{
//    rectangle( info->rsMat, _clickArea, Scalar( 255, 255, 255 ) );
//    imshow( "click area task", info->rsMat );
    MouseController::mc.mousePress( _state, info->tl() + Util::genRandQPoint( _clickArea ) );
}
