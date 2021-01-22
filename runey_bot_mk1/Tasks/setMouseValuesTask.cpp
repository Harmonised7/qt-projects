#include "setMouseValuesTask.h"

SetMouseValuesTask::SetMouseValuesTask( MouseValueType type , double value ):
    _type( type ),
    _minValue( value ),
    _maxValue( value )
{

}


SetMouseValuesTask::SetMouseValuesTask( MouseValueType type, double minValue, double maxValue ) :
        _type( type ),
        _minValue( minValue ),
        _maxValue( maxValue )
{
}

void SetMouseValuesTask::execute( BotInfo *info )
{
    if( _type == MouseValueType::ClickDelay )
        MouseController::mc.setClickDelay( _minValue, _maxValue );
    else if( _type == MouseValueType::Jitter )
        MouseController::mc.setJitter( Util::genRand( _minValue, _maxValue ) );
    else if( _type == MouseValueType::Speed )
        MouseController::mc.setSpeed( _minValue, _maxValue );
}
