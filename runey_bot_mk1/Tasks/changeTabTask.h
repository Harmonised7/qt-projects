#ifndef CHANGETABTASK_H
#define CHANGETABTASK_H

#define MIN_SLEEP 500
#define MAX_SLEEP 2500

#include "Tasks/task.h"

typedef QPair<int, int> IntPair;

class ChangeTabTask : public Task
{
public:
    ChangeTabTask( int tab, bool goBack = false );
    ChangeTabTask( IntPair tabRange, bool goBack = false );
    ChangeTabTask( QSet<int> tabRange, bool goBack = false );

    void execute( BotInfo *info ) override;

private:
    QSet<int> *_tabs = new QSet<int>();
    int _originTab;
    bool _goBack;
};

#endif // CHANGETABTASK_H
