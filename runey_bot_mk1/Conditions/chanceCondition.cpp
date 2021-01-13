#include "chanceCondition.h"

ChanceCondition::ChanceCondition( double percentChance ) :
    _minPercentChance( percentChance ),
    _maxPercentChance( percentChance )
{
}

ChanceCondition::ChanceCondition( double minPercentChance, double maxPercentChance ) :
    _minPercentChance( minPercentChance ),
    _maxPercentChance( maxPercentChance )
{
}

bool ChanceCondition::checkCondition( BotInfo *info )
{
    return Util::genRandDouble( 100 ) <= Util::genRandDouble( _minPercentChance, _maxPercentChance );
}
