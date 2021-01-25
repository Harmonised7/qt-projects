#ifndef HIGHLIGHTTASK_H
#define HIGHLIGHTTASK_H

#include <QPoint>
#include <QSet>

#include "Tasks/task.h"
#include "antiBanTask.h"

class HighlightTask : public Task
{
public:
    HighlightTask( cv::Vec3b pixel, bool click = true );
    HighlightTask( cv::Vec3b p1, cv::Vec3b p2, bool click = true );

    void execute( BotInfo *info ) override;

private:
    cv::Vec3b _p1, _p2;
    bool _click;
};

#endif // HIGHLIGHTTASK_H
