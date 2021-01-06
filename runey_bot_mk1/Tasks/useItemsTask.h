#ifndef USEITEMSTASK_H
#define USEITEMSTASK_H


//Qt
#include <QList>
#include <QtMath>

#include "Tasks/task.h"

typedef QMap<int, int> Inventory;

class UseItemsTask : public Task
{
public:
    UseItemsTask( const int &item1 = 1, const int &item2 = 2, const int &times = 1 );
    void execute( BotInfo *info ) override;

private:
    int _item1, _item2, _times;
};

#endif // USEITEMSTASK_H
