#ifndef CONDITION_H
#define CONDITION_H

//Qt
#include <QList>

//Other
#include "util.h"
#include "botinfo.h"

class Condition
{
public:
    virtual ~Condition() {};
    virtual bool checkCondition( BotInfo *info ) = 0;
};

#endif // CONDITION_H
