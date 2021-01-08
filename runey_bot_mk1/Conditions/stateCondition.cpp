#include "stateCondition.h"

StateCondition::StateCondition( int stateType, bool boolType ) :
    _stateType( stateType ),
    _boolType( boolType )
{
}

bool StateCondition::checkCondition( BotInfo *info )
{
    if( _stateType == 1 )
         return info->wcState == _boolType;
    if( _stateType == 2 )
        return info->miningState == _boolType;

    return false;
}
