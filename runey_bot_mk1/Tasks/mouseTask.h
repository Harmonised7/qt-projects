#ifndef MOUSETASK_H
#define MOUSETASK_H

#include "Tasks/task.h"

enum class MouseTaskType
{
    MoveCamera,
    LeftClick,
    MoveRelative
};

class MouseTask : public Task
{
public:
    MouseTask( MouseTaskType type );

    void execute( BotInfo *info ) override;

    static void execute( MouseTaskType type, cv::Rect area );

private:
    MouseTaskType _type;
};

#endif // MOUSETASK_H
