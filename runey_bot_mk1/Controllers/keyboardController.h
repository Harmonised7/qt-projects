#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#define SCREEN 0
#define TSDELAY_MIN 35000
#define TSDELAY_MAX 75000

#include <QDebug>

//Util Includes
#include "Util/sleeper.h"
#include "Util/util.h"

enum class KeyboardState
{
    Press = 0,
    Up = 1,
    Down = 2,
    Write = 3
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
