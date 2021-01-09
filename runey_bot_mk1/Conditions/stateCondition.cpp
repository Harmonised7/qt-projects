#include "stateCondition.h"

StateCondition::StateCondition( int stateType, bool boolType ) :
    _stateType( stateType ),
    _boolType( boolType )
{
}

bool StateCondition::checkCondition( BotInfo *info )
{
    if( _stateType == 1 )
         return info->gatherState == _boolType;

    return false;
}
