#ifndef RNDCONTROLLER_H
#define RNDCONTROLLER_H

// Qt Native Includes //
#include <QRandomGenerator>
#include <qglobal.h>
#include <QDebug>
#include <QTime>

class RndController
{
public:
    RndController();

    void changeRandSeed();

    int generateRandom( int bound1, int bound2 = 0 );
    double generateRandomDouble( double bound1, double bound2 = 0 );

private:
    QTime _time;
    QRandomGenerator _rGer;
};

#endif // RNDCONTROLLER_H
