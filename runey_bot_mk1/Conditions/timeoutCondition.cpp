#include "timeoutCondition.h"

TimeoutCondition::TimeoutCondition( unsigned int minWaitTime, unsigned int maxWaitTime ) :
    _minWaitTime( minWaitTime ),
    _maxWaitTime( maxWaitTime ),
    _timeToWait( Util::genRand( minWaitTime, maxWaitTime ) )
{

}

bool TimeoutCondition::checkCondition( BotInfo *info )
{
    return checkCondition( info->timer );
}

bool TimeoutCondition::checkCondition( Timer *timer )
{
    if( timer->elapsed() - _lastTrigger >= _timeToWait )
    {
        _timeToWait = Util::genRand( _minWaitTime, _maxWaitTime );
        _lastTrigger = timer->elapsed();
        return true;
    }
    return false;
}
