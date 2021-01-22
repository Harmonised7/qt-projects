#ifndef BOTFACTORY_H
#define BOTFACTORY_H

#include "botInstance.h"

//Condition Includes
#include "Conditions/condition.h"
#include "Conditions/inventoryCondition.h"
#include "Conditions/timeoutCondition.h"
#include "Conditions/stateCondition.h"
#include "Conditions/tabCondition.h"
#include "Conditions/imageCondition.h"
#include "Conditions/pixelsCondition.h"
#include "Conditions/chanceCondition.h"

//Task Includes
#include "Tasks/task.h"
#include "Tasks/clickItemsTask.h"
#include "Tasks/clickImagesTask.h"
#include "Tasks/clickHighlightTask.h"
#include "Tasks/clickAreaTask.h"
#include "Tasks/antiBanTask.h"
#include "Tasks/changeTabTask.h"
#include "Tasks/keyboardTask.h"
#include "Tasks/setStateTask.h"
#include "Tasks/delayTask.h"
#include "Tasks/takeBreakTask.h"
#include "Tasks/timerTask.h"
#include "Tasks/setMouseValuesTask.h"

class BotFactory
{
public:
    static BotInstance *makeGathererBot( QPoint pos, StrPair loginInfo, bool dropper = true );
    static BotInstance *makeKillerBot( QPoint pos, StrPair loginInfo );

    static void addGathererModules( BotInstance *bot, bool dropper );
    static void addKillerModules( BotInstance *bot );

    static void addEssentialModules( BotInstance *bot );
    static void addLoginModules( BotInstance *bot );
    static void addPauseModules( BotInstance *bot );
    static void addRunOnModules( BotInstance *bot );

    static void addDebugModules( BotInstance *bot );
};

#endif // BOTFACTORY_H
