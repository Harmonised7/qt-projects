#include "tabCondition.h"

using namespace cv;

TabCondition::TabCondition( int tab, bool boolType ) :
    _tab( tab ),
    _boolType( boolType )
{
}

bool TabCondition::checkCondition( BotInfo *info )
{
    info->invTabId = BotInfo::getCurrentTab( info );
    if( _boolType )
        return info->invTabId == _tab;
    else
        return info->invTabId != _tab;
}
