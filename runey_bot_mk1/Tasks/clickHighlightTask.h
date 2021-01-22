#ifndef CLICKHIGHLIGHTTASK_H
#define CLICKHIGHLIGHTTASK_H

#include <QPoint>
#include <QSet>

#include "Tasks/task.h"
#include "antiBanTask.h"

class ClickHighlightTask : public Task
{
public:
    ClickHighlightTask( cv::Vec3b pixel );
    ClickHighlightTask( cv::Vec3b p1, cv::Vec3b p2 );

    void execute( BotInfo *info ) override;

private:
    cv::Vec3b _p1, _p2;
};

#endif // CLICKHIGHLIGHTTASK_H
