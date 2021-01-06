#ifndef DROPITEMSTASK_H
#define DROPITEMSTASK_H

//Qt
#include <QList>

#include "Tasks/task.h"

typedef QMap<int, int> Inventory;

class DropItemsTask : public Task
{
public:
    DropItemsTask( Inventory *items );
    DropItemsTask( const int &item, const int &amount = 28 );
    void execute( BotInfo *info ) override;

private:
    Inventory *_items;
};

#endif // DROPITEMSTASK_H
