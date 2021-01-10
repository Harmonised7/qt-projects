#include "stateCondition.h"

StateCondition::StateCondition( BotStates stateType, bool boolType ) :
    _stateType( stateType ),
    _boolType( boolType )
{
}

bool StateCondition::checkCondition( BotInfo *info )
{
    return info->states.value( _stateType ) == _boolType;
}
