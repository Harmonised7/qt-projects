#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#define SCREEN 0
#define TSDELAY_MIN 10000
#define TSDELAY_MAX 20000

#include <QDebug>
#include "sleeper.h"
#include "util.h"

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
    KeyboardController( int screen );

    void press( KeyboardState state, std::string key, int minTsDelay = TSDELAY_MIN, int maxTsDelay = TSDELAY_MAX );

    static KeyboardController kc;
    QMap<char, std::string> specialChars;

private:
    int _screen;
};

#endif // KEYBOARDCONTROLLER_H
