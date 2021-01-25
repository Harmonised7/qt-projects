#include "keyboardTask.h"

KeyboardTask::KeyboardTask( KeyboardTaskType state, std::string key, int minTsDelay, int maxTsDelay ) :
    _state( state ),
    _key( key ),
    _minTsDelay( minTsDelay ),
    _maxTsDelay( maxTsDelay )
{
}

void KeyboardTask::execute( BotInfo *info )
{
    if( (int) _state > 3 )
    {
        if( _state == KeyboardTaskType::MoveCamera )
            moveCamera( _minTsDelay, _maxTsDelay );
    }
    else
        KeyboardController::kc.press( (KeyboardState) _state, _key, _minTsDelay, _maxTsDelay );
}

void KeyboardTask::moveCamera( int minTime, int maxTime )
{
    int keyboardType = Util::genRand( 1, 5 );

    if( keyboardType == 1 )
        KeyboardController::kc.press( KeyboardState::Down, "Right" );
    else if( keyboardType == 2 )
        KeyboardController::kc.press( KeyboardState::Down, "Left" );

    if( Util::genRand( 1, 10 ) <= 7 )
        KeyboardController::kc.press( KeyboardState::Down, "Up" );

    Sleeper::msleep( Util::genRand( 25, 75 ) );
    if( Util::genRand( 1, 17 ) < 8 )
    {
        KeyboardController::kc.press( KeyboardState::Up, "Right" );
        KeyboardController::kc.press( KeyboardState::Up, "Left" );
        KeyboardController::kc.press( KeyboardState::Up, "Up" );
        return;
    }

    Sleeper::msleep( Util::genRand( minTime, maxTime ) );

    KeyboardController::kc.press( KeyboardState::Up, "Right" );
    KeyboardController::kc.press( KeyboardState::Up, "Left" );
    KeyboardController::kc.press( KeyboardState::Up, "Up" );
}
