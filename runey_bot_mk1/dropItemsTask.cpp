#include "dropItemsTask.h"

DropItemsTask::DropItemsTask( BotInfo *info )
{
    _info = info;
    _itemsToDrop = info->getItems();
}

void execute()
{
    //drop items
}
