#ifndef INVENTORYCONDITION_H
#define INVENTORYCONDITION_H

#include "condition.h"

class InventoryCondition : public Condition
{
public:
    InventoryCondition( Inventory *items, bool up );
    InventoryCondition( RangedInventory *items, bool up );
    InventoryCondition( int item, bool up, int amount = 28 );
    InventoryCondition( int item, bool up, int minAmount, int maxAmount );
    bool checkCondition( BotInfo *info ) override;

private:
    Inventory *_items;
    RangedInventory *_itemRanges;

    bool _up;
};

#endif // INVENTORYCONDITION_H
