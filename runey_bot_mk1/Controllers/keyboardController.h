#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#define SCREEN 0
#define TSDELAY_MIN 10000
#define TSDELAY_MAX 20000

#include <QDebug>

//Util Includes
#include "Util/sleeper.h"
#include "Util/util.h"

enum class KeyboardState
{
    Press,
    Up,
    Down,
    Write
};

class KeyboardController
{
public:
    void press( KeyboardState state, std::string key, int minTsDelay = TSDELAY_MIN, int maxTsDelay = TSDELAY_MAX );

    static KeyboardController kc;
    QMap<char, std::string> specialChars;

private:
    KeyboardController( int screen );

    int _screen;
};

#endif // KEYBOARDCONTROLLER_H
