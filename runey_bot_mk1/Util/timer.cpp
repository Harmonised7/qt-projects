#include "timer.h"

Timer::Timer() :
    _startTime( QDateTime::currentMSecsSinceEpoch() )
{
}

void Timer::start()
{
    _startTime = QDateTime::currentMSecsSinceEpoch();
    _running = true;
}

void Timer::pause()
{
    if( _running )
    {
        _elapsed += QDateTime::currentMSecsSinceEpoch() - _startTime;
        _running = false;
    }
}

void Timer::stop()
{
    _elapsed = 0;
    _running = false;
}

void Timer::restart()
{
    _elapsed = 0;
    start();
}

unsigned long Timer::elapsed()
{
    return _elapsed + ( _running ? QDateTime::currentMSecsSinceEpoch() - _startTime : 0 );
}
