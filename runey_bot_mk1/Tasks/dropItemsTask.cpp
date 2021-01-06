#include "Tasks/dropItemsTask.h"

DropItemsTask::DropItemsTask()
{
}

void DropItemsTask::execute( BotInfo *info )
{
    for( int i : BotInfo::_dropPatterns[ RndController::genRand( BotInfo::_dropPatterns.length() - 1 ) ] )
    {
        if( ( *info->getItems())[ i ] )
        {
            MouseController::_mc.mousePress( MouseStates::Left, RndController::genRandPoint( Util::getInvSlotRect( i ) ) + QPoint( info->x, info->y ), 50, 75 );
        }
    }
}
