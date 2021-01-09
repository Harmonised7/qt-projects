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

    qDebug() << "Initialized Keyboard Controller...";
}

void KeyboardController::pressKey( std::string key )
{
    xdo_send_keysequence_window( xDoTool, 0, key.c_str(), TSDELAY );
}

void KeyboardController::pressKeyUp( std::string key )
{
    xdo_send_keysequence_window_up( xDoTool, 0, key.c_str(), TSDELAY );
}

void KeyboardController::pressKeyDown( std::string key )
{
    xdo_send_keysequence_window_down( xDoTool, 0, key.c_str(), TSDELAY );
}

void KeyboardController::write( std::string word )
{
xdo_send_keysequence_window( xDoTool, 0, word.c_str(), TSDELAY );
}
