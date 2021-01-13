#ifndef CHANCECONDITION_H
#define CHANCECONDITION_H

#include "Conditions/condition.h"

class ChanceCondition : public Condition
{
public:
    ChanceCondition( double percentChance );
    ChanceCondition( double minPercentChance, double maxPercentChance );

    bool checkCondition( BotInfo *info ) override;

private:
    unsigned long _minPercentChance, _maxPercentChance;
};

#endif // CHANCECONDITION_H
