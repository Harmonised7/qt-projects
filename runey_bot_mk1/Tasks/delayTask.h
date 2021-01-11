#ifndef DELAYTASK_H
#define DELAYTASK_H

#include "Tasks/task.h"

class DelayTask : public Task
{
public:
    DelayTask( unsigned int ms );
    DelayTask( unsigned int minMs, unsigned int maxMs );

    void execute( BotInfo *info ) override;

private:
    unsigned int _startMs, _minMs, _maxMs;
};

#endif // DELAYTASK_H
