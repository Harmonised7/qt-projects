#include "timerTask.h"

TimerTask::TimerTask( TimerOperation operation, TimerType type ) :
   _operation( operation ),
   _type( type )
{
}

void TimerTask::execute( BotInfo *info )
{
    if( _operation == TimerOperation::Pause )
        info->pauseTimer->pause();
    else if( _operation == TimerOperation::Start )
        info->pauseTimer->start();
    else if( _operation == TimerOperation::Stop )
        info->pauseTimer->stop();
    else if( _operation == TimerOperation::Restart )
        info->pauseTimer->restart();
}
