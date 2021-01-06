#ifndef CONDITION_H
#define CONDITION_H

#include "Tasks/task.h"

//Qt
#include <QList>

//Other
#include "botinfo.h"

class Condition
{
public:
    virtual ~Condition() {};
    virtual bool checkCondition( BotInfo *info ) = 0;

private:
    QList<Task *> tasks;
};

#endif // CONDITION_H
