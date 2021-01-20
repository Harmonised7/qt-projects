#ifndef TASK_H
#define TASK_H

//Controller Includes
#include "Controllers/mouseController.h"
#include "Controllers/keyboardController.h"

//Util Includes
#include "Util/defines.h"
#include "Util/util.h"
#include "Util/sleeper.h"

//Other Includes
#include "botinfo.h"

class Task
{
public:
    virtual ~Task() {};
    virtual void execute( BotInfo *info ) = 0;
};

#endif // TASK_H
