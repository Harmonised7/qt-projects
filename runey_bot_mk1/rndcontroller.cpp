#include "rndcontroller.h"

int RndController::genRand( int min, int max )
{
    if( min == max )
        return min;
    else if( max > min )
        return QRandomGenerator::global()->bounded( min, max + 1 );
    else
        return QRandomGenerator::global()->bounded( max, min + 1 );
}

double RndController::genRandDouble( double min, double max )
{
    if( min == max )
        return min;
    else if( max > min )
        return min + QRandomGenerator::global()->bounded( max - min + 1 );
    else
        return max + QRandomGenerator::global()->bounded( min - max + 1 );
}

QPoint RndController::genRandPoint( cv::Rect area )
{
    return QPoint( genRand( area.tl().x, area.tl().y ), genRand( area.br().x, area.br().y ) );
}

QPoint RndController::genRandPoint( QPoint p1, QPoint p2 )
{
    return QPoint( genRand( p1.x(), p1.y() ), genRand( p2.x(), p2.y() ) );
}
