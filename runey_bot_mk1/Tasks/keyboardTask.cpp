#include "keyboardTask.h"

KeyboardTask::KeyboardTask( KeyboardStates state, std::string key, int minTsDelay, int maxTsDelay ) :
    _state( state ),
    _key( key ),
    _minTsDelay( minTsDelay ),
    _maxTsDelay( maxTsDelay )
{
}

void KeyboardTask::execute( BotInfo *info )
{
    KeyboardController::kc.press( _state, _key, _minTsDelay, _maxTsDelay );
}
