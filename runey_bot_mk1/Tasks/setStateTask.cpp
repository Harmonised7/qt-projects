#include "setStateTask.h"

SetStateTask::SetStateTask( BotState stateType, bool newState ) :
    _stateType( stateType ),
    _newState( newState )
{
}

void SetStateTask::execute( BotInfo *info )
{
    if( _stateType == BotState::Login )
        qDebug() << "Login state set to" << _newState;
    info->states.insert( _stateType, _newState );
}
