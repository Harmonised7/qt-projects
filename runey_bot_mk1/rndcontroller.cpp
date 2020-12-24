#include "rndcontroller.h"

RndController::RndController()
{
    _time = QTime::currentTime();
    qsrand(static_cast<uint>(_time.msec()));

    qDebug() << "Initialized Random Controller...";
}

int RndController::generateRandom(int min, int max)
{
    changeRandSeed();

    if (max > min)
        return static_cast<int>( _rGer.bounded(min, max) );
    else
        return static_cast<int>( _rGer.bounded(max, min) );
}

double RndController::generateRandomDouble(double min, double max)
{
    changeRandSeed();

    if (max > min)
        return static_cast<double>( _rGer.bounded(max - min) + min );
    else
        return static_cast<double>( _rGer.bounded(min - max) + max );
}

void RndController::changeRandSeed()
{
    _rGer.seed(static_cast<uint>(_time.msec()) + 10);
}
