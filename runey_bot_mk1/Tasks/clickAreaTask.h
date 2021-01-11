#ifndef CLICKTASK_H
#define CLICKTASK_H

#include "Tasks/task.h"

class ClickAreaTask : public Task
{
public:
    ClickAreaTask( MouseState state, cv::Point p );
    ClickAreaTask( MouseState state, cv::Rect area );

    void execute( BotInfo *info ) override;

private:
    MouseState _state;
    cv::Rect _clickArea;
};

#endif // CLICKTASK_H
