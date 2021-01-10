#ifndef STATECONDITION_H
#define STATECONDITION_H

#include "Conditions/condition.h"

class StateCondition : public Condition
{
public:
    StateCondition( BotStates stateType, bool boolType = 0 );

    bool checkCondition( BotInfo *info ) override;

private:
    BotStates _stateType;
    bool _boolType;
};

#endif // STATECONDITION_H
