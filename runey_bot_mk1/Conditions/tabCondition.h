#ifndef TABCONDITION_H
#define TABCONDITION_H

#include "Conditions/condition.h"

class TabCondition : public Condition
{
public:
    TabCondition( int tab, bool boolType = true );

    bool checkCondition( BotInfo *info ) override;

private:
    int _tab = 0;
    bool _boolType;
};

#endif // TABCONDITION_H
