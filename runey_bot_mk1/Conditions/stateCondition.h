#ifndef STATECONDITION_H
#define STATECONDITION_H

#include "Conditions/condition.h"

class StateCondition : public Condition
{
public:
    StateCondition( BotState stateType, bool boolType = 1 );

    bool checkCondition( BotInfo *info ) override;

private:
    BotState _stateType;
    bool _boolType;
};

#endif // STATECONDITION_H
