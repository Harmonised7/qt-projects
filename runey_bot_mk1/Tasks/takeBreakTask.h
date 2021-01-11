#ifndef TAKEBREAKTASK_H
#define TAKEBREAKTASK_H

#include "Tasks/task.h"

class TakeBreakTask : public Task
{
public:
    TakeBreakTask( unsigned long minBreakTime, unsigned long maxBreakTime );

    void execute( BotInfo *info ) override;

private:
    unsigned long _minBreakTime, _maxBreakTime;
};

#endif // TAKEBREAKTASK_H
