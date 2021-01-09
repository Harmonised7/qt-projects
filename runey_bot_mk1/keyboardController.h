#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#define SCREEN 0
#define TSDELAY 50

#include <QDebug>

class KeyboardController
{
public:
    KeyboardController( int screen );

    void pressKey( std::string key );
    void pressKeyDown( std::string key );
    void pressKeyUp( std::string key );

    void write( std::string word );

    static KeyboardController kc;

private:
    int _screen;
};

#endif // KEYBOARDCONTROLLER_H
