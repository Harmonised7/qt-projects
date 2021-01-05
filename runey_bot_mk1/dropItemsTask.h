#ifndef DROPITEMSTASK_H
#define DROPITEMSTASK_H

//Qt
#include <QList>

#include "task.h"

typedef QMap<int, int> Inventory;

class DropItemsTask : public Task
{
public:
    DropItemsTask( BotInfo *info );
    void execute( BotInfo *info ) override;

private:
    BotInfo *_info;
    Inventory *_itemsToDrop;
};

#endif // DROPITEMSTASK_H
