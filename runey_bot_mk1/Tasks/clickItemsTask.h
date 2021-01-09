#ifndef CLICKITEMSTASK_H
#define CLICKITEMSTASK_H

//Qt
#include <QList>
#include <QPair>

#include "Tasks/task.h"

typedef QMap<int, int> Inventory;
typedef QPair<int, int> Range;
typedef QMap<int, Range> RangedInventory;

class ClickItemsTask : public Task
{
public:
    ClickItemsTask( Inventory *items );
    ClickItemsTask( RangedInventory *items );
    ClickItemsTask( int item, int amount = 28 );
    ClickItemsTask( int item, int minAmount, int maxAmount );
    void execute( BotInfo *info ) override;
    void setFailRate( int failRate );

private:
    RangedInventory *_items;
    int _failRate = 0;
};

#endif // CLICKITEMSTASK_H
