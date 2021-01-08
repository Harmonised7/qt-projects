#ifndef ANTIBANTASK_H
#define ANTIBANTASK_H

#define RIGHTCLICK_SAFE_DOWN 16
#define RIGHTCLICK_SAFE_HORIZONTAL 6

#include "Tasks/task.h"

class AntiBanTask : public Task
{
public:
    AntiBanTask();

    void execute( BotInfo *info ) override;
    static void doAntiBan( BotInfo *info );
};

#endif // ANTIBANTASK_H
