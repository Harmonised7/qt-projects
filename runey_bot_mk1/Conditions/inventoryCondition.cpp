#include "Conditions/inventoryCondition.h"

InventoryCondition::InventoryCondition( const int &item, const int &amount ) :
    _item( item ),
    _amount( amount )
{
}

bool InventoryCondition::checkCondition( BotInfo *info )
{
    return info->getItems()->size() >= _amount;
//    return info->getItems()->keys().contains( _item ) && (*info->getItems())[ _item ] >= _amount;
}
