#ifndef KEYBOARDTASK_H
#define KEYBOARDTASK_H

#include "Tasks/task.h"

class KeyboardTask : public Task
{
public:
    KeyboardTask( KeyboardStates state, std::string key, int minTsDelay = TSDELAY_MIN, int maxTsDelay = TSDELAY_MAX );

    void execute( BotInfo *info ) override;

private:
    KeyboardStates _state;
    std::string _key;
    int _minTsDelay, _maxTsDelay;
};

#endif // KEYBOARDTASK_H
