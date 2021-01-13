#ifndef CHANGETABTASK_H
#define CHANGETABTASK_H

#define MIN_SLEEP 500
#define MAX_SLEEP 2500

#include "Tasks/task.h"

typedef QPair<int, int> IntPair;

enum class TabType
{
    Inventory,
    Bottom
};

class ChangeTabTask : public Task
{
public:
    ChangeTabTask( int tab,             TabType type, bool goBack = false );
    ChangeTabTask( IntPair tabRange,    TabType type, bool goBack = false );
    ChangeTabTask( QSet<int> tabRange,  TabType type, bool goBack = false );

    void execute( BotInfo *info ) override;
    static cv::Rect getTabRect( int tab, TabType type );

private:
    QSet<int> *_tabs = new QSet<int>();
    int _originTab;
    TabType _type;
    bool _goBack;
};

#endif // CHANGETABTASK_H
