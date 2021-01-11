#ifndef TIMERTASK_H
#define TIMERTASK_H

#include "Tasks/task.h"

enum class TimerOperation
{
    Start,
    Pause,
    Stop
};

enum class TimerType
{
    PauseTimer
};

class TimerTask : public Task
{
public:
    TimerTask( TimerOperation operation, TimerType type = TimerType::PauseTimer );

    void execute( BotInfo *info ) override;

private:
    TimerOperation _operation;
    TimerType _type;
};

#endif // TIMERTASK_H
