#ifndef DROPITEMSTASK_H
#define DROPITEMSTASK_H

//Qt
#include <QList>

#include "task.h"

typedef QMap<int, int> Inventory;

class DropItemsTask : public Task
{
public:
    DropItemsTask();
    void execute( BotInfo *info ) override;

private:
};

#endif // DROPITEMSTASK_H
