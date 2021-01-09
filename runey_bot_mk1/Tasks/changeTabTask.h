#ifndef CHANGETABTASK_H
#define CHANGETABTASK_H

#define MIN_SLEEP 500
#define MAX_SLEEP 2500

#include "Tasks/task.h"

class ChangeTabTask : public Task
{
public:
    ChangeTabTask( int tab, bool goBack = true );

    void execute( BotInfo *info ) override;

private:
    int _tab, _originTab;
    bool _goBack;
};

#endif // CHANGETABTASK_H
