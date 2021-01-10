#include "setStateTask.h"

SetStateTask::SetStateTask( BotStates stateType, int newState ) :
    _stateType( stateType ),
    _newState( newState )
{
}

void SetStateTask::execute( BotInfo *info )
{
    info->states.insert( _stateType, _newState );
}
