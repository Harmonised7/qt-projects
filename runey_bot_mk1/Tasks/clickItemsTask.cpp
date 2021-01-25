#include "Tasks/clickItemsTask.h"

ClickItemsTask::ClickItemsTask( RangedInventory *items )
{
    _items = items;
}

ClickItemsTask::ClickItemsTask( Inventory *items )
{
    for( int item : items->keys() )
    {
        _items->insert( item, IntPair( items->value( item ), items->value( item ) ) );
    }
}

ClickItemsTask::ClickItemsTask( int item, int amount )
{
    _items = new RangedInventory();
    _items->insert( item, IntPair( amount, amount ) );
}

ClickItemsTask::ClickItemsTask( int item, int minAmount, int maxAmount )
{
    _items = new RangedInventory();
    _items->insert( item, IntPair( minAmount, maxAmount ) );
}

void ClickItemsTask::setFailRate( int failRate )
{
    _failRate = failRate;
}

void ClickItemsTask::execute( BotInfo *info )
{
    BotInfo::updateInventory( info );

    Inventory *items = info->invItems;
    Inventory *itemsToDrop = new Inventory();
    int item;

    MouseController::mc.setSpeed( 0.02, 0.05 );

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
            if( Util::genRand( 1, 100 ) < 100 - _failRate )
                MouseController::mc.mousePress( MouseState::Left, Util::genRandQPoint( Util::getInvSlotRect( i ) ) + QPoint( info->x, info->y ) );
        }
    }

    MouseController::mc.resetSpeed();
}
