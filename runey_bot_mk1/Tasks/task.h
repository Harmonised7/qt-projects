#ifndef TASK_H
#define TASK_H

#include "botinfo.h"
#include "mouseController.h"
#include "util.h"

class Task
{
public:
    virtual ~Task() {};
    virtual void execute( BotInfo *info ) = 0;
};

#endif // TASK_H
