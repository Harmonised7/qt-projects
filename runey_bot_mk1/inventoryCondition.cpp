#include "inventoryCondition.h"

InventoryCondition::InventoryCondition( Task *task, const int &item, const int &amount ) :
    _task( task ),
    _item( item ),
    _amount( amount )
{
}

bool InventoryCondition::checkCondition( BotInfo *info )
{
    return info->getItems()->size() >= _amount;
//    return info->getItems()->keys().contains( _item ) && (*info->getItems())[ _item ] >= _amount;
}

void InventoryCondition::execute( BotInfo *info )
{
    _task->execute( info );
}
