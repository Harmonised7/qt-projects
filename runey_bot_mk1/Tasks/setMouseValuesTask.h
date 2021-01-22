#ifndef SETMOUSEVALUESTASK_H
#define SETMOUSEVALUESTASK_H

#include "Tasks/task.h"

enum class MouseValueType
{
    Speed,
    Jitter,
    ClickDelay
};

class SetMouseValuesTask : public Task
{
public:
    SetMouseValuesTask( MouseValueType type, double value );
    SetMouseValuesTask( MouseValueType type, double minValue, double maxValue );

    void execute( BotInfo *info ) override;

private:
    MouseValueType _type;
    double _minValue, _maxValue;
};

#endif // SETMOUSEVALUESTASK_H
