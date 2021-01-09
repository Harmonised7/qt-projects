#include "Conditions/inventoryCondition.h"

InventoryCondition::InventoryCondition( Inventory *items, bool up ) :
    _items( items ),
    _up( up )
{
    _itemRanges = new RangedInventory;
    for( int item : items->keys() )
    {
        _itemRanges->insert( item, IntPair( items->value( item ), items->value( item ) ) );
    }
}

InventoryCondition::InventoryCondition( RangedInventory *itemRanges, bool up ) :
    _itemRanges( itemRanges ),
    _up( up )
{
    _itemRanges = new RangedInventory;
    for( int item : itemRanges->keys() )
    {
        _items->insert( item, Util::genRand( itemRanges->value( item ).first, itemRanges->value( item ).second ) );
    }
}

InventoryCondition::InventoryCondition( int item, bool up, int amount) :
    _up( up )
{
    _items = new Inventory();
    _itemRanges = new RangedInventory;
    _items->insert( item, amount );
    _itemRanges->insert( item, IntPair( amount, amount ) );
}

InventoryCondition::InventoryCondition( int item, bool up, int minAmount, int maxAmount ) :
    _up( up )
{
    _items = new Inventory();
    _itemRanges = new RangedInventory;
    _items->insert( item, Util::genRand( minAmount, maxAmount ) );
    _itemRanges->insert( item, IntPair( minAmount, maxAmount ) );
}

bool InventoryCondition::checkCondition( BotInfo *info )
{
    BotInfo::updateInventory( info );
    Inventory itemsFound;

    //init items found
    for( int item : _items->keys() )
    {
        itemsFound[ item ] = 0;
    }

    //count relevant items
    for( int item : info->invItems->values() )
    {
        if( _items->contains( item ) )
            ++itemsFound[ item ];
    }

    //check if conditions met
    for( int item : _items->keys() )
    {
        //If looking for enough items, and found less than required OR
        //If looking for lack of items, and found more than required
        if( (  _up && itemsFound[ item ] < _items->value( item ) ) ||
            ( !_up && itemsFound[ item ] > _items->value( item ) ) )
            return false;
    }

    //Look for new item amounts now
    for( int item : _itemRanges->keys() )
    {
        _items->insert( item, Util::genRand( _itemRanges->value( item ).first, _itemRanges->value( item ).second ) );
    }

    return true;
}
