#include "changeTabTask.h"

using namespace cv;

ChangeTabTask::ChangeTabTask( int tab, bool goBack ) :
    _tab( tab ),
    _goBack( goBack )
{
}

void ChangeTabTask::execute( BotInfo *info )
{
    info->tabId = _tab;
    MouseController::mc.mousePress( MouseStates::Left, Util::genRandQPoint( Util::getInvTabRect( _tab ) ) + QPoint( info->x, info->y ) );

    if( _goBack )
    {
        Sleeper::msleep( Util::genRand( MIN_SLEEP, MAX_SLEEP ) );
        MouseController::mc.mousePress( MouseStates::Left, Util::genRandQPoint( Util::getInvTabRect( _originTab ) ) + QPoint( info->x, info->y ) );
        info->tabId = _originTab;
    }
}
