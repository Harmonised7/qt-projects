#include "keyboardController.h"

extern "C"
{
#include "xdo.h"
}

KeyboardController KeyboardController::kc = KeyboardController( SCREEN );
static xdo_t *xDoTool;

KeyboardController::KeyboardController( int screen ) :
    _screen( screen )
{
    xDoTool = xdo_new(nullptr);

    specialChars.insert( '.', "period" );
    specialChars.insert( '@', "at" );

    qDebug() << "Initialized Keyboard Controller...";
}

void KeyboardController::press( KeyboardStates state, std::string key, int minTsDelay, int maxTsDelay )
{
    qDebug() << QString::fromStdString( key );
    if( state == KeyboardStates::Press )
        xdo_send_keysequence_window( xDoTool, 0, key.c_str(), Util::genRand( minTsDelay, maxTsDelay ) );
    else if( state == KeyboardStates::Down )
        xdo_send_keysequence_window_down( xDoTool, 0, key.c_str(), Util::genRand( minTsDelay, maxTsDelay ) );
    else if( state == KeyboardStates::Up )
        xdo_send_keysequence_window_up( xDoTool, 0, key.c_str(), Util::genRand( minTsDelay, maxTsDelay ) );
    else if( state == KeyboardStates::Write )
    {
        for( unsigned long i = 0; i < key.size(); i++ )
        {
            if( specialChars.contains( key[i] ) )
                xdo_send_keysequence_window( xDoTool, 0, specialChars.value( key[i] ).c_str(), Util::genRand( minTsDelay, maxTsDelay ) );
            else
            {
                char c[1];
                c[0] = key[i];
                xdo_send_keysequence_window( xDoTool, 0, c, Util::genRand( minTsDelay, maxTsDelay ) );
            }
        }
    }
}
