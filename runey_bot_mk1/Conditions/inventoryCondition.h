#ifndef INVENTORYCONDITION_H
#define INVENTORYCONDITION_H

#include "condition.h"

typedef QMap<int, int> Inventory;

class InventoryCondition : public Condition
{
public:
    InventoryCondition( Inventory *items, const bool &up );
    InventoryCondition( const int &item, const bool &up, const int &amount = 28 );
    bool checkCondition( BotInfo *info );

private:
    Inventory *_items;
    bool _up;
};

#endif // INVENTORYCONDITION_H
