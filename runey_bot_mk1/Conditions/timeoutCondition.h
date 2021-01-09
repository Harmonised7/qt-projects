#ifndef TIMEOUTCONDITION_H
#define TIMEOUTCONDITION_H

#include "Conditions/condition.h"

class TimeoutCondition : public Condition
{
public:
    TimeoutCondition( unsigned int minWaitTime, unsigned int maxWaitTime );

    bool checkCondition( BotInfo *info ) override;
    bool checkCondition( QElapsedTimer *timer );

private:
    unsigned long _minWaitTime, _maxWaitTime, _timeToWait, _lastTrigger;
};

#endif // TIMEOUTCONDITION_H
