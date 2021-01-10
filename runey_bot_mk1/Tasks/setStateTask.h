#ifndef SETSTATETASK_H
#define SETSTATETASK_H

#include "Tasks/task.h"

class SetStateTask : public Task
{
public:
    SetStateTask( BotStates stateType, int newState );

    void execute( BotInfo *info ) override;

private:
    BotStates _stateType;
    int _newState;
};

#endif // SETSTATETASK_H
