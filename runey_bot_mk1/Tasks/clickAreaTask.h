#ifndef CLICKTASK_H
#define CLICKTASK_H

#include "Tasks/task.h"

class ClickAreaTask : public Task
{
public:
    ClickAreaTask( MouseStates state, cv::Point p );
    ClickAreaTask( MouseStates state, cv::Rect area );

    void execute( BotInfo *info ) override;

private:
    MouseStates _state;
    cv::Rect _clickArea;
};

#endif // CLICKTASK_H
