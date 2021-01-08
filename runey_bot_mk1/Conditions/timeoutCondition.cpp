#include "timeoutCondition.h"

TimeoutCondition::TimeoutCondition( unsigned int minWaitTime, unsigned int maxWaitTime ) :
    _minWaitTime( minWaitTime ),
    _maxWaitTime( maxWaitTime ),
    _timeToWait( Util::genRand( minWaitTime, maxWaitTime ) )
{

}

bool TimeoutCondition::checkCondition( BotInfo *info )
{
//    qDebug() << _timeToWait - (info->timer->elapsed() - _lastTrigger);
    if( info->timer->elapsed() - _lastTrigger >= _timeToWait )
    {
        _timeToWait = Util::genRand( _minWaitTime, _maxWaitTime );
        _lastTrigger = info->timer->elapsed();
        return true;
    }
    return false;
}
