#include "changeTabTask.h"

using namespace cv;

ChangeTabTask::ChangeTabTask( int tab, bool goBack ) :
    _goBack( goBack )
{
    _tabs->insert( tab );
}

ChangeTabTask::ChangeTabTask( IntPair tabRange, bool goBack ) :
    _goBack( goBack )
{
    if( tabRange.first > tabRange.second )
    {
        int temp = tabRange.first;
        tabRange.first = tabRange.second;
        tabRange.first = temp;
    }

    for( int i = tabRange.first; i <= tabRange.second; i++ )
    {
        _tabs->insert( i );
    }
}

ChangeTabTask::ChangeTabTask( QSet<int> tabRange, bool goBack ) :
    _tabs( new QSet<int>( tabRange ) ),
    _goBack( goBack )
{
}

void ChangeTabTask::execute( BotInfo *info )
{
    _originTab = info->tabId;
    do  //Pick a tab that's not the current tab, if range exists
    {
        info->tabId = _tabs->values()[ Util::genRand( _tabs->size() - 1 ) ];
    }
    while( _tabs->size() > 1 && _originTab == info->tabId );
    MouseController::mc.mousePress( MouseState::Left, Util::genRandQPoint( Util::getInvTabRect( info->tabId ) ) + QPoint( info->x, info->y ) );

    if( _goBack )
    {
        Sleeper::msleep( Util::genRand( MIN_SLEEP, MAX_SLEEP ) );
        MouseController::mc.mousePress( MouseState::Left, Util::genRandQPoint( Util::getInvTabRect( _originTab ) ) + QPoint( info->x, info->y ) );
        info->tabId = _originTab;
    }
}
