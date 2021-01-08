#ifndef CLICKITEMSTASK_H
#define CLICKITEMSTASK_H

//Qt
#include <QList>
#include <QPair>

#include "Tasks/task.h"

typedef QMap<int, int> Inventory;
typedef QMap<int, QPair<int, int>> RangedInventory;

class ClickItemsTask : public Task
{
public:
    ClickItemsTask( Inventory *items );
    ClickItemsTask( RangedInventory *items );
    ClickItemsTask( int item, int amount = 28 );
    ClickItemsTask( int item, int minAmount, int maxAmount );
    void execute( BotInfo *info ) override;

private:
    RangedInventory *_items;
};

#endif // CLICKITEMSTASK_H
