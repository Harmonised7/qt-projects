#ifndef SETSTATETASK_H
#define SETSTATETASK_H

#include "Tasks/task.h"

class SetStateTask : public Task
{
public:
    SetStateTask( BotState stateType, bool newState );

    void execute( BotInfo *info ) override;

private:
    BotState _stateType;
    int _newState;
};

#endif // SETSTATETASK_H
