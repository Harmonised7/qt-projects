#ifndef BOTFACTORY_H
#define BOTFACTORY_H

#include "botInstance.h"

//Condition Includes
#include "Conditions/condition.h"
#include "Conditions/inventoryCondition.h"
#include "Conditions/timeoutCondition.h"
#include "Conditions/stateCondition.h"

//Task Includes
#include "Tasks/task.h"
#include "Tasks/clickItemsTask.h"
#include "Tasks/clickHighlightTask.h"
#include "Tasks/antiBanTask.h"

class BotFactory
{
public:
    static BotInstance *makeWcBot( int botX, int botY );
    static BotInstance *makeMiningBot( int botX, int botY );

};

#endif // BOTFACTORY_H
