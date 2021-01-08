#include "Tasks/clickItemsTask.h"

ClickItemsTask::ClickItemsTask( RangedInventory *items )
{
    _items = items;
}

ClickItemsTask::ClickItemsTask( Inventory *items )
{
    for( int item : items->keys() )
    {
        _items->insert( item, QPair<int, int>( items->value( item ), items->value( item ) ) );
    }
}

ClickItemsTask::ClickItemsTask( int item, int amount )
{
    _items = new RangedInventory();
    _items->insert( item, QPair<int, int>( amount, amount ) );
}

ClickItemsTask::ClickItemsTask( int item, int minAmount, int maxAmount )
{
    _items = new RangedInventory();
    _items->insert( item, QPair<int, int>( minAmount, maxAmount ) );
}

void ClickItemsTask::execute( BotInfo *info )
{    
    Inventory *items = info->invItems;
    Inventory *itemsToDrop = new Inventory();
    int item;

    for( int item : _items->keys() )
    {
        itemsToDrop->insert( item, Util::genRand( _items->value( item ).first, _items->value( item ).second ) );
    }

    for( int i : BotInfo::_dropPatterns[ Util::genRand( BotInfo::_dropPatterns.length() - 1 ) ] )
    {
        item = items->value( i );
        if( item && itemsToDrop->value( item ) > 0 )
        {
            itemsToDrop->insert( item, itemsToDrop->value( item ) - 1 );
            MouseController::mc.mousePress( MouseStates::Left, Util::genRandPoint( Util::getInvSlotRect( i ) ) + QPoint( info->x, info->y ), 50, 75 );
        }
    }
}
