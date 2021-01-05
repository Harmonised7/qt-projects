#ifndef RNDCONTROLLER_H
#define RNDCONTROLLER_H

// Qt Native Includes //
#include <QRandomGenerator>
#include <qglobal.h>
#include <QDebug>
#include <QTime>
#include <QPoint>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

class RndController
{
public:
    void changeRandSeed();

    static int genRand( int bound1, int bound2 = 0 );
    static double genRandDouble( double bound1, double bound2 = 0 );
    static QPoint genRandPoint( cv::Rect area );
    static QPoint genRandPoint( QPoint p1, QPoint p2 );
};

#endif // RNDCONTROLLER_H
