#include "dropItemsTask.h"

DropItemsTask::DropItemsTask()
{
}

void DropItemsTask::execute( BotInfo *info )
{
//    MouseController::_mc.mousePress( MouseStates::Left, Util::getMidPoint( cv::Rect( info->x + INV_X, info->y + INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 ) ), 50, 75 );
    for( int i : BotInfo::_dropPatterns[ RndController::genRand( BotInfo::_dropPatterns.length() - 1 ) ] )
    {
        if( ( *info->getItems())[ i ] )
        {
            MouseController::_mc.mousePress( MouseStates::Left, Util::getMidPoint( Util::getInvSlotRect( i ) ) + QPoint( info->x, info->y ), 50, 75 );
        }
    }
}
