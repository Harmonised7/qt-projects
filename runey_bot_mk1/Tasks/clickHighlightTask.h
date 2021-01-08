#ifndef CLICKHIGHLIGHTTASK_H
#define CLICKHIGHLIGHTTASK_H

#include <QPoint>
#include <QSet>

#include "Tasks/task.h"
#include "antiBanTask.h"

class ClickHighlightTask : public Task
{
public:
    ClickHighlightTask();

    void execute( BotInfo *info ) override;
};

#endif // CLICKHIGHLIGHTTASK_H
