#ifndef UTIL_H
#define UTIL_H

#define INV_X 558
#define INV_Y 211

#define INV_SLOT_X 42
#define INV_SLOT_Y 36

#define INV_SLOT_SHRINK 6

#include <QPoint>

//Qt Stuff
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <qmath.h>
#include <QRandomGenerator>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

class Util
{
public:
    Util();

    //Method Declarations
    static QPoint getMidPoint( cv::Rect area );
    static QPoint getMidPoint( QPoint p1, QPoint p2 );
    static int makeAbsolute( int value );
    static QPixmap matToPixmap(const cv::Mat &openCVMat);
    static cv::Mat pixMapToMat(const QPixmap &QtPixmap);
    static QImage pixmapToQImage(const QPixmap &QtPixmap);
    static cv::Point QPointToPoint( QPoint point );
    static double map(const double &x, const double &in_min, const double &in_max, const double &out_min, const double &out_max);
    static double mapCapped(const double &x, const double &in_min, const double &in_max, const double &out_min, const double &out_max);
    static double cap( const double &x, const double &min_bound, const double &max_bound );
    static cv::Rect getInvSlotRect( int index );
    static int getInvSlotIndex( const cv::Rect &rect );
    static int getInvSlotIndex( const QPoint &point );
    static double getDistance( QPoint &p1, QPoint &p2 );
    static double getDistance( cv::Point &p1, cv::Point &p2 );
    static int genRand( int bound1, int bound2 = 0 );
    static double genRandDouble( double bound1, double bound2 = 0 );
    static QPoint genRandPoint( cv::Rect area );
    static QPoint genRandPoint( cv::Mat mat );
//    static QPoint genRandPointOfColor( cv::Mat mat, cv::Vec3b color, int attempts = 10000 );
    static QPoint genRandPoint( QPoint p1, QPoint p2 );
};

#endif // UTIL_H
