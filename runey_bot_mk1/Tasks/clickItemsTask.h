#ifndef CLICKITEMSTASK_H
#define CLICKITEMSTASK_H

//Qt
#include <QList>

#include "Tasks/task.h"

typedef QMap<int, int> Inventory;

class ClickItemsTask : public Task
{
public:
    ClickItemsTask( Inventory *items );
    ClickItemsTask( const int &item, const int &amount = 28 );
    void execute( BotInfo *info ) override;

private:
    Inventory *_items;
};

#endif // CLICKITEMSTASK_H
