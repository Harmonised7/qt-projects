#ifndef INVENTORYCONDITION_H
#define INVENTORYCONDITION_H

#include "condition.h"

typedef QMap<int, int> Inventory;
typedef QPair<int, int> Range;
typedef QMap<int, Range> RangedInventory;

class InventoryCondition : public Condition
{
public:
    InventoryCondition( Inventory *items, bool up );
    InventoryCondition( RangedInventory *items, bool up );
    InventoryCondition( int item, bool up, int amount = 28 );
    InventoryCondition( int item, bool up, int minAmount, int maxAmount );
    bool checkCondition( BotInfo *info );

private:
    Inventory *_items;
    RangedInventory *_itemRanges;

    bool _up;
};

#endif // INVENTORYCONDITION_H
