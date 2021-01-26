#include "delayTask.h"

DelayTask::DelayTask( unsigned int ms ) :
    _minMs( ms ),
    _maxMs( ms )
{
}

DelayTask::DelayTask( unsigned int minMs, unsigned int maxMs ) :
    _minMs( Util::min( minMs, maxMs ) ),
    _maxMs( Util::max( minMs, maxMs ) )
{
}

void DelayTask::execute( BotInfo *info )
{
    Sleeper::msleep( Util::genRand( _minMs, _maxMs ) );
}
