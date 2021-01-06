#include "Tasks/dropItemsTask.h"

DropItemsTask::DropItemsTask( Inventory *items )
{
    _items = items;
}

DropItemsTask::DropItemsTask( const int &item, const int &amount )
{
    _items = new Inventory();
    _items->insert( item, amount );
}

void DropItemsTask::execute( BotInfo *info )
{    
    Inventory *items = info->getItems();
    Inventory *itemsToDrop = new Inventory();
    int item;

    for( int item : _items->keys() )
    {
        itemsToDrop->insert( item, _items->value( item ) );
    }

    for( int i : BotInfo::_dropPatterns[ RndController::genRand( BotInfo::_dropPatterns.length() - 1 ) ] )
    {
        item = items->value( i );
        if( item && itemsToDrop->value( item ) > 0 )
        {
            itemsToDrop->insert( item, itemsToDrop->value( item ) - 1 );
            MouseController::_mc.mousePress( MouseStates::Left, RndController::genRandPoint( Util::getInvSlotRect( i ) ) + QPoint( info->x, info->y ), 50, 75 );
        }
    }
}
