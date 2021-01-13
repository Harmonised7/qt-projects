#include "changeTabTask.h"

using namespace cv;

ChangeTabTask::ChangeTabTask( int tab, TabType type, bool goBack ) :
    _type( type ),
    _goBack( goBack )
{
    _tabs->insert( tab );
}

ChangeTabTask::ChangeTabTask( IntPair tabRange, TabType type, bool goBack ) :
    _type( type ),
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

ChangeTabTask::ChangeTabTask( QSet<int> tabRange, TabType type, bool goBack ) :
    _tabs( new QSet<int>( tabRange ) ),
    _type( type ),
    _goBack( goBack )
{
}

void ChangeTabTask::execute( BotInfo *info )
{
    int *currTabId;

    if( _type == TabType::Inventory )
        currTabId = &info->invTabId;
    else if( _type == TabType::Bottom )
        currTabId = &info->botTabId;
    else
    {
        qDebug() << "Unaccounted for TabType at ChangeTabTask::execute";
        return;
    }

    _originTab = *currTabId;

    do  //Pick a tab that's not the current tab, if range exists
    {
        *currTabId = _tabs->values()[ Util::genRand( _tabs->size() - 1 ) ];
    }
    while( _tabs->size() > 1 && _originTab == *currTabId );

    if( _type == TabType::Inventory )


    MouseController::mc.mousePress( MouseState::Left, Util::genRandQPoint( getTabRect( *currTabId, _type ) ) + QPoint( info->x, info->y ) );

    if( _goBack )
    {
        Sleeper::msleep( Util::genRand( MIN_SLEEP, MAX_SLEEP ) );
        MouseController::mc.mousePress( MouseState::Left, Util::genRandQPoint( getTabRect( _originTab, _type ) ) + QPoint( info->x, info->y ) );
        info->invTabId = _originTab;
    }
}

Rect ChangeTabTask::getTabRect( int tab, TabType type )
{
    if( type == TabType::Inventory )
        return Util::getInvTabRect( tab );
    else if( type == TabType::Bottom )
        return Util::getBotTabRect( tab );
    else
    {
        qDebug() << "Unaccounted for TabType at ChangeTabTask::getTabRect";
        return Rect();
    }
}
