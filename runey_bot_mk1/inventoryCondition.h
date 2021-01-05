#ifndef INVENTORYCONDITION_H
#define INVENTORYCONDITION_H

#include "condition.h"

class InventoryCondition : public Condition
{
public:
    InventoryCondition( Task *task, const int &item, const int &amount = 1 );
    bool checkCondition( BotInfo *info );
    void execute( BotInfo *info );

private:
    Task *_task;
    int _item;
    int _amount;
};

#endif // INVENTORYCONDITION_H
