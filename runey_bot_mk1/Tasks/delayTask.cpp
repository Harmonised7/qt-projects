#include "delayTask.h"

DelayTask::DelayTask( unsigned int ms ) :
    _minMs( ms ),
    _maxMs( ms )
{
}

DelayTask::DelayTask( unsigned int minMs, unsigned int maxMs ) :
    _minMs( cv::min( minMs, maxMs ) ),
    _maxMs( cv::max( minMs, maxMs ) )
{
}

void DelayTask::execute( BotInfo *info )
{
    Sleeper::msleep( Util::genRand( _minMs, _maxMs ) );
}
