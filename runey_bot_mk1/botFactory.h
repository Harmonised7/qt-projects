#ifndef BOTFACTORY_H
#define BOTFACTORY_H

#include "botInstance.h"

//Condition Includes
#include "Conditions/condition.h"
#include "Conditions/inventoryCondition.h"
#include "Conditions/timeoutCondition.h"
#include "Conditions/stateCondition.h"
#include "Conditions/tabCondition.h"

//Task Includes
#include "Tasks/task.h"
#include "Tasks/clickItemsTask.h"
#include "Tasks/clickHighlightTask.h"
#include "Tasks/antiBanTask.h"
#include "Tasks/changeTabTask.h"

typedef QPair<int, int> IntPair;

class BotFactory
{
public:
    static BotInstance *makeGathererBot( int botX, int botY );

};

#endif // BOTFACTORY_H
