#ifndef KEYBOARDTASK_H
#define KEYBOARDTASK_H

#include "Tasks/task.h"

enum class KeyboardTaskType
{
    Press = 0,
    Up = 1,
    Down = 2,
    Write = 3,
    MoveCamera = 4
};

class KeyboardTask : public Task
{
public:
    KeyboardTask( KeyboardTaskType state, std::string key, int minTsDelay = TSDELAY_MIN, int maxTsDelay = TSDELAY_MAX );

    void execute( BotInfo *info ) override;

    static void moveCamera( int minTime, int maxTime );

private:
    KeyboardTaskType _state;
    std::string _key;
    int _minTsDelay, _maxTsDelay;
};

#endif // KEYBOARDTASK_H
