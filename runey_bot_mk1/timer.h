#ifndef TIMER_H
#define TIMER_H

#include <QDateTime>

class Timer
{
public:
    Timer();

    void start();
    void pause();
    void stop();
    void restart();
    unsigned long elapsed();

private:
    bool _running = false;
    unsigned long _startTime, _elapsed = 0;
};

#endif // TIMER_H
