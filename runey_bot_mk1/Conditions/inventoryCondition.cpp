#include "Conditions/inventoryCondition.h"

InventoryCondition::InventoryCondition( Inventory *items, const bool &up ) :
    _items( items ),
    _up( up )
{

}

InventoryCondition::InventoryCondition( const int &item, const bool &up, const int &amount ) :
    _up( up )
{
    _items = new Inventory();
    _items->insert( item, amount );
}

bool InventoryCondition::checkCondition( BotInfo *info )
{
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

    return true;
}
